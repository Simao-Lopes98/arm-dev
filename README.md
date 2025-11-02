# ARM Cortex M3 Bare-Metal Development Repository

A collection of resources and tools for STM32 microcontroller programming.

## Features

- STM32 firmware development
- Open-source toolchain setup
- STLink programming support

## Getting Started

### Prerequisites

Install the following tools to compile and program STM32 devices via STLink:

```bash
sudo apt install gcc-arm-none-eabi binutils-arm-none-eabi gdb-multiarch openocd stlink-tools make
```

### Build

To build use the following:
```bash
make
```
This will create the object files and the .elf file. Additionally, dependency and .map files are generated.

To flash to the MCU use the following:
```bash
make flash
```

To clear all object and elf files:
```bash
make clean
```

### Documentation

Refer to the project documentation for system clarification.

---