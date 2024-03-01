-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Firstly lets look at the crime scene report:

SELECT * FROM crime_scene_reports LIMIT 10;

-- But we know that the theft took place at 28 July 2023 and on Humphery Street,
-- So now let's look at the data after 28th July.

SELECT * FROM crime_scene_reports WHERE day > 27 LIMIT 50;

-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted ,with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.
-- Now we look at the interviews..

SELECT * FROM interviews WHERE day > 27;

-- 1. After lookin at the interviews.., here.. we get a lot of hints.., first.. Ruth - within 10 min. of the theft the thief got into a car in the backery parking lot
-- 2. Eugene (Before he arrv. at Emma's backery)- thief was at ATM on Leggett Street.. withdrawing some money..!
-- 3. Raymond - as the thief was leaving the backery.. they called someone.. spoke for less than a min. they were planning to take flight tomorrow. the earliest possible.., and to buy a ticket
-- 4. Also table "People" links name, phone-number, passportnumber, licence plate

-- 1. So, for the backery security logs..we run the query

SELECT * FROM bakery_security_logs WHERE day = 28 AND hour = 10 AND minute > 15 AND minute < 40;

-- Here we got Lincence plates..
-- getting the name of the people..

SELECT * FROM people WHERE license_plate IN
(SELECT license_plate FROM bakery_security_logs WHERE day = 28 AND hour = 10 AND minute > 15 AND minute < 25);

-- CURRENT SUSPECTS:
-- Vanessa  | (725) 555-4692 | 2963008352      | 5P2BI95
-- Barry   | (301) 555-4174 | 7526138472      | 6P58WS2
-- Iman    | (829) 555-5269 | 7049073643      | L93JTIZ
-- Sofia   | (130) 555-0289 | 1695452385      | G412CB7
-- Luca    | (389) 555-5198 | 8496433585      | 4328GD8
-- Diana   | (770) 555-1861 | 3592750733      | 322W7JE
-- Kelsey  | (499) 555-9472 | 8294398571      | 0NTHK55
-- Bruce   | (367) 555-5533 | 5773159633      | 94KL13X

-- Now checking ATM:
-- And also checking bankaccounts from that days' transactions.. And cross verifying with people table..
--  Kenny   | (826) 555-1652 | 9878712108      | 30G67EN
--  Iman    | (829) 555-5269 | 7049073643      | L93JTIZ
--  Benista | (338) 555-6650 | 9586786673      | 8X428L0
--  Taylor  | (286) 555-6063 | 1988161715      | 1106N58
--  Brooke  | (122) 555-4581 | 4408372428      | QX4YZN3
--  Luca    | (389) 555-5198 | 8496433585      | 4328GD8
--  Diana   | (770) 555-1861 | 3592750733      | 322W7JE
--  Bruce   | (367) 555-5533 | 5773159633      | 94KL13X
--  Kaelyn  | (098) 555-1164 | 8304650265      | I449449

-- Okay now.. checking the people that were at the bakery and left the bakery after theft and at the ATM too..

SELECT name FROM people WHERE license_plate IN
(SELECT license_plate FROM bakery_security_logs WHERE day = 28 AND hour = 10 AND minute > 15 AND minute < 25)
AND name IN
(SELECT name FROM people WHERE id IN
(SELECT person_id FROM bank_accounts WHERE account_number IN
(SELECT account_number FROM atm_transactions WHERE day = 28 AND atm_location = 'Leggett Street')));

-- We get.. Iman, Luca, Diana, Bruce

-- Now need to create a new table of suspects who were at both ATM and the bakery..!!!
-- and then maybe look at tickets booked and passengers and cities...!!!

SELECT * FROM flights WHERE day > 27 AND day < 30 ORDER BY day, hour;

-- This gives us... FLIGHT ID - 36, ORIGIN - 8, DESTINAION- 4, TIME - 8:20
-- So looking at the passengers at that flight..

SELECT * FROM suspects
WHERE passport_number IN
    (SELECT passport_number FROM passengers WHERE flight_id = 36);

-- We get luca, bruce
-- Now also checking the calls at 28th...

SELECT * FROM suspects WHERE phone_number IN
    (SELECT caller FROM phone_calls WHERE caller IN
        (SELECT phone_number FROM people WHERE license_plate IN
(SELECT license_plate FROM bakery_security_logs WHERE day = 28 AND hour = 10 AND minute > 15 AND minute < 40)
AND name IN
(SELECT name FROM people WHERE id IN
(SELECT person_id FROM bank_accounts WHERE account_number IN
(SELECT account_number FROM atm_transactions WHERE day = 28 AND atm_location = 'Leggett Street')))
) AND day = 28 AND duration < 60);

-- We have Diana, Bruce
-- Well, we have our Culprit.. MR. Bruce..
-- Now, checking for the Accomplice..

SELECT name FROM people WHERE phone_number IN
(SELECT receiver FROM phone_calls WHERE caller =
(SELECT phone_number FROM suspects WHERE name = 'Bruce') AND duration < 60 AND day = 28);
-- This gives us MR. Robin

-- Now where did they escape to..?

SELECT * FROM airports WHERE id IN
(SELECT destination_airport_id FROM flights WHERE id = 36);

-- New York City
