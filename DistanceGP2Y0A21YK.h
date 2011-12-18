/****************************************************************************************************************
 * DistanceGP2Y0A21YK.h - Arduino library for retrieving data from the analog GP2Y0A21YK IR Distance sensor     *
 * DATASHEET: http://www.sparkfun.com/datasheets/Components/GP2Y0A21YK.pdf                                      *
 ****************************************************************************************************************
 * Version History:                                                                                             *
 *  Version 0.1: getDistanceRaw, getDistanceVolt, getDistanceCentimeter (with incorrect LUT)                    *
 *														*
 * Roadmap:													*
 *  Version 0.2: Correct LUT											*
 *  Version 0.3: Take sensor height above the ground into account						*
 *  Version 0.4; Take object type into account (differtent LUT for wooden vs stone walls ...)			*
 ****************************************************************************************************************
 * Created by Jeroen Doggen: Suggestions, questions or comments please contact me                               *
 *  -mail: jeroendoggen at gmail dot com                                                                   *
 *  -skype: jeroendoggen                                                                                        *
 ***************************************************************************************************************/

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

