# Description
Single Responsibility Principle (SRP)

The Car class is responsible only for car-related data and behavior.
The CarInfoPrinter class is responsible only for displaying car information, separating logic from presentation.
Open/Closed Principle (OCP)

The system is open for extension but closed for modification.
New car types can be added by creating new classes that inherit from Car without changing existing code.
Liskov Substitution Principle (LSP)

Objects of derived classes (ElectricCar, GasCar, HybridCar) can be used wherever a Car object is expected.
The startCarEngine() function works correctly with any Car type.
Interface Segregation Principle (ISP)

The IRechargeable interface is used only by cars that support recharging (electric and hybrid cars).
Gas cars are not forced to implement unnecessary methods.
Dependency Inversion Principle (DIP)

High-level functions depend on abstractions rather than concrete implementations.
The startCarEngine() function depends on the abstract Car class, not on specific car types.
Program Flow:

Different types of cars are created based on their behavior.
Car information is printed using a separate class.
Engines are started polymorphically using a base class reference.
Recharge functionality is applied only to applicable car types.
