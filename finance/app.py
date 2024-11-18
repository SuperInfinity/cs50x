import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, jsonify
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user = session["user_id"]
    user_data = db.execute("select * from users where id = ?", user)

    data = db.execute("""select sum(quantity) as quantity, sum(ttl_value) as ttl_value, stock_symbol from purchase where username = ?
                          group by stock_symbol order by stock_symbol""", user_data[0]["username"])

    curr = db.execute("select * from curr_holdings order by stock_symbol")

    rm_cash = round(user_data[0]['cash'], 2)

    ext_data = []
    gnd_ttl = rm_cash

    if not curr or len(curr) < 1:
        return render_template("Nos.html", cash=rm_cash)
    for i in range(len(data)):
        d = {}
        d['stock_symbol'] = data[i]['stock_symbol']
        d['quantity'] = curr[i]['quantity']
        d['curr_price'] = lookup(d['stock_symbol'])['price']
        d['ttl_value'] = d['quantity'] * d['curr_price']

        ext_data.append(d)
        gnd_ttl += int(d['ttl_value'])

    return render_template("index.html", data=ext_data, cash=usd(rm_cash), grand_ttl=usd(gnd_ttl))


@app.route("/see")
@login_required
def see():
    """Show portfolio of stocks"""
    q = request.args.get("q")
    data = lookup(q)
    if not data:
        data = {}
    print("------->>>", data)
    print("-------------->>>", jsonify([data]))
    return jsonify([data])


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol or not symbol.isalpha():
            return apology("Invaild Symbol!", 400)
        if not shares or not shares.isnumeric() or not shares.isdigit() or int(shares) < 1:
            return apology("Invaild Number of shares", 400)

        data = lookup(symbol)
        if not data:
            return apology("Invaild Number of shares", 400)
        user = session["user_id"]
        req_money = int(shares) * round(data["price"])

        row = db.execute("select * from users where id = ?", user)

        if row[0]["cash"] >= req_money:
            db.execute("update users set cash=? where id=?", (row[0]["cash"] - req_money), user)
            db.execute("""insert into purchase (username, stock_symbol, bought_single_at_price, quantity, ttl_value, date_time)
                    values(?, ?, ?, ?, ?, (select(datetime())))""", row[0]["username"], data["symbol"], data["price"], int(shares), req_money)
            curr = db.execute(
                "select * from curr_holdings where username = ? and stock_symbol = ?", row[0]['username'], data['symbol'])
            if len(curr) != 1:
                db.execute("insert into curr_holdings (username, stock_symbol, quantity) values(?, ?, ?)",
                           row[0]['username'], data['symbol'], shares)
            else:
                db.execute("update curr_holdings set quantity = quantity + ? where id = ?",
                           shares, curr[0]['id'])
            return redirect("/")
        else:
            return apology("Not Enough Money", 403)

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    user_data = db.execute("select * from users")
    user_history = {}
    for i in user_data:
        purchases = db.execute("select * from purchase where username = ?", i['username'])
        sells = db.execute("select * from sells where username = ?", i['username'])
        user_history[i['username']] = {"purchases": purchases, "sells": sells}

    return render_template("history.html", data=user_history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if symbol and symbol.isalpha():
            data = lookup(symbol)
            if not data:
                return apology("Enter valid stock!", 400)
            return render_template("quoted.html", data=data)
        else:
            return apology("Enter valid stock!", 400)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # apologze if invalid inputs!
        if not username:
            return apology("must provide username", 400)
        if not password:
            return apology("must provide password", 400)
        if password != confirmation:
            return apology("must provide password", 400)

        try:
            db.execute("insert into users(username, hash) values(?, ?)",
                       username, generate_password_hash(password))
        except ValueError:
            return apology("Username already exists", 400)

        return redirect("/login")

    else:
        return render_template("register.html")


@app.route("/changep", methods=["GET", "POST"])
def changep():
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # apologze if invalid inputs!
        if not username:
            return apology("must provide username", 403)
        if not password:
            return apology("must provide password", 403)
        if password != confirmation:
            return apology("must provide password", 403)

        try:
            db.execute("update users set hash = ? where username = ?",
                       generate_password_hash(password), username)
        except Exception:
            return apology("Coldn't do it", 403)

        return redirect("/login")

    else:
        return render_template("changep.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        shares = int(request.form.get("shares"))

        user = session["user_id"]
        user_data = db.execute("select * from users where id = ?", user)

        data = db.execute("select sum(quantity) as quantity, stock_symbol from purchase where username = ? and stock_symbol = ?",
                          user_data[0]["username"], symbol)

        curr = db.execute(
            "select * from curr_holdings where username = ? and stock_symbol = ?", user_data[0]['username'], symbol)

        if len(curr) == 1 and curr[0]['quantity'] >= shares:
            stock = lookup(symbol)
            money_made = shares * stock['price']
            if (curr[0]['quantity'] - shares) == 0:
                db.execute("delete from curr_holdings where id = ?", curr[0]['id'])
            else:
                db.execute("update curr_holdings set quantity = ? where id = ?",
                           (curr[0]['quantity'] - shares), curr[0]['id'])
            db.execute("update users set cash = cash + ? where id = ?", money_made, user)
            db.execute("""insert into sells (username, stock_symbol, sold_at, quantity, ttl_value, date_time)
                    values(?, ?, ?, ?, ?, (select(datetime())))""", user_data[0]["username"], symbol, stock["price"], int(shares), money_made)

            return redirect("/")
        else:
            return apology("Not Enough Stocks!", 400)

    else:
        user = session["user_id"]
        user_data = db.execute("select * from users where id = ?", user)
        curr = db.execute(
            "select distinct(stock_symbol) from curr_holdings where username = ?", user_data[0]['username'])

        stocks = []
        if curr and len(curr) > 0:
            for i in curr:
                stocks.append(i["stock_symbol"])
        else:
            apology("No Stocks to sell", 400)

        return render_template("sell.html", stocks=stocks)
