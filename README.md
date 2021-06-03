Richi's GUI

Raspberry Pi configured to start in console mode through `sudo raspi-config`

Configured `startx` modifying the file `.xinitrc` to run the GUI:
```
xrandr --output HDMI-1 --mode 1280x800
export QT_QPA_EGLFS_HIDECURSOR=1
/home/pi/Documents/GUI/richi_gui
```

Purged ModemManager - Sometimes took possession of serial port:
```
sudo apt purge modemmanager
```

Added the following line to `/etc/udev/rules.d/99-com.rules`:
```
SUBSYSTEM=="tty", ATTRS{idVendor}=="3032", ATTRS{idProduct}=="0010", SYMLINK+="ttyUSB-GPSLink"
```


Friendly reminder that I had to change the USB cable because the one I had sucked!