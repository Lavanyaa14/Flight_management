#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_FLIGHTS 100
#define MAX_PASSENGERS 100
#define FLIGHT_FILE "flights.dat"
#define PASSENGER_FILE "passengers.dat"

typedef struct {
    int flightId;
    char name[50];
    char source[30];
    char destination[30];
    float fare;
    int totalSeats;
    int bookedSeats;
    char status[20];
} Flight;

typedef struct {
    int passengerId;
    char name[50];
    int age;
    char contact[15];
    int flightId;
    int checkedIn;
    int ticketBooked;
    char ticketClass[20];
} Passenger;

Flight flights[MAX_FLIGHTS];
int flightCount = 0;

Passenger passengers[MAX_PASSENGERS];
int passengerCount = 0;

/* Revenue Tracking */
float totalRevenue = 0.0;

/* ---------------- MODULE 1: Admin Login ---------------- */
int admin_login()
{
    char user[20], pass[20];
    printf("Username: ");
    scanf("%19s", user);
    printf("Password: ");
    scanf("%19s", pass);

    if (strcmp(user, "admin") == 0 && strcmp(pass, "admin123") == 0)
    {
        printf("Login successful.\n");
        return 1;
    }
    printf("Invalid credentials.\n");
    return 0;
}

/* ---------------- MODULE 2: Add Flight ---------------- */
void add_flight()
{
    if (flightCount >= MAX_FLIGHTS)
    {
        printf("Flight storage full.\n");
        return;
    }
    Flight f;
    f.flightId = flightCount + 1;
    printf("Enter Flight Name: ");
    scanf("%49s", f.name);
    printf("Enter Source: ");
    scanf("%29s", f.source);
    printf("Enter Destination: ");
    scanf("%29s", f.destination);
    printf("Enter Fare: ");
    scanf("%f", &f.fare);
    printf("Enter Total Seats: ");
    scanf("%d", &f.totalSeats);
    f.bookedSeats = 0;
    strcpy(f.status, "On Time");

    flights[flightCount++] = f;
    printf("Flight added successfully. Flight ID: %d\n", f.flightId);
}

/* ---------------- MODULE 3: View Flights ---------------- */
void view_flights()
{
    int i;
    if (flightCount == 0)
    {
        printf("No Flights Available.\n");
        return;
    }
    printf("%-5s %-15s %-12s %-12s %-8s %-6s %-10s\n",
           "ID", "Name", "Source", "Dest", "Fare", "Seats", "Status");
    for (i = 0; i < flightCount; i++)
    {
        printf("%-5d %-15s %-12s %-12s %-8.2f %d/%-4d %-10s\n",
               flights[i].flightId, flights[i].name, flights[i].source,
               flights[i].destination, flights[i].fare,
               flights[i].bookedSeats, flights[i].totalSeats, flights[i].status);
    }
}

/* ---------------- MODULE 4: Search Flight ---------------- */
void search_flight()
{
    char src[30], dest[30];
    int i, found = 0;
    printf("Enter Source: ");
    scanf("%29s", src);
    printf("Enter Destination: ");
    scanf("%29s", dest);

    for (i = 0; i < flightCount; i++)
    {
        if (strcmp(flights[i].source, src) == 0 && strcmp(flights[i].destination, dest) == 0)
        {
            found = 1;
            printf("Flight Found\nName : %s\nSource : %s\nDestination : %s\nFare : %.2f\n",
                   flights[i].name, flights[i].source, flights[i].destination, flights[i].fare);
        }
    }
    if (!found)
        printf("No flights found for this route.\n");
}

/* ---------------- MODULE 5: Update Flight ---------------- */
void update_flight()
{
    int id, i, found = 0;
    printf("Enter Flight ID to update: ");
    scanf("%d", &id);

    for (i = 0; i < flightCount; i++)
    {
        if (flights[i].flightId == id)
        {
            found = 1;
            printf("Enter New Fare: ");
            scanf("%f", &flights[i].fare);
            printf("Enter New Source: ");
            scanf("%29s", flights[i].source);
            printf("Enter New Destination: ");
            scanf("%29s", flights[i].destination);
            printf("Flight updated successfully.\n");
            break;
        }
    }
    if (!found)
        printf("Flight ID not found.\n");
}

