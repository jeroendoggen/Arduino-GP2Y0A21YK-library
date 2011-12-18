/************************************************************************************************************
 * DistanceGP2Y0A21YK.h - Arduino library for retrieving data from the analog GP2Y0A21YK IR Distance sensor *
 * Copyright 2011 Jeroen Doggen (jeroendoggen@gmail.com)                                                    *
 * Datasheet: http://www.sparkfun.com/datasheets/Components/GP2Y0A21YK.pdf                                  *
 ************************************************************************************************************
 * Version History:                                                                                         *
 *  Version 0.1: getDistanceRaw, getDistanceVolt, getDistanceCentimeter (with incorrect LUT)                *
 *                                                                                                          *
 * Roadmap:                                                                                                 *
 *  Version 0.2: Correct LUT                                                                                *
 *  Version 0.3: Take sensor height above the ground into account                                           *
 *  Version 0.4; Take object type into account (differtent LUT for wooden vs stone walls?? ...)             *
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




#ifndef DistanceGP2Y0A21YK_h
#define DistanceGP2Y0A21YK_h
#include <Arduino.h>

class DistanceGP2Y0A21YK
{
	public:
		DistanceGP2Y0A21YK();
		void begin();
		void begin(int distancePin);

		int getDistanceRaw();
		int getDistanceVolt();
		int getDistanceCentimeter();

		void setAveraging(int avg);
		void setARefVoltage(int _refV);

	private:
		int _mapGP2Y0A21YK_V(int value);
		int _mapGP2Y0A21YK_CM(int value);
		int _distancePin;
		int _average;
		int _transferFunctionLUT3V[];
		int _transferFunctionLUT5V[];
		int _refVoltage;
};
#endif
