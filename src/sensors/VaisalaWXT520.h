/*
 *VaisalaWXT520.h
 *This file is part of the EnviroDIY modular sensors library for Arduino
 *
 *Initial library developement done by Sara Damiano (sdamiano@stroudcenter.org).
 *
 *This file is based on DecagonCTD.h
 *It is dependent on the EnviroDIY SDI-12 library and the SDI12Sensors super class.
 *
 * 
 * Dm Direction average, Sm Speed average, Pa Air pressure, Ta Air temperature, Ua Air humidity, Rc Rain amount, Th Heating temperature, Vh Heating voltage
*/

// Header Guards
#ifndef VaisalaWXT520_h
#define VaisalaWXT520_h

// Included Dependencies
#include "sensors/SDI12Sensors.h"

// Sensor Specific Defines
#define WXT_NUM_VARIABLES 6
#define WXT_WARM_UP_TIME_MS 500
#define WXT_STABILIZATION_TIME_MS 0
#define WXT_MEASUREMENT_TIME_MS 12500

#define WXT_DM_RESOLUTION 1
#define WXT_DM_VAR_NUM 0

#define WXT_SM_RESOLUTION 1
#define WXT_SM_VAR_NUM 1

#define WXT_PA_RESOLUTION 1
#define WXT_PA_VAR_NUM 2

#define WXT_TA_RESOLUTION 1
#define WXT_TA_VAR_NUM 3

#define WXT_UA_RESOLUTION 1
#define WXT_UA_VAR_NUM 4

#define WXT_RC_RESOLUTION 1
#define WXT_RC_VAR_NUM 5

// The main class for the Vaisala WXT520
class VaisalaWXT520 : public SDI12Sensors
{
public:
    // Constructors with overloads
    VaisalaWXT520(char SDI12address, int8_t powerPin, int8_t dataPin, uint8_t measurementsToAverage = 1)
     : SDI12Sensors(SDI12address, powerPin, dataPin, measurementsToAverage,
                    "VaisalaWXT520", WXT_NUM_VARIABLES,
                    WXT_WARM_UP_TIME_MS, WXT_STABILIZATION_TIME_MS, WXT_MEASUREMENT_TIME_MS)
    {}
    VaisalaWXT520(char *SDI12address, int8_t powerPin, int8_t dataPin, uint8_t measurementsToAverage = 1)
     : SDI12Sensors(SDI12address, powerPin, dataPin, measurementsToAverage,
                    "VaisalaWXT520", WXT_NUM_VARIABLES,
                    WXT_WARM_UP_TIME_MS, WXT_STABILIZATION_TIME_MS, WXT_MEASUREMENT_TIME_MS)
    {}
    VaisalaWXT520(int SDI12address, int8_t powerPin, int8_t dataPin, uint8_t measurementsToAverage = 1)
     : SDI12Sensors(SDI12address, powerPin, dataPin, measurementsToAverage,
                    "VaisalaWXT520", WXT_NUM_VARIABLES,
                    WXT_WARM_UP_TIME_MS, WXT_STABILIZATION_TIME_MS, WXT_MEASUREMENT_TIME_MS)
    {}
    // Destructor
    ~VaisalaWXT520(){}
};

// Defines the Dm Variable
class VaisalaWXT520_Dm : public Variable
{
public:
    VaisalaWXT520_Dm(Sensor *parentSense,
                    const char *uuid = "",
                    const char *varCode = "WXTDm")
      : Variable(parentSense,
                 (const uint8_t)WXT_DM_VAR_NUM,
                 (uint8_t)WXT_DM_RESOLUTION,
                 "direction", "degrees",
                 varCode, uuid)
    {}
    VaisalaWXT520_Dm()
      : Variable((const uint8_t)WXT_DM_VAR_NUM,
                 (uint8_t)WXT_DM_RESOLUTION,
                 "direction", "degrees", "WXTDm")
    {}
    ~VaisalaWXT520_Dm(){}
};

