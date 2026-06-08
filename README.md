# C++ Text-Based RPG

A simple, console-based Role-Playing Game written in C++. I built this project primarily as a hands-on way to practice and solidify my understanding of Object-Oriented Programming (OOP) concepts in C++.

## 🎮 Gameplay Overview
In this game, you step into the shoes of a hero aiming to reach level 20 to win. Along the way, you will encounter random monsters and must decide whether to stand your ground or attempt an escape.

* **Start your journey:** Enter your name and begin with 10 health and 0 gold.
* **Face randomized enemies:** Encounter Slimes, Orcs, or Dragons, each with different health, damage, and gold drops.
* **Combat choices:** Choose to `(F)ight` to deal damage, or try to `(R)un` (which has a 50% chance of failing, leaving you open to attack).
* **Level up:** Defeating enemies grants you gold, increases your level, and boosts your attack damage. 
* **Permadeath:** If your health hits 0, the game is over and your gold is lost!

## 💻 OOP Concepts Demonstrated
Since the main goal of this project was learning, the architecture relies heavily on core C++ OOP principles:

* **Inheritance:** A base `Creature` class handles shared properties (name, symbol, health, damage, gold), while `Player` and `Monster` inherit and expand upon these features.
* **Encapsulation:** Class variables are protected or private, accessed safely via public getter methods (e.g., `getHealth()`, `getName()`).
* **Static Members:** The `Monster` class utilizes a `static inline` array to store a database of monster stats efficiently.
* **Enums:** Used for clean and readable monster type management.

## 🚀 How to Run
To compile and run this game locally, you will need a C++ compiler (like GCC) that supports C++17 or later. 

1. Clone the repository to your local machine.
2. Ensure both `main.cpp` and `random.h` (and any other dependencies) are in the same directory.
3. Compile via your terminal:
   ```bash
   g++ main.cpp -o text_rpg -std=c++17
