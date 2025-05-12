# PBL-Intro2IoT
This document describes a Project-Based Learning (PBL) activity for the Introduction to IoT course offered by Dawson College’s Electrical Engineering Technology Department.

# Number Memory Game

A fast-paced memory game for Arduino in which players must remember a seven-digit sequence and determine whether a "KEY" was included. "IN" is indicated by one button and "OUT" by the other.  For the right answer, a green LED and the words "Correct!" appeared.  For incorrect answers, a red LED will illuminate and the buzzer will sound twice, displaying "Wrong!"  The twist?  Every round gets faster!

<p align="center">
  <img src_NumberMemoryGame_FinalVersion="docs/PBL Circuit Diagram.jpg" width="480" alt="Number Memory Game">
</p>




---

## ✨ Features 

| ✓ | Description |
|---|-------------|
| **7-digit sequence challenge** | Displays a random 7-digit number the player must memorize. |
| **Binary decision buttons** | Player chooses if a digit was part of the sequence using “IN” or “OUT” buttons. |
| **Dynamic difficulty** | Display time decreases by 100ms after each correct round (minimum 400ms). |
| **Single RGB LED feedback** | One RGB LED module lights **green** for correct answers and **red** for incorrect ones. |
| **Sound alert** | A passive buzzer sounds twice for wrong answers using `tone()`. |
| **Score tracking** | LCD shows current score and stores the session's high score. |
| **Module-based simplicity** | Uses plug-and-play modules (LCD, buttons, buzzer, RGB LED) to simplify wiring—no resistors needed. |
| **GNU-licensed** | Open-source under GNU GPL, with code, Tinkercad schematic, and documentation included. |

---

## 🛠 Bill of Materials 

| Qty | Part | Notes |
|-----|------|-------|
| 1 | **Arduino Uno** | Core controller for the game logic. |
| 1 | **16x2 LCD (HD44780) Module** | Includes header pins; V0 (contrast) connected through an **820 Ω** resistor to GND. |
| 1 | **Passive buzzer module** | Connected to D5. Requires `tone()` function for sound generation. |
| 1 | **RGB LED module** (common cathode) | Red → D2, Green → D6. Built-in resistors—no external resistors required. |
| 2 | **Push button modules** | One for “IN” (D3), one for “OUT” (D4). Connected with `INPUT_PULLUP` logic. |
| — | **Jumper wires & breadboard** | Standard half-size breadboard is sufficient. |

---

## 🔌 Circuit
