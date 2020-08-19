/**
 * @file MaximDS18.h
 * @copyright 2020 Stroud Water Research Center
 * Part of the EnviroDIY ModularSensors library for Arduino
 * @author Sara Geleskie Damiano <sdamiano@stroudcenter.org>
 *
 * @brief Contains the MaximDS18 sensor subclass and the MaximDS18_Temp variable
 * subclass.
 *
 * These are for the Maxim DS18B20, DS18S20, MAX31820, DS1822, and DS1820
 * vtemperature sensors.
 *
 * This depends on Dallas Temperature library, which itself is dependent on the
 * OneWire library.
 */
/* clang-format off */
/**
 * @defgroup ds18_group Maxim DS18
 * Classes for the Maxim DS18 one-wire temperature sensors.
 *
 * @ingroup the_sensors
 *
 * @tableofcontents
 * @m_footernavigation
 *
 * @section ds18_intro Introduction
 *
 * The Maxim temperature probes communicate using the OneWire library, which can
 * be used on any digital pin on any of the supported boards.  The same module
 * should work with a
 * [DS18B20](https://www.maximintegrated.com/en/products/analog/sensors-and-sensor-interface/DS18B20.html),
 * [DS18S20](https://www.maximintegrated.com/en/products/analog/sensors-and-sensor-interface/DS18S20.html),
 * [DS1822](https://www.maximintegrated.com/en/products/analog/sensors-and-sensor-interface/DS1822.html),
 * [MAX31820](https://www.maximintegrated.com/en/products/analog/sensors-and-sensor-interface/MAX31820.html),
 * and the no-longer-sold
 * [DS1820](https://www.maximintegrated.com/en/products/analog/sensors-and-sensor-interface/DS1820.html)
 * sensor.  These sensors can be attached to a 3.0-5.5V power source or they can
 * take "parasitic power" from the data line.  When using the more typical setup
 * with power, ground, and data lines, a 4.7k resistor must be attached as a
 * pull-up between the data and power lines.  The one-wire communication
 * protocol is slow and _interrupts are turned off during communication_.  Keep
 * this in mind if using this sensor in combination with a rain gauge or other
 * interrupt-driven sensor.
 *
 * The resolution of the DS18B20, DS1822, and MAX31820 temperature sensors are
 * user-configurable to 9, 10, 11, or 12 bits, corresponding to increments of
 * 0.5°C, 0.25°C, 0.125°C, and 0.0625°C, respectively.
 * The default resolution at power-up is 12-bit, unless it has previously been
 * set to something else.  The resolution of the DS18S20 is set at 9-bit
 *
 * The OneWire hex address of the sensor, the Arduino pin controlling power
 * on/off, and the Arduino pin sending and receiving data are required for the
 * sensor constructor.  The OneWire address is an array of 8 hex values, for
 * example:  {0x28, 0x1D, 0x39, 0x31, 0x2, 0x0, 0x0, 0xF0}.  To get the address
 * of your sensor, plug a single sensor into your device and run the
 * [oneWireSearch](https://github.com/milesburton/Arduino-Temperature-Control-Library/blob/master/examples/oneWireSearch/oneWireSearch.ino)
 * example or the
 * [Single](https://github.com/milesburton/Arduino-Temperature-Control-Library/blob/master/examples/Single/Single.pde)
 * example provided within the Dallas Temperature library.  The sensor address
 * is programmed at the factory and cannot be changed.
 *
 * @section ds18_datasheet Sensor Datasheet
 * - [DS18B20 Datasheet](https://github.com/EnviroDIY/ModularSensors/wiki/Sensor-Datasheets/Maxim-DS18B20-1-Wire-Temperature-Probe-Datasheet.pdf)
 * - [DS18S20 Datasheet](https://github.com/EnviroDIY/ModularSensors/wiki/Sensor-Datasheets/Maxim-DS18S20-1-Wire-Temperature-Probe-Datasheet.pdf)
 * - [DS1822 Datasheet](https://github.com/EnviroDIY/ModularSensors/wiki/Sensor-DatasheetsMaxim-DS1822-1-Wire-Temperature-Probe-Datasheet.pdf)
 * - [MAX31820 Datasheet](https://github.com/EnviroDIY/ModularSensors/wiki/Sensor-Datasheets/Maxim-MAX31820-1-Wire-Temperature-Probe-Datasheet.pdf)
 *
 * @section ds18_sensor The DS18 Sensor
 * @ctor_doc{MaximDS18, DeviceAddress OneWireAddress, int8_t powerPin, int8_t dataPin, uint8_t measurementsToAverage}
 * @subsection ds18_timing Sensor Timing
 * - Max time to take reading at 12-bit: 750ms
 * - Reset time is < 480 µs
 *
 * @section ds18_temp Temperature Output
 *   - Range is -55°C to 125°C
 *   - Accuracy:
 *     - ± 0.5°C from -10°C to +85°C for DS18S20 and DS18B20
 *     - ± 2°C for DS1822 and MAX31820
 *   - Result stored in sensorValues[0]
 *   - Resolution:
 *     - 0.0625°C for DS18B20, DS1822, and MAX31820 (12-bit)
 *     - 0.5°C for DS18S20 (9-bit)
 *   - Reported as degrees Celsius (°C)
 *   - Default variable code is DS18Temp
 * @variabledoc{ds18_temp,MaximDS18,Temp,DS18Temp}
 *
 * ___
 * @section ds18_examples Example Code
 * The Maxim DS18 is used in the @menulink{ds18} example.
 *
 * @menusnip{ds18}
 */
