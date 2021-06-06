/***************
BMX055 library
File: BMX055_regs.h
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

#ifndef __BMX055_REGS_H__
#define __BMX055_REGS_H__

#define BMX055_ACC_ADDR 0x18
#define BMX055_GYR_ADDR 0x68
#define BMX055_MAG_ADDR 0x10


/*** ACC REGs ***/
#define BMX055_ACC_REG_ACCD_X_LSB 0x02
#define BMX055_ACC_REG_ACCD_X_MSB 0x03
#define BMX055_ACC_REG_ACCD_Y_LSB 0x04
#define BMX055_ACC_REG_ACCD_Y_MSB 0x05
#define BMX055_ACC_REG_ACCD_Z_LSB 0x06
#define BMX055_ACC_REG_ACCD_Z_MSB 0x07

#define BMX055_ACC_REG_PMU_RANGE 0x0F
#define BMX055_ACC_REG_PMU_BW    0x10
#define BMX055_ACC_REG_ACCD_HBW  0x13



enum BMX055_ACC_BW{
    BMX055_ACC_BW_7_81HZ = 0b01000,
    BMX055_ACC_BW_15_63HZ,
    BMX055_ACC_BW_31_25HZ,
    BMX055_ACC_BW_62_50HZ,
    BMX055_ACC_BW_125HZ,
    BMX055_ACC_BW_250HZ,
    BMX055_ACC_BW_500HZ,
    BMX055_ACC_BW_1000HZ
};

enum BMX055_ACC_RANGE{
    BMX055_ACC_RANGE_2G  = 0b0011,
    BMX055_ACC_RANGE_4G  = 0b0101,
    BMX055_ACC_RANGE_8G  = 0b1000,
    BMX055_ACC_RANGE_16G = 0b1100,
};


/*** GYRO regs ***/

#define BMX055_GYR_REG_GYRD_X_LSB 0x02
#define BMX055_GYR_REG_GYRD_X_MSB 0x03
#define BMX055_GYR_REG_GYRD_Y_LSB 0x04
#define BMX055_GYR_REG_GYRD_Y_MSB 0x05
#define BMX055_GYR_REG_GYRD_Z_LSB 0x06
#define BMX055_GYR_REG_GYRD_Z_MSB 0x07

#define BMX055_GYR_REG_RANGE 0x0F
enum BMX055_GYR_RANGE{
    BMX055_GYR_RANGE_2000 = 0b000,
    BMX055_GYR_RANGE_1000 = 0b001,
    BMX055_GYR_RANGE_500  = 0b010,
    BMX055_GYR_RANGE_250  = 0b011,
    BMX055_GYR_RANGE_125  = 0b100,
};


#define BMX055_GYR_REG_BW 0x10
enum BMX055_GYR_BW{
    BMX055_GYR_BW_UNFILTERED  = 0b000,
    BMX055_GYR_BW_230Hz  = 0b001,
    BMX055_GYR_BW_116Hz  = 0b010,
    BMX055_GYR_BW_47Hz   = 0b011,
    BMX055_GYR_BW_23Hz  = 0b100,
    BMX055_GYR_BW_12Hz  = 0b101,
    BMX055_GYR_BW_64Hz  = 0b110,
    BMX055_GYR_BW_32Hz  = 0b111,
};

#define BMX055_GYR_REG_LPM1 0x11
#define BMX055_GYR_REG_RATE_HBW 0x13
#define BMX055_GYR_REG_RATE_HBW_HBW (1u<<7u)
#define BMX055_GYR_REG_RATE_HBW_SHADOW_DIS (1u<<6u)

#endif //__BMX055_REGS_H__