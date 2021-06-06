/***************
BMX055 library
File: BMX055.cpp
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

#include <stdint.h>
#include "BMX055_HALs.h"
#include <BMX055.h>


BMX055::BMX055( uint8_t pAddressAcc,
                uint8_t pAddressGyr, 
                uint8_t pAddressMag):
    mAddressAcc(pAddressAcc),
    mAddressGyr(pAddressGyr),
    mAddressMag(pAddressMag)
{
#ifdef ARDUINO
    InitHAL(writeByte, readByte);
#endif
}

void BMX055::InitHAL( uint8_t (*pI2cSendByte)(uint8_t, uint8_t, uint8_t),
                      uint8_t (*pI2cRecvByte)(uint8_t, uint8_t) )
{
    if (pI2cRecvByte != nullptr)
    {
        mI2cRecvByte = pI2cRecvByte;
    }

    if(pI2cSendByte != nullptr)
    {
        mI2cSendByte = pI2cSendByte;
    }
}

void BMX055::InitAcc(enum BMX055_ACC_BW pBw, enum BMX055_ACC_RANGE pRange){
    
    if(mI2cRecvByte == nullptr || mI2cSendByte == nullptr)
    {
        return;
    }

    // Store the Acc configuration 
    mAccBandwidth = pBw;
    mAccRange = pRange;

    mI2cSendByte(mAddressAcc, BMX055_ACC_REG_PMU_BW, pBw & 0x011111);
    mI2cSendByte(mAddressAcc, BMX055_ACC_REG_PMU_RANGE, pRange & 0b01111);
    mI2cSendByte(mAddressAcc, BMX055_ACC_REG_ACCD_HBW, 0x0);
}

#if 0
uint8_t BMX055::ReadRawAccData(int16_t accData[3]){

    if(mI2cRecvByte == nullptr || mI2cSendByte == nullptr)
    {
        return 0;
    }
    /*
    switch(mAccRange){
        case BMX055_ACC_RANGE_2G:  lDelta = 0.98; break;
        case BMX055_ACC_RANGE_4G:  lDelta = 1.95; break;
        case BMX055_ACC_RANGE_8G:  lDelta = 3.91; break;
        case BMX055_ACC_RANGE_16G: lDelta = 7.81; break;
        default: return 0;
    }*/

    accData[0] = mI2cRecvByte(mAddressAcc, BMX055_ACC_REG_ACCD_X_LSB);
    accData[0] = accData[0] >> 4;
    accData[0] = (mI2cRecvByte(mAddressAcc, BMX055_ACC_REG_ACCD_X_MSB) << 4) | accData[0];
    if (accData[0] > 2047){
        accData[0] -= 4096;
    }

    accData[1] = mI2cRecvByte(mAddressAcc, BMX055_ACC_REG_ACCD_Y_LSB);
    accData[1] = accData[1] >> 4;
    accData[1] = (mI2cRecvByte(mAddressAcc, BMX055_ACC_REG_ACCD_Y_MSB) << 4) | accData[1];
    if (accData[1] > 2047){
        accData[1] -= 4096;
    }

    accData[2] = mI2cRecvByte(mAddressAcc, BMX055_ACC_REG_ACCD_Z_LSB);
    accData[2] = accData[2] >> 4;
    accData[2] = (mI2cRecvByte(mAddressAcc, BMX055_ACC_REG_ACCD_Z_MSB) << 4) | accData[2];
    if (accData[2] > 2047){
        accData[2] -= 4096;
    }

    return 0;
}
#endif

