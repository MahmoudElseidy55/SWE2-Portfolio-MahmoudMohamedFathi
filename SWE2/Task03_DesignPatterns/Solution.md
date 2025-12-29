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

