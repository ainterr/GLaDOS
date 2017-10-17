# GLaDOS

A kernel-mode rootkit for linux. 

Currently, this just starts a kernel thread which prints messages (GLaDOS
quotes in [quotes.txt](quotes.txt)) to every terminal every N seconds until it
runs out of quotes, at which point it [prints the portal song](song/song.c) to
every terminal and then shuts down the system.

Note: because this is a kernel module, it must be compiled on the target system
or on a system with the same kernel version.

## Building

`make`

## Installing

`sudo make install`

## Uninstalling

1. Remove the line `GLaDOS` from `/etc/modules` 
2. Remove the file `GLaDOS.ko` from `/lib/modules/$(uname -r)/kernel/drivers/pci` 
3. `rmmod GLaDOS && depmod` (this may take up to N seconds where N in the
configured message interval)
4. Reboot
