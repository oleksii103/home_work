#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream> // Для роботи з файлами

using namespace std;

struct Car {
    string name;
    int year;
    double engineVolume;
    double price;

    void display() const {
        cout << "Name: " << name << ", Year: " << year
            << ", Engine Volume: " << engineVolume << "L, Price: $" << price << endl;
    }
};

class Dealership {
private:
    vector<Car> cars;

public:
    void addCar(const string& name, int year, double engineVolume, double price) {
        cars.push_back({ name, year, engineVolume, price });
    }

    void removeCar(const string& name) {
        auto it = remove_if(cars.begin(), cars.end(), [&](const Car& car) {
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
        for (const auto& car : cars) {
            car.display();
        }
    }

    void sortCars(bool (*comparator)(const Car&, const Car&)) {
        sort(cars.begin(), cars.end(), comparator);
    }

    void searchCars(bool (*predicate)(const Car&)) const {
        bool found = false;
        for (const auto& car : cars) {
            if (predicate(car)) {
                car.display();
                found = true;
            }
        }
        if (!found) {
            cout << "No matching cars found.\n";
        }
    }

    void saveToFile(const string& filename) const {
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "Failed to open file for saving.\n";
            return;
        }
        for (const auto& car : cars) {
            file << car.name << ";" << car.year << ";"
                << car.engineVolume << ";" << car.price << "\n";
        }
        file.close();
        cout << "Data saved to file successfully.\n";
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Failed to open file for loading.\n";
            return;
        }
        cars.clear();
        string line;
        while (getline(file, line)) {
            size_t pos = 0;
            string name;
            int year;
            double engineVolume, price;

            pos = line.find(";");
            name = line.substr(0, pos);
            line.erase(0, pos + 1);

            pos = line.find(";");
            year = stoi(line.substr(0, pos));
            line.erase(0, pos + 1);

            pos = line.find(";");
            engineVolume = stod(line.substr(0, pos));
            line.erase(0, pos + 1);

            price = stod(line);

            cars.push_back({ name, year, engineVolume, price });
        }
        file.close();
        cout << "Data loaded from file successfully.\n";
    }
};

int main() {
    Dealership dealership;
    int choice;

    const string filename = "cars_data.txt";

    dealership.loadFromFile(filename); // Завантаження даних із файлу

    do {
        cout << "\nCar Dealership Menu:\n"
            << "1. Add car\n"
            << "2. Remove car\n"
            << "3. Display all cars\n"
            << "4. Sort cars\n"
            << "5. Search cars\n"
            << "6. Save and Exit\n"
            << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string name;
            int year;
            double engineVolume, price;
            cout << "Enter car name: ";
            cin.ignore(); // Очищення буфера
            getline(cin, name);
            cout << "Enter year: ";
            cin >> year;
            cout << "Enter engine volume (L): ";
            cin >> engineVolume;
            cout << "Enter price ($): ";
            cin >> price;
            dealership.addCar(name, year, engineVolume, price);
            break;
        }
        case 2: {
            string name;
            cout << "Enter car name to remove: ";
            cin.ignore();
            getline(cin, name);
            dealership.removeCar(name);
            break;
        }
        case 3:
            dealership.displayCars();
            break;
        case 4: {
            int sortChoice;
            cout << "Sort by:\n"
                << "1. Name\n"
                << "2. Year\n"
                << "3. Engine Volume\n"
                << "4. Price\n"
                << "Enter your choice: ";
            cin >> sortChoice;

            switch (sortChoice) {
            case 1:
                dealership.sortCars([](const Car& a, const Car& b) {
                    return a.name < b.name;
                    });
                break;
            case 2:
                dealership.sortCars([](const Car& a, const Car& b) {
                    return a.year < b.year;
                    });
                break;
            case 3:
                dealership.sortCars([](const Car& a, const Car& b) {
                    return a.engineVolume < b.engineVolume;
                    });
                break;
            case 4:
                dealership.sortCars([](const Car& a, const Car& b) {
                    return a.price < b.price;
                    });
                break;
            default:
                cout << "Invalid choice.\n";
            }
            break;
        }
        case 5: {
            int searchChoice;
            cout << "Search by:\n"
                << "1. Name\n"
                << "2. Year\n"
                << "3. Engine Volume\n"
                << "4. Price\n"
                << "Enter your choice: ";
            cin >> searchChoice;

            switch (searchChoice) {
            case 1: {
                string name;
                cout << "Enter name to search: ";
                cin.ignore();
                getline(cin, name);
                dealership.searchCars([&](const Car& car) {
                    return car.name == name;
                    });
                break;
            }
            case 2: {
                int year;
                cout << "Enter year to search: ";
                cin >> year;
                dealership.searchCars([&](const Car& car) {
                    return car.year == year;
                    });
                break;
            }
            case 3: {
                double engineVolume;
                cout << "Enter engine volume to search (L): ";
                cin >> engineVolume;
                dealership.searchCars([&](const Car& car) {
                    return car.engineVolume == engineVolume;
                    });
                break;
            }
            case 4: {
                double price;
                cout << "Enter price to search ($): ";
                cin >> price;
                dealership.searchCars([&](const Car& car) {
                    return car.price == price;
                    });
                break;
            }
            default:
                cout << "Invalid choice.\n";
            }
            break;
        }
        case 6:
            dealership.saveToFile(filename); // Збереження даних у файл
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 6);

    return 0;
}
