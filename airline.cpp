#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <cctype>
#include <stdexcept>
using namespace std;

// constants
const int MAX_FLIGHTS = 10;
const int MAX_BOOKINGS = 50;

// flight structure
struct flight
{
    string flightID;
    string departureTime;
    string locationFrom;
    string destination;
    string classType;
    int ticketPrice;
};

// booking structure
struct booking
{
    string bookingID;
    string passengerName;
    int age;
    string cnic;
    string flightID;
    string paymentMethod;
    string transactionID;
};

// Global arrays
flight flights[MAX_FLIGHTS];
booking bookings[MAX_BOOKINGS];
int flightCount = 0;
int bookingCount = 0;

// Function declarations
void adminPanel();
void passengerPanel();
void displayFlights();
void addFlight();
void updateFlight();
void deleteFlight();
void bookTicket();
void cancelTicket();
void showBookings();
string generateBookingID();
int getValidatedChoice();
string intToString(int);

// main
int main()
{
    int choice;
    do
    {
        cout << "\n========================\n";
        cout << "       MAIN MENU\n";
        cout << "========================\n";
        cout << "1. ADMIN PANEL\n";
        cout << "2. PASSENGER PANEL\n";
        cout << "3. EXIT\n";
        cout << "Enter your choice: ";
        choice = getValidatedChoice();

        switch (choice)
        {
        case 1:
            adminPanel();
            break;
        case 2:
            passengerPanel();
            break;
        case 3:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 3);

    return 0;
}

int getValidatedChoice()
{
    int choice;
    cin >> choice;

    while (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Enter number: ";
        cin >> choice;
    }
    return choice;
}

// ADMIN PANEL
void adminPanel()
{
    string password;
    cout << "Enter admin password: ";
    cin >> password;

    if (password == "2005")
    {
        int adminChoice;
        do
        {
            cout << "\n====== ADMIN PANEL ======\n";
            cout << "1. Add Flight\n";
            cout << "2. Update Flight\n";
            cout << "3. Delete Flight\n";
            cout << "4. Back\n";
            cout << "Enter choice: ";
            adminChoice = getValidatedChoice();

            switch (adminChoice)
            {
            case 1:
                addFlight();
                break;
            case 2:
                updateFlight();
                break;
            case 3:
                deleteFlight();
                break;
            case 4:
                break;
            default:
                cout << "Invalid choice!\n";
            }
        } while (adminChoice != 4);
    }
    else
    {
        cout << "Wrong password!\n";
    }
}

// ADD FLIGHT (Exception Handling Added Here)
void addFlight()
{
    if (flightCount >= MAX_FLIGHTS)
    {
        cout << "Flight storage full!\n";
        return;
    }

    string tempID;
    bool validID;
    do
    {
        validID = true;
        cout << "Enter Flight ID (5 digits): ";
        cin >> tempID;

        // Check format: must be 4 digits
        if (tempID.length() != 5)
        {
            validID = false;
            cout << "Invalid Flight ID format! Must be exactly 5 digits.\n";
        }
        else
        {
            for (int i=0; i<tempID.length();i++)
            {
                if (!isdigit(tempID[i]))
                {
                    validID = false;
                    cout << "Invalid Flight ID format! Must contain only digits.\n";
                    break;
                }
            }
        }

        // If format is valid, check for uniqueness
        if (validID)
        {
            for (int k = 0; k < flightCount; k++)
            {
                if (flights[k].flightID == tempID)
                {
                    validID = false;
                    cout << "THIS ID ALREADY EXISTS\n";
                    break;
                }
            }
        }

    } while (!validID);

    // Assign the validated ID
    flights[flightCount].flightID = tempID;

    cout << "Enter Departure Time: ";
    cin >> flights[flightCount].departureTime;
    cout << "Enter Location From: ";
    cin >> flights[flightCount].locationFrom;
    cout << "Enter Destination: ";
    cin >> flights[flightCount].destination;
    cout << "Enter Class(Business/Economy): ";
    cin >> flights[flightCount].classType;

    // ===== Exception Handling =====
    while (true)
    {
        try
        {
            cout << "Enter Ticket Price: ";
            cin >> flights[flightCount].ticketPrice;

            if (cin.fail() || flights[flightCount].ticketPrice <= 0)
                throw runtime_error("Invalid ticket price!");

            break;
        }
        catch (exception &e)
        {
            cout << "Error: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    flightCount++;
    cout << "Flight Added Successfully!\n";
}

// UPDATE FLIGHT
void updateFlight()
{
    string id;
    cout << "Enter Flight ID: ";
    cin >> id;

    for (int i = 0; i < flightCount; i++)
    {
        if (flights[i].flightID == id)
        {
            cout << "Enter new Departure Time: ";
            cin >> flights[i].departureTime;
            cout << "Enter new From: ";
            cin >> flights[i].locationFrom;
            cout << "Enter new Destination: ";
            cin >> flights[i].destination;
            cout << "Enter new Class: ";
            cin >> flights[i].classType;
            cout << "Enter new Price: ";
            cin >> flights[i].ticketPrice;
            cout << "Flight Updated!\n";
            return;
        }
    }
    cout << "Flight not found!\n";
}

// DELETE FLIGHT
void deleteFlight()
{
    string id;
    cout << "Enter Flight ID to delete: ";
    cin >> id;

    for (int i = 0; i < flightCount; i++)
    {
        if (flights[i].flightID == id)
        {
            for (int j = i; j < flightCount - 1; j++)
                flights[j] = flights[j + 1];

            flightCount--;
            cout << "Flight Deleted!\n";
            return;
        }
    }
    cout << "Flight not found!\n";
}

// PASSENGER PANEL
void passengerPanel()
{
    int choice;
    do
    {
        cout << "\n====== PASSENGER PANEL ======\n";
        cout << "1. View Flights\n";
        cout << "2. Book Ticket\n";
        cout << "3. Cancel Ticket\n";
        cout << "4. View Bookings\n";
        cout << "5. Back\n";
        cout << "Enter choice: ";
        choice = getValidatedChoice();

        switch (choice)
        {
        case 1:
            displayFlights();
            break;
        case 2:
            bookTicket();
            break;
        case 3:
            cancelTicket();
            break;
        case 4:
            showBookings();
            break;
        case 5:
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 5);
}

// DISPLAY FLIGHTS
void displayFlights()
{
    if (flightCount == 0)
    {
        cout << "No flights available!\n";
        return;
    }
    for (int i = 0; i < flightCount; i++)
    {
        cout << "Flight ID: " << flights[i].flightID << ", From: " << flights[i].locationFrom 
             << ", To: " << flights[i].destination << ", Time: " << flights[i].departureTime 
             << ", Class: " << flights[i].classType << ", Price: " << flights[i].ticketPrice << " PKR\n";
    }
}

// BOOK TICKET
void bookTicket()
{
    if (bookingCount >= MAX_BOOKINGS)
    {
        cout << "Booking storage full!\n";
        return;
    }

    string id;
    displayFlights();
    cout << "Enter Flight ID: ";
    cin >> id;

    for (int i = 0; i < flightCount; i++)
    {
        if (flights[i].flightID == id)
        {
            bookings[bookingCount].bookingID = generateBookingID();
            cin.ignore();
            cout << "Enter Name: ";
            getline(cin, bookings[bookingCount].passengerName);
            cout << "Enter Age: ";
            cin >> bookings[bookingCount].age;

            bool validCNIC;
            do
            {
                validCNIC = true;
                cout << "Enter CNIC (13 digits): ";
                cin >> bookings[bookingCount].cnic;

                if (bookings[bookingCount].cnic.length() != 13)
                    validCNIC = false;

                for(int i=0; i< bookings[bookingCount].cnic.length();i++)
                {
                    if (!isdigit(bookings[bookingCount].cnic[i]))
                    {
                        validCNIC = false;
                        break;
                    }
                }

                if (!validCNIC)
                    cout << "Invalid CNIC!\n";
            } while (!validCNIC);

            bookings[bookingCount].flightID = id;
            cout << "Enter Payment Method: ";
            cin >> bookings[bookingCount].paymentMethod;
            cout << "Enter Transaction ID: ";
            cin >> bookings[bookingCount].transactionID;
            bookingCount++;
            cout << "Ticket Booked! ID: " << bookings[bookingCount - 1].bookingID << endl;
            return;
        }
    }
    cout << "Flight not found!\n";
}

// CANCEL TICKET
void cancelTicket()
{
    string id;
    cout << "Enter Booking ID: ";
    cin >> id;

    for (int i = 0; i < bookingCount; i++)
    {
        if (bookings[i].bookingID == id)
        {
            for (int j = i; j < bookingCount - 1; j++)
                bookings[j] = bookings[j + 1];

            bookingCount--;
            cout << "Booking Cancelled!\n";
            return;
        }
    }
    cout << "Booking not found!\n";
}

// SHOW BOOKINGS
void showBookings()
{
    if (bookingCount == 0)
    {
        cout << "There are no bookings!\n";
        return;
    }

    for (int i = 0; i < bookingCount; i++)
    {
        cout << "Booking ID: " << bookings[i].bookingID << ", Name: " << bookings[i].passengerName 
             << ", Age: " << bookings[i].age << ", CNIC: " << bookings[i].cnic 
             << ", Flight ID: " << bookings[i].flightID << ", Payment: " << bookings[i].paymentMethod 
             << ", Transaction ID: " << bookings[i].transactionID << endl;
    }
}

// BOOKING ID
string generateBookingID()
{
    return "BKG" + intToString(bookingCount + 1);
}

// INT TO STRING
string intToString(int num)
{
    ostringstream ss;
    ss << num;
    return ss.str();
}