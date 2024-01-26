

/* https://cs50.harvard.edu/x/2023/psets/7/fiftyville/
Authorities believe that the thief stole the duck and then, shortly afterwards, took a flight out of town with the help of an accomplice. Your goal is to identify:

Who the thief is,
What city the thief escaped to, and
Who the thief’s accomplice is who helped them escape
All you know is that the theft took place on July 28, 2021 and that it took place on Humphrey Street.
*/
-- Keep a log of any SQL queries you execute as you solve the mystery.

.schema
/*
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


--Based on Initial Clue of theft date and location
SELECT description FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28 AND street = "Humphrey Street";

/*
description                                                                                                        |
Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.
Littering took place at 16:36. No known witnesses.
*/

--Get the witness interviews transcripts from "today" July 28, 2021, that mention the bakery (regex on bakery)
SELECT transcript FROM interviews WHERE year = 2021 AND month = 7 AND day = 28 AND transcript LIKE "%bakery%";

/*transcript
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



-- find the id and name of the airport at Fifty Ville
SELECT id, full_name FROM airports WHERE full_name LIKE "%fiftyville%";
/*
+----+-----------------------------+
| id |          full_name          |
+----+-----------------------------+
| 8  | Fiftyville Regional Airport |
+----+-----------------------------+
*/

--find all flights out of FiftyVille on 29 Jul and get the earliest one
SELECT id,hour,minute, destination_airport_id FROM flights WHERE origin_airport_id = 8 AND year = 2021 AND month = 7 AND day = 29 ORDER BY hour,minute;
/*
+----+------+--------+------------------------+
| id | hour | minute | destination_airport_id |
+----+------+--------+------------------------+
| 36 | 8    | 20     | 4                      |
| 43 | 9    | 30     | 1                      |
| 23 | 12   | 15     | 11                     |
| 53 | 15   | 20     | 9                      |
| 18 | 16   | 0      | 6                      |
+----+------+--------+------------------------+
*/

-- find name of airport 4
SELECT id, full_name,city FROM airports WHERE id=4;
/*
+----+-------------------+---------------+
| id |     full_name     |     city      |
+----+-------------------+---------------+
| 4  | LaGuardia Airport | New York City |
+----+-------------------+---------------+
the cuplrit escaped to new york city
*/

--find all passengers on earliest flight 36
SELECT name from people WHERE passport_number IN(
SELECT passport_number FROM passengers WHERE flight_id IN (
SELECT id FROM flights WHERE id = 36));

/*
+--------+
|  name  |
+--------+
| Kenny  |
| Sofia  |
| Taylor |
| Luca   |
| Kelsey |
| Edward |
| Bruce  |
| Doris  |
+--------+
*/

--find commmon names among all 3 clues


SELECT people.name FROM bakery_security_logs JOIN people ON bakery_security_logs.license_plate = people.license_plate
WHERE bakery_security_logs.year = 2021 AND bakery_security_logs.month = 7 AND bakery_security_logs.day = 28
AND bakery_security_logs.hour = 10

INTERSECT

SELECT name from people WHERE passport_number IN(
SELECT passport_number FROM passengers WHERE flight_id IN (
SELECT id FROM flights WHERE id = 36))

INTERSECT

SELECT name FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE transaction_type = 'withdraw' AND atm_location LIKE '%Leggett%' AND year = 2021 AND month = 7 AND day = 28))

/*
+--------+
|  name  |
+--------+
| Bruce  |
| Luca   |
| Taylor |
+--------+
*/

