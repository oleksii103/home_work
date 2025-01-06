#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Product {
    string name;
    string category;
    double price;
    int quantity;

    void display() const {
        cout << name << "\t" << category << "\t" << price << "\t" << quantity << '\n';
    }

    string toCSV() const {
        return name + "," + category + "," + to_string(price) + "," + to_string(quantity);
    }
};

class ElectronicsStore {
private:
    const string filename = "products.txt";

    vector<Product> loadProducts() const {
        ifstream file(filename);
        vector<Product> products;
        if (!file.is_open()) {
            cerr << "Could not open file: " << filename << "\n";
            return products;
        }

        string line;
        while (getline(file, line)) {
            string name, category;
            double price;
            int quantity;

            size_t pos = 0;
            pos = line.find(',');
            name = line.substr(0, pos);  
            line.erase(0, pos + 1);  

            pos = line.find(',');
            category = line.substr(0, pos); 
            line.erase(0, pos + 1);  

            pos = line.find(',');
            price = stod(line.substr(0, pos));  
            line.erase(0, pos + 1);  

            quantity = stoi(line); 

            products.push_back({ name, category, price, quantity });
        }
        file.close();
        return products;
    }

    void saveProducts(const vector<Product>& products) const {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Could not open file for writing: " << filename << "\n";
            return;
        }

        for (const auto& product : products) {
            file << product.toCSV() << '\n';
        }
        file.close();
    }

public:
    void addProduct(const string& name, const string& category, double price, int quantity) {
        vector<Product> products = loadProducts();
        products.push_back({ name, category, price, quantity });
        saveProducts(products);
        cout << "Product added successfully.\n";
    }

    void displayProducts() const {
        vector<Product> products = loadProducts();
        if (products.empty()) {
            cout << "No products available.\n";
            return;
        }

        cout << "Name\tCategory\tPrice\tQuantity\n";
        cout << string(40, '-') << '\n';
        for (const auto& product : products) {
            product.display();
        }
    }

    void searchProduct(const string& name) const {
        vector<Product> products = loadProducts();
        auto it = find_if(products.begin(), products.end(), [&name](const Product& p) {
            return p.name == name;
            });

        if (it != products.end()) {
            cout << "Product found:\n";
            cout << "Name\tCategory\tPrice\tQuantity\n";
            cout << string(40, '-') << '\n';
            it->display();
        }
        else {
            cout << "Product not found.\n";
        }
    }

    void updateProduct(const string& name, double newPrice, int newQuantity) {
        vector<Product> products = loadProducts();
        auto it = find_if(products.begin(), products.end(), [&name](const Product& p) {
            return p.name == name;
            });

        if (it != products.end()) {
            it->price = newPrice;
            it->quantity = newQuantity;
            saveProducts(products);
            cout << "Product updated successfully.\n";
        }
        else {
            cout << "Product not found.\n";
        }
    }

    void deleteProduct(const string& name) {
        vector<Product> products = loadProducts();
        auto it = remove_if(products.begin(), products.end(), [&name](const Product& p) {
            return p.name == name;
            });

        if (it != products.end()) {
            products.erase(it, products.end());
            saveProducts(products);
            cout << "Product deleted successfully.\n";
        }
        else {
            cout << "Product not found.\n";
        }
    }
};

int main() {
    ElectronicsStore store;
    int choice;

    do {
        cout << "\nElectronics Store Management System\n";
        cout << "1. Add Product\n";
        cout << "2. Display All Products\n";
        cout << "3. Search Product by Name\n";
        cout << "4. Update Product\n";
        cout << "5. Delete Product\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string name, category;
            double price;
            int quantity;
            cout << "Enter product name: ";
            cin >> name;
            cout << "Enter product category: ";
            cin >> category;
            cout << "Enter price: ";
            cin >> price;
            cout << "Enter quantity: ";
            cin >> quantity;
            store.addProduct(name, category, price, quantity);
            break;
        }
        case 2:
            store.displayProducts();
            break;
        case 3: {
            string name;
            cout << "Enter product name to search: ";
            cin >> name;
            store.searchProduct(name);
            break;
        }
        case 4: {
            string name;
            double newPrice;
            int newQuantity;
            cout << "Enter product name to update: ";
            cin >> name;
            cout << "Enter new price: ";
            cin >> newPrice;
            cout << "Enter new quantity: ";
            cin >> newQuantity;
            store.updateProduct(name, newPrice, newQuantity);
            break;
        }
        case 5: {
            string name;
            cout << "Enter product name to delete: ";
            cin >> name;
            store.deleteProduct(name);
            break;
        }
        case 0:
            cout << "Exiting the program.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
