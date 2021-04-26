# BMX055 library 

This is a WIP library for BMX055, currently supporting only accelerometer in Arduino.

*Tested on:* ESP32-devkit-v1


# TODO List

- [x] Support for Accelerometer:
  - [x] Configuration
  - [x] Raw Data retrieval
  - [x] Scaled Data retrieval
- [ ] Support for Gyroscope:
  - [ ] Configuration
  - [ ] Raw Data retrieval
  - [ ] Scaled Data retrieval
- [ ] Support for Magnetometer:
  - [ ] Configuration
  - [ ] Raw Data retrieval
  - [ ] Scaled Data retrieval

Future:
- [ ] Interrupts
- [ ] Other configs (Tap detect, freefall detect, ...)

# Example for Arduino

```c
#include <Arduino.h>
#include <BMX055.h>

void setup(){

  Serial.begin(115200);

  bmx.InitAcc(BMX055_ACC_BW::BMX055_ACC_BW_62_50HZ,
              BMX055_ACC_RANGE::BMX055_ACC_RANGE_2G);
              
}

int16_t rawDataAcc[3] = {0,0,0};

void loop(){

  bmx.updateAccData();
  bmx.getRawAccData(rawDataAcc);

  Serial.println(rawDataAcc[0]);

}

```