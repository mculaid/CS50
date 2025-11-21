-- Keep a log of any SQL queries you execute as you solve the mystery.
--A duck was stolen On July 28th, 2024 On Humphrey Street
-- Thief had an accomplice, Thief took a flight out of town shortly after

-- look up database structure
.schema

--look up tables
.tables

--check crime scene reports structure
select * from crime_scene_reports;

--check day of incident
select * from crime_scene_reports WHERE year = 2024 AND month is 7 AND day is 28;

--check interviews for witness reports from that day
SELECT * FROM interviews WHERE year = 2024 AND month = 7 AND day = 28;

--find out who purchased a flight ticket for the earliest flight leaving on 29th
--cross-reference with people outgoing phone calls right after incident took place
--find parking lot security footage between 10:15 am - 10:25 am for plate number
--check ATM on Leggett Street in the morning

--find out how atm_transactions look like and who withdrew
select * from atm_transactions where year = 2024 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw';
SELECT name, flights.day, flights.id, flights.hour, flights.minute FROM people
JOIN phone_calls ON people.phone_number = phone_calls.caller
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON passengers.flight_id = flights.id
WHERE
phone_calls.year = 2024 AND phone_calls.month = 7 and phone_calls.day = 28
AND
atm_transactions.year = 2024 AND atm_transactions.month = 7 AND atm_transactions.day = 28 AND atm_transactions.atm_location = 'Leggett Street' AND atm_transactions.transaction_type = 'withdraw'
AND
flights.year = 2024 AND flights.month = 7 AND flights.day = 28;
--need some more
SELECT name, flights.day, flights.id, flights.hour, flights.minute, phone_calls.receiver FROM people
JOIN phone_calls ON people.phone_number = phone_calls.caller
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON passengers.flight_id = flights.id
WHERE
phone_calls.year = 2024 AND phone_calls.month = 7 and phone_calls.day = 28
AND
atm_transactions.year = 2024 AND atm_transactions.month = 7 AND atm_transactions.day = 28 AND atm_transactions.atm_location = 'Leggett Street' AND atm_transactions.transaction_type = 'withdraw'
AND
flights.year = 2024 AND flights.month = 7 AND flights.day = 28;
--Find who she Brooke called
select name FROM people where phone_number = '(831) 555-0973';
--this did it
SELECT name, flights.day, flights.id, flights.hour, flights.minute FROM people
JOIN phone_calls ON people.phone_number = phone_calls.caller
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON passengers.flight_id = flights.id
WHERE
phone_calls.year = 2024 AND phone_calls.month = 7 and phone_calls.day = 28
AND
atm_transactions.year = 2024 AND atm_transactions.month = 7 AND atm_transactions.day = 28 AND atm_transactions.atm_location = 'Leggett Street' AND atm_transactions.transaction_type = 'withdraw'
AND
flights.year = 2024 AND flights.month = 7 AND flights.day = 29 AND flights.hour = 8
AND
people.license_plate IN (select license_plate from bakery_security_logs WHERE year = 2024 AND month = 7 AND day = 28 AND hour = 10 AND (minute >= 15 AND minute <= 25) AND activity = 'exit')
AND
phone_calls.caller = people.phone_number
GROUP by name;
--check airport
SELECT name, flights.day, airports.city as Destination, flights.id, flights.hour, flights.minute FROM people
JOIN phone_calls ON people.phone_number = phone_calls.caller
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON passengers.flight_id = flights.id
JOIN airports ON airports.id = destination_airport_id
WHERE
phone_calls.year = 2024 AND phone_calls.month = 7 and phone_calls.day = 28
AND
atm_transactions.year = 2024 AND atm_transactions.month = 7 AND atm_transactions.day = 28 AND atm_transactions.atm_location = 'Leggett Street' AND atm_transactions.transaction_type = 'withdraw'
AND
flights.year = 2024 AND flights.month = 7 AND flights.day = 29 AND flights.hour = 8
AND
people.license_plate IN (select license_plate from bakery_security_logs WHERE year = 2024 AND month = 7 AND day = 28 AND hour = 10 AND (minute >= 15 AND minute <= 25) AND activity = 'exit')
AND
phone_calls.caller = people.phone_number
GROUP by name;