/* clang-format on */

// Header Guards
#ifndef SRC_SENSORS_MAXIMDS18_H_
#define SRC_SENSORS_MAXIMDS18_H_

// Debugging Statement
// #define MS_MAXIMDS18_DEBUG

#ifdef MS_MAXIMDS18_DEBUG
#define MS_DEBUGGING_STD "MaximDS18"
#endif

// Included Dependencies
#include "ModSensorDebugger.h"
#undef MS_DEBUGGING_STD
#include "VariableBase.h"
#include "SensorBase.h"
#include <DallasTemperature.h>
#include <OneWire.h>

// Sensor Specific Defines

/// Sensor::_numReturnedValues; the DS18 can report 1 value.
#define DS18_NUM_VARIABLES 1
/// Sensor::_warmUpTime_ms; the DS18 warms up in 2ms.
#define DS18_WARM_UP_TIME_MS 2
/// Sensor::_stabilizationTime_ms; the DS18 is stable after 0ms.
#define DS18_STABILIZATION_TIME_MS 0
/// Sensor::_measurementTime_ms; the DS18 takes 750ms to complete a measurement.
#define DS18_MEASUREMENT_TIME_MS 750
/// Variable number; temperature is stored in sensorValues[0].
#define DS18_TEMP_VAR_NUM 0
/// Decimals places in string representation; temperature should have 4.
#define DS18_TEMP_RESOLUTION 4

/* clang-format off */
/**
 * @brief The Sensor sub-class for the
 * [DS18 one-wire temperature sensors](@ref ds18_group).
 *
 * @ingroup ds18_group
 */
/* clang-format on */
class MaximDS18 : public Sensor {
 public:
    /**
     * @brief Construct a new Maxim DS18
     *
     * Use this version for more than one sensor attached to the OneWire bus.
     *
     * @param OneWireAddress The unique address of the sensor.  Should be an
     * array of 8 values.  To get the address of your sensor, plug a single
     * sensor into your device and run the
     * [oneWireSearch](https://github.com/milesburton/Arduino-Temperature-Control-Library/blob/master/examples/oneWireSearch/oneWireSearch.ino)
     * example or the
     * [Single](https://github.com/milesburton/Arduino-Temperature-Control-Library/blob/master/examples/Single/Single.pde)
     * example provided within the Dallas Temperature library.  The sensor
     * address is programmed at the factory and cannot be changed.
     * @param powerPin The pin on the mcu controlling power to the DS18, if
     * using a separate power pin.  Use -1 if the DS18 is continuously powered
     * or you are using "parasitic" power.
     * - Requires a 3.0 - 5.5V power source
     * @param dataPin The pin on the mcu of the OneWire bus.
     * @param measurementsToAverage The number of measurements to take and
     * average before giving a "final" result from the sensor; optional with a
     * default value of 1.
     */
    MaximDS18(DeviceAddress OneWireAddress, int8_t powerPin, int8_t dataPin,
              uint8_t measurementsToAverage = 1);
    /**
     * @brief Construct a new Maxim DS18.
     *
     * Use this version of the constructor when there is only one temperature
     * sensor attached to the OneWire bus and the address of that sensor is not
     * known.
     *
     * @param powerPin The pin on the mcu controlling power to the DS18, if
     * using a separate power pin.  Use -1 if the DS18 is continuously powered
     * or you are using "parasitic" power.
     * - Requires a 3.0 - 5.5V power source
     * @param dataPin The pin on the mcu of the OneWire bus.
     * @param measurementsToAverage The number of measurements to take and
     * average before giving a "final" result from the sensor; optional with a
     * default value of 1.
     */
    MaximDS18(int8_t powerPin, int8_t dataPin,
              uint8_t measurementsToAverage = 1);
    /**
     * @brief Destroy the Maxim DS18 object
     */
    ~MaximDS18();

