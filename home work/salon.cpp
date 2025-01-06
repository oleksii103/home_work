#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

struct Car {
    string name;
    int year;
    double engineVolume;
    double price;

    void display() const {
        cout << name << "\t" << year << "\t" << engineVolume << "\t" << price << '\n';
    }

    void saveToFile(std::ofstream& outFile) const {
        outFile << name << ',' << year << ',' << engineVolume << ',' << price << '\n';
    }
};

class AutoSalon {
private:
    vector<Car> cars;

public:
    void addCar(const string& name, int year, double engineVolume, double price) {
        cars.push_back({ name, year, engineVolume, price });
    }

    void removeCar(const std::string& name) {
        auto it = remove_if(cars.begin(), cars.end(), [&name](const Car& car) {
            return car.name == name;
            });
        if (it != cars.end()) {
            cars.erase(it, cars.end());
            cout << "Car removed successfully.\n";
        }
        else {
            cout << "Car not found.\n";
        }
    }

    void displayCars() const {
        if (cars.empty()) {
            cout << "No cars available.\n";
            return;
        }

        cout << "Name\tYear\tEngine Volume\tPrice\n";
        cout << string(40, '-') << '\n';

        for (const auto& car : cars) {
            car.display();
        }
    }

    void sortCars(const string& criteria) {
        if (criteria == "name") {
            sort(cars.begin(), cars.end(), [](const Car& a, const Car& b) {
                return a.name < b.name;
                });
        }
        else if (criteria == "year") {
            sort(cars.begin(), cars.end(), [](const Car& a, const Car& b) {
                return a.year < b.year;
                });
        }
        else if (criteria == "engine") {
            sort(cars.begin(), cars.end(), [](const Car& a, const Car& b) {
                return a.engineVolume < b.engineVolume;
                });
        }
        else if (criteria == "price") {
            sort(cars.begin(), cars.end(), [](const Car& a, const Car& b) {
                return a.price < b.price;
                });
        }
        else {
            cout << "Invalid sorting criteria.\n";
            return;
        }
        cout << "Cars sorted successfully.\n";
    }

    void searchCars(const string& criteria, const string& value) const {
        vector<Car> results;
        if (criteria == "name") {
            copy_if(cars.begin(), cars.end(), back_inserter(results), [&value](const Car& car) {
                return car.name.find(value) != string::npos;
                });
        }
        else if (criteria == "year") {
            int year = std::stoi(value);
            copy_if(cars.begin(), cars.end(), back_inserter(results), [&year](const Car& car) {
                return car.year == year;
                });
        }
        else if (criteria == "engine") {
            double engineVolume = stod(value);
            copy_if(cars.begin(), cars.end(), back_inserter(results), [&engineVolume](const Car& car) {
                return car.engineVolume == engineVolume;
                });
        }
        else if (criteria == "price") {
            double price = stod(value);
            copy_if(cars.begin(), cars.end(), std::back_inserter(results), [&price](const Car& car) {
                return car.price == price;
                });
        }
        else {
            cout << "Invalid search criteria.\n";
            return;
        }

        if (results.empty()) {
            cout << "No cars found matching the criteria.\n";
        }
        else {
            cout << "Search results:\n";
            cout << "Name\tYear\tEngine Volume\tPrice\n";
            cout << string(40, '-') << '\n';
            for (const auto& car : results) {
                car.display();
            }
        }
    }

    void saveToFile(const std::string& filename) const {
        ofstream outFile(filename);
        if (!outFile) {
            cerr << "Failed to open file for writing.\n";
            return;
        }

        for (const auto& car : cars) {
            car.saveToFile(outFile);
        }

        cout << "Cars data saved to " << filename << " successfully.\n";
    }
};

int main() {
    AutoSalon salon;
    int choice;

    do {
        cout << "\nAuto Salon Management System\n";
        cout << "1. Add Car\n";
        cout << "2. Remove Car\n";
        cout << "3. Display Cars\n";
        cout << "4. Sort Cars\n";
        cout << "5. Search Cars\n";
        cout << "6. Save Cars to File\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string name;
            int year;
            double engineVolume, price;
            cout << "Enter car name: ";
            cin >> name;
            cout << "Enter year of manufacture: ";
            cin >> year;
            cout << "Enter engine volume: ";
            cin >> engineVolume;
            cout << "Enter price: ";
            cin >> price;
            salon.addCar(name, year, engineVolume, price);
            break;
        }
        case 2: {
            string name;
            cout << "Enter the name of the car to remove: ";
            cin >> name;
            salon.removeCar(name);
            break;
        }
        case 3:
            salon.displayCars();
            break;
        case 4: {
            string criteria;
            cout << "Enter sorting criteria (name, year, engine, price): ";
            cin >> criteria;
            salon.sortCars(criteria);
            break;
        }
        case 5: {
            string criteria, value;
            cout << "Enter search criteria (name, year, engine, price): ";
            cin >> criteria;
            cout << "Enter value to search: ";
            cin >> value;
            salon.searchCars(criteria, value);
            break;
        }
        case 6:
            salon.saveToFile("cars_data.txt");
            break;
        case 0:
            cout << "Exiting the program.\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