/* ---------------- MODULE 6: Delete Flight ---------------- */
void delete_flight()
{
    int id, i, j, found = 0;
    printf("Enter Flight ID to delete: ");
    scanf("%d", &id);

    for (i = 0; i < flightCount; i++)
    {
        if (flights[i].flightId == id)
        {
            found = 1;
            for (j = i; j < flightCount - 1; j++)
                flights[j] = flights[j + 1];
            flightCount--;
            printf("Flight deleted successfully.\n");
            break;
        }
    }
    if (!found)
        printf("Flight ID not found.\n");
}

/* ---------------- MODULE 7: Flight Status Update ---------------- */
void flight_status()
{
    int id, i, found = 0, choice;
    printf("Enter Flight ID: ");
    scanf("%d", &id);

    for (i = 0; i < flightCount; i++)
    {
        if (flights[i].flightId == id)
        {
            found = 1;
            printf("Current Status: %s\n", flights[i].status);
            printf("1. On Time\n2. Delayed\n3. Cancelled\nUpdate Status: ");
            scanf("%d", &choice);
            switch (choice)
            {
                case 1: strcpy(flights[i].status, "On Time"); break;
                case 2: strcpy(flights[i].status, "Delayed"); break;
                case 3: strcpy(flights[i].status, "Cancelled"); break;
                default: printf("Invalid choice.\n"); return;
            }
            printf("Status updated to %s\n", flights[i].status);
            break;
        }
    }
    if (!found)
        printf("Flight ID not found.\n");
}

/* ---------------- MODULE 8: Seat Availability ---------------- */
void seat_availability()
{
    int id, i, found = 0;
    printf("Enter Flight ID: ");
    scanf("%d", &id);

    for (i = 0; i < flightCount; i++)
    {
        if (flights[i].flightId == id)
        {
            found = 1;
            int available = flights[i].totalSeats - flights[i].bookedSeats;
            printf("Flight: %s\n", flights[i].name);
            printf("Total Seats: %d\n", flights[i].totalSeats);
            printf("Booked Seats: %d\n", flights[i].bookedSeats);
            printf("Available Seats: %d\n", available);
            break;
        }
    }
    if (!found)
        printf("Flight ID not found.\n");
}

/* ---------------- MODULE 9: Register Passenger ---------------- */
void register_passenger()
{
    if (passengerCount >= MAX_PASSENGERS)
    {
        printf("Passenger storage full.\n");
        return;
    }
    Passenger p;
    p.passengerId = passengerCount + 1;
    printf("Enter Name: ");
    scanf("%49s", p.name);
    printf("Enter Age: ");
    scanf("%d", &p.age);
    printf("Enter Contact: ");
    scanf("%14s", p.contact);
    p.flightId = 0;
    p.checkedIn = 0;
    p.ticketBooked = 0;

    strcpy(p.ticketClass, "NotBooked");

    passengers[passengerCount++] = p;
    printf("Passenger registered successfully. Passenger ID: %d\n", p.passengerId);
}

/* ---------------- MODULE 10: View Passengers ---------------- */
void view_passengers()
{
    int i;
    if (passengerCount == 0)
    {
        printf("No Passengers Registered.\n");
        return;
    }
    printf("%-5s %-15s %-5s %-15s %-12s %-10s %-8s\n",
       "ID","Name","Age",
       "Contact","Class",
       "FlightID","CheckIn");

    for (i = 0; i < passengerCount; i++)
    {
       printf("%-5d %-15s %-5d %-15s %-12s %-10d %-8s\n",
       passengers[i].passengerId,
       passengers[i].name,
       passengers[i].age,
       passengers[i].contact,
       passengers[i].ticketClass,
       passengers[i].flightId,
       passengers[i].checkedIn ? "Yes" : "No");
    }
}

