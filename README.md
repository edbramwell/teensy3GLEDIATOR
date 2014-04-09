teensy3GLEDIATOR
================

Virtual USB COM Port interface understanding GLEDIATOR data pushing them to WS2811 RGB LEDs strips

A small ARDUION sketch implements a virtual COM port which understands the GLEDIATOR protocol.
It uses the OctoWS2811 library to send these GLEDIATOR data to attached RGB strips.

Installation instructions so you can program you TEENSY with the sketch:
* download ARDUINO 1.0.5 and install it
* download and install TEENSYDUINO by following the instructions given on https://www.pjrc.com/teensy/td_download.html. It is sufficient to install only the OctoWS2811 libraries
* Now start the ARDUINO IDE and be sure to have BOARD -> "Teensy 3.1" selected
* Load the sketch into ARDUINO and upload it. If you get an error while the sketch gets checked, please double check that "Teensy 3.1" is you selected board type
* You should have got a new serial port now (e.g. /dev/tty.usbmodem32731 when using OSX). If you work on Windows, you will have to point the hardware installation wizard to the INF file provided. DO NOT USE THE AUTOMATIC MODE - IT WILL NOT WORK. This is because Windows is too stupid to install virtual COM ports without additional information although the USB descriptors are given all the necessary information. On host operationg systems like OSX or LINUX you just get a new serial device without further interaction
* Now you can use GLEDIATOR provided by Solderlabs (http://www.solderlab.de/index.php/software/glediator) to drive your LED strips.

Hint: use RGB format for the output data
