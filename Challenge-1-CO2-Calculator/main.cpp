
#include <iostream>
#include <string>
#include <limits>
using namespace std;

// Function to get the distance travelled
double getDistance() {
    double distance;

    while (true) {
        cout << "Enter distance travelled in miles: ";
        if (cin >> distance && distance >= 0) {
            return distance;
        }

        cout << "Invalid distance. Please enter a positive number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Function to get the fuel type
string getFuelType() {
    string fuel;

    while (true) {
        cout << "Enter fuel type (petrol/diesel): ";
        cin >> fuel;

        if (fuel == "petrol" || fuel == "diesel") {
            return fuel;
        }

        cout << "Invalid fuel type. Please try again.\n";
    }
}

// Function to calculate CO2 emissions
double calculateCO2(double distance, string fuel) {
    const double fuelConsumption = 9.66;
    double emissionRate;

    if (fuel == "diesel") {
        emissionRate = 2.68;
    } else {
        emissionRate = 2.31;
    }

    double litresUsed = (distance / 100) * fuelConsumption;
    return litresUsed * emissionRate;
}

int main() {
    cout << "===== CO2 EMISSIONS CALCULATOR =====\n\n";

    double distance = getDistance();
    string fuel = getFuelType();

    double emissions = calculateCO2(distance, fuel);

    cout << "\n===== JOURNEY SUMMARY =====\n";
    cout << "Distance: " << distance << " miles\n";
    cout << "Fuel type: " << fuel << "\n";
    cout << "CO2 emissions: " << emissions << " kg\n";

    cout << "\nThank you for using the calculator!\n";

    return 0;
}
