
import java.util.ArrayList;
import java.util.List;

public class Taskone1 {

    // ========= Abstract Class =========
    abstract static class Vehicle {
        protected String make;
        protected String model;
        protected int year;

        public Vehicle(String make, String model, int year) {
            this.make = make;
            this.model = model;
            this.year = year;
        }

        public abstract void startEngine();
        public abstract void move();

        public String getInfo() {
            return year + " " + make + " " + model;
        }
    }

    // ========= Car Class =========
    static class Car extends Vehicle {
        private int numDoors;

        public Car(String make, String model, int year, int numDoors) {
            super(make, model, year);
            this.numDoors = numDoors;
        }

        @Override
        public void startEngine() {
            System.out.println(getInfo() + ": Car engine starts with a key or button.");
        }

        @Override
        public void move() {
            System.out.println(getInfo() + ": The car is driving on the road.");
        }

        public void openTrunk() {
            System.out.println(getInfo() + ": Trunk is now open.");
        }
    }

    // ========= Truck Class =========
    static class Truck extends Vehicle {
        private double loadCapacity;

        public Truck(String make, String model, int year, double loadCapacity) {
            super(make, model, year);
            this.loadCapacity = loadCapacity;
        }

        @Override
        public void startEngine() {
            System.out.println(getInfo() + ": Truck engine rumbles to life.");
        }

        @Override
        public void move() {
            System.out.println(getInfo() + ": The truck is hauling goods.");
        }

        public void load(double tons) {
            System.out.println(getInfo() + ": Loading " + tons + " tons (capacity " + loadCapacity + " tons).");
        }
    }

    // ========= ElectricCar Class =========
    static class ElectricCar extends Car {
        private int batteryPercentage;

        public ElectricCar(String make, String model, int year, int numDoors, int batteryPercentage) {
            super(make, model, year, numDoors);
            this.batteryPercentage = batteryPercentage;
        }

        @Override
        public void startEngine() {
            System.out.println(getInfo() + ": Silent electric start (battery " + batteryPercentage + "%).");
        }

        @Override
        public void move() {
            System.out.println(getInfo() + ": The electric car is gliding silently.");
        }

        public void charge(int amount) {
            batteryPercentage = Math.min(100, batteryPercentage + amount);
            System.out.println(getInfo() + ": Charged to " + batteryPercentage + "%.");
        }
    }

    // ========= Main Method =========
    public static void main(String[] args) {
        System.out.println("=== Car System Demo ===\n");

        List<Vehicle> garage = new ArrayList<>();

        Vehicle v1 = new Car("Toyota", "Corolla", 2018, 4);
        Vehicle v2 = new Truck("Volvo", "FH", 2015, 12.5);
        Vehicle v3 = new ElectricCar("Tesla", "Model 3", 2022, 4, 85);

        garage.add(v1);
        garage.add(v2);
        garage.add(v3);

        for (Vehicle v : garage) {
            System.out.println("Vehicle: " + v.getInfo());
            v.startEngine();
            v.move();
            System.out.println();
        }

        ((Car) v1).openTrunk();
        ((ElectricCar) v3).charge(10);

        System.out.println("\n=== End Demo ===");
    }
}
