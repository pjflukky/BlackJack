Overview

This project implements a simplified Blackjack game on the Cypress PSoC6 microcontroller as part of the ECE 353: Embedded Systems course at the University of Wisconsin–Madison.
It demonstrates embedded programming concepts such as hardware I/O, state machines, and event-driven logic while recreating the logic of a classic card game.

🎯 Objective

The goal of this project is to apply embedded systems principles to design an interactive game using real hardware peripherals. It emphasizes:

Input handling using buttons, switches, or sensors

Output display via LEDs, LCD, or serial console

Program structure using finite state machines

Integration of randomness (card dealing) and scoring logic

🧩 Features

Simulated card dealing for player and dealer

Hit/Stand gameplay logic

Automatic win/loss determination

Display of results via console or hardware output

Modular design with separate game logic and hardware interface layers

⚙️ Hardware and Tools

Microcontroller: Cypress PSoC6 (CY8CKIT-062 or similar)

Development Environment: ModusToolbox IDE

Programming Language: C

Interfaces: GPIO (for buttons/LEDs), UART (for serial output)
