//HDC2x Example Code to allow users to read from the HDC2x humidity/temperature sensor using a C-based program.
//This program configures the HDC2x for Trigger on Demand Mode.
//This code applies to all available HDC2x sensors: HDC2010, HDC2021/HDC2022 and HDC2080.
//Author: Harry Gill
//Texas Instruments
//v1.0

/*

Copyright <2025> <Texas Instruments - http://www.ti.com/>

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS “AS IS” AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY 
AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, 
OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND 
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED 
OF THE POSSIBILITY OF SUCH DAMAGE.

*/

 #include <Wire.h>

// |Device Definitions| \\

// HDC2x address configuration
#define DEVICE_ADDR 0x40 // ADDR pin Connected to GND

// register addresses
#define CONFIG_REG_ADDR 0x0E // Config Register
#define MEASUREMENT_CONFIG_REG_ADDR 0x0F // Measurement Config Register

// register configurations
#define CONFIG_REG_VAL 0x00 // Auto Measurement Mode for 0.2 Hz (1 sample/ 5 seconds)
#define MEASUREMENT_CONFIG_REG_VAL 0x00 // Humidity + Temperature @ 14-bit resolution

//#define DEVICE_TEMP_REG_ADDR_MSB 0x01 //
#define DEVICE_TEMP_REG_ADDR_LSB 0x0 //

//#define DEVICE_RH_REG_ADDR_MSB 0x03 //
#define DEVICE_RH_REG_ADDR_LSB 0x02 //

void setup() {
  
  // put your setup code here, to run once:
  Wire.begin();
  Serial.println("HDC2x Arduino Example");
  Serial.begin(115200);

  //initialize device
  writeReg(CONFIG_REG_ADDR, CONFIG_REG_VAL); //set device to Trigger on Demand mode
  writeReg(MEASUREMENT_CONFIG_REG_ADDR, MEASUREMENT_CONFIG_REG_VAL); //set device to output temperature and humidity
  
  delay(100); // wait 100ms for device to initialize

  writeReg(MEASUREMENT_CONFIG_REG_ADDR, 0x01); // trigger measurements 
  delay(20); // wait 20ms for data

}

void loop() {

  // put your main code here, to run repeatedly:

  // pass device and temp/hum register addresses to get measurements
  uint16_t tempData = readMeasurements(DEVICE_TEMP_REG_ADDR_LSB); // grab raw temperature readings
  uint16_t humData = readMeasurements(DEVICE_RH_REG_ADDR_LSB); // grab raw humidity readings

  float celcius = (tempData / 65536.0) * 165.0 - 40.0; // equation for temperature output
  float hum = (humData / 65536.0) * 100.0; // equation for humidity output

  // print temperature
  Serial.print("Temp: ");
  Serial.print(celcius);
  Serial.println(" °C");

  // print humidity 
  Serial.print("Relative Humidity: ");
  Serial.print(hum);
  Serial.println(" %");

  delay(1000); // wait one second until next read operation 

}

    // function for writing to device registers

    void writeReg(uint8_t reg, uint8_t regVal){

      Wire.beginTransmission(DEVICE_ADDR);
      Wire.write(reg);
      Wire.write(regVal);

      Wire.endTransmission();

    }

    // function for reading measurements from registers

    uint16_t readMeasurements(uint8_t reg){
      
      Wire.beginTransmission(DEVICE_ADDR);
      Wire.write(reg);
      Wire.endTransmission(false);
      Wire.requestFrom(DEVICE_ADDR, 2);

      uint8_t lsb = Wire.read();
      uint8_t msb = Wire.read();

      return ((uint16_t) msb << 8) | lsb; // adds MSB of data to an empty 16-bit variable, shifts 8 bits left then "or" with LSB data

    }

    // general function for reading device measurements 

    uint8_t readReg(uint8_t reg){

      Wire.beginTransmission(DEVICE_ADDR);
      Wire.write(reg);
      Wire.endTransmission(false);
      Wire.requestFrom(DEVICE_ADDR, 1);

      return Wire.read();

    }
