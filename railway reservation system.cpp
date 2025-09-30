#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct Seat {
    int seatNo;
    bool isReserved;
    string reservedBy;
    Seat* prev;
    Seat* next;
    Seat(int no) : seatNo(no), isReserved(false), reservedBy("Passenger"), prev(NULL), next(NULL) {}
};

struct Transaction {
    string type; // Reservation / Cancellation
    string bogieType;
    int bogieNumber;
    int* seats;
    int seatCount;
    int pricePerSeat;
    string date;
    string departure;
    string trainName;
    string fromCity;
    string toCity;
    string userName;
};

class Bogie {
public:
    string type;
    int price;
    int bogieNumber;
    Seat* head;
    int seatCount;

    Bogie(string t, int count, int p, int bNo) {
        type = t;
        price = p;
        seatCount = count;
        bogieNumber = bNo;
        head = NULL;
        for (int i = 1; i <= seatCount; i++) addSeat(i);
    }

    ~Bogie() {
        Seat* curr = head;
        while (curr) {
            Seat* temp = curr;
            curr = curr->next;
            delete temp;
        }
    }

    void addSeat(int seatNo) {
        Seat* newSeat = new Seat(seatNo);
        if (!head) head = newSeat;
        else {
            Seat* curr = head;
            while (curr->next) curr = curr->next;
            curr->next = newSeat;
            newSeat->prev = curr;
        }
    }

    Seat* findSeat(int seatNo) {
        Seat* curr = head;
        while (curr) {
            if (curr->seatNo == seatNo) return curr;
            curr = curr->next;
        }
        return NULL;
    }

    void displaySeatsFull() {
        cout << "\nBogie " << bogieNumber << " - " << type << " | Price: " << price << " Rs.\n";
        cout << "==================================\n";
        cout << left << setw(10) << "Seat" << setw(15) << "Status" << "\n";
        cout << "==================================\n";
        Seat* curr = head;
        while (curr) {
            cout << left << setw(10) << curr->seatNo
                 << setw(15) << (curr->isReserved ? "Reserved" : "Available") << "\n";
            curr = curr->next;
        }
    }

    void displaySeatsMini(int perRow = 5) {
        cout << "\nBogie " << bogieNumber << " - " << type << " | Price: " << price << "\n";
        Seat* curr = head;
        int count = 0;
        cout << "\nO = available, X = reserved\n";
        while (curr) {
            if (count % perRow == 0 && count != 0) cout << "\n";
            cout << "[ " << setw(2) << curr->seatNo << " : " << (curr->isReserved ? "X" : "O") << " ] ";
            curr = curr->next;
            count++;
        }
        cout << "\n";
    }

    bool reserveSeats(int seats[], int n) {
        bool success = true;
        for (int i = 0; i < n; i++) {
            Seat* s = findSeat(seats[i]);
            if (!s || s->isReserved) {
                cout << "Seat " << seats[i] << " not available.\n";
                success = false;
            } else s->isReserved = true;
        }
        return success;
    }

    bool cancelSeats(int seats[], int n) {
        bool success = true;
        for (int i = 0; i < n; i++) {
            Seat* s = findSeat(seats[i]);
            if (s && s->isReserved) s->isReserved = false;
            else {
                cout << "Seat " << seats[i] << " not reserved or invalid.\n";
                success = false;
            }
        }
        return success;
    }

    void generateReceipt(int seats[], int n, string typeOfTransaction, string trainName, string fromCity, string toCity, string date, string departure, string userName) {
        int totalPrice = n * price;
        cout << "\n================= " << typeOfTransaction << " RECEIPT =================\n";
        cout << "Train: " << trainName << " | Bogie No: " << bogieNumber << "\n";
        cout << "From: " << fromCity << "   To: " << toCity << "\n";
        cout << "Date: " << date << "   Departure: " << departure << "\n";
        cout << "Passenger: " << userName << "\n";
        cout << "Bogie: " << type << "\n";
        cout << "---------------------------------------\n";
        cout << left << setw(10) << "Seat" << setw(10) << "Price" << "\n";
        for (int i = 0; i < n; i++)
            cout << left << setw(10) << seats[i] << setw(10) << price << "\n";
        cout << "---------------------------------------\n";
        cout << "Total Seats: " << n << "\n";
        if (typeOfTransaction == "Cancellation") cout << "Refund Amount: " << totalPrice << "\n";
        else cout << "Total Price: " << totalPrice << "\n";
        cout << "==================================================\n";
    }
};

