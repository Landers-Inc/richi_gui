# Cross-compiling
Follow instructions from https://github.com/Landers-Inc/cross_compile.

Remember to copy `config.ini` file into `/home/pi`.

The software will run only when a USB audio device is present, otherwise the file `src/dataprocessor.cpp` must be modified.

# Build
In the file `.vscode/tasks.json` there are several routines to compile and deploy the file, they can be used with Visual Studio Code or you can copy them and use them directly in the console

# Build directly in the Raspberry Pi 4
Qt 5.15.2 must be compiled and installed from source, but the dependencies mentioned in https://github.com/Landers-Inc/cross_compile must be taken into account.

# Run on Raspberry Pi 4 startup
configure the Raspberry Pi to start in console mode through `sudo raspi-config`.

Configure `startx` modifying the file `/home/pi/.xinitrc` to run the GUI:
```
xrandr --output HDMI-1 --mode 1280x800
export QT_QPA_EGLFS_HIDECURSOR=1
/home/pi/richi_gui
```

Purge ModemManager - Sometimes took possession of serial port used by the EMLID GPS:
```
sudo apt purge modemmanager
```

Added the following line to `/etc/udev/rules.d/99-com.rules` for the GPS:
```
SUBSYSTEM=="tty", ATTRS{idVendor}=="3032", ATTRS{idProduct}=="0010", SYMLINK+="ttyUSB-GPSLink"
```

**When the EMLID GPS is not connected, the software will use a Fake GPS with white noise data.**