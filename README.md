# PBL-Intro2IoT
This document describes a Project-Based Learning (PBL) activity for the Introduction to IoT course offered by Dawson College’s Electrical Engineering Technology Department.

# Number Memory Game

A fast-paced memory game for Arduino in which players must remember a seven-digit sequence and determine whether a "KEY" was included. "IN" is indicated by one button and "OUT" by the other.  For the right answer, a green LED and the words "Correct!" appeared.  For incorrect answers, a red LED will illuminate and the buzzer will sound twice, displaying "Wrong!"  The twist?  Every round gets faster!





---

## ✨ Features
| ✓ | Description |
|---|-------------|
| **7-digit sequence challenge** | Displays a random 7-digit number the player must memorize. |
| **Binary decision buttons** | Player chooses if a digit was part of the sequence using “IN” or “OUT” buttons. |
| **Dynamic difficulty** | Display time decreases by 100ms after each correct round (minimum 400ms). |
| **Visual & audio feedback** | Green LED signals correct input; red LED and buzzer indicate incorrect input. |
| **Score tracking** | LCD shows current score and stores the session's high score. |
| **Minimal components** | Only uses Arduino Uno, 16x2 LCD, two pushbuttons, buzzer, and RGB LED. |
| **GNU-licensed** | Open-source under GNU GPL, with code, Tinkercad schematic, and documentation included. |

---

## 🛠 Bill of Materials 

| Qty | Part | Notes |
|-----|------|-------|
| 1 | **Arduino Uno** | Core controller for the game logic. |
| 1 | **16x2 LCD (HD44780)** | For displaying the sequence, key, messages, and scores. |
| 1 | **Active piezo buzzer** | + → D5, − → GND. Emits sound on wrong input. |
| 1 | **Common cathode RGB LED** | **Green (→ D6)**, **Red (→ D2)**, cathode → GND. anode → VCC. |
| 2 | **Momentary push-buttons** | One for “IN” (D3), one for “OUT” (D4). Each connected to GND and VCC. |
| 1 | **820 Ω resistor** | Connected to LCD V0 for fixed contrast control. |
| — | **Jumper wires & breadboard** | Standard half-size breadboard is sufficient. |

---

## 🔌 Circuit