class Train {
private:
    Bogie* premium;
    Bogie* normal;
    Transaction* history[100];
    int historyCount;

    // Train details
    string trainName;
    string trainNumber;
    string fromCity;
    string toCity;
    string departureTime;
    string arrivalTime;
    string travelDate;

public:
    Train() {
        trainName = "Shatabdi Express";
        trainNumber = "12345";
        fromCity = "Delhi";
        toCity = "Chandigarh";
        departureTime = "07:00";
        arrivalTime = "11:30";
        travelDate = "29-09-2025";

        premium = new Bogie("Premium", 10, 500, 1);
        normal = new Bogie("Normal", 20, 300, 2);
        historyCount = 0;
    }

    ~Train() {
        delete premium;
        delete normal;
        for (int i = 0; i < historyCount; i++) {
            delete[] history[i]->seats;
            delete history[i];
        }
    }

    void showTrainInfo() {
        cout << "\nTrain: " << trainName << "\nTrain Number: " << trainNumber << "\n";
        cout << "Route: " << fromCity << " to " << toCity << "\n";
        cout << "Departure: " << departureTime << "   Arrival: " << arrivalTime << "\n";
        cout << "Bogie 1: Premium (10 seats, Rs. 500 each)\n";
        cout << "Bogie 2: Normal (20 seats, Rs. 300 each)\n";
    }

    void showFullSeats() {
        premium->displaySeatsFull();
        normal->displaySeatsFull();
    }

    void reserveSeats(string userName) {
        Bogie* bogie;
        int choice;
        while (true) {
            cout << "\nSelect Bogie (1=Premium, 2=Normal): ";
            cin >> choice;
            if (choice == 1) { bogie = premium; break; }
            else if (choice == 2) { bogie = normal; break; }
            else cout << "Invalid input! Try again.\n";
        }

        bool success = false;
        while (!success) {
            bogie->displaySeatsMini();
            int numSeats;
            cout << "\nHow many seats do you want to reserve? ";
            cin >> numSeats;

            int* seatsArr = new int[numSeats];

            if (numSeats == 1) {
                cout << "Enter seat number: ";
                cin >> seatsArr[0];
            } else {
                cout << "Enter seat numbers (separated by space): ";
                for (int i = 0; i < numSeats; i++) cin >> seatsArr[i];
            }

            success = bogie->reserveSeats(seatsArr, numSeats);
            if (!success) cout << "Some seats were unavailable. Please try again.\n";
            else {
                cout << "Seats reserved successfully!\n";
                bogie->generateReceipt(seatsArr, numSeats, "Reservation", trainName, fromCity, toCity, travelDate, departureTime, userName);

                Transaction* t = new Transaction;
                t->type = "Reservation";
                t->bogieType = bogie->type;
                t->bogieNumber = bogie->bogieNumber;
                t->seatCount = numSeats;
                t->pricePerSeat = bogie->price;
                t->seats = new int[numSeats];
                t->trainName = trainName;
                t->fromCity = fromCity;
                t->toCity = toCity;
                t->date = travelDate;
                t->departure = departureTime;
                t->userName = userName;
                for (int i = 0; i < numSeats; i++) t->seats[i] = seatsArr[i];
                history[historyCount++] = t;
            }
            delete[] seatsArr;
        }
    }

    void cancelSeats(string userName) {
        Bogie* bogie;
        int choice;
        while (true) {
            cout << "\nSelect Bogie (1=Premium, 2=Normal): ";
            cin >> choice;
            if (choice == 1) { bogie = premium; break; }
            else if (choice == 2) { bogie = normal; break; }
            else cout << "Invalid input! Try again.\n";
        }

        bool success = false;
        while (!success) {
            bogie->displaySeatsMini();
            int numSeats;
            cout << "\nHow many seats do you want to cancel? ";
            cin >> numSeats;

            int* seatsArr = new int[numSeats];

            if (numSeats == 1) {
                cout << "Enter seat number to cancel: ";
                cin >> seatsArr[0];
            } else {
                cout << "Enter seat numbers (separated by space): ";
                for (int i = 0; i < numSeats; i++) cin >> seatsArr[i];
            }

            success = bogie->cancelSeats(seatsArr, numSeats);
            if (!success) cout << "Some seats were invalid or not reserved. Please try again.\n";
            else {
                cout << "Seats canceled successfully!\n";
                bogie->generateReceipt(seatsArr, numSeats, "Cancellation", trainName, fromCity, toCity, travelDate, departureTime, userName);

                Transaction* t = new Transaction;
                t->type = "Cancellation";
                t->bogieType = bogie->type;
                t->bogieNumber = bogie->bogieNumber;
                t->seatCount = numSeats;
                t->pricePerSeat = bogie->price;
                t->seats = new int[numSeats];
                t->trainName = trainName;
                t->fromCity = fromCity;
                t->toCity = toCity;
                t->date = travelDate;
                t->departure = departureTime;
                t->userName = userName;
                for (int i = 0; i < numSeats; i++) t->seats[i] = seatsArr[i];
                history[historyCount++] = t;
            }
            delete[] seatsArr;
        }
    }

