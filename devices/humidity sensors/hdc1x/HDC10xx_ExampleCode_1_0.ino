//HDC1x Example Code to allow users to read from the HDC1x family of humidity/temperature sensors using a C-based program.
//This code applies to all available HDC1x sensors: HDC1000 (obsolete), HDC1010 and HDC1080.
//Author: Harry Gill
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

//|| Device Definitions ||\\

// register Configurations
#define CONFIG_REG_ADDR 0x02 //
#define MEASUREMENT_CONFIG_VALUE 0x10 // sets bit in config register to read both temperature and humidity 
#define DEVICE_ADDR 0x40 // fixed I2C address

#define DEVICE_TEMP_REG_ADDR 0x00 //
#define DEVICE_RH_REG_ADDR 0x01 //

void setup() {

  // put your setup code here, to run once:
  Wire.begin();
  Serial.println("HDC1x Arduino Example");
  Serial.begin(115200);

  device_init(); // initialize HDC1x

  delay(20); // wait 20 ms for configurations to load

}

void loop() {

  // put your main code here, to run repeatedly:
  
  Wire.beginTransmission(DEVICE_ADDR); // initialize communication for starting measurement

  /* 
    Since Temp and RH are measured sequentially, they are loaded into the same register
    eliminating the need to read from humidity register separately
  */

  Wire.write(0x00); // trigger device measurements

  Wire.endTransmission();
 
  delay(20); // gives device time to start measurements
  
  float temp, hum; // variables for Temp/Humidity  
  
  getMeasurements(temp, hum);
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.println(" °C");
  Serial.print("Relative Humidity: ");
  Serial.print(hum);
  Serial.println(" %");

  delay(1000); // wait one second until next read operation 

}


// function for reading and converting Temp/Humidity data from registers

void getMeasurements(float &temp, float &hum) {

  Wire.requestFrom(DEVICE_ADDR, 4); // requesting 4 bytes from device

  if (Wire.available() == 4) { // once 4 bytes are received, store it in appropriate variables  

    /* 
      Stores raw temperature and humidity data 
      Reads/stores first byte (MSB), then reads/stores second byte
      Combines each pair of bytes into a 16-bit integer
    */       
    uint16_t tempBytes = (Wire.read() << 8) | Wire.read();
    uint16_t humBytes = (Wire.read() << 8) | Wire.read();

    temp = (tempBytes / 65536.0) * 165.0 - 40.0; // equation for Temperature Output in Celsius

    hum = (humBytes / 65536.0) * 100.0; // equation for Humidity Output

  }
}

// helper function for initializing HDC1x

void device_init() {

  Wire.beginTransmission(DEVICE_ADDR); // initiate communication with sensor

  Wire.write(CONFIG_REG_ADDR); // point to config register
      
  Wire.write(MEASUREMENT_CONFIG_VALUE); // write 8-bit configuration setting to config register (MSB)

  Wire.write(0x00);  // write 8 0s to Reserved bits (LSB)
      
  Wire.endTransmission();

  delay(20);

}