/* ---------------- MODULE 11: Update Passenger ---------------- */
void update_passenger()
{
    int id, i, found = 0;
    printf("Enter Passenger ID to update: ");
    scanf("%d", &id);

    for (i = 0; i < passengerCount; i++)
    {
        if (passengers[i].passengerId == id)
        {
            found = 1;
            printf("Enter New Name: ");
            scanf("%49s", passengers[i].name);
            printf("Enter New Age: ");
            scanf("%d", &passengers[i].age);
            printf("Enter New Contact: ");
            scanf("%14s", passengers[i].contact);
            printf("Passenger updated successfully.\n");
            break;
        }
    }
    if (!found)
        printf("Passenger ID not found.\n");
}

/* ---------------- MODULE 12: Search Passenger ---------------- */
void search_passenger()
{
    int id, i, found = 0;
    printf("Enter Passenger ID: ");
    scanf("%d", &id);

    for (i = 0; i < passengerCount; i++)
    {
        if (passengers[i].passengerId == id)
        {
            found = 1;
            printf("Name : %s\nAge : %d\nContact : %s\nFlight ID : %d\nChecked In : %s\n",
                   passengers[i].name, passengers[i].age, passengers[i].contact,
                   passengers[i].flightId, passengers[i].checkedIn ? "Yes" : "No");
            break;
        }
    }
    if (!found)
        printf("Passenger ID not found.\n");
}

/* ---------------- MODULE 13: Book Ticket ---------------- */
void book_ticket()
{
    int pid, fid, i, j, pFound = 0, fFound = 0;
    printf("Enter Passenger ID: ");
    scanf("%d", &pid);
    printf("Enter Flight ID: ");
    scanf("%d", &fid);

    for (i = 0; i < passengerCount; i++)
    {
        if (passengers[i].passengerId == pid)
        {
            pFound = 1;
            for (j = 0; j < flightCount; j++)
            {
                if (flights[j].flightId == fid)
                {
                    fFound = 1;
                    if (flights[j].bookedSeats >= flights[j].totalSeats)
                    {
                        printf("No seats available on this flight.\n");
                        return;
                    }
                    int classChoice;
                    printf("\nSelect Ticket Class");
                    printf("\n1. Economy");
                    printf("\n2. Business");
                    printf("\nChoice : ");
                    scanf("%d", &classChoice);

                    float fare = flights[j].fare;
                    if (classChoice == 1)
                    {
                        strcpy(passengers[i].ticketClass, "Economy");
                    }
                    else if (classChoice == 2)
                    {
                        strcpy(passengers[i].ticketClass, "Business");
                        fare = flights[j].fare * 2;
                    }
                    else
                    {
                        printf("Invalid Ticket Class\n");
                        return;
                    }
                    passengers[i].flightId = fid;
                    passengers[i].ticketBooked = 1;
                    flights[j].bookedSeats++;
                    totalRevenue += fare;
                    printf("\nTicket booked successfully\n");
                    printf("Passenger : %s\n", passengers[i].name);
                    printf("Flight : %s\n", flights[j].name);
                    printf("Class : %s\n", passengers[i].ticketClass);
                    printf("Fare : %.2f\n", fare);
                    return;
                }
            }
        }
    }
    if (!pFound) printf("Passenger ID not found.\n");
    else if (!fFound) printf("Flight ID not found.\n");
}

/* ---------------- MODULE 14: Cancel Ticket ---------------- */
void cancel_ticket()
{
    int pid, i, j, found = 0;
    printf("Enter Passenger ID: ");
    scanf("%d", &pid);

    for (i = 0; i < passengerCount; i++)
    {
        if (passengers[i].passengerId == pid)
        {
            found = 1;
            if (!passengers[i].ticketBooked)
            {
                printf("No active ticket for this passenger.\n");
                return;
            }
            for (j = 0; j < flightCount; j++)
            {
                if (flights[j].flightId == passengers[i].flightId)
                {
                    flights[j].bookedSeats--;
                    break;
                }
            }
            passengers[i].ticketBooked = 0;
            passengers[i].flightId = 0;
            passengers[i].checkedIn = 0;
            printf("Ticket cancelled successfully.\n");
            break;
        }
    }
    if (!found)
        printf("Passenger ID not found.\n");
}

