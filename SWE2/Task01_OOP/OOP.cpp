#include <iostream>
using namespace std;

class Car {
private:
    string brand;
    int year;

public:
    Car(string b, int y) {
        brand = b;
        year = y;
    }

    void setBrand(string b) {
        brand = b;
    }

    void setYear(int y) {
        year = y;
    }

    string getBrand() {
        return brand;
    }

    int getYear() {
        return year;
    }

    virtual void start() = 0;

    void showInfo() {
        cout << "Brand: " << brand << "Year: " << year << endl;
    }
};

class ElectricCar : public Car {
public:
    ElectricCar(string b, int y) : Car(b, y) {}

    void start() {
        cout << "ElectricCar starting silently=" << endl;
    }
};

class GasCar : public Car {
public:
    GasCar(string b, int y) : Car(b, y) {}

    void start() {
        cout << "GasCar engine starts with a roar" << endl;
    }
};

class HybridCar : public Car {
public:
    HybridCar(string b, int y) : Car(b, y) {}

    void start() {
        cout << "HybridCar uses electric motor then gas engine" << endl;
    }
};

int main() {
    ElectricCar c1("Tesla", 2023);
    GasCar c2("BMW", 2022);
    HybridCar c3("Toyota", 2024);

    cout << "+++=== Car Information ===++++" << endl;
    c1.showInfo();
    c2.showInfo();
    c3.showInfo();
cout<<endl;

    cout << "= Starting Engines =" << endl;
    c1.start();
    c2.start();
    c3.start();

    return 0;
}
