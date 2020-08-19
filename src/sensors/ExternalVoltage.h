/**
 * @file ExternalVoltage.h *
 * @copyright 2020 Stroud Water Research Center
 * Part of the EnviroDIY ModularSensors library for Arduino
 * @author Written By: Bobby Schulz <schu3119@umn.edu>
 * Edited by Sara Geleskie Damiano <sdamiano@stroudcenter.org>
 * Adapted from CampbellOBS3.h by Sara Geleskie Damiano
 * <sdamiano@stroudcenter.org>
 *
 * @brief This file contains the ExternalVoltage sensor subclass and the
 * ExternalVoltage_Volt variable subclass.
 *
 * These are used for any voltage measureable on a TI ADS1115 or ADS1015.  There
 * is a multiplier allowed for a voltage divider between the raw voltage and the
 * ADS.
 *
 * This depends on the soligen2010 fork of the Adafruit ADS1015 library.
 */
/* clang-format off */
/**
 * @defgroup analog_group Analog Sensors via TI ADS1x15
 * The Sensor and Variable objects for all analog sensors requiring
 * analog-to-digital conversion by TI ADS1x15.
 *
 * @ingroup the_sensors
 *
 * @tableofcontents
 * @m_footernavigation
 *
 * @section ads1x15_intro Introduction
 *
 * Many sensors output simple analog voltages and leave the conversion to a digital
 * signal and final result up to the user.  These types of sensors are supported in
 * Modular sensors by way of a Texas Instruments ADS1115 or ADS1015.  The TI ADS1115 ADD
 * is a precision, low-power, 16-bit, I2C-compatible, analog-to-digitalconverter (ADC).
 * It is built into the EnviroDIY Mayfly.  The ADS1015 is a very similar ADC with 12-bit
 * resolution and a slightly lower price point.  Both chips are widely available in
 * Arduino-ready breakouts.
 *
 * ModularSensors always uses the TI ADS1115 (also ADS1113 or ADS1114) by default, but
 * if you wish to use a 12 bit TI ADS1015 (also ADS1013 or ADS1014) you can compile with
 * the build flag ```-DMS_USE_ADS1015```.
 *
 * In the majority of break-out boards, and on the Mayfly, the I2C address of the
 * ADS1x15 is set as 0x48 by tying the address pin to ground.  Up to four of these ADD's
 * be used by changing the address value by changing the connection of the address pin
 * on the ADS1x15.  The ADS1x15 requires an input voltage of 2.0-5.5V, but *this library
 * always assumes the ADS is powered with 3.3V*.
 *
 * Communication with the ADS1x15 depends on the
 * [soligen2010 fork of the Adafruit ADS1015 library](https://github.com/soligen2010/Adafruit_ADS1X15).
 *
 * @note We do *not* use the Adafruit library! The soligen2010 fork corrects some errors
 * in the Adafruit library.  Until those corrections are pulled into the main library, we
 * use the fork instead.
 *
 * @section ads1x15_specs Specifications
 * @note *In all cases, we assume that the ADS1x15 is powered at 3.3V and set the ADC's internal gain to 1x.
 * This divices the bit resolution over the range of 0-4.096V.
 * - Response time: < 1ms
 * - Resample time: 860 samples per second (~1.2ms)
 * - Range:
 *   - Range is determined by supply voltage - No more than VDD + 0.3 V r 5.5 V
 *     (whichever is smaller) must be applied to this device.
 *   - 0 - 3.6V [when ADC is powered at 3.3V]
 * - Accuracy:
 *   - 16-bit ADC: < 0.25% (gain error), <0.25 LSB (offset errror)
 *   - 12-bit ADC: < 0.15% (gain error), <3 LSB (offset errror)
 * - Resolution:
 *   - 16-bit ADC:
 *     - without voltage divider:  0.125 mV
 *   - 12-bit ADC:
 *     - without voltage divider:  2 mV
 *   @note 1 bit of resolution is lost in single-ended reading.  The maximum possible
 * resolution is over the differential range from negative to positive full scale, a
 * single ended reading is only over the range from 0 to positive full scale).
 *
 * @section ads1x15_datasheet Sensor Datasheet *
 * Technical specifications for the TI ADS1115 can be found at: http://www.ti.com/product/ADS1115
 * For the ADS1015, see: https://www.ti.com/product/ADS1015
 * [ADS1115 Datasheet](https://github.com/EnviroDIY/ModularSensors/wiki/Sensor-Datasheets/TI-ADS101x-Analog-to-Digital-Converter.pdf)
 * [ADS1015 Datasheet](https://github.com/EnviroDIY/ModularSensors/wiki/Sensor-Datasheets/TI-ADS111x-Analog-to-Digital-Converter.pdf)
 */
