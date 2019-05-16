/*
 *DigiXBeeCellularBypass.cpp
 *This file is part of the EnviroDIY modular sensors library for Arduino
 *
 *Initial library developement done by Sara Damiano (sdamiano@stroudcenter.org).
 *
 *This file is for Digi Cellular XBee's BASED ON UBLOX CHIPS in bypass mode
*/

// Included Dependencies
#include "DigiXBeeCellularBypass.h"
#include "modems/LoggerModemMacros.h"

// Constructors
DigiXBeeCellularBypass::DigiXBeeCellularBypass(Stream* modemStream,
                           int8_t powerPin, int8_t statusPin, bool useCTSStatus,
                           int8_t modemResetPin, int8_t modemSleepRqPin,
                           const char *apn,
                           uint8_t measurementsToAverage)
  : DigiXBee(powerPin, statusPin, useCTSStatus,
             modemResetPin, modemSleepRqPin,
             measurementsToAverage),
    #ifdef MS_DIGIXBEECELLULARBYPASS_DEBUG_DEEP
    _modemATDebugger(*modemStream, DEBUGGING_SERIAL_OUTPUT),
    _tinyModem(_modemATDebugger)
    #else
    _tinyModem(*modemStream)
    #endif
{
    _apn = apn;
    TinyGsmClient *tinyClient = new TinyGsmClient(_tinyModem);
    _tinyClient = tinyClient;
}


MS_MODEM_DID_AT_RESPOND(DigiXBeeCellularBypass);
MS_MODEM_IS_INTERNET_AVAILABLE(DigiXBeeCellularBypass);
MS_MODEM_IS_MEASUREMENT_COMPLETE(DigiXBeeCellularBypass);
MS_MODEM_ADD_SINGLE_MEASUREMENT_RESULT(DigiXBeeCellularBypass);
MS_MODEM_CONNECT_INTERNET(DigiXBeeCellularBypass);
MS_MODEM_DISCONNECT_INTERNET(DigiXBeeCellularBypass);
MS_MODEM_GET_NIST_TIME(DigiXBeeCellularBypass);


bool DigiXBeeCellularBypass::extraModemSetup(void)
{
    bool success = true;
    delay(1010);  // Wait the required guard time before entering command mode
    MS_DBG(F("Putting XBee into command mode..."));
    _tinyModem.streamWrite(GF("+++"));  // enter command mode
    if (success &= _tinyModem.waitResponse(2000, F("OK\r")) == 1)
    {
        MS_DBG(F("Setting I/O Pins..."));
        // Set DIO8 to be used for sleep requests
        // NOTE:  Only pin 9/DIO8/DTR can be used for this function
        _tinyModem.sendAT(F("D8"),1);
        success &= _tinyModem.waitResponse(F("OK\r")) == 1;
        // Turn on status indication pin - it will be HIGH when the XBee is awake
        // NOTE:  Only pin 13/ON/SLEEPnot/DIO9 can be used for this function
        _tinyModem.sendAT(F("D9"),1);
        success &= _tinyModem.waitResponse(F("OK\r")) == 1;
        // Turn on CTS pin - it will be LOW when the XBee is ready to receive commands
        // This can be used as proxy for status indication if the true status pin is not accessible
        // NOTE:  Only pin 12/DIO7/CTS can be used for this function
        _tinyModem.sendAT(F("D7"),1);
        success &= _tinyModem.waitResponse(F("OK\r")) == 1;
        // Put the XBee in pin sleep mode
        MS_DBG(F("Setting Sleep Options..."));
        _tinyModem.sendAT(F("SM"),1);
        success &= _tinyModem.waitResponse(F("OK\r")) == 1;
        // Disassociate from network for lowest power deep sleep
        _tinyModem.sendAT(F("SO"),0);
        success &= _tinyModem.waitResponse(F("OK\r")) == 1;
        MS_DBG(F("Setting Other Options..."));
        // Disable remote manager, USB Direct, and LTE PSM
        // NOTE:  LTE-M's PSM (Power Save Mode) sounds good, but there's no
        // easy way on the LTE-M Bee to wake the cell chip itself from PSM,
        // so we'll use the Digi pin sleep instead.
        _tinyModem.sendAT(F("DO"),0);
        success &= _tinyModem.waitResponse(F("OK\r")) == 1;
        // Make sure USB direct won't be pin enabled on XBee3 units
        _tinyModem.sendAT(F("P0"),0);
        success &= _tinyModem.waitResponse(F("OK\r")) == 1;
        // Make sure pins 7&8 are not set for USB direct on XBee3 units
        _tinyModem.sendAT(F("P1"),0);
        success &= _tinyModem.waitResponse(F("OK\r")) == 1;
        MS_DBG(F("Setting Cellular Carrier Options..."));
        // Cellular carrier profile - AT&T
        // Hologram says they can use any network, but I've never succeeded with anything but AT&T
        _tinyModem.sendAT(F("CP"),2);
        success &= _tinyModem.waitResponse(F("OK\r")) == 1;
        // Cellular network technology - LTE-M Only
        // LTE-M XBee connects much faster on AT&T/Hologram when set to LTE-M only (instead of LTE-M/NB IoT)
        _tinyModem.sendAT(F("N#"),2);
        success &= _tinyModem.waitResponse(F("OK\r")) == 1;
        MS_DBG(F("Turning on Bypass Mode..."));
        // Turn on bypass mode
        _tinyModem.sendAT(F("AP5"));
        success &= _tinyModem.waitResponse(F("OK\r")) == 1;
        // Write changes to flash
        _tinyModem.sendAT(F("WR"));
        success &= _tinyModem.waitResponse(F("OK\r")) == 1;
        // Apply changes
        _tinyModem.sendAT(F("AC"));
        success &= _tinyModem.waitResponse(F("OK\r")) == 1;
        // Force reset to actually enter bypass mode - this effectively exits bypass mode
        MS_DBG(F("Resetting the module to reboot in bypass mode..."));
        _tinyModem.sendAT(F("FR"));
        success &= _tinyModem.waitResponse(F("OK\r")) == 1;
        delay(200);  // Allow the unit to reset
        // re-initialize
        MS_DBG(F("Attempting to reconnect to the u-blox module..."));
        success &= _tinyModem.init();
        _modemName = _tinyModem.getModemName();
    }
    else success = false;
    if (success) MS_DBG(F("... Setup successful!"));
    else MS_DBG(F("... failed!"));
    return success;
}