    /**
     * @brief Do any one-time preparations needed before the sensor will be able
     * to take readings.
     *
     * This sets the pin modes and verifies the DS18's address.  It also
     * verifies that the sensor is connected, reporting maximum resolution, and
     * operating in ASYNC mode and updates the #_sensorStatus.  The sensor must
     * be powered for setup.
     *
     * @return **bool** True if the setup was successful.
     */
    bool setup(void) override;
    /**
     * @copydoc Sensor::getSensorLocation()
     */
    String getSensorLocation(void) override;

    /**
     * @brief Tell the sensor to start a single measurement, if needed.
     *
     * This also sets the #_millisMeasurementRequested timestamp.
     *
     * @note This function does NOT include any waiting for the sensor to be
     * warmed up or stable!
     *
     * @return **bool** True if the start measurement function completed
     * successfully. successfully.
     */
    bool startSingleMeasurement(void) override;
    /**
     * @copydoc Sensor::addSingleMeasurementResult()
     */
    bool addSingleMeasurementResult(void) override;

 private:
    DeviceAddress _OneWireAddress;
    bool          _addressKnown;
    // Setup an internal OneWire instance to communicate with any OneWire
    // devices (not just Maxim/Dallas temperature ICs)
    OneWire _internalOneWire;
    // Set up the internal a "Dallas Temperature" instance for communication
    // specifically with the temperature sensors.
    DallasTemperature _internalDallasTemp;
    // Turns the address into a printable string
    String makeAddressString(DeviceAddress OneWireAddress);
};


/* clang-format off */
/**
 * @brief The Variable sub-class used for the
 * [temperature output](@ref ds18_temp) from a
 * [Maxim one-wire temperature sensor](@ref ds18_group).
 *
 * @ingroup ds18_group
 */
/* clang-format on */
class MaximDS18_Temp : public Variable {
 public:
    /**
     * @brief Construct a new MaximDS18_Temp object.
     *
     * @param parentSense The parent MaximDS18 providing the result values.
     * @param uuid A universally unique identifier (UUID or GUID) for the
     * variable; optional with the default value of an empty string.
     * @param varCode A short code to help identify the variable in files;
     * optional with a default value of "DS18Temp".
     */
    explicit MaximDS18_Temp(MaximDS18* parentSense, const char* uuid = "",
                            const char* varCode = "DS18Temp")
        : Variable(parentSense, (const uint8_t)DS18_TEMP_VAR_NUM,
                   (uint8_t)DS18_TEMP_RESOLUTION, "temperature",
                   "degreeCelsius", varCode, uuid) {}
    /**
     * @brief Construct a new MaximDS18_Temp object.
     *
     * @note This must be tied with a parent MaximDS18 before it can be used.
     */
    MaximDS18_Temp()
        : Variable((const uint8_t)DS18_TEMP_VAR_NUM,
                   (uint8_t)DS18_TEMP_RESOLUTION, "temperature",
                   "degreeCelsius", "DS18Temp") {}
    /**
     * @brief Destroy the MaximDS18_Temp object - no action needed.
     */
    ~MaximDS18_Temp() {}
};

#endif  // SRC_SENSORS_MAXIMDS18_H_
