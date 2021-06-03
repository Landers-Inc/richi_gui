Richi's GUI

Purged ModemManager - Sometimes took possession of serial :
```
sudo apt purge modemmanager
```
Added the following line to `/etc/udev/rules.d/99-com.rules`:
```
SUBSYSTEM=="tty", ATTRS{idVendor}=="3032", ATTRS{idProduct}=="0010", SYMLINK+="ttyUSB-GPSLink"
```

Friendly reminder that I had to change the USB cable because the one I had sucked!