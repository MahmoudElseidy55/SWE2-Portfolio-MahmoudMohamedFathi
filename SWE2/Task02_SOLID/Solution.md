#include <iostream>
using namespace std;

class Car {
protected:
    string brand;
    int year;

public:
    Car(string b, int y) : brand(b), year(y) {}

    string getBrand() { return brand; }
    int getYear() { return year; }

    virtual void start() = 0;
    virtual ~Car() {}
};

class CarInfoPrinter {
public:
    void showInfo(Car &c) {
        cout << "Brand: " << c.getBrand() << ", Year: " << c.getYear() << endl;
    }
};

class IRechargeable {
public:
    virtual void recharge() = 0;
};

class ElectricCar : public Car, public IRechargeable {
public:
    ElectricCar(string b, int y) : Car(b, y) {}

    void start() override {
        cout << "ElectricCar starting silently ⚡️" << endl;
    }

    void recharge() override {
        cout << "Charging the battery 🔋" << endl;
    }
};

class GasCar : public Car {
public:
    GasCar(string b, int y) : Car(b, y) {}

    void start() override {
        cout << "GasCar engine starts with a roar ⛽️" << endl;
    }
};

class HybridCar : public Car, public IRechargeable {
public:
    HybridCar(string b, int y) : Car(b, y) {}

    void start() override {
        cout << "HybridCar starts with electric motor then gas engine ⚙️" << endl;
    }

    void recharge() override {
        cout << "Recharging hybrid system battery 🔋" << endl;
    }
};

void startCarEngine(Car &car) {
    car.start();
}

int main() {
    ElectricCar tesla("Tesla", 2023);
    GasCar bmw("BMW", 2022);
    HybridCar toyota("Toyota", 2024);

    CarInfoPrinter printer;

    cout << "=== Car Information ===" << endl;
    printer.showInfo(tesla);
    printer.showInfo(bmw);
    printer.showInfo(toyota);
    cout << endl;

    cout << "=== Starting Engines ===" << endl;
    startCarEngine(tesla);
    startCarEngine(bmw);
    startCarEngine(toyota);
    cout << endl;

    cout << "=== Recharging Cars ===" << endl;
    tesla.recharge();
    toyota.recharge();

    return 0;
}
