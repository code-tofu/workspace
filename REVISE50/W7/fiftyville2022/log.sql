/*
Authorities believe that the thief stole the duck and then, shortly afterwards, took a flight out of town with the help of an accomplice. Your goal is to identify:
Who the thief is,
What city the thief escaped to, and
Who the thief’s accomplice is who helped them escape
All you know is that the theft took place on July 28, 2021 and that it took place on Humphrey Street.
*/
-- Keep a log of any SQL queries you execute as you solve the mystery.

--Look at table schema
.schema

--Based on Initial Clue of theft date and location
SELECT description FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28 AND street = "Humphrey Street";

/*
Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.
Littering took place at 16:36. No known witnesses.
*/
--Get the witness interviews transcripts from TODAY, then mention the bakery (regex on bakery)
SELECT transcript FROM interviews WHERE year = 2021 AND month = 7 AND day = 28 AND transcript LIKE "%bakery%";

/*
Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.

I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.

As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.
*/

--Based on security footage of parking lot, within 10mins of theft i.e. before/after 10:15
SELECT bakery_security_logs.hour, bakery_security_logs.minute,bakery_security_logs.license_plate,people.name
FROM bakery_security_logs JOIN people ON bakery_security_logs.license_plate = people.license_plate
WHERE bakery_security_logs.year = 2021 AND bakery_security_logs.month = 7 AND bakery_security_logs.day = 28
AND bakery_security_logs.hour = 10 ORDER BY bakery_security_logs.minute;

/*
+------+--------+---------------+---------+
| hour | minute | license_plate |  name   |
+------+--------+---------------+---------+
| 10   | 8      | R3G7486       | Brandon |
| 10   | 14     | 13FNH73       | Sophia  |
| 10   | 16     | 5P2BI95       | Vanessa |
| 10   | 18     | 94KL13X       | Bruce   |
| 10   | 18     | 6P58WS2       | Barry   |
| 10   | 19     | 4328GD8       | Luca    |
| 10   | 20     | G412CB7       | Sofia   |
| 10   | 21     | L93JTIZ       | Iman    |
| 10   | 23     | 322W7JE       | Diana   |
| 10   | 23     | 0NTHK55       | Kelsey  |
| 10   | 35     | 1106N58       | Taylor  |
| 10   | 42     | NRYN856       | Denise  |
| 10   | 44     | WD5M8I6       | Thomas  |
| 10   | 55     | V47T75I       | Jeremy  |
+------+--------+---------------+---------+
*/

--Look for type of transactions in ATM transaction table: deposit/withdraw
SELECT DISTINCT transaction_type FROM atm_transactions;
--Based on ATM on Leggett Street, theif was at ATM before i.e. 10::15 at Leggett street
SELECT name FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE transaction_type = 'withdraw' AND atm_location LIKE '%Leggett%' AND year = 2021 AND month = 7 AND day = 28));
/*
+---------+
|  name   |
+---------+
| Kenny   |
| Iman    |
| Benista |
| Taylor  |
| Brooke  |
| Luca    |
| Diana   |
| Bruce   |
+---------+
*/
-- Common names are Bruce, Luca, Iman, Diana,




/*--TABLES SCHEMA:
CREATE TABLE crime_scene_reports (
    id INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    street TEXT,
    description TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE interviews (
    id INTEGER,
    name TEXT,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    transcript TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE atm_transactions (
    id INTEGER,
    account_number INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    atm_location TEXT,
    transaction_type TEXT,
    amount INTEGER,
    PRIMARY KEY(id)
);
CREATE TABLE bank_accounts (
    account_number INTEGER,
    person_id INTEGER,
    creation_year INTEGER,
    FOREIGN KEY(person_id) REFERENCES people(id)
);
CREATE TABLE airports (
    id INTEGER,
    abbreviation TEXT,
    full_name TEXT,
    city TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE flights (
    id INTEGER,
    origin_airport_id INTEGER,
    destination_airport_id INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    hour INTEGER,
    minute INTEGER,
    PRIMARY KEY(id),
    FOREIGN KEY(origin_airport_id) REFERENCES airports(id),
    FOREIGN KEY(destination_airport_id) REFERENCES airports(id)
);
CREATE TABLE passengers (
    flight_id INTEGER,
    passport_number INTEGER,
    seat TEXT,
    FOREIGN KEY(flight_id) REFERENCES flights(id)
);
CREATE TABLE phone_calls (
    id INTEGER,
    caller TEXT,
    receiver TEXT,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    duration INTEGER,
    PRIMARY KEY(id)
);
CREATE TABLE people (
    id INTEGER,
    name TEXT,
    phone_number TEXT,
    passport_number INTEGER,
    license_plate TEXT,
    PRIMARY KEY(id)
);
CREATE TABLE bakery_security_logs (
    id INTEGER,
    year INTEGER,
    month INTEGER,
    day INTEGER,
    hour INTEGER,
    minute INTEGER,
    activity TEXT,
    license_plate TEXT,
    PRIMARY KEY(id)
);
*/

