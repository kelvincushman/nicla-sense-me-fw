# Nicla

[![Check Arduino status](https://github.com/arduino/nicla-sense-me-fw/actions/workflows/check-arduino.yml/badge.svg)](https://github.com/arduino/nicla-sense-me-fw/actions/workflows/check-arduino.yml)
[![Compile Examples status](https://github.com/arduino/nicla-sense-me-fw/actions/workflows/compile-examples.yml/badge.svg)](https://github.com/arduino/nicla-sense-me-fw/actions/workflows/compile-examples.yml)
[![Check License status](https://github.com/arduino/nicla-sense-me-fw/actions/workflows/check-license.yml/badge.svg)](https://github.com/arduino/nicla-sense-me-fw/actions/workflows/check-license.yml)
[![Spell Check status](https://github.com/arduino/nicla-sense-me-fw/actions/workflows/spell-check-task.yml/badge.svg)](https://github.com/arduino/nicla-sense-me-fw/actions/workflows/spell-check-task.yml)
[![Sync Labels status](https://github.com/arduino/nicla-sense-me-fw/actions/workflows/sync-labels.yml/badge.svg)](https://github.com/arduino/nicla-sense-me-fw/actions/workflows/sync-labels.yml)

This repo contains everything needed to program Nicla Sense ME and to control it from another device. Further documentation can be found on the [Arduino Docs website](https://docs.arduino.cc/hardware/nicla-sense-me).

Nicla Sense ME belongs to Arduino Mbed OS boards and its core is available [here](https://github.com/arduino/ArduinoCore-mbed).
The packaged core can also be downloaded from Arduino IDE as 'Arduino Mbed OS Nicla Boards'

Table of Contents:
- [Nicla](#nicla)
  - [Repo structure](#repo-structure)
  - [Main use cases](#main-use-cases)
    - [Nicla standalone mode](#nicla-standalone-mode)
    - [Control Nicla from an arduino board through ESLOV](#control-nicla-from-an-arduino-board-through-eslov)
    - [Control Nicla from a PC - web server](#control-nicla-from-a-pc---web-server)
    - [Control Nicla from a PC - command line tool](#control-nicla-from-a-pc---command-line-tool)
    - [Update Nicla firmware](#update-nicla-firmware)
      - [Update procedure through BLE:](#update-procedure-through-ble)
      - [Update procedure through ESLOV:](#update-procedure-through-eslov)
  
## Repo structure

------------
[Arduino_BHY2](Arduino_BHY2) - is the library to be included when making sketches for Nicla. It can be used for configuring bhi's sensors and for retrieving bhi's sensors data either from a sketch running on Nicla (standalone mode)  or from an external device (through ESLOV or BLE). 

In [examples](Arduino_BHY2/examples) there are already working examples for both scenarios:
- Standalone mode - [Standalone](Arduino_BHY2/examples/Standalone/Standalone.ino) exploits bhi's sensors directly from Nicla.
- Control from external device mode - [App](Arduino_BHY2/examples/App/App.ino) waits for external stimuli, coming from ESLOV or BLE channels.
- Upload a Fail Safe Firmware - [Fail_Safe_flasher](Arduino_BHY2/examples/Fail_Safe_flasher/Fail_Safe_flasher.ino) uploads a binary to Anna's QSPIFlash. Pressing the button 3 times, Nicla checks if a Fail Safe firmware is present and, if it is valid, runs it.
------------

[Arduino_BHY2Host](Arduino_BHY2Host) - is the library that an Arduino board should include in order to control the Nicla through the ESLOV port.
  It can also act as a passthrough, to allow the control of Nicla from a PC.
  There is an example for both these use cases in [examples](Arduino_BHY2Host/examples):
  - Act as passthrough - [Passthrough](Arduino_BHY2Host/examples/Passthrough/Passthrough.ino)
  - Control Nicla sensors directly - [Accelerometer](Arduino_BHY2Host/examples/Accelerometer/Accelerometer.ino), [Orientation](Arduino_BHY2Host/examples/Orientation/Orientation.ino), [Temperature](Arduino_BHY2Host/examples/Temperature/Temperature.ino)
  
------------

[bootloader](bootloader)  - contains the source code for Nicla's bootloader.

------------

[tools](tools/bhy-controller) - contains the source code of the command line tool to control Nicla from a PC.
  There is also a webserver mode that allows to control Nicla from a browser on your PC.
  The `bhy-controller` executable files for the main operating systems can be downloaded from the [latest release](https://github.com/arduino/nicla-sense-me-fw/releases/latest#:~:text=Assets).

------------


## Main use cases

### Nicla standalone mode
In this use case, Nicla will be able to control its own sensors without the need for an external host.  
- Make a standalone sketch importing [Arduino_BHY2](Arduino_BHY2) library, follow this [example](Arduino_BHY2/examples/Standalone/Standalone.ino) to write the code.
- Select Nicla Sense ME as the compilation target, then compile and upload.


### Control Nicla from an arduino board through ESLOV
- Upload the [App](Arduino_BHY2/examples/App/App.ino) example to Nicla.
- Use an Arduino board, like a MKR, acting as a host by importing [Arduino_BHY2Host](Arduino_BHY2Host) and following the [example](Arduino_BHY2Host/examples/Accelerometer/Accelerometer.ino).
- Upload the host sketch to the Arduino MKR board.
- Connect Nicla to the MKR board with an ESLOV cable or I2C pins.


### Control Nicla from a PC - web server 
A local web server has been implemented to manage Nicla from a browser. See [browser compatibility](https://developer.mozilla.org/en-US/docs/Web/API/Web_Bluetooth_API#browser_compatibility).

BLE is used instead of ESLOV, thus there is no need for an intermediary arduino board.
- Upload the [App](Arduino_BHY2/examples/App/App.ino) example to Nicla.
- Access the command line tool folder.
- Execute the following command `./bhy webserver` to start the local web server.
- Open the `http://localhost:8000/index.html` web page with a browser listed in the compatibility list.
  NB: make sure that WebBLE is enabled! If it is not, enable it from chrome://flags, setting "Experimental Web Platform features".

There are two web pages
- `sensor.html` allows to configure the sensors and read their values in real time.
- `dfu.html` allows to update the firmware of either Nicla or bhi.


### Control Nicla from a PC - command line tool
The command line tool can be used to update the firmware of Nicla or bhi, manage Nicla's sensors and read their values in real time. Refer to [tools](tools/bhy-controller) for the list of available commands. 
Here the ESLOV protocol is employed, so an arduino board is needed between Nicla and the PC.
- Upload the [App](Arduino_BHY2/examples/App/App.ino) example to Nicla.
- Upload the [Passthrough](Arduino_BHY2Host/examples/Passthrough/Passthrough.ino) example to an arduino board.
- Connect the arduino board to your PC via USB.
- Connect the arduino board to Nicla through the ESLOV port.
- Access the command line tool folder
- Refer to [tools](tools/bhy-controller) for the list of available commands.


### Update Nicla firmware
The procedure to update the firmware is the same for both bhi and Nicla. You just need to specify the target during the procedure.
#### Update procedure through BLE:
- Follow these steps [Control Nicla from a PC - web server](#control-nicla-from-a-pc---web-server).
- Select _**DFU**_ in the page located at `http://localhost:8000/index.html` - or directly go to `http://localhost:8000/dfu.html`.
- Select the target (bhi or nicla).
- Select the .bin firmware file.
- Click on update and wait for the transfer to complete.
Then, Nicla will reset and the firmware will be updated.

#### Update procedure through ESLOV:
- Follow [Control Nicla from a PC - command line tool](#control-nicla-from-a-pc---command-line-tool)
- Execute the command `./bhy dfu -p YOUR_PORT -t TARGET -bin BIN_FILE`
    * Replace `YOUR_PORT` with the serial port used by the arduino board
    * Replace `TARGET` with `nicla` or `bhi`
    * Replace `BIN_FILE` with the path of the binary file to be uploaded
- Nicla will reset and the firmware will be updated

Commander.py - Data Harvester for Arduino Nicla Sense ME
This script is a companion application for the DataHarvester sketch on the Arduino Nicla Sense ME. It controls data acquisition operations, connects to the Arduino board via serial communication, and saves the received data to a CSV file.

Requirements
Ensure you have the following installed on your system:

Python 3.x (Make sure Python is added to your system's PATH)
Required Python libraries:
bash
Copy code
pip install pyreadline3 pyserial cobs
Setup
1. Clone the Repository
Clone the Arduino Nicla Sense ME firmware repository or download the Commander.py script directly.

bash
Copy code
git clone https://github.com/arduino/nicla-sense-me-fw.git
cd nicla-sense-me-fw/Arduino_BHY2/examples/DataHarvester/extras/Commander
2. Connect Your Arduino Board
Connect your Arduino Nicla Sense ME board to your computer via USB.
Identify the correct COM port for your Arduino in the Windows Device Manager under "Ports (COM & LPT)".
3. Run the Script
Execute the Commander.py script with the required arguments. Replace COM_PORT, MyDevice, and Session1 with your specific port, device name, and session tag.

bash
Copy code
python Commander.py COM_PORT "MyDevice" "Session1"
4. Interact with the Script
Once the script is running, use the following commands to control the data acquisition:

R - Start data acquisition and save data to a CSV file.
S - Stop data acquisition.
C - Close the serial connection.
O - Open the serial connection (if it was closed).
Q - Quit the program.
5. CSV Output
The script saves the collected data in a CSV file in the same directory. The filename is based on the provided arguments and the current timestamp.

Troubleshooting
Raw Data Length Issues
During testing, it was observed that each data packet received from the Arduino was 18 bytes long instead of the expected 16 bytes. The last 2 bytes (b'E\x00') were identified as markers or padding.

The script was adjusted to remove these last 2 bytes before decoding the data packet.

Debugging
If you encounter issues, you can add print statements to inspect the raw data and adjust the script accordingly. Here’s an example:

python
Copy code
print(f"Raw data received (length {n}): {data.hex()}")
This will output the raw data in hexadecimal format, helping you understand its structure.
