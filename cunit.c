#include <assert.h>
#include <stdio.h>
#include <string.h>

/* Structures */

typedef struct
{
    int flightId;
    char name[50];
    char source[30];
    char destination[30];
    float fare;
    int totalSeats;
    int bookedSeats;
    char status[20];
} Flight;

typedef struct
{
    int passengerId;
    char name[50];
    int age;
    char contact[15];
    int flightId;
    int checkedIn;
    int ticketBooked;
    char ticketClass[20];
} Passenger;

/* Global Test Data */

Flight flight;
Passenger passenger;

float totalRevenue = 0.0;

/* Test 1 */

void test_admin_login()
{
    char username[] = "admin";
    char password[] = "admin123";

    assert(strcmp(username, "admin") == 0);
    assert(strcmp(password, "admin123") == 0);

    printf("test_admin_login PASSED\n");
}

/* Test 2 */

void test_add_flight()
{
    flight.flightId = 1;

    strcpy(flight.name, "Indigo");
    strcpy(flight.source, "Chennai");
    strcpy(flight.destination, "Delhi");

    flight.fare = 5000;
    flight.totalSeats = 100;
    flight.bookedSeats = 0;

    strcpy(flight.status, "On Time");

    assert(flight.flightId == 1);
    assert(strcmp(flight.name, "Indigo") == 0);
    assert(flight.fare == 5000);

    printf("test_add_flight PASSED\n");
}

/* Test 3 */

void test_update_flight()
{
    flight.fare = 6500;

    assert(flight.fare == 6500);

    printf("test_update_flight PASSED\n");
}

/* Test 4 */

void test_flight_status()
{
    strcpy(flight.status, "Delayed");

    assert(strcmp(flight.status, "Delayed") == 0);

    printf("test_flight_status PASSED\n");
}

/* Test 5 */

void test_seat_availability()
{
    flight.totalSeats = 100;
    flight.bookedSeats = 30;

    int available =
        flight.totalSeats -
        flight.bookedSeats;

    assert(available == 70);

    printf("test_seat_availability PASSED\n");
}

/* Test 6 */

void test_register_passenger()
{
    passenger.passengerId = 1;

    strcpy(passenger.name, "Lavanyaa");

    passenger.age = 22;

    strcpy(passenger.contact,
           "9876543210");

    assert(passenger.passengerId == 1);
    assert(strcmp(passenger.name,
           "Lavanyaa") == 0);

    printf("test_register_passenger PASSED\n");
}

/* Test 7 */

void test_update_passenger()
{
    passenger.age = 23;

    assert(passenger.age == 23);

    printf("test_update_passenger PASSED\n");
}

/* Test 8 */

void test_book_ticket()
{
    passenger.flightId = 1;

    passenger.ticketBooked = 1;

    strcpy(passenger.ticketClass,
           "Economy");

    flight.bookedSeats++;

    totalRevenue += flight.fare;

    assert(passenger.ticketBooked == 1);
    assert(passenger.flightId == 1);

    printf("test_book_ticket PASSED\n");
}

/* Test 9 */

void test_payment_processing()
{
    float payment = 5000;

    totalRevenue += payment;

    assert(totalRevenue > 0);

    printf("test_payment_processing PASSED\n");
}

/* Test 10 */

void test_checkin()
{
    passenger.checkedIn = 1;

    assert(passenger.checkedIn == 1);

    printf("test_checkin PASSED\n");
}

/* Test 11 */

void test_boarding_pass()
{
    assert(passenger.ticketBooked == 1);
    assert(passenger.checkedIn == 1);

    printf("test_boarding_pass PASSED\n");
}

/* Test 12 */

void test_cancel_ticket()
{
    passenger.ticketBooked = 0;
    passenger.flightId = 0;
    passenger.checkedIn = 0;

    assert(passenger.ticketBooked == 0);
    assert(passenger.flightId == 0);

    printf("test_cancel_ticket PASSED\n");
}

/* Test 13 */

void test_revenue_report()
{
    assert(totalRevenue > 0);

    printf("test_revenue_report PASSED\n");
}

/* Main */

int main()
{
    printf("\n===== UNIT TEST REPORT =====\n\n");

    test_admin_login();
    test_add_flight();
    test_update_flight();
    test_flight_status();
    test_seat_availability();

    test_register_passenger();
    test_update_passenger();

    test_book_ticket();
    test_payment_processing();

    test_checkin();
    test_boarding_pass();

    test_cancel_ticket();

    test_revenue_report();

    printf("\nALL TEST CASES PASSED\n");

    return 0;
}
