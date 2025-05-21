<div align="center">

<picture>
  
  <img src="https://github.com/TexasInstruments-Sandbox/ti-environmental-sensors/blob/main/docs/media/ti-logo.svg"><br/>
  
</picture>

# TI Environmental Sensors Example Code

[Introduction](#introduction) | [Devices](#devices) | [Environmental Sensors Homepage](https://www.ti.com/sensors/overview.html) | [Repo Organization](#repo-organization) | [Licensing](#licensing) | [Contributions](#contributions) | [Helpful Content](helpful-content) | [Dev Resources](dev-resources)
</div>

<img src="https://github.com/TexasInstruments-Sandbox/ti-environmental-sensors/blob/main/docs/media/environmental_sensing.jpg"><br/>

</div>

## Introduction

Environmental Sensors from Texas Instruments are specialized sensors used across the industry from Personal Electronics to Medical Devices. These sensors come in a variety of interface types such as I2C (most common), I3C (coming soon), UART, SPI, Analog, Single-Wire and more. These sensors are typically integrated in systems using MCUs to read, interpret and react to measurements read from environmental sensors.

This repository contains a collection of firmware ranging from simple Arduino sample codes to in-depth drivers to provide engineers with an easy design and implementation process.


## Devices

Below is a list of devices supported in this repo (please note this list is always evolving):


### Digital Local Temperature:
- [TMP118](https://www.ti.com/product/TMP118) ±0.1°C accurate, ultrasmall (336μm²) thin (240μm) I²C digital temperature sensor


### Relative Humidity & Temperature:

- [HDC302x](https://www.ti.com/product/HDC3020) Third Gen 0.5% RH I²C digital humidity sensor, 0.19% long-term drift, 400 nA, 4-sec response time
- [HDC2010](https://www.ti.com/product/HDC2010) Second Gen 2% RH ultra-small, low-power digital relative humidity sensor
- [HDC2021](https://www.ti.com/product/HDC2021) Second Gen 2% RH ultra-low-power digital relative humidity sensor, tape cover
- [HDC2022](https://www.ti.com/product/HDC2022) Second Gen 2% RH ultra-low-power digital relative humidity sensor, IP67 filter
- [HDC2080](https://www.ti.com/product/HDC2080) Second Gen 2% RH ultra-low-power digital relative humidity sensor, interrupt/DRDY
- [HDC1080](https://www.ti.com/product/HDC1080) First Gen 2% RH low-power digital relative humidity sensor
- [HDC1010](https://www.ti.com/product/HDC1010) First Gen ±2% low-power digital humidity and temperature sensor in WCSP


## Environmental Sensors Homepage




## Repo Organization
`Devices which currently have code examples can be found in the main /devices folder. Inside, subfolders distinguish sensors from their type (digital-local, humidity, etc.). Example code will primarily be in Arduino. Additionally, some devices may include complete Arduino driver code with appropriate header and main files. This list is always updating so check back regularly or reach out to us for a specific device!`


## Licensing
[See License](docs/media/LICENSE.md)


## Contributions 

This repo is currently not accepting contributions, however we welcome your feedback! Please send any feedback of our repo or examples [here] (insert ths github email) or [E2E](https://e2e.ti.com).


---
## Helpful Content

`Available content for Interfacing With TI's Environmental Sensors`

## Dev Resources
[TI E2E™ design support forums](https://e2e.ti.com) | [Learn about software development at TI](https://www.ti.com/design-development/software-development.html) | [Training Academies](https://www.ti.com/design-development/ti-developer-zone.html#ti-developer-zone-tab-1) | [TI Developer Zone](https://dev.ti.com/)
