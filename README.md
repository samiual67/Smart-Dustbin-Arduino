<div align="center">

# Touchless Smart Dustbin with Dual-Ultrasonic Level Monitoring

**An Automated, Hygienic Waste Disposal & Real-Time Overflow Alert System Built on Arduino UNO**

[![Platform](https://img.shields.io/badge/Platform-Arduino%20UNO-00979D?style=for-the-badge&logo=arduino&logoColor=white)](https://www.arduino.cc/)
[![Language](https://img.shields.io/badge/Language-C%2B%2B%20%2F%20Arduino-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)](https://isocpp.org/)
[![Sensors](https://img.shields.io/badge/Sensors-Dual%20HC--SR04-1E3A8A?style=for-the-badge)](#hardware-architecture--bill-of-materials)
[![Actuator](https://img.shields.io/badge/Actuator-SG90%20Servo-D97706?style=for-the-badge)](#hardware-architecture--bill-of-materials)

*Department of Computer Science & Engineering (CSE) — Pundra University of Science & Technology, Bogura*

</div>

---

## Overview

Conventional waste bins require physical hand contact to open their lids and provide no feedback when full, leading to cross-contamination hazards and unnoticed garbage overflow. This project implements a cost-effective **Touchless Smart Dustbin** powered by an **Arduino UNO (ATmega328P)** microcontroller.

### Key Capabilities
- **Hands-Free Proximity Actuation:** An exterior front-mounted **HC-SR04** ultrasonic sensor detects user hand movement within `20 cm` and commands an **SG90 micro servo motor** to lift the lid (`90°`) for `3 seconds`.
- **Real-Time Internal Fill-Level Monitoring:** A secondary downward-facing **HC-SR04** sensor mounted underneath the lid continuously tracks garbage accumulation.
- **Dual Visual & Acoustic Overflow Alert:** Once internal waste reaches within `8 cm` of the lid, the system illuminates a current-limited **Red LED** (`330 Ω`) and sounds a `1000 Hz` **Active Buzzer** alarm.
- **Fail-Open Usability:** Automated lid opening remains active even during a *Bin-Full* alert so users are never forced to leave waste outside the container.
- **Safe Power Isolation:** Powered by a rechargeable battery pack with a dedicated manual **SPST toggle switch** for safe emptying and maintenance.

---

## Hardware Architecture & Bill of Materials

| SL | Component | Specification | Qty | Functional Role |
| :-: | :--- | :--- | :-: | :--- |
| 01 | **Arduino UNO R3** | ATmega328P, 5V Logic, 16 MHz | 1 | Central controller for ToF ranging & PWM control |
| 02 | **Ultrasonic Sensor 1 (Outer)** | HC-SR04 (5V, 40 kHz, 2–400 cm) | 1 | Front-mounted hand proximity detection (`≤ 20 cm`) |
| 03 | **Ultrasonic Sensor 2 (Inner)** | HC-SR04 (5V, 40 kHz, 2–400 cm) | 1 | Lid-mounted internal waste level sensing (`≤ 8 cm`) |
| 04 | **Micro Servo Motor** | Tower Pro SG90 (4.8–6V, 180° PWM) | 1 | Actuates mechanical linkage rod to open/close lid |
| 05 | **Red Indicator LED** | 5mm Diffused Red (`Vf ≈ 2.0V`) | 1 | Visual warning indicator when bin is full |
| 06 | **Active Buzzer** | 5V DC Piezo/Magnetic Buzzer | 1 | Emits `1000 Hz` audible alarm when bin is full |
| 07 | **Resistor** | `330 Ω` (±5%, 1/4W Carbon Film) | 1 | Limits Red LED current to `~9.1 mA` |
| 08 | **Battery & Switch** | 4V–6V Rechargeable Battery + SPST Switch | 1 | Portable power supply with manual cutoff |

---

## Pin Configuration Matrix

| Peripheral Module | Module Terminal | Arduino UNO Pin | Connection Notes |
| :--- | :--- | :---: | :--- |
| **SG90 Servo Motor** | Signal (Orange) / VCC (Red) / GND (Brown) | `D5 (PWM)` / `+5V` / `GND` | `0°` = Closed, `90°` = Open |
| **Outer HC-SR04 (Hand)** | `Trig` / `Echo` / `VCC` / `GND` | `D6` / `D7` / `+5V` / `GND` | Front panel proximity sensor |
| **Inner HC-SR04 (Level)** | `Trig` / `Echo` / `VCC` / `GND` | `D9` / `D10` / `+5V` / `GND` | Downward lid-mounted sensor |
| **Red LED Indicator** | Anode (`+`) via `330 Ω` / Cathode (`-`) | `D11` / `GND` | Active-HIGH on full bin |
| **Active Buzzer** | Positive (Yellow) / Negative (Black) | `D12` / `GND` | `1000 Hz` tone on full bin |
| **Power Supply** | Battery (`+`) via Switch / Battery (`-`) | `VIN (Barrel)` / `GND` | Switch OFF before cleaning |

---

## Working Principle

1. **Acoustic Time-of-Flight (ToF) Ranging:**
   The Arduino sends a `10 µs` HIGH trigger pulse to each HC-SR04 sensor and measures the round-trip echo pulse duration (`Δt`) with a `30 ms` timeout:
   ```text
   Distance (cm) = (Duration_us × 0.034) / 2
   ```
2. **Fill-Level Evaluation:**
   If `0 < binLevel <= 8 cm`, pin `D11` drives the Red LED HIGH and pin `D12` outputs a `1000 Hz` tone. Once emptied (`binLevel > 8 cm`), both alerts turn off automatically.
3. **Lid Actuation:**
   If `0 < handDist <= 20 cm`, the SG90 servo on pin `D5` rotates to `90°` for `3000 ms` before returning to `0°`.

---

## Repository Structure

```text
Smart-Dustbin-Arduino/
├── Smart_Dustbin.ino                             # Well-commented Arduino C++ source code
├── README.md                                     # Project documentation
├── circuit_diagram.png                           # Pin-to-pin hardware wiring schematic
├── block_diagram.png                             # System functional block diagram
├── prototype_showcase.png                        # Real hardware prototype demonstration states
├── Smart_Dustbin_Project_Report_PUB_Final.docx   # Complete academic project report
└── live_demo_video.mp4                           # Original hardware working prototype video
```

---

## Getting Started & Uploading Code

1. Clone this repository:
   ```bash
   git clone https://github.com/samiual67/Smart-Dustbin-Arduino.git
   ```
2. Open `Smart_Dustbin.ino` in **Arduino IDE**.
3. Select **Tools → Board → Arduino UNO** and choose your active **COM Port**.
4. Click **Upload (`→`)** to flash the firmware onto the board.

---

## Team & Academic Context

- **Institution:** Pundra University of Science & Technology, Bogura – 5800, Bangladesh
- **Department:** Computer Science & Engineering (CSE) — B.Sc. 6th Semester
- **Supervisor:** M. Z. I. Juwel, Lecturer, Department of CSE
- **Team Members & Roles:**
  - **Md. Samiual Mia** (ID: 0322410105101001) — Firmware Lead: Coding, Debugging & Sensor Calibration
  - **Md. Maruf Hasan** (ID: 0322320105101061) — Hardware Lead: Circuit Design, Wiring, Assembly & Testing
  - **Mst. Tamanna** (ID: 0322310205101053) — Documentation Lead: Project Report, Schematics & Presentation
