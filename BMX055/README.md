# BMX055 library 

This is a WIP library for BMX055, currently supporting only accelerometer in Arduino.


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