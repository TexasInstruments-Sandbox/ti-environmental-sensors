//TMP118 Example Code to allow users to read from the TMP118 temperature sensor in One-Shot Mode using a C-based program.
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

//|| Device Definitions ||\\

// Register Configurations
#define DEVICE_CONFIG_REG_ADDR 0x10  //
#define DEVICE_ADDR 0x48 //
#define DEVICE_TEMP_REG_ADDR 0x00 //

// Device Mode Options \\

// One-Shot
#define CONFIG_OS 0x10 //
// Continuous
//#define CONFIG_CONTINUOUS 0x00 //


void setup() {
  
  // put your setup code here, to run once:
  Wire.begin();
  Serial.println("TMP118 Arduino Example");
  Serial.begin(9600);

  device_init(); // initialize device
  
  delay(8); // wait 8ms for device to initialize

}

void loop() {

  // put your main code here, to run repeatedly:

  int16_t tempData = getData(DEVICE_ADDR, DEVICE_TEMP_REG_ADDR); // Pass device address and temp register address

  float celcius = tempData * 0.0078125; // convert raw data to Celsius 

  Serial.print("Temp (C): "); // optional print commands for serial output
  Serial.println(celcius);

  delay(1000);  // wait one second until next temp read

}

    // initialize device and load configuration into sensor

    void device_init(){

      Wire.beginTransmission(DEVICE_ADDR); // initiate contact with sensor

      Wire.write(DEVICE_CONFIG_REG_ADDR); // write to config register
      
      Wire.write(CONFIG_OS); // write OS mode to config register
      
      Wire.endTransmission();

    }

    // read from TMP118 temperature register and return raw data

    int16_t getData(int8_t sensorAddr, int8_t tempReg) {
      
      Wire.beginTransmission(sensorAddr);
      Wire.write(tempReg);
      Wire.endTransmission();
      Wire.requestFrom(sensorAddr, 2); // request 2 bytes from TMP118

      int16_t bytes = Wire.read() << 8; // load the MSB of raw temp data into 16-bit bytes variable
      bytes |= Wire.read(); // load remaining LSB into bytes variable

      return bytes;
      
    }
 