/* ---------------- MODULE 15: Passenger Check-In ---------------- */
void passenger_checkin()
{
    int id, i, found = 0;
    printf("Enter Passenger ID for Check-In: ");
    scanf("%d", &id);

    for (i = 0; i < passengerCount; i++)
    {
        if (passengers[i].passengerId == id)
        {
            found = 1;
            if (!passengers[i].ticketBooked)
                printf("No ticket booked. Cannot check in.\n");
            else if (passengers[i].checkedIn)
                printf("Passenger already checked in.\n");
            else
            {
                passengers[i].checkedIn = 1;
                printf("Check-in successful for %s.\n", passengers[i].name);
            }
            break;
        }
    }
    if (!found)
        printf("Passenger ID not found.\n");
}

/* ---------------- MODULE 16: Boarding Pass ---------------- */
void boarding_pass()
{
    int pid, i, j, pFound = 0;
    printf("Enter Passenger ID: ");
    scanf("%d", &pid);

    for (i = 0; i < passengerCount; i++)
    {
        if (passengers[i].passengerId == pid)
        {
            pFound = 1;
            if (!passengers[i].ticketBooked)
            {
                printf("No ticket booked for this passenger.\n");
                return;
            }
            if (!passengers[i].checkedIn)
            {
                printf("Passenger has not checked in yet.\n");
                return;
            }
            for (j = 0; j < flightCount; j++)
            {
                if (flights[j].flightId == passengers[i].flightId)
                {
                    printf("\n===== BOARDING PASS =====\n");
                    printf("Passenger : %s\n", passengers[i].name);
                    printf("Flight    : %s\n", flights[j].name);
                    printf("Source    : %s\n", flights[j].source);
                    printf("Destination: %s\n", flights[j].destination);
                    printf("Fare      : %.2f\n", flights[j].fare);
                    printf("Class     : %s\n", passengers[i].ticketClass);
                    printf("==========================\n");
                    break;
                }
            }
            break;
        }
    }
    if (!pFound)
        printf("Passenger ID not found.\n");
}

/* ---------------- MODULE 17: Revenue Report ---------------- */
void revenue_report()
{
    int i;

    if (flightCount == 0)
    {
        printf("\nNo Flights Available.\n");
        return;
    }

    printf("\n==================================");
    printf("\n       REVENUE REPORT");
    printf("\n==================================");

    printf("\nTotal Flights    : %d", flightCount);
    printf("\nTotal Passengers : %d", passengerCount);
    printf("\nTotal Revenue    : Rs. %.2f\n", totalRevenue);

    printf("\n-------- Flight Wise Details --------\n");

    for (i = 0; i < flightCount; i++)
    {
        printf("\nFlight ID       : %d", flights[i].flightId);
        printf("\nFlight Name     : %s", flights[i].name);
        printf("\nBooked Seats    : %d", flights[i].bookedSeats);
        printf("\nAvailable Seats : %d", flights[i].totalSeats - flights[i].bookedSeats);
        printf("\nBase Fare       : Rs. %.2f\n", flights[i].fare);
    }

    printf("\n==================================\n");
}

/* ---------------- MODULE 18: Payment Processing ---------------- */
void payment_processing()
{
    int option;
    float amount;

    printf("\n===== PAYMENT PROCESSING =====\n");

    printf("Enter Amount : ");
    scanf("%f", &amount);

    printf("\n1. UPI");
    printf("\n2. Debit Card");
    printf("\n3. Credit Card");
    printf("\n4. Net Banking");

    printf("\nChoose Payment Method : ");
    scanf("%d", &option);

    switch (option)
    {
        case 1:
            printf("\nUPI Payment Successful\n");
            break;
        case 2:
            printf("\nDebit Card Payment Successful\n");
            break;
        case 3:
            printf("\nCredit Card Payment Successful\n");
            break;
        case 4:
            printf("\nNet Banking Payment Successful\n");
            break;
        default:
            printf("\nInvalid Payment Method\n");
            return;
    }

    printf("Amount Paid : %.2f\n", amount);
}