    void showHistory() {
        if (historyCount == 0) {
            cout << "\nNo reservations or cancellations yet.\n";
            return;
        }

        cout << "\nTransaction History:\n";
        cout << left << setw(5) << "ID"
             << setw(15) << "Type"
             << setw(10) << "Bogie"
             << setw(12) << "Total Price"
             << setw(12) << "Status" << "\n";
        cout << "====================================================\n";

        for (int i = 0; i < historyCount; i++) {
            int totalPrice = history[i]->seatCount * history[i]->pricePerSeat;
            cout << left << setw(5) << (i + 1)
                 << setw(15) << history[i]->type
                 << setw(10) << history[i]->bogieType
                 << setw(12) << totalPrice
                 << setw(12) << "Complete" << "\n"; // Default status
        }

        int id;
        cout << "\nEnter Transaction ID to view receipt (0 to return): ";
        cin >> id;

        if (id > 0 && id <= historyCount) {
            Transaction* t = history[id - 1];

            cout << "\n================= RECEIPT =================\n";
            cout << "Train: " << t->trainName << "\n";
            cout << "Bogie No: " << t->bogieNumber << " (" << t->bogieType << ")\n";
            cout << "From: " << t->fromCity << "   To: " << t->toCity << "\n";
            cout << "Date: " << t->date << "   Departure: " << t->departure << "\n";
            cout << "Passenger: " << t->userName << "\n";
            cout << "Type: " << t->type << "\n";
            cout << "-----------------------------------------\n";
            cout << left << setw(10) << "Seat" << setw(10) << "Price" << "\n";
            for (int i = 0; i < t->seatCount; i++)
                cout << left << setw(10) << t->seats[i] << setw(10) << t->pricePerSeat << "\n";
            cout << "-----------------------------------------\n";

            int totalPrice = t->seatCount * t->pricePerSeat;
            if (t->type == "Cancellation") cout << "Refund Amount: " << totalPrice << "\n";
            else cout << "Total Price: " << totalPrice << "\n";

            cout << "==========================================\n";
        }
    }

};

int main() {
    Train train;
    int mainChoice;

    while (true) {
        cout << "\nWELCOME TO RAILWAY RESERVATION SYSTEM\n";
        cout << "1. Enter Software\n2. Exit Program\nEnter choice (1 or 2): ";
        cin >> mainChoice;

        if (mainChoice == 2) break;
        else if (mainChoice != 1) {
            cout << "Invalid choice, please try again.\n";
            continue;
        }

        string userName;
        cout << "Enter your name: ";
        cin.ignore();
        getline(cin, userName);
        cout << "\nHello, " << userName <<"...\n";

        int choice;
        do {
            cout << "\n======== MAIN MENU ========\n";
            cout << "1. Train Info\n";
            cout << "2. View All Seats\n";
            cout << "3. Reserve Seats\n";
            cout << "4. Cancel Seats\n";
            cout << "5. History\n";
            cout << "6. Exit to Main Menu\n";
            cout << "===========================\n";
            cout << "Choose (1-6): ";
            cin >> choice;

            switch (choice) {
                case 1: train.showTrainInfo(); break;
                case 2: train.showFullSeats(); break;
                case 3: train.reserveSeats(userName); break;
                case 4: train.cancelSeats(userName); break;
                case 5: train.showHistory(); break;
                case 6: cout << "Returning to main menu...\n"; break;
                default: cout << "Invalid choice, try again.\n";
            }

        } while (choice != 6);
    }

    cout << "\nThank you for using the Railway Reservation System!\n";
    return 0;
}
