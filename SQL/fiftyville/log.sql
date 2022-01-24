-- Keep a log of any SQL queries you execute as you solve the mystery.

/* .schema;
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
CREATE TABLE courthouse_security_logs (
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
); */

/* SELECT * FROM crime_scene_reports 
WHERE day = 28
AND month = 07
SELECT * FROM passengers
WHERE flight_id = 36
AND YEAR = 2020
AND street = 'Chamberlin Street'; */

/* 295|2020|7|28|Chamberlin Street|Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse. Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse. */

/* SELECT * FROM interviews
WHERE day = 28
AND month = 07
AND YEAR = 2020
AND transcript LIKE '%courthouse%'; */

/* 161|Ruth|2020|7|28|Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
162|Eugene|2020|7|28|I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
163|Raymond|2020|7|28|As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. */

/* 161 */ 

/* SELECT name, phone_number, passport_number, people.license_plate FROM people
JOIN courthouse_security_logs ON 
courthouse_security_logs.license_plate = people.license_plate
WHERE day = 28
AND month = 07
AND YEAR = 2020
AND hour = 10
AND minute >= 15
AND minute <= 25; */

/* 221103|Patrick|(725) 555-4692|2963008352|5P2BI95
243696|Amber|(301) 555-4174|7526138472|6P58WS2
396669|Elizabeth|(829) 555-5269|7049073643|L93JTIZ
398010|Roger|(130) 555-0289|1695452385|G412CB7
467400|Danielle|(389) 555-5198|8496433585|4328GD8
514354|Russell|(770) 555-1861|3592750733|322W7JE
560886|Evelyn|(499) 555-9472|8294398571|0NTHK55
686048|Ernest|(367) 555-5533|5773159633|94KL13X */

/* 162 */

/* SELECT name, phSELECT name, phone_number, passport_number, people.license_plate FROM people
JOIN courthouse_security_logs c ON 
c.license_plate = people.license_plate
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions a ON a.account_number = bank_accounts.account_number
WHERE a.atm_location = 'Fifer Street'
AND a.transaction_type = 'withdraw'
AND a.day = 28
AND a.month = 07
AND a.YEAR = 2020
AND c.hour = 10
AND c.minute >= 15
AND c.minute <= 25one_number, passport_number, people.license_plate FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions a ON a.account_number = bank_accounts.account_number
WHERE a.atm_location = 'Fifer Street'
AND a.transaction_type = 'withdraw'
AND a.day = 28
AND a.month = 07
AND a.YEAR = 2020; */

/* Ernest|(367) 555-5533|5773159633|94KL13X
Russell|(770) 555-1861|3592750733|322W7JE
Roy|(122) 555-4581|4408372428|QX4YZN3
Bobby|(826) 555-1652|9878712108|30G67EN
Elizabeth|(829) 555-5269|7049073643|L93JTIZ
Danielle|(389) 555-5198|8496433585|4328GD8
Madison|(286) 555-6063|1988161715|1106N58
Victoria|(338) 555-6650|9586786673|8X428L0 */

/* 161 + 162 */

/* SELECT name, phone_number, passport_number, people.license_plate FROM people
JOIN courthouse_security_logs c ON 
c.license_plate = people.license_plate
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions a ON a.account_number = bank_accounts.account_number
WHERE a.atm_location = 'Fifer Street'
AND a.transaction_type = 'withdraw'
AND a.day = 28
AND a.month = 07
AND a.YEAR = 2020
AND c.hour = 10
AND c.minute >= 15
AND c.minute <= 25 */

/* Danielle|(389) 555-5198|8496433585|4328GD8
Elizabeth|(829) 555-5269|7049073643|L93JTIZ
Ernest|(367) 555-5533|5773159633|94KL13X
Russell|(770) 555-1861|3592750733|322W7JE */

/* 163 */

/* SELECT * FROM flights
WHERE day = 29
AND month = 07
AND YEAR = 2020
ORDER BY hour
LIMIT 1; */

/* 36|8|4|2020|7|29|8|20 */

/* Fligth ID = 36 */

/* SELECT city FROM airports ap
JOIN flights fli ON fli.destination_airport_id = ap.id
WHERE fli.day = 29
AND fli.month = 07
AND fli.year = 2020day = 28
AND month = 07
AND YEAR = 2020
AND hour = 10
AND minute >= 15
AND minute <= 25
AND fli.id = 36; */

/* DESTINATION = London */

/* SELECT name, phone_number FROM people
JOIN courthouse_security_logs c ON 
c.license_plate = people.license_plate
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions a ON a.account_number = bank_accounts.account_number
JOIN passengers p ON p.passport_number = people.passport_number
WHERE a.atm_location = 'Fifer Streetday = 28
AND month = 07
AND YEAR = 2020
AND hour = 10
AND minute >= 15
AND minute <= 25'
AND a.transaction_type = 'withdraw'
AND a.day = 28
AND a.month = 07
AND a.YEAR = 2020
AND c.hour = 10
AND c.minute >= 15
AND c.minute <= 25
AND p.flight_id = 36 */

/* Ernest|(367) 555-5533
Danielle|(389) 555-5198 */

/* SELECT * FROM phone_calls
WHERE caller in ('(367) 555-5533', '(389) 555-5198') 
AND day = 28
AND month = 07
AND YEAR = 2020
AND duration < 60; */

/* 233|(367) 555-5533|(375) 555-8161|2020|7|28|45 */

/* Thief: Ernest */

/* SELECT name FROM people
WHERE phone_number = '(375) 555-8161'; */

/*  ACCOMPLICE: Berthold */