/* ---------------- MODULE 19: Save Data ---------------- */
void save_data()
{
    FILE *fp = fopen(FLIGHT_FILE, "wb");
    if (fp)
    {
        fwrite(&flightCount, sizeof(int), 1, fp);
        fwrite(flights, sizeof(Flight), (size_t)flightCount, fp);
        fclose(fp);
    }
    fp = fopen(PASSENGER_FILE, "wb");
    if (fp)
    {
        fwrite(&passengerCount, sizeof(int), 1, fp);
        fwrite(passengers, sizeof(Passenger), (size_t)passengerCount, fp);
        fclose(fp);
    }
    printf("Data saved successfully.\n");
}

/* ---------------- MODULE 20: Load Data ---------------- */
void load_data()
{
    FILE *fp;

    fp = fopen(FLIGHT_FILE, "rb");
    if (fp)
    {
        fread(&flightCount, sizeof(int), 1, fp);
        if (flightCount < 0 || flightCount > MAX_FLIGHTS)
        {
            flightCount = 0;
        }
        fread(flights, sizeof(Flight), (size_t)flightCount, fp);
        fclose(fp);
    }

    fp = fopen(PASSENGER_FILE, "rb");
    if (fp)
    {
        fread(&passengerCount, sizeof(int), 1, fp);
        if (passengerCount < 0 || passengerCount > MAX_PASSENGERS)
        {
            passengerCount = 0;
        }
        fread(passengers, sizeof(Passenger), (size_t)passengerCount, fp);
        fclose(fp);
    }
}

/* ---------------- MODULE: Main Menu ---------------- */
int main()
{
    int choice;

    load_data();

    if (flightCount < 0 || flightCount > MAX_FLIGHTS)
    {
        flightCount = 0;
    }

    if (passengerCount < 0 || passengerCount > MAX_PASSENGERS)
    {
        passengerCount = 0;
    }

    printf("===== FLIGHT MANAGEMENT SYSTEM =====\n");

    if (!admin_login())
        return 0;

    do
    {
        printf("\n1. Add Flight\n");
        printf("2. View Flights\n");
        printf("3. Search Flight\n");
        printf("4. Update Flight\n");
        printf("5. Delete Flight\n");
        printf("6. Flight Status\n");
        printf("7. Seat Availability\n");
        printf("8. Register Passenger\n");
        printf("9. View Passengers\n");
        printf("10. Update Passenger\n");
        printf("11. Search Passenger\n");
        printf("12. Book Ticket\n");
        printf("13. Cancel Ticket\n");
        printf("14. Passenger Check-In\n");
        printf("15. Boarding Pass\n");
        printf("16. Revenue Report\n");
        printf("17. Payment Processing\n");
        printf("18. Save Data\n");
        printf("0. Exit\n");

        printf("Enter Choice : ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1: add_flight(); break;
            case 2: view_flights(); break;
            case 3: search_flight(); break;
            case 4: update_flight(); break;
            case 5: delete_flight(); break;
            case 6: flight_status(); break;
            case 7: seat_availability(); break;
            case 8: register_passenger(); break;
            case 9: view_passengers(); break;
            case 10: update_passenger(); break;
            case 11: search_passenger(); break;
            case 12: book_ticket(); break;
            case 13: cancel_ticket(); break;
            case 14: passenger_checkin(); break;
            case 15: boarding_pass(); break;
            case 16: revenue_report(); break;
            case 17: payment_processing(); break;
            case 18: save_data(); break;
            case 0:
                save_data();
                printf("Exiting... Data saved.\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 0);
return 0;
