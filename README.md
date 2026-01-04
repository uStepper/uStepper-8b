# uStepper 8b

The library contains support for driving the stepper, reading out encoder data. A few examples are included to show the functionality of the library.
The library is supported by and tested with Arduino IDE 2.3.7.

For more information, visit www.ustepper.com

## Installation

Installation is split into two parts - Hardware and Library. Both are required to use the uStepper 8b boards.

### Hardware Installation 

To add hardware support for uStepper in the Arduino IDE (2.3.x) do the following:
 - Open Arduino IDE
 - Go to "File -> Preferences"
 - In the "Additional Board URLs" field, replace or add the following URL: https://raw.githubusercontent.com/uStepper/uStepperHardware/master/package_ustepper_index.json
 - Press OK
 - Go to "Tools -> Board -> Board Manager..."
 - Scroll to the bottom (after it has loaded new files), select "uStepper by uStepper ApS," and press "Install"

You have now added uStepper hardware support and should be able to select uStepper 8b under "Tools -> Board."

### Library Installation

To add the uStepper 8b library, follow these steps:

- Open Arduino IDE (Version 2.3.x)
- Go to "Sketch -> Include Library -> Manage Libraries..."
- In the Library Manager, type "uStepper 8b" into the search bar
- Locate "uStepper 8b" in the search results and click "Install"
- Close the Library Manager

## Documentation
The documentation for this library can be found at the following URL:

http://ustepper.com/docs/ustepper8b/html/index.html

### MAC (and a few Windows) Users:
In order to make the uStepper 8b show up in the "ports" list, you need to install the VCP driver from the following link: 
https://www.silabs.com/software-and-tools/usb-to-uart-bridge-vcp-drivers?tab=downloads

##To Do
- Update keywords.txt
- Better comments
- Variable cleanup

## Known Bugs
- none

## Change Log
1.0.0:

- Initial release, based off of uStepper S-lite library version 1.2.1 (https://github.com/uStepper/uStepper-S-lite/archive/refs/tags/1.2.1.zip)

<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a><br /><span xmlns:dct="http://purl.org/dc/terms/" property="dct:title">uStepper</span> by <a xmlns:cc="http://creativecommons.org/ns#" href="www.ustepper.com" property="cc:attributionName" rel="cc:attributionURL">uStepper</a> is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License</a>.