/* clang-format on */
/* clang-format off */
/**
 * @defgroup ext_volt_group TI ADS1x15 External Voltage Sensor
 * Classes for simple external analog voltage measurements.
 *
 * @ingroup analog_group
 *
 * @tableofcontents
 * @m_footernavigation
 *
 * @section ext_volt_intro Introduction
 *
 * Analog data output is supported in ModularSensors by way of the
 * Texas Instruments ADS1115.
 *
 * The External Voltage module is used for any case where the voltage itself is
 * the desired value (as for an external battery).  It can also be used in
 * combination with a [calculated variable](@ref calc_var_page) to support any
 * other analog sensor not explicity supported by ModularSensors.  To increase
 * the range available for voltage measurements, this module supports the use of
 * a voltage divider.
 *
 * If you are working with an EnviroDIY Mayfly, the easiest voltage divider to
 * connect is the Grove voltage divider sold by seeed studio.  The grove voltage
 * divider is a simple voltage divider designed to measure high external
 * voltages on a low voltage ADC.  This module employs a variable gain via two
 * pairs of voltage dividers, and a unity gain amplification to reduce output
 * impedance of the module.
 *
 * @section ext_volt_datasheet Sensor Datasheet
 * @see ads1x15_datasheet
 * Technical specifications for the Grove Voltage Divider can be found at:
 * http://wiki.seeedstudio.com/Grove-Voltage_Divider
 *
 * @section ext_volt_sensor The External Voltage Sensor
 * @ctor_doc{ExternalVoltage, int8_t powerPin, uint8_t adsChannel, float gain, uint8_t i2cAddress, uint8_t measurementsToAverage}
 * @subsection ext_volt_timing Sensor Timing
 * The timing used for simple external voltage measurements is that of the ADS1x15.
 * - Response time: < 1ms
 * - Resample time: max of ADC (860/sec)
 * @subsection ext_volt_flags Build flags
 * - ```-D MS_USE_ADS1015```
 *      - switches from the 16-bit ADS1115 to the 12 bit ADS1015
 *
 * @section ext_volt_volt Voltage Output
 *   - Range:
 *     - without voltage divider:  0 - 3.6V [when ADC is powered at 3.3V]
 *     - 1/gain = 3x: 0.3 ~ 12.9V
 *     - 1/gain = 10x: 1 ~ 43V
 *   - Accuracy:
 *     - 16-bit ADC: < 0.25% (gain error), <0.25 LSB (offset errror)
 *     - 12-bit ADC: < 0.15% (gain error), <3 LSB (offset errror)
 *   - Resolution:
 *     - 16-bit ADC:
 *       - without voltage divider:  0.125 mV
 *       - 1/gain = 3x: 0.375 mV
 *       - 1/gain = 10x: 1.25 mV
 *     - 12-bit ADC:
 *       - without voltage divider:  2 mV
 *       - 1/gain = 3x: 6 mV
 *       - 1/gain = 10x: 20 mV *
 *   - Result stored in sensorvalues[0]
 *   - Reported as volts (V)
 *   - Default variable code is extVoltage
 * @variabledoc{ext_volt_volt,ExternalVoltage,Volt,extVoltage}
 *
 * ___
 * @section ext_volt_examples Example Code
 * The TI ADS1X15 external voltage sensor is used in the @menulink{ext_volt}
 * example.
 *
 * @menusnip{ext_volt}
 */
/* clang-format on */

// Header Guards
#ifndef SRC_SENSORS_EXTERNALVOLTAGE_H_
#define SRC_SENSORS_EXTERNALVOLTAGE_H_

// Debugging Statement
// #define MS_EXTERNALVOLTAGE_DEBUG

#ifdef MS_EXTERNALVOLTAGE_DEBUG
#define MS_DEBUGGING_STD "ExternalVoltage"
#endif

// Included Dependencies
#include "ModSensorDebugger.h"
#undef MS_DEBUGGING_STD
#include "VariableBase.h"
#include "SensorBase.h"

// Sensor Specific Defines

