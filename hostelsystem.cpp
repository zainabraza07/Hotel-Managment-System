#include <iostream>
#include <fstream>   // For file handling
#include <cstring>   // For strlen()

using namespace std;

struct Room {
    string bookedBy;
    string contactInfo;
    bool isBooked;
};

Room rooms[3]; // Array to hold room information for 3 rooms

// Function declarations
void display_title(const char* title);
void displayPaymentDetails(int room_type);
void displayRoomType();
void displayHotelAmenities();
bool isRoomAvailable(int room_type);
void bookRoom(int room_type);
void clearRoomBooking(int room_type);
void displayBookedRooms(); 
int getBookingDays();
bool checkLoyaltyProgram();
void getUserInfo(string& name, int& age, int& numPeople, string& email, string& phoneNumber);
void displayRoomAssignmentInfo();
void getSpecialRequest(string& specialRequest);
void displayCancellationPolicy();
void cancelBooking(bool& bookingCancelled);
void returnToMainMenu();
void saveBookedRoomsToFile();
void loadBookedRoomsFromFile();
namespace ANSI
{
    const string SKYBLUE= "\033[96m";
}

int main()
{
    const char* title = "VOYAGE HOTEL";

    // Initialize rooms as available
    for (int i = 0; i < 3; ++i) {
        rooms[i].isBooked = false;
    }

    // Load previously booked rooms from file (if any)
    loadBookedRoomsFromFile();

    while (true) {
        display_title(title); // Display the title each time the main menu is shown

        // Show options to the user
        cout << "1. Display Room Types and Payment Details" << endl;
        cout << "2. Book a Room" << endl;
        cout << "3. Display Hotel Amenities" << endl;
        cout << "4. Show Booked Rooms" << endl; 
        cout << "5. Delete Room Booking" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice (1-6): ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                displayPaymentDetails(1);
                displayPaymentDetails(2);
                displayPaymentDetails(3);
                break;
            case 2: {
                displayRoomType();
                int roomTypeChoice;
                cout << "Enter room type to book (1, 2, or 3): ";
                cin >> roomTypeChoice;

                if (roomTypeChoice >= 1 && roomTypeChoice <= 3) {
                    if (isRoomAvailable(roomTypeChoice)) {
                        bookRoom(roomTypeChoice);
                        saveBookedRoomsToFile(); // Save booked rooms after booking
                    } else {
                        cout << "Room type " << roomTypeChoice << " is not available." << endl;
                    }
                } else {
                    cout << "Invalid room type entered. Please enter 1, 2, or 3." << endl;
                }
                break;
            }
            case 3:
                displayHotelAmenities();
                break;
            case 4:
                displayBookedRooms(); 
                break;
            case 5: {
                displayRoomType();
                int roomTypeChoice;
                cout << "Enter room type to delete booking (1, 2, or 3): ";
                cin >> roomTypeChoice;

                if (roomTypeChoice >= 1 && roomTypeChoice <= 3) {
                    clearRoomBooking(roomTypeChoice);
                    cout << "Room type " << roomTypeChoice << " booking deleted successfully." << endl;
                    saveBookedRoomsToFile(); // Save booked rooms after deletion
                } else {
                    cout << "Invalid room type entered. Please enter 1, 2, or 3." << endl;
                }
                break;
            }
            case 6:
                cout << "Exiting the program. Thank you!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 6." << endl;
                break;
        }

        returnToMainMenu(); // Wait for user input to return to the main menu
    }

    return 0;
}

// Function definition for display_title
void display_title(const char* title)
{
    const char* bold_start = "\033[1m";
    const char* bold_end = "\033[0m";
    int title_width = strlen(title) + 6; // Calculate title width including borders

    cout << string(title_width, '=') << endl;                 // Top border
    cout << "*  " << bold_start <<ANSI::SKYBLUE<<title << bold_end << "  *" << endl;  // Title line in bold
    cout << string(title_width, '=') << endl;                 // Bottom border
}

// Function definition for displayPaymentDetails
void displayPaymentDetails(int room_type)
{
    cout << "Payment details" << endl;
    cout << "---------------------------" << endl;
    switch (room_type)
    {
        case 1:
            cout << "Single room: $100 per day" << endl;
            cout << "Amenities: WiFi, TV, bed" << endl;
            break;
        case 2:
            cout << "Double room: $150 per day" << endl;
            cout << "Amenities: WiFi, TV, 2 beds" << endl;
            break;
        case 3:
            cout << "Meeting room: $250 per day" << endl;
            cout << "Amenities: WiFi, projector, chairs" << endl;
            break;
        default:
            cout << "Invalid room type" << endl;
            break;
    }
    cout << "---------------------------------" << endl;
}

