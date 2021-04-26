/***************
BMX055 library
File: BMX055_HALs.h
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

#ifndef __BMX055_HALS_H__
#define __BMX055_HALS_H__

#ifdef ARDUINO
#include <Arduino.h>
#include <Wire.h>

uint8_t writeByte(uint8_t address, uint8_t subAddress, uint8_t data);
uint8_t readByte(uint8_t address, uint8_t subAddress);

#endif


#endif //__BMX055_HALS_H__