/******************************************************************************
 * DistanceGP2Y0A21YK - Arduino library for retrieving data from the analog   *
 *    GP2Y0A21YK IR Distance sensor                                           *
 * Copyright 2011-2012 Jeroen Doggen (jeroendoggen@gmail.com)                 *
 ******************************************************************************
 * This library is free software; you can redistribute it and/or              *
 * modify it under the terms of the GNU Lesser General Public                 *
 * License as published by the Free Software Foundation; either               *
 * version 2.1 of the License, or (at your option) any later version.         *
 *                                                                            *
 * This library is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU          *
 * Lesser General Public License for more details.                            *
 *                                                                            *
 * You should have received a copy of the GNU Lesser General Public           *
 * License along with this library; if not, write to the Free Software        *
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA *
 *****************************************************************************/

/// <summary>
/// DistanceGP2Y0A21YK.cpp - Library for retrieving data from the GP2Y0A21YK IR Distance sensor.
/// For more information: variable declaration, changelog,... see DistanceGP2Y0A21YK.h
/// </summary>

#include <DistanceGP2Y0A21YK.h>
#include <DistanceGP2Y0A21YK_LUTs.h>

/// <summary>
/// Constructor
/// </summary>
DistanceGP2Y0A21YK::DistanceGP2Y0A21YK()
{
}

/// <summary>
/// Begin variables
/// - int _distancePin: number indicating the distance to an object: ANALOG IN
/// When you use begin() without variables standard values are loaded: A0
/// </summary>
void DistanceGP2Y0A21YK::begin(int distancePin)
{
  setEnabled(true);
  pinMode(distancePin, INPUT);
	_distancePin=distancePin;
	setAveraging(1);		      //1: all samples passed to higher level
	setARefVoltage(5);		      // 5: default analog reference of 5 volts (on 5V Arduino boards) or 3.3 volts (on 3.3V Arduino boards)
		//setARefVoltage(3);  // external analog reference: for 3.3V: put a wire between the AREF pin and the 3.3V VCC pin.
		//This increases accuracy (and uses a different LUT)
}

/// <summary>
/// Begin variables
/// - int _distancePin: number indicating the distance to an object: ANALOG IN
/// - int vccPin: pin connected to the vcc pin of the sensor (switch the sensor on/off)
/// When you use begin() without variables standard values are loaded: A0
/// </summary>
void DistanceGP2Y0A21YK::begin(int distancePin, int vccPin)
{
	_vccPin=vccPin;
	begin (distancePin);
	pinMode(_vccPin, OUTPUT); 
	setEnabled(true);
	//digitalWrite(vccPin, HIGH); 
}

/// <summary>
/// setAveraging(int avg): Sets how many samples have to be averaged in getDistanceCentimeter, default value is 1.
/// </summary>
void DistanceGP2Y0A21YK::setAveraging(int avg)
{
	_average=avg;
}

/// <summary>
/// getDistanceRaw(): Returns the distance as a raw value: ADC output: 0 -> 1023
/// </summary>
int DistanceGP2Y0A21YK::getDistanceRaw()
{
	if (_enabled == true)
	{
		return (analogRead(_distancePin));
	}
	else
	{
		return (1023);
	}
	
}

/// <summary>
/// getDistanceVolt(): Returns the distance as a Voltage: ADC Input: 0V -> 5V (or 0V -> 3.3V)
/// </summary>
int DistanceGP2Y0A21YK::getDistanceVolt()
{
	return _mapGP2Y0A21YK_V(getDistanceRaw());
}

/// <summary>
/// getDistanceCentimeter(): Returns the distance in centimeters
/// </summary>
int DistanceGP2Y0A21YK::getDistanceCentimeter()
{
	return _mapGP2Y0A21YK_CM(getDistanceRaw());
}

/// <summary>
/// _mapGP2Y0A21YKV: calculates the input voltage of the ADC
/// </summary>
int DistanceGP2Y0A21YK::_mapGP2Y0A21YK_V(int value)
{
	if (_refVoltage == 3)
	{
		return map(value,0,1023,0,3300);
	}
	if (_refVoltage == 5)
	{
		return map(value,0,1023,0,5000);
	}
}

/// <summary>
/// _mapGP2Y0A21YK_CM: calculates the distance in centimeters using a lookup table
///    -> Two different LUTs depending on ADC reference voltage
/// </summary>
int DistanceGP2Y0A21YK::_mapGP2Y0A21YK_CM(int value)
{
	if (_refVoltage == 3)
	{
		int sum = 0;
		for (int i=0;i<_average;i++)
		{
			// this code is equivalent to: sum=sum+transferFunctionLUT5V[(getDistanceRaw()/4)];
			// but this alternative syntax is needed to read the program memory
			sum=sum + pgm_read_byte_near (transferFunctionLUT3V + (getDistanceRaw()/4));
		}
		return(sum/_average);
	}
	if (_refVoltage == 5)
	{
		int sum = 0;
		for (int i=0;i<_average;i++)
		{
			sum=sum + pgm_read_byte_near (transferFunctionLUT5V + (getDistanceRaw()/4));
		}
		return(sum/_average);
	}
}

/// <summary>
/// setARefVoltage:set the ADC reference voltage: (default value: 5V, set to 3 for external reference value, typically 3.3 on Arduino boards)
/// </summary>
void DistanceGP2Y0A21YK::setARefVoltage(int refV)
{
	if (_refVoltage == 5)
	{
		analogReference(DEFAULT);
	}
	if (_refVoltage == 3)
	{
		analogReference(EXTERNAL);
	}
	_refVoltage=refV;
}

/// <summary>
/// isCloser: check whether the distance to the detected object is smaller than a given threshold
/// </summary>
boolean DistanceGP2Y0A21YK::isCloser(int threshold)
{
	if (threshold>getDistanceCentimeter())
	{
		return (true);
	}
	else
	{
		return (false);
	}
}

/// <summary>
/// isFarther: check whether the distance to the detected object is smaller than a given threshold
/// </summary>
boolean DistanceGP2Y0A21YK::isFarther(int threshold)
{
	if (threshold<getDistanceCentimeter())
	{
		return true;
	}
	else
	{
		return false;
	}
}

/// <summary>
/// setEnabled: enable or disable the sensor (only works when sensor Vcc is connected to digital output pin)
/// </summary>
void DistanceGP2Y0A21YK::setEnabled(bool status)
{
	_enabled = status;
	if (_enabled)
	{
		digitalWrite(_vccPin, HIGH);
	}
	else
	{
		digitalWrite(_vccPin, LOW);	
	}
}