// Defines the Sm Variable
class VaisalaWXT520_Sm : public Variable
{
public:
    VaisalaWXT520_Sm(Sensor *parentSense,
                    const char *uuid = "",
                    const char *varCode = "WXTSm")
      : Variable(parentSense,
                 (const uint8_t)WXT_SM_VAR_NUM,
                 (uint8_t)WXT_SM_RESOLUTION,
                 "speed", "metersPerSecond",
                 varCode, uuid)
    {}
    VaisalaWXT520_Sm()
      : Variable((const uint8_t)WXT_SM_VAR_NUM,
                 (uint8_t)WXT_SM_RESOLUTION,
                 "speed", "metersPerSecond", "WXTSm")
    {}
    ~VaisalaWXT520_Sm(){}
};


// Defines the Pa Variable
class VaisalaWXT520_Pa : public Variable
{
public:
    VaisalaWXT520_Pa(Sensor *parentSense,
                     const char *uuid = "",
                     const char *varCode = "WXTPa")
      : Variable(parentSense,
                 (const uint8_t)WXT_PA_VAR_NUM,
                 (uint8_t)WXT_PA_RESOLUTION,
                 "airPressure", "hPa",
                 varCode, uuid)
    {}
    VaisalaWXT520_Pa()
      : Variable((const uint8_t)WXT_PA_VAR_NUM,
                 (uint8_t)WXT_PA_RESOLUTION,
                 "airPressure", "hPa", "WXTPa")
    {}
    ~VaisalaWXT520_Pa(){}
};

// Defines the Ta Variable
class VaisalaWXT520_Ta : public Variable
{
public:
    VaisalaWXT520_Ta(Sensor *parentSense,
                    const char *uuid = "",
                    const char *varCode = "WXTTa")
      : Variable(parentSense,
                 (const uint8_t)WXT_TA_VAR_NUM,
                 (uint8_t)WXT_TA_RESOLUTION,
                 "airTemperature", "degreeCelsius",
                 varCode, uuid)
    {}
    VaisalaWXT520_Ta()
      : Variable((const uint8_t)WXT_TA_VAR_NUM,
                 (uint8_t)WXT_TA_RESOLUTION,
                 "airTemperature", "degreeCelsius", "WXTTa")
    {}
    ~VaisalaWXT520_Ta(){}
};

// Defines the Ua Variable
class VaisalaWXT520_Ua : public Variable
{
public:
    VaisalaWXT520_Ua(Sensor *parentSense,
                     const char *uuid = "",
                     const char *varCode = "WXTUa")
      : Variable(parentSense,
                 (const uint8_t)WXT_UA_VAR_NUM,
                 (uint8_t)WXT_UA_RESOLUTION,
                 "relativeHumidity", "percent",
                 varCode, uuid)
    {}
    VaisalaWXT520_Ua()
      : Variable((const uint8_t)WXT_UA_VAR_NUM,
                 (uint8_t)WXT_UA_RESOLUTION,
                 "relativeHumidity", "percent", "WXTUa")
    {}
    ~VaisalaWXT520_Ua(){}
};


// Defines the Rc Variable
class VaisalaWXT520_Rc : public Variable
{
public:
    VaisalaWXT520_Rc(Sensor *parentSense,
                    const char *uuid = "",
                    const char *varCode = "WXTRc")
      : Variable(parentSense,
                 (const uint8_t)WXT_RC_VAR_NUM,
                 (uint8_t)WXT_RC_RESOLUTION,
                 "rainfall", "mm",
                 varCode, uuid)
    {}
    VaisalaWXT520_Rc()
      : Variable((const uint8_t)WXT_RC_VAR_NUM,
                 (uint8_t)WXT_RC_RESOLUTION,
                 "rainfall", "mm", "WXTRc")
    {}
    ~VaisalaWXT520_Rc(){}
};

#endif  // Header Guard