--Find people who made phone calls on 28 July
SELECT people.name,phone_calls.duration, people.phone_number FROM people JOIN phone_calls ON people.phone_number = phone_calls.caller
WHERE phone_calls.year = 2021 AND phone_calls.month = 7 AND phone_calls.day = 28 ORDER BY phone_calls.duration;
/*
+-----------+----------+----------------+
|   name    | duration |  phone_number  |
+-----------+----------+----------------+
| Kelsey    | 36       | (499) 555-9472 |
| Carina    | 38       | (031) 555-6622 |
| Taylor    | 43       | (286) 555-6063 |
| Bruce     | 45       | (367) 555-5533 |
| Diana     | 49       | (770) 555-1861 |
| Kelsey    | 50       | (499) 555-9472 |
| Sofia     | 51       | (130) 555-0289 |
| Benista   | 54       | (338) 555-6650 |
| Kenny     | 55       | (826) 555-1652 |
| Kathryn   | 60       | (609) 555-5876 |
| Peter     | 61       | (751) 555-6567 |
| Harold    | 67       | (669) 555-6918 |
| Jason     | 69       | (636) 555-4198 |
| Bruce     | 75       | (367) 555-5533 |
| John      | 88       | (016) 555-9166 |
| Terry     | 101      | (730) 555-5115 |
| Anna      | 103      | (704) 555-2131 |
| Mark      | 109      | (873) 555-3868 |
| Arthur    | 111      | (394) 555-3247 |
| Betty     | 113      | (233) 555-0473 |
| Sean      | 116      | (867) 555-9103 |
| Bruce     | 120      | (367) 555-5533 |
| Logan     | 121      | (219) 555-0139 |
| Jack      | 142      | (996) 555-8899 |
| Judy      | 146      | (918) 555-5327 |
| Alexander | 148      | (801) 555-9266 |
| Daniel    | 149      | (971) 555-6468 |
| James     | 153      | (676) 555-6554 |
| Joan      | 157      | (711) 555-3007 |
| Nathan    | 195      | (293) 555-1469 |
| Carl      | 200      | (704) 555-5790 |
| Harold    | 233      | (669) 555-6918 |
| Taylor    | 235      | (286) 555-6063 |
| Brittany  | 237      | (398) 555-1013 |
| Douglas   | 241      | (491) 555-2505 |
| Bruce     | 241      | (367) 555-5533 |
| Christina | 272      | (547) 555-8781 |
| Zachary   | 278      | (839) 555-1757 |
| Christine | 280      | (608) 555-9302 |
| Ralph     | 288      | (771) 555-7880 |
| Cheryl    | 298      | (450) 555-8297 |
| Paul      | 305      | (357) 555-0246 |
| Rose      | 318      | (336) 555-0077 |
| Jose      | 320      | (914) 555-5994 |
| Eugene    | 326      | (666) 555-5774 |
| William   | 328      | (324) 555-0416 |
| Ethan     | 346      | (594) 555-6254 |
| Joan      | 358      | (711) 555-3007 |
| Kristina  | 359      | (918) 555-2946 |
| Patricia  | 361      | (594) 555-2863 |
| Olivia    | 368      | (258) 555-5627 |
| Margaret  | 371      | (068) 555-0183 |
| Dorothy   | 379      | (047) 555-0577 |
| Jean      | 383      | (695) 555-0348 |
| Virginia  | 398      | (478) 555-1565 |
| Beverly   | 404      | (342) 555-9260 |
| Andrew    | 421      | (579) 555-5030 |
| Alexander | 425      | (801) 555-9266 |
| Daniel    | 441      | (971) 555-6468 |
| Ryan      | 451      | (901) 555-8732 |
| Vanessa   | 456      | (725) 555-4692 |
| Keith     | 487      | (209) 555-7806 |
| Brooke    | 491      | (122) 555-4581 |
| Billy     | 510      | (060) 555-2489 |
| Logan     | 514      | (219) 555-0139 |
| Bryan     | 525      | (696) 555-9195 |
| Ashley    | 527      | (770) 555-1196 |
| Randy     | 546      | (984) 555-5921 |
| Dylan     | 550      | (380) 555-4380 |
| Beverly   | 560      | (342) 555-9260 |
| Teresa    | 565      | (041) 555-4011 |
| Virginia  | 573      | (478) 555-1565 |
| Carolyn   | 573      | (234) 555-1294 |
| Louis     | 575      | (749) 555-4874 |
| Jordan    | 579      | (328) 555-9658 |
| Barry     | 583      | (301) 555-4174 |
| Walter    | 595      | (544) 555-8087 |
+-----------+----------+----------------+
*/
--Luca did not make any calls

/*
Hence Bruce is the culprit because he
- withdrew money on the morning of the crime
- drove out of the parket lot within 10min of the crime
- made a call of less than 60s on the day of the crime
- was on the first flight out the next day
*/

SELECT people.name,phone_calls.duration FROM people JOIN phone_calls ON people.phone_number = phone_calls.receiver
WHERE phone_calls.year = 2021 AND phone_calls.month = 7 AND phone_calls.day = 28 AND phone_calls.caller = '(367) 555-5533' ORDER BY phone_calls.duration;

/*
+---------+----------+
|  name   | duration |
+---------+----------+
| Robin   | 45       |
| Carl    | 75       |
| Deborah | 120      |
| Gregory | 241      |
+---------+----------+
Robin is the accomplice because he had the same 45sec call with Bruce*/