// Function definition for displayRoomType
void displayRoomType()
{
    cout << "Room types available" << endl;
    cout << "1. Single room" << endl;
    cout << "2. Double room" << endl;
    cout << "3. Meeting room" << endl;
}

// Function definition for displayHotelAmenities
void displayHotelAmenities()
{
    cout << "\nHotel Amenities:" << endl;
    cout << "- Swimming pool" << endl;
    cout << "- Breakfast, lunch, and dinner available" << endl;
    cout << "- Room service" << endl;
    cout << "- Library" << endl;
    cout << "- Gym" << endl;
}

// Function definition for isRoomAvailable
bool isRoomAvailable(int room_type)
{
    // Simulate room availability logic
    // For demonstration, let's assume all room types are always available
    return true;
}

// Function definition for bookRoom
void bookRoom(int room_type)
{
    string roomName;
    int pricePerDay = 0;

    switch (room_type)
    {
        case 1:
            roomName = "Single room";
            pricePerDay = 100;
            break;
        case 2:
            roomName = "Double room";
            pricePerDay = 150;
            break;
        case 3:
            roomName = "Meeting room";
            pricePerDay = 250;
            break;
        default:
            cout << "Invalid room type selected" << endl;
            return; // Exit function early if room type is invalid
    }

    // Get the number of days the room is booked for
    int bookingDays = getBookingDays();

    // Calculate the total price
    int totalPrice = pricePerDay * bookingDays;
    cout << "----------------------------------------------" << endl;

    // Check if the customer is part of the loyalty program
    bool isLoyalCustomer = checkLoyaltyProgram();
    if (isLoyalCustomer)
    {
        double discount = 0.10; // 10% discount for loyal customers
        totalPrice = totalPrice * (1 - discount);
        cout << "Loyalty discount applied! New total price: $" << totalPrice << endl;
    }

    // Display booking details
    cout << "Room booked: " << roomName << endl;
    cout << "Price per day: $" << pricePerDay << endl;
    cout << "Total price for " << bookingDays << " day(s): $" << totalPrice << endl;

    // Mark room as booked
    rooms[room_type - 1].isBooked = true;

    // Get user information
    string name, email, phoneNumber;
    int age, numPeople;
    getUserInfo(name, age, numPeople, email, phoneNumber);

    // Store booking details
    rooms[room_type - 1].bookedBy = name;
    rooms[room_type - 1].contactInfo = email;

    // Display user information
    cout << "\nThank you for booking with us, " << name << "!" << endl;
    cout << "Your booking details:" << endl;
    cout << "Room type: " << roomName << endl;
    cout << "Number of people: " << numPeople << endl;
    cout << "Email: " << email << endl;
    cout << "Phone number: " << phoneNumber << endl;

    // Get special request from the user
    string specialRequest;
    getSpecialRequest(specialRequest);
    if (!specialRequest.empty())
    {
        cout << "Special request: " << specialRequest << endl;
    }

    // Display room assignment info
    displayRoomAssignmentInfo();

    // Display cancellation policy
    displayCancellationPolicy();

    // Allow cancellation and apply charges if necessary
    bool bookingCancelled = false;
    cancelBooking(bookingCancelled);
    if (bookingCancelled)
    {
        // Apply cancellation charges if cancelled after 24 hours
        if (bookingDays > 1)
        {
            cout << "Cancellation charges: $20 applied." << endl;
        }
        else
        {
            cout << "Booking successfully cancelled. No charges applied." << endl;
        }
    }
    else
    {
        // Display confirmation message after booking
        cout << "You will receive a confirmation email or SMS shortly. Thank you for choosing and trusting Voyage Hotel!" << endl;
    }

    // Wait for user input to return to the main menu
    returnToMainMenu();
}

// Function to clear room booking
void clearRoomBooking(int room_type)
{
    if (room_type >= 1 && room_type <= 3) {
        rooms[room_type - 1].isBooked = false;
        rooms[room_type - 1].bookedBy = "";
        rooms[room_type - 1].contactInfo = "";
    } else {
        cout << "Invalid room type." << endl;
    }
}

// Function to display booked rooms
void displayBookedRooms()
{
    bool foundBookedRoom = false;

    cout << "Currently Booked Rooms:" << endl;
    cout << "-----------------------" << endl;

    for (int i = 0; i < 3; ++i) {
        if (rooms[i].isBooked) {
            cout << "Room Type: " << (i + 1) << endl;
            cout << "Booked by: " << rooms[i].bookedBy << endl;
            cout << "Contact Info: " << rooms[i].contactInfo << endl;
            cout << "-----------------------" << endl;
            foundBookedRoom = true;
        }
    }

    if (!foundBookedRoom) {
        cout << "No rooms are currently booked." << endl;
    }
}

