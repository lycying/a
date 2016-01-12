http://arduino.stackexchange.com/questions/5119/arduino-nano-no-serial-port-for-macbook-air-2013

Downloaded this driver
http://www.wch.cn/downloads.php?name=pro&proid=178
Installed it
Ran sudo nvram boot-args="kext-dev-mode=1"
Rebooted
Serial ports are shown in Arduino software and even when I ls -1 /dev/tty.*

Hopes this helps someone.

Reference: This thread

http://forum.arduino.cc/index.php?topic=261375.0

