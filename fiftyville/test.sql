SELECT * FROM airports WHERE id IN
(SELECT destination_airport_id FROM flights WHERE id = 36);
