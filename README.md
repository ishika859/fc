# STM32F405 Flight Controller

Custom flight controller board based on the STM32F405RGT6 ARM Cortex-M4 microcontroller.

The board is designed as a compact flight-control platform with an onboard IMU, barometric sensor, four motor outputs, USB-C connectivity, removable storage, multiple serial interfaces and battery monitoring.

This repository contains the KiCad schematic, PCB layout, manufacturing files, bill of materials, firmware starter code and project documentation.

## Why This Project?

The goal of this project was to design a complete flight controller from the schematic level instead of only using an existing development board.

The work included selecting the controller and sensors, designing the power sections, assigning footprints, placing components, routing the PCB, checking the board in KiCad and preparing the manufacturing files.

The project also provides a useful platform for learning how sensor data, motor outputs, communication ports and power monitoring work together in an embedded flight-control system.

## Hardware

| Feature | Description |
|---|---|
| **Microcontroller** | STM32F405RGT6 ARM Cortex-M4, 168 MHz, 1 MB Flash |
| **Inertial sensor** | TDK InvenSense ICM-42688-P 6-axis IMU |
| **Barometer** | Bosch BMP280 pressure sensor |
| **Motor outputs** | Four outputs for M1, M2, M3 and M4 ESC connections |
| **Battery input** | 2S to 6S battery connector with voltage sensing |
| **Current sensing** | Analog current-monitor input |
| **Power regulation** | AP63205WU buck regulator and AP2112K-3.3 LDO |
| **USB connectivity** | USB-C connector with USB ESD protection |
| **Removable storage** | microSD card connector |
| **Serial interfaces** | UART1 receiver, UART3 GPS and I2C, UART4 VTX, UART6 auxiliary port |
| **Debug interface** | 1.27 mm SWD connector |
| **User connections** | LED strip output and buzzer connector |
| **PCB** | Two-layer KiCad PCB layout |

## Main Connections

The ICM-42688-P is connected to the STM32 through SPI. The BMP280 uses the I2C bus shared with the GPS expansion connector.

The four motor nets are connected as follows:

| Motor | MCU pin |
|---|---|
| M1 | PB0 |
| M2 | PB1 |
| M3 | PA3 |
| M4 | PA2 |

The board also includes ADC inputs for battery voltage and current measurement, plus status LEDs and a buzzer driver.

## Project Images

### 3D PCB Design

The board can be inspected in KiCad's 3D Viewer to check component placement, connector access and the overall mechanical layout.

<img width="717" height="425" alt="image" src="https://github.com/user-attachments/assets/19a9d4fd-f281-4e5d-8cd3-122d5c19f6d1" />

<img width="888" height="517" alt="image" src="https://github.com/user-attachments/assets/3bf5c479-3502-4e75-8b5a-8c409080c1df" />

### PCB Layout and Routing

<img width="914" height="550" alt="image" src="https://github.com/user-attachments/assets/592a1b2f-2d73-4904-bb98-e4601c023420" />

### Circuit Schematic

<img width="1084" height="757" alt="image" src="https://github.com/user-attachments/assets/aedf7f2f-df74-4777-99bd-ea435b37ffe6" />

## Bill of Materials

The component list with purchase links and estimated prices is available in [`bom.csv`](bom.csv).
<img width="805" height="516" alt="image" src="https://github.com/user-attachments/assets/48739911-8749-48a6-ba53-b7846ad71ba9" />

The current estimated component subtotal is approximately **$31.27 USD** before shipping and taxes. Prices are indicative and can change with supplier stock and order quantity.

Important main parts include:

| Component | Quantity | Description |
|---|---:|---|
| STM32F405RGT6 | 1 | Main flight-controller microcontroller |
| ICM-42688-P | 1 | Accelerometer and gyroscope |
| BMP280 | 1 | Barometric pressure sensor |
| AP63205WU | 1 | Buck regulator |
| AP2112K-3.3 | 1 | 3.3 V linear regulator |
| USBLC6-2SC6 | 1 | USB ESD protection device |
| USB-C receptacle | 1 | USB connection |
| microSD connector | 1 | Flight log storage interface |

## Firmware

The firmware starter is located in [`firmware/`](firmware/).

The initial firmware structure is based on the STM32F405 pin mapping from the schematic and includes the basic peripheral mapping for:

- SPI1 for the ICM-42688-P
- I2C1 for the BMP280
- Four motor output connections
- Battery and current ADC inputs
- UART1, UART3, UART4 and UART6
- USB detect, LEDs and buzzer control

The starter firmware keeps all motor outputs disabled. It is intended for bench testing and peripheral bring-up only. A complete flight firmware still requires sensor initialization, calibration, receiver protocol support, attitude estimation, PID control, motor timing, arming logic and failsafe handling.

Always test firmware with propellers removed until the motor mapping, sensor orientation and failsafe behavior have been verified.

## Repository Structure

```text
hardware/
  flight_controller.kicad_sch
  flight_controller.kicad_pcb

firmware/
  main.c
  README.md

manufacturing/
  gerbers/
  gerbers.zip

documentation/
  project journal and design notes

bom.csv
README.md
```

## Design Verification

The current PCB has been checked in KiCad and the present board revision reports no remaining DRC warnings or errors.

The schematic and PCB should still be reviewed against the final assembled components before ordering. Particular attention should be given to the USB-C shell pads, connector mounting pads, regulator layout, sensor orientation and the motor-output order.

## Manufacturing

The `manufacturing/gerbers/` folder contains the exported Gerber and drill files needed to order the PCB.

The manufacturing package includes:

- Front and back copper
- Front and back solder mask
- Front and back silkscreen
- Paste layers where required
- Edge cuts board outline
- Plated and non-plated drill files
- Gerber job file

Before ordering, upload the Gerber archive to the chosen PCB manufacturer and confirm that the board outline, layer count, drill files and solder-mask openings are detected correctly.

## Project Status

The hardware design, schematic, PCB layout, BOM and manufacturing outputs are complete for the current revision.

The next stage is hardware bring-up. This includes checking the power rails, programming through SWD, confirming USB communication, reading the IMU and barometer, testing the ADC inputs and validating each motor output independently.

## License

Add the project license here before publishing the repository.
