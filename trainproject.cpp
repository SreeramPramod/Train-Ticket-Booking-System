#include <iostream>
#include <string>

using namespace std;

class Train {
public:
    string trainNumber;
    string driverName;
    string route;
    string timing;
    int totalSeats;
    bool* seats;

    Train(string trainNumber, string driverName, string route, string timing, int totalSeats)
        : trainNumber(trainNumber), driverName(driverName), route(route), timing(timing), totalSeats(totalSeats) {
        seats = new bool[totalSeats];
        for (int i = 0; i < totalSeats; ++i) {
            seats[i] = true;
        }
    }

    ~Train() {
        delete[] seats;
    }

    void showTrainInfo() {
        cout << "Train Number: " << trainNumber << endl;
        cout << "Driver Name: " << driverName << endl;
        cout << "Route: " << route << endl;
        cout << "Timing: " << timing << endl;
        cout << "Available Seats: " << countAvailableSeats() << "/" << totalSeats << endl;
    }

    int countAvailableSeats() {
        int count = 0;
        for (int i = 0; i < totalSeats; ++i) {
            if (seats[i]) {
                count++;
            }
        }
        return count;
    }

    bool bookSeats(int numSeats) {
        if (numSeats <= 0) {
            cout << "Invalid number of seats." << endl;
            return false;
        }
        int availableSeats = countAvailableSeats();
        if (numSeats > availableSeats) {
            cout << "Not enough seats available. Only " << availableSeats << " seats left." << endl;
            return false;
        }
        int seatsBooked = 0;
        for (int i = 0; i < totalSeats && seatsBooked < numSeats; ++i) {
            if (seats[i]) {
                seats[i] = false;
                seatsBooked++;
            }
        }
        cout << numSeats << " seats successfully booked." << endl;
        return true;
    }
};

class TrainReservationSystem {
private:
    Train* trains[6];

public:
    TrainReservationSystem() {
        trains[0] = new Train("1200", "Davis", "Tokyo to Kyoto", "10:00 AM", 240);
        trains[1] = new Train("5068", "Roy", "Kyoto to Osaka", "12:00 PM", 230);
        trains[2] = new Train("9506", "Joseph", "Tokyo to Osaka", "02:00 PM", 250);
        trains[3] = new Train("2045", "Emily", "Osaka to Hiroshima", "04:00 PM", 200);
        trains[4] = new Train("3078", "Sophia", "Hiroshima to Fukuoka", "06:00 PM", 220);
        trains[5] = new Train("4096", "James", "Fukuoka to Sapporo", "08:00 PM", 260);
    }

    ~TrainReservationSystem() {
        for (int i = 0; i < 6; ++i) {
            delete trains[i];
        }
    }

    void showAllTrains() {
        for (int i = 0; i < 6; ++i) {
            trains[i]->showTrainInfo();
            cout << endl;
        }
    }

    void bookSeats(string trainNumber, int numSeats) {
        for (int i = 0; i < 6; ++i) {
            if (trains[i]->trainNumber == trainNumber) {
                trains[i]->bookSeats(numSeats);
                return;
            }
        }
        cout << "Train not found." << endl;
    }

    void showTrainDetails(string trainNumber) {
        for (int i = 0; i < 6; ++i) {
            if (trains[i]->trainNumber == trainNumber) {
                trains[i]->showTrainInfo();
                return;
            }
        }
        cout << "Train not found." << endl;
    }
};

int main() {
    TrainReservationSystem system;

    int choice;
    do {
        cout << "1. Show all Trains" << endl;
        cout << "2. Show Train details" << endl;
        cout << "3. Book seats" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            system.showAllTrains();
            break;
        case 2: {
            string trainNumber;
            cout << "Enter Train number: ";
            cin >> trainNumber;
            system.showTrainDetails(trainNumber);
            break;
        }
        case 3: {
            string trainNumber;
            int numSeats;
            cout << "Enter Train number: ";
            cin >> trainNumber;
            cout << "Enter number of seats to book: ";
            cin >> numSeats;
            system.bookSeats(trainNumber, numSeats);
            break;
        }
        case 4:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
