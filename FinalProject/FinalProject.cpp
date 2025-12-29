#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Car {
protected:
    string brand;
    int year;
public:
    Car(string b, int y) : brand(b), year(y) {}
    virtual ~Car() {}
    string getBrand() { return brand; }
    int getYear() { return year; }
    virtual void start() = 0;
};

class IRechargeable {
public:
    virtual void recharge() = 0;
};

class ElectricCar : public Car, public IRechargeable {
public:
    ElectricCar(string b, int y) : Car(b, y) {}
    void start() override { cout << "ElectricCar " << brand << " starting silently ??" << endl; }
    void recharge() override { cout << "Charging ElectricCar " << brand << " ?" << endl; }
};

class GasCar : public Car {
public:
    GasCar(string b, int y) : Car(b, y) {}
    void start() override { cout << "GasCar " << brand << " engine starts with a roar ?" << endl; }
};

class HybridCar : public Car, public IRechargeable {
public:
    HybridCar(string b, int y) : Car(b, y) {}
    void start() override { cout << "HybridCar " << brand << " starts with electric motor then gas engine ???" << endl; }
    void recharge() override { cout << "Recharging HybridCar " << brand << " battery ?" << endl; }
};

class CarInfoPrinter {
public:
    void showInfo(Car &c) {
        cout << "Brand: " << c.getBrand() << ", Year: " << c.getYear() << endl;
    }
};

class Logger {
private:
    static Logger* instance;
    Logger() {}
public:
    static Logger* getInstance() {
        if (!instance) instance = new Logger();
        return instance;
    }
    void log(const string& msg) { cout << "[LOG]: " << msg << endl; }
};
Logger* Logger::instance = nullptr;

class Beverage {
public:
    virtual string getName() = 0;
    virtual double cost() = 0;
    virtual ~Beverage() {}
};

class Coffee : public Beverage {
public:
    string getName() { return "Coffee"; }
    double cost() { return 5; }
};

class Tea : public Beverage {
public:
    string getName() { return "Tea"; }
    double cost() { return 3; }
};

class BeverageFactory {
public:
    static Beverage* createBeverage(const string& type) {
        if (type == "coffee") return new Coffee();
        if (type == "tea") return new Tea();
        return nullptr;
    }
};

class BeverageBuilder {
protected:
    Beverage* beverage;
    string extra;
public:
    BeverageBuilder(Beverage* b) : beverage(b) {}
    BeverageBuilder* addExtra(const string& e) { extra = e; return this; }
    Beverage* build() {
        if (!extra.empty())
            Logger::getInstance()->log(beverage->getName() + " with " + extra + " built");
        else
            Logger::getInstance()->log(beverage->getName() + " built");
        return beverage;
    }
};

class BeverageDecorator : public Beverage {
protected:
    Beverage* beverage;
public:
    BeverageDecorator(Beverage* b) : beverage(b) {}
};

class MilkDecorator : public BeverageDecorator {
public:
    MilkDecorator(Beverage* b) : BeverageDecorator(b) {}
    string getName() override { return beverage->getName() + " + Milk"; }
    double cost() override { return beverage->cost() + 1; }
};

class Observer {
public:
    virtual void update(const string& message) = 0;
};

class Customer : public Observer {
    string name;
public:
    Customer(string n) : name(n) {}
    void update(const string& message) override {
        cout << name << " received notification: " << message << endl;
    }
};

class Cafe {
    vector<Observer*> customers;
public:
    void attach(Observer* c) { customers.push_back(c); }
    void notify(const string& message) {
        for (auto& c : customers) c->update(message);
    }
};

class Client {
public:
    string name;
    Car* car;
    Beverage* beverage;
    Client(string n, Car* c, Beverage* b) : name(n), car(c), beverage(b) {}
};

int main() {
    Logger::getInstance()->log("=== Extended Scenario Started ===");

    Car* car1 = new ElectricCar("Tesla", 2023);
    Car* car2 = new GasCar("BMW", 2022);
    Car* car3 = new HybridCar("Toyota", 2024);

    Beverage* bev1 = BeverageBuilder(BeverageFactory::createBeverage("coffee")).addExtra("Chocolate")->build();
    Beverage* bev2 = BeverageBuilder(BeverageFactory::createBeverage("tea")).addExtra("Lemon")->build();
    Beverage* bev3 = new MilkDecorator(BeverageBuilder(BeverageFactory::createBeverage("coffee")).addExtra("Caramel")->build());

    Client c1("Ahmed", car1, bev1);
    Client c2("Hoda", car2, bev2);
    Client c3("Mona", car3, bev3);

    vector<Client*> clients = { &c1, &c2, &c3 };

    Cafe cafe;
    Customer obs1("Observer1"), obs2("Observer2");
    cafe.attach(&obs1);
    cafe.attach(&obs2);

    for (auto client : clients) {
        cout << "\n--- " << client->name << " Scenario ---" << endl;
        client->car->start();
        if (IRechargeable* r = dynamic_cast<IRechargeable*>(client->car)) {
            r->recharge();
        }
        cafe.notify(client->name + " ordered: " + client->beverage->getName());
    }

    Logger::getInstance()->log("=== Extended Scenario Ended ===");

    delete car1;
    delete car2;
    delete car3;
    delete bev1;
    delete bev2;
    delete bev3;

    return 0;
}
