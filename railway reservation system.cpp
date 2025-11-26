#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct Passenger {
    int seatNo;
    string name;
    int age;
    char gender;
    Passenger* next;
};

void addPassenger(Passenger*& head, int seatNo, string name, int age, char gender) {
    Passenger* p = new Passenger();
    p->seatNo = seatNo;
    p->name = name;
    p->age = age;
    p->gender = gender;
    p->next = head;
    head = p;
}

bool removePassenger(Passenger*& head, int seatNo) {
    Passenger* curr = head;
    Passenger* prev = NULL;

    while (curr) {
        if (curr->seatNo == seatNo) {
            if (prev) prev->next = curr->next;
            else head = curr->next;
            delete curr;
            return true;
        }
        prev = curr;
        curr = curr->next;
    }
    return false;
}

void displayPassengers(Passenger* head) {
    if (!head) {
        cout << "\nNo passengers booked.\n";
        return;
    }
    cout << "\nPassenger List:\n";
    cout << "-------------------------------------------\n";
    Passenger* curr = head;
    while (curr) {
        cout << "Seat " << curr->seatNo
             << " | Name: " << curr->name
             << " | Age: " << curr->age
             << " | Gender: " << curr->gender << "\n";
        curr = curr->next;
    }
}

void displaySeatMap(int* seats, int totalSeats) {
    cout << "\nTRAIN SEAT MAP (O = Available, X = Booked)\n";
    cout << "---------------------------------------------\n";

    for (int i = 0; i < totalSeats; i++) {
        if (i % 4 == 0) cout << "\n";

        cout << "[ "
             << setw(2) << (i + 1)
             << " : "
             << (seats[i] ? "X" : "O")
             << " ] ";
    }
    cout << "\n\n";
}

void bookTicket(int* seats, int totalSeats, Passenger*& head) {
    displaySeatMap(seats, totalSeats);

    int seatNo;
    cout << "Enter seat number to book (1 - " << totalSeats << "): ";
    cin >> seatNo;

    if (seatNo < 1 || seatNo > totalSeats) {
        cout << "Invalid seat number!\n";
        return;
    }

    if (seats[seatNo - 1] == 1) {
        cout << "Seat already booked!\n";
        return;
    }
    string name;
    int age;
    char gender;

    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter Age: ";
    cin >> age;

    cout << "Enter Gender (M/F): ";
    cin >> gender;
    gender = toupper(gender);

    seats[seatNo - 1] = 1;
    addPassenger(head, seatNo, name, age, gender);

    cout << "\nTicket Booked Successfully! Seat No: " << seatNo << "\n";
}

void cancelTicket(int* seats, int totalSeats, Passenger*& head) {
    displaySeatMap(seats, totalSeats);

    int seatNo;
    cout << "Enter seat number to cancel: ";
    cin >> seatNo;

    if (seatNo < 1 || seatNo > totalSeats) {
        cout << "Invalid seat number!\n";
        return;
    }

    if (seats[seatNo - 1] == 0) {
        cout << "Seat is not booked!\n";
        return;
    }
    seats[seatNo - 1] = 0;

    if (removePassenger(head, seatNo))
        cout << "\nBooking cancelled for seat " << seatNo << ".\n";
    else
        cout << "Passenger not found (unexpected error).\n";
}

void viewTrainStatus(int* seats, int totalSeats) {
    cout << "\nTrain Status:\n";
    for (int i = 0; i < totalSeats; i++) {
        cout << "Seat " << (i + 1) << ": "
             << (seats[i] ? "Booked" : "Available") << "\n";
    }
}

void freeMemory(int* seats, Passenger* head) {
    delete[] seats;
    while (head) {
        Passenger* temp = head;
        head = head->next;
        delete temp;
    }
}


// Menu
int main() {
    int totalSeats = 32;
    int* seats = new int[totalSeats];
    for (int i = 0; i < totalSeats; i++){
            seats[i] = 0;
    }
    Passenger* head = NULL;

    int choice;
    do {
        cout << "\nRAILWAY RESERVATION SYSTEM\n----------------------------\n";
        cout << "1. Book Ticket\n";
        cout << "2. Cancel Ticket\n";
        cout << "3. View Train Status\n";
        cout << "4. View Passenger List\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: bookTicket(seats, totalSeats, head); break;
            case 2: cancelTicket(seats, totalSeats, head); break;
            case 3: displaySeatMap(seats, totalSeats); break;
            case 4: displayPassengers(head); break;
            case 5:
                cout << "\nExiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 5);

    freeMemory(seats, head);

    return 0;
}

