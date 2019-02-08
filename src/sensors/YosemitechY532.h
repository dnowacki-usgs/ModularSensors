/*
 *YosemitechY532.h
 *This file is part of the EnviroDIY modular sensors library for Arduino
 *
 *Initial library developement done by Sara Damiano (sdamiano@stroudcenter.org).
 *
 *This file is for the Yosemitech Y532 pH sensor
 *It is dependent on the YosemitechParent super class.
 *
 *Documentation for the Modbus Protocol commands and responses can be found
 *within the documentation in the YosemitechModbus library at:
 *https://github.com/EnviroDIY/YosemitechModbus
 *
 *These devices output very high "resolution" (32bits) so the resolutions are
 *based on their accuracy, not the resolution of the sensor
 *
 * For pH:
 *     Resolution is 0.01 pH units
 *     Accuracy is ± 0.1 pH units
 *     Range is 2 to 12 pH units
 *
 * For Temperature:
 *     Resolution is 0.1 °C
 *     Accuracy is ± 0.2°C
 *     Range is 0°C to + 50°C
 *
 * Time before sensor responds after power - 500ms
 * Time between "StartMeasurement" command and stable reading - 4.5sec
*/

#ifndef YosemitechY532_h
#define YosemitechY532_h

#include "YosemitechParent.h"
#include "VariableBase.h"

#define Y532_NUM_VARIABLES 3
#define Y532_WARM_UP_TIME_MS 500
#define Y532_STABILIZATION_TIME_MS 4500
#define Y532_MEASUREMENT_TIME_MS 1800

#define Y532_PH_RESOLUTION 2
#define Y532_PH_VAR_NUM 0

#define Y532_TEMP_RESOLUTION 1
#define Y532_TEMP_VAR_NUM 1

#define Y532_VOLT_RESOLUTION 0
#define Y532_VOLT_VAR_NUM 2

// The main class for the Decagon Y532
class YosemitechY532 : public YosemitechParent
{
public:
    // Constructors with overloads
    YosemitechY532(byte modbusAddress, Stream* stream, int8_t powerPin,
                   int8_t enablePin = -1, uint8_t measurementsToAverage = 1)
     : YosemitechParent(modbusAddress, stream, powerPin, enablePin, measurementsToAverage,
                        Y532, "YosemitechY532", Y532_NUM_VARIABLES,
                        Y532_WARM_UP_TIME_MS, Y532_STABILIZATION_TIME_MS, Y532_MEASUREMENT_TIME_MS)
    {}
    YosemitechY532(byte modbusAddress, Stream& stream, int8_t powerPin,
                   int8_t enablePin = -1, uint8_t measurementsToAverage = 1)
     : YosemitechParent(modbusAddress, stream, powerPin, enablePin, measurementsToAverage,
                        Y532, "YosemitechY532", Y532_NUM_VARIABLES,
                        Y532_WARM_UP_TIME_MS, Y532_STABILIZATION_TIME_MS, Y532_MEASUREMENT_TIME_MS)
    {}
};


// Defines the pH
class YosemitechY532_pH : public Variable
{
public:
    YosemitechY532_pH(Sensor *parentSense,
                      const char *UUID = "", const char *customVarCode = "")
     : Variable(parentSense, Y532_PH_VAR_NUM,
                "pH", "pH",
                Y532_PH_RESOLUTION,
                "Y532pH", UUID, customVarCode)
    {}
};


// Defines the Temperature Variable
class YosemitechY532_Temp : public Variable
{
public:
    YosemitechY532_Temp(Sensor *parentSense,
                        const char *UUID = "", const char *customVarCode = "")
     : Variable(parentSense, Y532_TEMP_VAR_NUM,
                "temperature", "degreeCelsius",
                Y532_TEMP_RESOLUTION,
                "Y532temp", UUID, customVarCode)
    {}
};


// Defines the Electrode Electrical Potential
class YosemitechY532_Voltage : public Variable
{
public:
    YosemitechY532_Voltage(Sensor *parentSense,
                           const char *UUID = "", const char *customVarCode = "")
     : Variable(parentSense, Y532_VOLT_VAR_NUM,
                "voltage", "millivolt",
                Y532_VOLT_RESOLUTION,
                "Y532Potential", UUID, customVarCode)
    {}
};

#endif