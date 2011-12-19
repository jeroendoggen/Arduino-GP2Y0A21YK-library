/************************************************************************************************************
 * DistanceGP2Y0A21YK.h - Arduino library for retrieving data from the analog GP2Y0A21YK IR Distance sensor *
 * Copyright 2011 Jeroen Doggen (jeroendoggen@gmail.com)                                                    *
 * For more information: variable declaration, changelog,... see DistanceGP2Y0A21YK.h                       *
 ************************************************************************************************************
 * This library is free software; you can redistribute it and/or                                            *
 * modify it under the terms of the GNU Lesser General Public                                               *
 * License as published by the Free Software Foundation; either                                             *
 * version 2.1 of the License, or (at your option) any later version.                                       *
 *                                                                                                          *
 * This library is distributed in the hope that it will be useful,                                          *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of                                           *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU                                        *
 * Lesser General Public License for more details.                                                          *
 *                                                                                                          *
 * You should have received a copy of the GNU Lesser General Public                                         *
 * License along with this library; if not, write to the Free Software                                      *
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA                               *
 ***********************************************************************************************************/

/// <summary>
/// DistanceGP2Y0A21YK.cpp - Library for retrieving data from the GP2Y0A21YK IR Distance sensor.
/// For more information: variable declaration, changelog,... see DistanceGP2Y0A21YK.h
/// </summary>

#include <Arduino.h>
#include <DistanceGP2Y0A21YK.h>

/// <summary>
/// Constructor
/// </summary>
DistanceGP2Y0A21YK::DistanceGP2Y0A21YK ()
{
}

/// <summary>
/// Begin function to set pins: distancePin = A0.
/// </summary>
void
DistanceGP2Y0A21YK::begin ()
{
	begin (A0);
}

/// <summary>
/// Begin variables
/// - int _distancePin: number indicating the distance to an object: ANALOG IN
/// - int _transferFunctionLUT3V: Transfer function Lookup Table (for 3.3V reference value)
/// - int _transferFunctionLUT5V: Transfer function Lookup Table (for 5V reference value)
/// When you use begin() without variables standard values are loaded: A0
/// </summary>
void
DistanceGP2Y0A21YK::begin (int distancePin)
{
	pinMode (distancePin, INPUT);
	_distancePin = distancePin;
	setAveraging (10);		      //1: all samples passed to higher level
	setARefVoltage (5);		      // 5 default situation
		//setARefVoltage(3);  // 3.3V: put a wire between the AREF pin and the 3.3V VCC pin.
		//This increases accuracy (and uses a different LUT)
	int _transferFunctionLUT3V[] =
	{
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 79,
		76, 73, 71, 69, 67, 65, 63, 62, 60, 58, 57, 52, 50, 49, 48, 47,
		49, 48, 47, 46, 45, 44, 43, 43, 42, 41, 40, 40, 39, 38, 37, 37,
		36, 36, 35, 35, 34, 33, 33, 32, 32, 31, 31, 31, 30, 30, 29, 29,
		29, 28, 28, 27, 27, 27, 26, 26, 26, 25, 25, 25, 25, 24, 24, 24,
		23, 23, 23, 23, 22, 22, 22, 22, 22, 21, 21, 21, 21, 20, 20, 20,
		20, 20, 20, 19, 19, 19, 19, 19, 18, 18, 18, 18, 18, 18, 18, 17,
		17, 17, 17, 17, 17, 17, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
		15, 15, 15, 15, 15, 15, 15, 14, 14, 14, 14, 14, 14, 14, 14, 14,
		13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 12, 12, 12,
		12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 11, 11, 11, 11, 11,
		11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 10, 10,
		10, 10, 10, 10, 10, 10, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00,
		00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00,
		00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00,
	};
	int _transferFunctionLUT5V[] =
	{
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44,
		0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44,
		0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44,
		0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	};
}

/// <summary>
/// setAveraging(int avg): Sets how many samples have to be averaged in getDistanceRaw, default value is 10.
/// </summary>
void DistanceGP2Y0A21YK::setAveraging (int avg)
{
	_average = avg;
}

/// <summary>
/// getDistanceRaw(): Returns the distance as a raw value: ADC output: 0 -> 1023
/// </summary>
int DistanceGP2Y0A21YK::getDistanceRaw ()
{
	return analogRead (_distancePin);
}

/// <summary>
/// getDistanceVolt(): Returns the distance as a Voltage: ADC Input: 0V -> 5V (or 0V -> 3.3V)
/// </summary>
int DistanceGP2Y0A21YK::getDistanceVolt ()
{
	return _mapGP2Y0A21YK_V (getDistanceRaw ());
}

/// <summary>
/// getDistanceCentimeter(): Returns the distance in centimeters
/// </summary>
int DistanceGP2Y0A21YK::getDistanceCentimeter ()
{
	return _mapGP2Y0A21YK_CM (getDistanceRaw ());
}

/// <summary>
/// _mapGP2Y0A21YKV: calculates the input voltage of the ADC
/// </summary>
int DistanceGP2Y0A21YK::_mapGP2Y0A21YK_V (int value)
{
	if (_refVoltage==3)
	{
		return map(value,0,1024,0,3300);
	}
	else
	{
		return map(value,0,1024,0,5000);
	}
}

/// <summary>
/// _mapGP2Y0A21YK_CM: calculates the distance in centimeters using a LUT (LUT filled with data calculated by the inverse tranferfunction)
///    -> Two different LUTs depending on ADC reference voltage
/// </summary>
int DistanceGP2Y0A21YK::_mapGP2Y0A21YK_CM (int value)
{
	if (_refVoltage == 3)
	{
		return _transferFunctionLUT3V[getDistanceRaw ()/4];
	}
	else
	{
		return _transferFunctionLUT5V[getDistanceRaw ()/4];
	}
}

/// <summary>
/// setARefVoltage:set the ADC reference voltage: (default value: 5V, set to 3 for 3.3V)
/// </summary>
void DistanceGP2Y0A21YK::setARefVoltage (int refV)
{
	_refVoltage = refV;
	if (_refVoltage == 3)
	{
		analogReference(EXTERNAL);
	}
}
