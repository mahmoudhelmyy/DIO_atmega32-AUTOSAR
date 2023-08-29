# DIO Driver for AVR ATmega32 Microcontroller [AUTOSAR 4.0.3]

Welcome to the DIO Driver repository for the AVR ATmega32 Microcontroller! This driver provides an easy way to control digital input and output pins.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Getting Started](#getting-started)
  - [Installation](#installation)
  - [Usage](#usage)
- [Configuration](#configuration)
- [API Documentation](#api-documentation)
- [Version Information](#version-information)

## Introduction

The DIO (Digital Input/Output) driver is an essential component for interacting with digital pins on the AVR ATmega32 microcontroller. It provides a straightforward API to configure pin directions, write digital values, read digital values, and more.

## Features

- **Initialization:** Initialize the DIO module with the `Dio_Init()` function.
- **Pin Configuration:** Set the direction of individual pins using `Dio_SetupChannelDirection()`.
- **Pin Control:** Write digital values to pins using `Dio_WriteChannel()` and read values using `Dio_ReadChannel()`.
- **Port Control:** Control the entire port's direction and values with `Dio_SetupPortDirection()` and `Dio_WritePort()`.
- **Pin Toggle:** Toggle the value of a pin using `Dio_FlipChannel()`.
- **Version Info:** Retrieve version information of the driver with `Dio_GetVersionInfo()`.

## Getting Started

### Installation

1. Clone this repository to your local machine:
   ```bash
   git clone https://github.com/your-username/dio-driver.git
   ```
2. Include the necessary source files (Dio.c, Dio.h, etc.) in your project.
3. Update the configuration in Dio_Cfg.h to match your hardware setup.
## Usage

### 1. Initialize the DIO module:
- `Dio_Init(&Dio_Configuration);` // Initialize with your configuration

### 2. Configure pin direction:
- `Dio_SetupChannelDirection(PORTA_ID, PIN0, OUTPUT);` // Set PORTA PIN0 as an output

### 3. Write and read pin values:
- `Dio_WriteChannel(PORTB_ID, PIN5, STD_HIGH);`  // Set PORTB PIN5 high
- `Dio_LevelType pinValue = Dio_ReadChannel(PORTB_ID, PIN5);** // Read PIN5 value

### 4. Toggle a pin's value:
- `Dio_FlipChannel(PORTC_ID, PIN2);` // Toggle PORTC PIN2 value

### 5. Version Info: 
- Retrieve version information of the driver with `Dio_GetVersionInfo()`.

## Configuration
The Dio_Cfg.h file contains the pin configuration settings. Adjust these settings based on your hardware requirements.

## API Documentation [SWS]
[AUTOSAR_SWS_DIODriver.pdf](https://github.com/mahmoudhelmyy/DIO_atmega32-AUTOSAR/files/12463142/AUTOSAR_SWS_DIODriver.pdf)
