# Microwave Oven Simulator (PIC16F877A)

This repository contains the embedded C firmware for a **Microwave Oven Simulator** designed for the **PIC16F877A** microcontroller. The project simulates real-world microwave functionalities including multiple cooking modes, temperature/time settings, and hardware control of a fan and timer.

## 🛠 Features

**Multi-Mode Operation**: Supports Micro, Grill, Convection, and Quick Start modes.
 
**User Interface**: Utilizes a 16x4 Character LCD (CLCD) for menu navigation and status display.
 
**Matrix Keypad Input**: 4x3 keypad for entering time, temperature, and controlling the oven state.

**Real-Time Clock**: Uses Timer2 interrupts to handle accurate 1-second countdowns.

**Safety Simulation**: Includes a fan control (RC2) and automatic "Time Up" alerts.

---

## 📂 Project Structure

| File | Description |
| --- | --- |
| **`main.c`** | Core state machine and system initialization. |
| **`micro_oven.c`** | Logic for cooking modes (Micro, Grill, Convection, Start).

 |
| **`matrix_keypad.c`** | Driver for 4x3 matrix keypad scanning and debouncing.

 |
| **`clcd.c`** | Driver for 16x4 Liquid Crystal Display in 4-bit mode. |
| **`isr.c`** | Interrupt Service Routine for the 1ms/1s timer countdown.

 |
| **`timers.c`** | Initialization and configuration for Timer2. |

---

## 🕹 Operation Modes

### 1. Micro Mode

**Function**: Standard heating at 900W power.
 
**Input**: User enters time (MM:SS) using the keypad.
 
**Action**: Pressing `#` starts the fan and timer.



### 2. Grill Mode
 
**Function**: Specialized grilling mode.

**Input**: Requires manual time entry.



### 3. Convection Mode
 
**Function**: Temperature-based cooking.

**Process**: User sets temperature  60-second Pre-heating  User sets time.



### 4. Start Mode (Quick Start)

**Function**: Immediate 30-second heating cycle.

**Control**: While running, pressing '4' adds 30 seconds to the remaining time.

---

## ⌨️ Controls

**Key 1-3**: Select Cooking Mode.

**Key 4**: Start/Resume or Add 30 seconds.
 
**Key 5**: Pause cooking (stops timer and fan).
 
**Key 6**: Stop/Reset to main menu.
 
**Key '*'**: Clear current input (Time/Temp).
 
**Key '#'**: Confirm/Enter.

---

## 🔧 Hardware Setup

**Microcontroller**: PIC16F877A.
**Display**: CLCD (16x4) connected to PORTD (Data) and PORTE (Control).
**Keypad**: 4x3 Matrix Keypad connected to PORTB (Columns) and PORTD (Rows). 
**Fan**: Connected to RC2.
**Oscillator**: 20MHz crystal.

---