// Function definition for getUserInfo
void getUserInfo(string& name, int& age, int& numPeople, string& email, string& phoneNumber)
{
    cout << "\nPlease enter your information:" << endl;
    cout << "Name: ";
    cin.ignore(); // Ignore any remaining newline characters from previous inputs
    getline(cin, name);

    cout << "Age: ";
    cin >> age;

    cout << "Number of people: ";
    cin >> numPeople;

    cin.ignore(); // Ignore any remaining newline characters from previous inputs
    while(true)
    {
        cout << "Email: ";
        getline(cin, email);
        if(email.find('@')!=string::npos &&  email.find('.') !=string::npos){
            break;
        }else{
         cout << "Invalid email format please enter a valid email"<<endl;

        }
    }
    

    cout << "Phone number: ";
    getline(cin, phoneNumber);
}

// Function definition for displayRoomAssignmentInfo
void displayRoomAssignmentInfo()
{
    cout << "\nNote: The room number will be assigned at the time of check-in." << endl;
}

// Function definition for checkLoyaltyProgram
bool checkLoyaltyProgram()
{
    char hasStayedBefore;
    cout << "Have you stayed with us before? (y/n): ";
    cin >> hasStayedBefore;
    return (hasStayedBefore == 'y' || hasStayedBefore == 'Y');
}

// Function definition for getSpecialRequest
void getSpecialRequest(string& specialRequest)
{
    cout << "Do you have any special requests? (Leave blank if none): ";
    cin.ignore(); // Ignore any remaining newline characters from previous inputs
    getline(cin, specialRequest);
}

// Function definition for getBookingDays
int getBookingDays()
{
    int days;
    cout << "How many days do you want to book the room for?: ";
    cin >> days;
    return days;
}

// Function definition for displayCancellationPolicy
void displayCancellationPolicy()
{
    cout << "\nCancellation Policy:" << endl;
    cout << "--------------------------------------------" << endl;
    cout << "Cancelling after 24 hours from booking has charges." << endl;
    cout << "Cancelling before 24 hours from booking is free." << endl;
}

// Function definition for cancelBooking
void cancelBooking(bool& bookingCancelled)
{
    char cancelChoice;
    cout << "\nDo you want to cancel your booking? (y/n): ";
    cin >> cancelChoice;

    if (cancelChoice == 'y' || cancelChoice == 'Y')
    {
        bookingCancelled = true;
    }
    else
    {
        bookingCancelled = false;
    }
    cout << "--------------------------------------------" << endl;
}

// Function definition for returnToMainMenu
void returnToMainMenu()
{
    char choice;
    cout << "\nPress any key and Enter to return to the main menu: ";
    cin >> choice;
    cin.ignore(); // Ignore any remaining newline characters
}

// Function to save booked rooms to a file
void saveBookedRoomsToFile()
{
    ofstream outFile("booked_rooms.txt");

    if (outFile.is_open())
    {
        for (int i = 0; i < 3; ++i)
        {
            if (rooms[i].isBooked)
            {
                outFile << "Room Type: " << (i + 1) << endl;
                outFile << "Booked by: " << rooms[i].bookedBy << endl;
                outFile << "Contact Info: " << rooms[i].contactInfo << endl;
                outFile << "-----------------------" << endl;
            }
        }
        outFile.close();
        cout << "Booked rooms saved to file." << endl;
    }
    else
    {
        cout << "Unable to open file to save booked rooms." << endl;
    }
}

// Function to load booked rooms from a file
void loadBookedRoomsFromFile()
{
    ifstream inFile("booked_rooms.txt");

    if (inFile.is_open())
    {
        string line;
        int roomType;
        while (getline(inFile, line))
        {
            if (line.find("Room Type: ") != string::npos)
            {
                roomType = line.back() - '0'; // Extract room type from the last character of the line
            }
            else if (line.find("Booked by: ") != string::npos)
            {
                getline(inFile, rooms[roomType - 1].bookedBy); // Read booked by information
            }
            else if (line.find("Contact Info: ") != string::npos)
            {
                getline(inFile, rooms[roomType - 1].contactInfo); // Read contact info
            }
        }
        inFile.close();
        cout << "Booked rooms loaded from file." << endl;
    }
    else
    {
        cout << "No booked rooms found in file." << endl;
    }
}
