# How to sync the buttons?

```
Update: Using NTP from an ESP is not accurate enough!:
The RTC (Real Time Clock) in an ESP is not
really real-time, because it has no battery
of its own! After the ESP has been in
low-power and gets active again the 'millis()'
are read and the RTC-time is set according to
the value of the millis. This will be accurate
on the second, but not on the millisecond...
```

## About RTC : Realtime Clock

In the `embedded world` this means a clock giving the time of day, for example `21:22:01`,
possibly including date. Often there is an extra chip that has its own battery to make sure the time keeps on ticking when the device is off or in standby. So it's not `Realtime` as in `Realtime Linux`.

Example chip : [Dallas DS3231](https://datasheets.maximintegrated.com/en/ds/DS3231.pdf).

Besides(!) there is an `arduino-command` called `millis()`, which returns the value of a counter based on the processor clock that _is_ accurate as long as the processor is on full power and not in standby!
So the challenge is to keep the processor out of `low-power mode`.

## NTP or Network Time Protocol

To sync computers via the internet often the so-called `NTP` is used. The freerunbuttons at first was thought to contact `some server` (preferably the same server used for showing the Times?) and sync time via the ntp-protocol.
5
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
+ [https://www.geekstips.com/arduino-time-sync-ntp-server-esp8266-udp/](https://www.geekstips.com/arduino-time-sync-ntp-server-esp8266-udp/)
+ [https://stackoverflow.com/questions/57821318/how-to-sync-multiple-esp8266](https://stackoverflow.com/questions/57821318/how-to-sync-multiple-esp8266)
+ [https://www.instructables.com/id/TESTED-Timekeeping-on-ESP8266-Arduino-Uno-WITHOUT-/](https://www.instructables.com/id/TESTED-Timekeeping-on-ESP8266-Arduino-Uno-WITHOUT-/)

### Similar project
+ [https://www.youtube.com/watch?v=7zIv-Qu5mro](https://www.youtube.com/watch?v=7zIv-Qu5mro)
+ [https://github.com/scottgchin/delta5_race_timer](https://github.com/scottgchin/delta5_race_timer)

### esp8266WiFi module

+ [https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/readme.html](https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/readme.html)

### Raspberry as server

+ [https://pimylifeup.com/raspberry-pi-wireless-access-point/](https://pimylifeup.com/raspberry-pi-wireless-access-point/)

### About ESP clock accuracy

[ESP8266: Extremely bad clock accuracy #2724](https://github.com/micropython/micropython/issues/2724)

### in dutch

[trouw: Tot op de honderdste millimeter](https://www.trouw.nl/es-b71e8b8e)
