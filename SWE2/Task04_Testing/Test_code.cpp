#####################
##_Cafe_patterns.cpp##
#####################

#include "cafe_patterns.h"

//////////////////////////
// Logger (Singleton)
//////////////////////////

Logger* Logger::instance = nullptr;

Logger::Logger() {}

Logger* Logger::getInstance() {
    if (!instance)
        instance = new Logger();
    return instance;
}

void Logger::log(const string& msg) {
    logs.push_back(msg);
    cout << "[LOG]: " << msg << endl;
}

//////////////////////////
// Factory Pattern
//////////////////////////

string Coffee::getName() {
    return "Coffee";
}

double Coffee::cost() {
    return 3;
}

string Tea::getName() {
    return "Tea";
}

double Tea::cost() {
    return 7;
}

Beverage* BeverageFactory::createBeverage(const string& type) {
    if (type == "coffee")
        return new Coffee();
    if (type == "tea")
        return new Tea();
    return nullptr;
}

//////////////////////////
// Builder Pattern
//////////////////////////

BeverageBuilder::BeverageBuilder(Beverage* b)
    : beverage(b) {}

BeverageBuilder* BeverageBuilder::addExtra(const string& e) {
    extra = e;
    return this;
}

Beverage* BeverageBuilder::build() {
    if (extra != "")
        Logger::getInstance()->log(beverage->getName() + " with " + extra);
    else
        Logger::getInstance()->log(beverage->getName());

    return beverage;
}

string BeverageBuilder::getExtra() {
    return extra;
}

//////////////////////////
// Decorator Pattern
//////////////////////////

BeverageDecorator::BeverageDecorator(Beverage* b)
    : beverage(b) {}

BeverageDecorator::~BeverageDecorator() {
    delete beverage;
}

MilkDecorator::MilkDecorator(Beverage* b)
    : BeverageDecorator(b) {}

string MilkDecorator::getName() {
    return beverage->getName() + " + Milk";
}

double MilkDecorator::cost() {
    return beverage->cost() + 1;
}

//////////////////////////
// Observer Pattern
//////////////////////////

void Cafe::attach(Observer* c) {
    customers.push_back(c);
}

void Cafe::notify(const string& message) {
    for (Observer* c : customers) {
        c->update(message);
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
###################
##_Cafe_patterns.h##
###################

#ifndef CAFE_PATTERNS_H
#define CAFE_PATTERNS_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Logger {
private:
    static Logger* instance;
    vector<string> logs;
    Logger();
public:
    static Logger* getInstance();
    void log(const string& msg);
};

class Beverage {
public:
    virtual string getName() = 0;
    virtual double cost() = 0;
    virtual ~Beverage() {}
};

class Coffee : public Beverage {
public:
    string getName() override;
    double cost() override;
};

class Tea : public Beverage {
public:
    string getName() override;
    double cost() override;
};

class BeverageFactory {
public:
    static Beverage* createBeverage(const string& type);
};

class BeverageBuilder {
    Beverage* beverage;
    string extra;
public:
    BeverageBuilder(Beverage* b);
    BeverageBuilder* addExtra(const string& e);
    Beverage* build();
    string getExtra();
};

class BeverageDecorator : public Beverage {
protected:
    Beverage* beverage;
public:
    BeverageDecorator(Beverage* b);
    virtual ~BeverageDecorator();
};

class MilkDecorator : public BeverageDecorator {
public:
    MilkDecorator(Beverage* b);
    string getName() override;
    double cost() override;
};

class Observer {
public:
    virtual void update(const string& message) = 0;
    virtual ~Observer() {}
};

class Cafe {
    vector<Observer*> customers;
public:
    void attach(Observer* c);
    void notify(const string& message);
};

#endif
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
##################
##_unit_tests.cpp##
##################

#include "cafe_patterns.h"
include <iostream>
using namespace std;

int passed = 0;
int failed = 0;

void CHECK(bool condition, const string& testName) {
    if (condition) {
        cout << "PASS: " << testName << endl;
        passed++;
    } else {
        cout << "FAILED: " << testName << endl;
        failed++;
    }
}

//////////////////////////
// Test Observer
//////////////////////////
class TestObserver : public Observer {
public:
    string lastMessage;
    void update(const string& message) override {
        lastMessage = message;
    }
};

//////////////////////////
// Tests
//////////////////////////
void testSingleton() {
    CHECK(Logger::getInstance() == Logger::getInstance(),
          "Singleton returns same instance");
}

void testFactory() {
    Beverage* coffee = BeverageFactory::createBeverage("coffee");
    Beverage* tea    = BeverageFactory::createBeverage("tea");

    CHECK(coffee != nullptr, "Factory creates Coffee");
    CHECK(tea != nullptr, "Factory creates Tea");

    CHECK(coffee->getName() == "Coffee", "Coffee name correct");
    CHECK(coffee->cost() == 5, "Coffee cost correct");

    CHECK(tea->getName() == "Tea", "Tea name correct");
    CHECK(tea->cost() == 3, "Tea cost correct");

    delete coffee;
    delete tea;
}

void testBuilder() {
    Beverage* coffee = new Coffee();
    BeverageBuilder builder(coffee);

    builder.addExtra("Chocolate");

    CHECK(builder.getExtra() == "Chocolate",
          "Builder adds extra correctly");

    delete coffee;
}

void testDecorator() {
    Beverage* drink = new MilkDecorator(new Coffee());

    CHECK(drink->getName() == "Coffee + Milk",
          "Decorator name correct");

    CHECK(drink->cost() == 5,
          "Decorator cost correct");

    delete drink;
}

void testObserver() {
    Cafe cafe;
    TestObserver o1, o2;

    cafe.attach(&o1);
    cafe.attach(&o2);

    cafe.notify("New Drink");

    CHECK(o1.lastMessage == "New Drink",
          "Observer 1 received notification");

    CHECK(o2.lastMessage == "New Drink",
          "Observer 2 received notification");
}

//////////////////////////
// Main
//////////////////////////
int main() {
    cout << "Running Unit Tests...\n\n";

    testSingleton();
    testFactory();
    testBuilder();
    testDecorator();
    testObserver();

    cout << "\n========================\n";
    cout << "Passed: " << passed << endl;
    cout << "Failed: " << failed << endl;
    cout << "========================\n";

    return 0;
}



