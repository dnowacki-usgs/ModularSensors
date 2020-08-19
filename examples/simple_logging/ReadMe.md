[//]: # ( @page simple_logging_example Simple Logging Example )
# Using ModularSensors to save data to an SD card

This shows the simplest use of a "logger" object.
That is, creating an array of variable objects and then creating a logger object that utilizes those variables to update all of the variable results together and save the data to a SD card.
The processor then goes to sleep between readings.
This example has a placeholder to show users where to insert sensors, which can be found in menu_a_la_carte.ino.

This is the example you should use to deploy a logger somewhere where you don't want or have access to a way of streaming live data and you won't want to upload data to the Monitor My Watershed data portal.
Those lines should be removed when using the example on your own board.

_______

[//]: # ( @section simple_logging_full The Complete Example Code: )
