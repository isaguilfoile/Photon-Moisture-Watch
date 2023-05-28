# Photon Moisture Watch

Project created for operation on Particle Photon development board. 
Compiled and flashed using Particle Workbench VSCode Extension. 
Created to monitor plant soil moisture using SparkFun Soil Moisture Sensor. 
The moisture level of the soil is displayed on a 2x8 character I2C LCD display, as well as the time since the last water. 
To avoid corrosion in the soil moisture sensor, AD conversions are only completed once per 10 minutes, and the sensor receives no power otherwise. 
In future versions, alerts will be sent using IoT capabilities of Photon board to alert owner when the plant has gone too long without water.


## Table of Contents

- Requirements
    - Required Hardware
    - Required Software
- Installation
- Configuration


## Requirements

### Required Hardware

- [SparkFun Soil Moisture Sensor](https://www.sparkfun.com/products/13322)
- [I2C Small LCD Board](https://international.switch-science.com/catalog/1405/)
- [Particle Photon Developement Board](https://www.adafruit.com/product/2721)


### Required Software

- [Visual Studio Code](https://code.visualstudio.com/download)
- [Particle Workbench Extension](https://www.particle.io/workbench/)


## Installation

1. Install and set up Particle Workbench VSCode extension
2. Create new project
3. Copy **Photon_Moisture_Watch.ino** from repository and place in /src folder in project directory
4. Copy all files in **Photon_Moisture_Watch/lib** from repository and place in /lib folder in project directory
5. Compile project to ensure proper installation
6. Create circuit as shown below (see below)
7. Water your plants!

![circuit](https://github.com/isaguilfoile/Photon_Moisture_Watch/assets/118629718/fd822386-a774-4344-a520-9dfce3a240a3)


## Project created by:

Isaiah Guilfoile 2023


### Copyright Statement

© 2023 Isaiah Guilfoile