/// Sensor::_numReturnedValues; the ADS1115 can report 1 value.
#define EXT_VOLT_NUM_VARIABLES 1
/// Sensor::_warmUpTime_ms; the ADS1115 warms up in 2ms.
#define EXT_VOLT_WARM_UP_TIME_MS 2
/**
 * @brief Sensor::_stabilizationTime_ms; the ADS1115 is stable 0ms after warm-up
 *
 * We assume a voltage is instantly ready.
 */
#define EXT_VOLT_STABILIZATION_TIME_MS 0
/**
 * @brief Sensor::_measurementTime_ms; the ADS1115 takes 0ms to complete a
 * measurement.
 */
#define EXT_VOLT_MEASUREMENT_TIME_MS 0

/// Variable number; voltage is stored in sensorValues[0].
#define EXT_VOLT_VAR_NUM 0
#ifdef MS_USE_ADS1015
/// Decimals places in string representation; voltage should have 1.
#define EXT_VOLT_RESOLUTION 1
#else
/// Decimals places in string representation; voltage should have 4.
#define EXT_VOLT_RESOLUTION 4
#endif

/// The assumed address of the ADS1115, 1001 000 (ADDR = GND)
#define ADS1115_ADDRESS 0x48

/* clang-format off */
/**
 * @brief The Sensor sub-class for the
 * [external votlage as measured by TI ADS1115 or ADS1015](@ref ext_volt_group).
 *
 * @ingroup ext_volt_group
 */
/* clang-format on */
class ExternalVoltage : public Sensor {
 public:
    /**
     * @brief Construct a new External Voltage object - need the power pin and
     * the data channel on the ADS1x15
     *
     * The gain value, I2C address, and number of measurements to average are
     * optional.  If nothing is given a 1x gain is used.
     *
     * @param powerPin The pin on the mcu controlling power to the sensor
     * Use -1 if it is continuously powered.
     * @param adsChannel The ADS channel of interest (0-3).
     * @param gain The gain multiplier, if a voltage divider is used.
     * @param i2cAddress The I2C address of the ADS 1x15, default is 0x48 (ADDR
     * = GND)
     * @param measurementsToAverage The number of measurements to take and
     * average before giving a "final" result from the sensor; optional with a
     * default value of 1.
     */
    ExternalVoltage(int8_t powerPin, uint8_t adsChannel, float gain = 1,
                    uint8_t i2cAddress            = ADS1115_ADDRESS,
                    uint8_t measurementsToAverage = 1);
    /**
     * @brief Destroy the External Voltage object
     */
    ~ExternalVoltage();

    /**
     * @copydoc Sensor::getSensorLocation()
     */
    String getSensorLocation(void) override;

    /**
     * @copydoc Sensor::addSingleMeasurementResult()
     */
    bool addSingleMeasurementResult(void) override;

 private:
    uint8_t _adsChannel;
    float   _gain;
    uint8_t _i2cAddress;
};


// The single available variable is voltage
/* clang-format off */
/**
 * @brief The Variable sub-class used for the
 * [voltage output](@ref ext_volt_volt) from a
 * [TI ADS1115 or ADS1015](@ref ext_volt_group).
 *
 * @ingroup ext_volt_group
 */
/* clang-format on */
class ExternalVoltage_Volt : public Variable {
 public:
    /**
     * @brief Construct a new ExternalVoltage_Volt object.
     *
     * @param parentSense The parent ExternalVoltage providing the result
     * values.
     * @param uuid A universally unique identifier (UUID or GUID) for the
     * variable; optional with the default value of an empty string.
     * @param varCode A short code to help identify the variable in files;
     * optional with a default value of extVoltage
     */
    explicit ExternalVoltage_Volt(ExternalVoltage* parentSense,
                                  const char*      uuid    = "",
                                  const char*      varCode = "extVoltage")
        : Variable(parentSense, (const uint8_t)EXT_VOLT_VAR_NUM,
                   (uint8_t)EXT_VOLT_RESOLUTION, "voltage", "volt", varCode,
                   uuid) {}
    /**
     * @brief Construct a new ExternalVoltage_Volt object.
     *
     * @note This must be tied with a parent ExternalVoltage before it can be
     * used.
     */
    ExternalVoltage_Volt()
        : Variable((const uint8_t)EXT_VOLT_VAR_NUM,
                   (uint8_t)EXT_VOLT_RESOLUTION, "voltage", "volt",
                   "extVoltage") {}
    /**
     * @brief Destroy the ExternalVoltage_Volt object - no action needed.
     */
    ~ExternalVoltage_Volt() {}
};

#endif  // SRC_SENSORS_EXTERNALVOLTAGE_H_
