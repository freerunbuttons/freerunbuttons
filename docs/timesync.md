# How to sync the buttons?

To sync computers via the internet the so-called `NTP` is used.
The freerunbuttons will contact `some server` (preferably the same server used for showing the Times?) and sync time via the ntp-protocol.

Ultimately we want to be independent of internet.

+ our server acts as an NTP-service of its own (not necessarely synced to the internet).

The ESPs in the buttons have to be as accurate as they can be, so we opt for a separate server!

At this moment I have a laptop & an old router in use especially to 'serve' the buttons. A step soon to be taken will be replacing the laptop by a raspberry pi.
So for the NTP-service it would be nice to use a raspberry from the start.
+ [Can we use a Raspberry as a NTP-server? (without conecting to the internet)](raspberryAsNtp)


## Looked/Looking at libraries

+ [ezTime](https://github.com/ropg/ezTime)
+ [NTPClient](https://github.com/arduino-libraries/NTPClient)
+ [raspberry as NTPserver](https://www.satsignal.eu/ntp/Raspberry-Pi-NTP.html)
