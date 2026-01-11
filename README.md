EBP (Event Based Project) - Multi-Platform Embedded Framework
EBP is a high-performance, modular embedded framework designed with a Hardware Abstraction Layer (HAL). It allows the same application logic to run seamlessly across diverse environments, from high-level Linux systems to bare-metal microcontrollers like the STM32 series.

🏗 Software Architecture & Event-Driven Design
The core philosophy of EBP is the decoupling of Event Producers (Hardware/Interrupts) and Event Consumers (Business Logic).

## 1. The Event Loop & Workflow
As seen in the architectural diagrams, the system follows a strict lifecycle:

◈ **Initialization:** The (System Setup) validates all peripherals. If a critical failure occurs, the (Restart) logic ensures system reliability.

◈ **The Event List (Queue):** A centralized buffer that collects events from various sources.

◈ **The Dispatcher:** The main loop checks (Is there an event?). If true, it pops the event and triggers (Process Event).

## 2. High Extensibility: Adding New Features
The architecture is designed for "Plug & Play" development:

Adding a Producer: To add a new sensor or input (e.g., a Proximity Sensor), you simply create a new hardware interrupt that calls EventEkle(NEW_EVENT_TYPE).

Adding a Consumer: Since the logic is centralized in the (Process Event) block, developers can add new case handlers without touching the low-level drivers. This isolation prevents "spaghetti code" and reduces regression bugs.

💻 Cross-Platform Compatibility (HAL)
One of EBP's strongest features is its ability to run on multiple platforms using a unified codebase.

Validated Platforms:

◆ **Linux (Ubuntu):** Compiled with gcc. Ideal for high-level simulation, logic testing, and CI/CD integration.

◆ **STM32F407:** High-performance ARM Cortex-M4 execution.

◆ **STM32L476RGTX:** Ultra-low-power optimization on the specific target board.

### Why this matters for the future:
Hardware Independence: If a specific MCU becomes unavailable due to supply chain issues, the project can be ported to a new chip by only rewriting the HAL layer.

Parallel Development: Software engineers can develop business logic on Linux simulators while hardware engineers finalize the PCB design.

Scalability: The architecture supports adding complex managers (like the Working Mode Manager or Temperature Manager) without increasing the complexity of the core kernel.

## 🔌 Hardware Unit Overview
The hardware design is robust, supporting industrial standards and various communication protocols.

◆ **Communication:** Dual UART (Debug & Update), CANBus, and I2C.
<br>

◆ **I/O Expansion:** Uses **TCA9555** for high-density GPIO management and **TCA8418** for a 4x4 Matrix Keypad.
<br>

◆ **Time & Environment:** **M41T11 RTC** for real-time tracking (battery-backed) and **LM75B** for precise temperature monitoring.
<br>

◆ **Power Management:** Wide input range (9-36V) regulated down to 3.3V and 5V to ensure stability in industrial environments.

## 🛠 Software Modules (Controllers)
| Module | Description |
| :--- | :--- |
| **BIT (Built-In Test)** | Monitors system health and manages the Watchdog Timer (WDT). |
| **CommCan Manager** | Handles high-level protocol parsing for CANBus packets. |
| **Working Mode Manager** | Switches system states (e.g., Maintenance, Update, Error modes). |
| **Logger** | Provides persistent and real-time logging for both field diagnostics and development. |

🚀 Getting Started
Prerequisites
For Linux: gcc, cmake, make

For STM32: arm-none-eabi-gcc, STM32CubeIDE or Keil.

## 🛠 Compilation & Build Process

The project is structured to be easily built across different IDEs and environments. Under the project root directory, you will find dedicated project folders for both embedded and desktop environments.

◆ **Project Structure:** Locate the `CubeMX` folder for STM32 targets and the `Linux-Eclipse` folder for Ubuntu/PC development.
<br>

◆ **Easy Build:** Simply open the respective project in **Eclipse** (or STM32CubeIDE). Use the standard **Build Button** (hammer icon) to compile the entire project automatically.
<br>

◆ **Multi-Platform Ready:** The build system is pre-configured to handle the Hardware Abstraction Layer (HAL) automatically based on the selected project environment.


