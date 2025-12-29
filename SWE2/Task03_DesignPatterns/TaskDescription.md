Task Description

This task was implemented using the **C++ programming language** to demonstrate
the application of common **Design Patterns** in a practical scenario.

Design Patterns Applied:

1. **Singleton Pattern**
   - Implemented using the `Logger` class.
   - Ensures that only one instance of the logger exists throughout the program.
   - Used for centralized logging of system events.

2. **Factory Pattern**
   - Implemented using the `BeverageFactory` class.
   - Responsible for creating different beverage objects (`Coffee`, `Tea`)
     without exposing the object creation logic to the client.

3. **Builder Pattern**
   - Implemented using the `BeverageBuilder` class.
   - Allows step-by-step construction of beverages with optional extras
     such as chocolate or lemon.

4. **Decorator Pattern**
   - Implemented using `BeverageDecorator` and `MilkDecorator`.
   - Adds additional functionality (milk) to an existing beverage
     without modifying its original class.

5. **Observer Pattern**
   - Implemented using the `Observer`, `Customer`, and `Cafe` classes.
   - Customers are notified whenever a beverage order is made.

 Program Flow:
- The system starts by initializing the logger using the Singleton pattern.
- Beverages are created using the Factory pattern.
- Extras are added using the Builder pattern.
- Additional features are added dynamically using the Decorator pattern.
- Customers receive notifications using the Observer pattern.

 Goal of the Task:
The goal of this task is to understand how multiple design patterns
can be combined together in a single system to create flexible,
maintainable, and extensible software architecture.
