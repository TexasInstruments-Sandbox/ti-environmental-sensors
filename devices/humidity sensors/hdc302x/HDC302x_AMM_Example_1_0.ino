//HDC302x Example Code to allow users to read from the HDC302x humidity/temperature sensor using a C-based program.
//This program configures the HDC302x for Auto Measurement Mode (AMM) for 1 measurement/sec.
//This code applies to all available HDC302x sensors: HDC3020 and HDC3021/HDC3022.
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

// raw humidity Variables
uint16_t HUM_MSB;
uint16_t HUM_DEC;
uint16_t HUM_OUTPUT;

// raw temperature variables
uint16_t TEMP_MSB;
uint16_t TEMP_DEC;
uint16_t TEMP_OUTPUT;

// device and address configurations
#define DEVICE_ADDR 0x44       // ADDR pin connected to GND & ADDR1 pin conneted to GND
//#define DEVICE_ADDR 0x45       // ADDR pin connected to VDD & ADDR1 pin conneted to GND
//#define DEVICE_ADDR 0x46       // ADDR pin connected to GND & ADDR1 pin conneted to VDD
//#define DEVICE_ADDR 0x47       // ADDR pin connected to VDD & ADDR1 pin conneted to VDD

// configured for Auto Measurement Mode (1 measurement/sec)
// lowest noise, highest repeatability 
#define DEVICE_CONFIG_MSB 0x21 // 
#define DEVICE_CONFIG_LSB 0x30 //

uint8_t HDC_DATA_BUFF[4]; // data buffer to hold data from HDC Sensor

void setup() {

  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(115200);
  Serial.println("HDC302x Sample Code");

  //initialize device
  deviceInit(); // initialize HDC3x sensor with chosen config settings
  delay(25); // wait 25 ms before reading

}

void loop() {

  float humidity;
  float temp;

  requestData(); // call function for sending readout command for temp and humidity 
  
  Wire.requestFrom(DEVICE_ADDR, 6); // request 6 bytes from HDC device
  Wire.readBytes(HDC_DATA_BUFF, 6); // move 6 bytes from HDC into a temporary buffer

  temp = getTemp(HDC_DATA_BUFF);
  Serial.print("Temp (C): ");
  Serial.println(temp);

  delay(50); // 50ms delay between temp/humidity data conversions

  humidity = getHum(HDC_DATA_BUFF);
  Serial.print("Humidity (RH): ");
  Serial.print(humidity);
  Serial.println("%");

  delay(1000); // wait 1s before reading next measurement

}

float getTemp(uint8_t humBuff[]) {

  float tempConv;
  float celsius;

  TEMP_MSB = humBuff[0] << 8 | humBuff[1]; // shift 8 bits off data in first array index to get MSB, then OR with LSB
  tempConv = (float)(TEMP_MSB);
  celsius = ((tempConv / 65535) * 175) - 45; // calculate celcius using formula in datasheet
  
  return celsius; 

}

float getHum(uint8_t humBuff[]){

  float humConv;
  float humidity;

  HUM_MSB = (humBuff[3] << 8) | humBuff[4]; // shift 8 bits off data in first array index to get MSB, then OR with LSB
  humConv = (float)(HUM_MSB);
  humidity = (humConv / 65535) * 100; // calculate celcius using formula in datasheet

  return humidity;

}

// helper function for initializing HDC3x device in appropriate measuring mode.

void deviceInit() {

  // send device command for highest repeatability 
  Wire.beginTransmission(DEVICE_ADDR);
  Wire.write(DEVICE_CONFIG_MSB); // send MSB of command
  Wire.write(DEVICE_CONFIG_LSB); // send LSB of command
  Wire.endTransmission();

}

// helper function for requesting data when in Auto Measurement Mode

void requestData() {

  Wire.beginTransmission(DEVICE_ADDR); // begin communication with HDC3x
  Wire.write(0xE0); // send MSB of read command
  Wire.write(0x00); // send LSB of read command
  Wire.endTransmission();

}