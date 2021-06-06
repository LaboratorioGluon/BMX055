/***************
BMX055 library
File: BMX055.h
Created by: Laboratorio Gluon
  
Copyright (C) 2021 Laboratorio Gluon

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

******************************************/

#ifndef __BMX055_H__
#define __BMX055_H__

#include "BMX055_regs.h"
#include "BMX055_HALs.h"

class BMX055{
public:

    BMX055(uint8_t pAddressAcc = BMX055_ACC_ADDR,
           uint8_t pAddressGyr = BMX055_GYR_ADDR,
           uint8_t pAddressMag = BMX055_MAG_ADDR
           );

    void InitHAL(
        uint8_t (*pI2cSendByte)(uint8_t, uint8_t, uint8_t),
        uint8_t (*pI2cRecvByte)(uint8_t, uint8_t)
        );


    // Accelerometer

    void    InitAcc(enum BMX055_ACC_BW pBw, enum BMX055_ACC_RANGE pRange);
    uint8_t updateAccData();
    uint8_t getRawAccData(int16_t pAccData[3]);
    uint8_t getAccData(float pAccData[3]);

    // Gyroscope

private:

    // I2C address of the three components.
    uint8_t mAddressAcc;
    uint8_t mAddressGyr;
    uint8_t mAddressMag;

    // Acc config
    uint8_t mAccBandwidth;
    uint8_t mAccRange;

    // HAL
    uint8_t (*mI2cSendByte)(uint8_t addr, uint8_t, uint8_t);
    uint8_t (*mI2cRecvByte)(uint8_t, uint8_t);

    // Stored data
    uint16_t mAccRawData[3];
    uint16_t mGyrRawData[3];
    uint16_t mMagRawData[3];

};

#endif //__BMX055_H__