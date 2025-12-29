#include <iostream>
#include <vector>
#include <string>
using namespace std;


class Logger {
private:
    static Logger* instance;
    Logger() {}   

public:
    static Logger* getInstance() {
        if (!instance)
            instance = new Logger();
        return instance;
    }

    void log(const string& msg) {
        cout << "[LOG]: " << msg << endl;
    }
};

Logger* Logger::instance = NULL;


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
        return NULL;
    }
};

class BeverageBuilder {
protected:
    Beverage* beverage;
    string extra;

public:
    BeverageBuilder(Beverage* b) : beverage(b) {}

    BeverageBuilder* addExtra(const string& e) {
        extra = e;
        return this;
    }

    Beverage* build() {
        if (extra != "")
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

    string getName() {
        return beverage->getName() + " + Milk";
    }

    double cost() {
        return beverage->cost() + 1;
    }
};

class Observer {
public:
    virtual void update(const string& message) = 0;
};

class Customer : public Observer {
    string name;

public:
    Customer(string n) : name(n) {}

    void update(const string& message) {
        cout << name << " received notification: " << message << endl;
    }
};

class Cafe {
    vector<Observer*> customers;

public:
    void attach(Observer* c) {
        customers.push_back(c);
    }

    void notify(const string& message) {
        for (int i = 0; i < customers.size(); i++) {
            customers[i]->update(message);
        }
    }
};


int main() {

   
    Logger::getInstance()->log("Cafe system started");

    
    Cafe cafe;
    Customer c1("ahmed"), c2("hoda");
    cafe.attach(&c1);
    cafe.attach(&c2);

    
    Beverage* base1 = BeverageFactory::createBeverage("coffee");
    Beverage* base2 = BeverageFactory::createBeverage("tea");

    
    BeverageBuilder builder1(base1);
    Beverage* bev1 = builder1.addExtra("Chocolate")->build();

    BeverageBuilder builder2(base2);
    Beverage* bev2 = builder2.addExtra("Lemon")->build();

    
    Beverage* milkCoffee = new MilkDecorator(bev1);

    cafe.notify(milkCoffee->getName());
    cafe.notify(bev2->getName());

    Logger::getInstance()->log("Cafe system ended");

    
    delete base1;
    delete base2;
    delete milkCoffee;

    return 0;
}
