DREVO Power Console Linux
====

Qt Creator 4.3.1
----
Based on Qt 5.9.0 (GCC 5.3.1 20160406 (Red Hat 5.3.1-6), 64 bit)

libusb: https://sourceforge.net/projects/libusb/
--

Installation
--

#### Arch Linux:
Package available through [AUR](https://aur.archlinux.org/packages/drevo-power-console-git/)

#### Building Manually

###### Debian/Ubuntu package requirements
```bash
sudo apt install build-essential qt5-default libusb-1.0-0-dev
```

###### run:
```bash
cd dpc_linux
qmake -makefile DrevoPowerConsole.pro
make
```

###### Udev Fix
To be able to run the program with non root access you will need to copy the `udev` rule to your installation:

```bash
cp udev/77-drevo-usb-allow-wheel.rules /usr/lib/udev/rules.d/
```

Screenshots
--

![](https://github.com/lanyu7/dpc_linux/blob/master/picture/1.png)
![](https://github.com/lanyu7/dpc_linux/blob/master/picture/2.png)
![](https://github.com/lanyu7/dpc_linux/blob/master/picture/3.png)
![](https://github.com/lanyu7/dpc_linux/blob/master/picture/4.png)
![](https://github.com/lanyu7/dpc_linux/blob/master/picture/5.png)

support@drevo.net