uint8_t BMX055::updateAccData(){

    if(mI2cRecvByte == nullptr || mI2cSendByte == nullptr)
    {
        return 0;
    }

    mAccRawData[0] = mI2cRecvByte(mAddressAcc, BMX055_ACC_REG_ACCD_X_LSB);
    mAccRawData[0] = mAccRawData[0] >> 4;
    mAccRawData[0] = (mI2cRecvByte(mAddressAcc, BMX055_ACC_REG_ACCD_X_MSB) << 4) | mAccRawData[0];
    
    if (mAccRawData[0] > 2047)
    {
        mAccRawData[0] -= 4096;
    }

    mAccRawData[1] = mI2cRecvByte(mAddressAcc, BMX055_ACC_REG_ACCD_Y_LSB);
    mAccRawData[1] = mAccRawData[1] >> 4;
    mAccRawData[1] = (mI2cRecvByte(mAddressAcc, BMX055_ACC_REG_ACCD_Y_MSB) << 4) | mAccRawData[1];
    
    if (mAccRawData[1] > 2047)
    {
        mAccRawData[1] -= 4096;
    }

    mAccRawData[2] = mI2cRecvByte(mAddressAcc, BMX055_ACC_REG_ACCD_Z_LSB);
    mAccRawData[2] = mAccRawData[2] >> 4;
    mAccRawData[2] = (mI2cRecvByte(mAddressAcc, BMX055_ACC_REG_ACCD_Z_MSB) << 4) | mAccRawData[2];
    
    if (mAccRawData[2] > 2047)
    {
        mAccRawData[2] -= 4096;
    }

    return 1;
}

uint8_t BMX055::getRawAccData(int16_t pAccData[3]){

    if(pAccData == nullptr)
    {
        return 0;
    }

    pAccData[0] = mAccRawData[0];
    pAccData[1] = mAccRawData[1];
    pAccData[2] = mAccRawData[2];

    return 1;
}


uint8_t BMX055::getAccData(float pAccData[3])
{

    float lDelta;

    if(pAccData == nullptr)
    {
        return 0;
    }

    switch(mAccRange){
        case BMX055_ACC_RANGE_2G:  lDelta = 0.98; break;
        case BMX055_ACC_RANGE_4G:  lDelta = 1.95; break;
        case BMX055_ACC_RANGE_8G:  lDelta = 3.91; break;
        case BMX055_ACC_RANGE_16G: lDelta = 7.81; break;
        default: return 0;
    }

    pAccData[0] = mAccRawData[0] * lDelta/1000.0f;
    pAccData[1] = mAccRawData[1] * lDelta/1000.0f;
    pAccData[2] = mAccRawData[2] * lDelta/1000.0f;

    return 1;
}


/*** GYRO ***/

void BMX055::InitGyr(enum BMX055_GYR_BW pBw, enum BMX055_GYR_RANGE pRange){

    if(mI2cRecvByte == nullptr || mI2cSendByte == nullptr)
    {
        return;
    }

    // Store the Acc configuration 
    mGyrBandwidth = pBw;
    mGyrRange = pRange;

    mI2cSendByte(mAddressGyr, BMX055_GYR_REG_BW, pBw & 0x01111);
    mI2cSendByte(mAddressGyr, BMX055_GYR_REG_RANGE, pRange & 0b0111);
    mI2cSendByte(mAddressGyr, BMX055_GYR_REG_RATE_HBW, 0x0);

}
uint8_t BMX055::updateGyrData(){
    if(mI2cRecvByte == nullptr || mI2cSendByte == nullptr)
    {
        return 0;
    }

    mGyrRawData[0] = mI2cRecvByte(mAddressGyr, BMX055_GYR_REG_GYRD_X_LSB);
    mGyrRawData[0] = (mI2cRecvByte(mAddressGyr, BMX055_GYR_REG_GYRD_X_MSB) << 8) | mGyrRawData[0];

    mGyrRawData[1] = mI2cRecvByte(mAddressGyr, BMX055_GYR_REG_GYRD_Y_LSB);
    mGyrRawData[1] = (mI2cRecvByte(mAddressGyr, BMX055_GYR_REG_GYRD_Y_MSB) << 8) | mGyrRawData[1];
    
    mGyrRawData[2] = mI2cRecvByte(mAddressGyr, BMX055_GYR_REG_GYRD_Z_LSB);
    mGyrRawData[2] = (mI2cRecvByte(mAddressGyr, BMX055_GYR_REG_GYRD_Z_MSB) << 8) | mGyrRawData[2];

    return 1;
}

uint8_t BMX055::getRawGyrData(int16_t pGyrData[3]){
    if(pGyrData == nullptr)
    {
        return 0;
    }

    pGyrData[0] = mGyrRawData[0];
    pGyrData[1] = mGyrRawData[1];
    pGyrData[2] = mGyrRawData[2];

    return 1;
}
uint8_t BMX055::getGyrData(float pGyrData[3]){

}