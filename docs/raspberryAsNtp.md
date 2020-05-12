# Can we use a Raspberry as a NTP-server?

Additional:
+ The buttons need to be time synced to each other.
the 'real' time!
+ The buttons can use the raspberry as an `NTP server`.  
+ It's only about durations, so it does not need to be 'the `real` time'.
+ So we don't need to connect to the internet.

Starting at:
[https://www.satsignal.eu/ntp/Raspberry-Pi-NTP.html](https://www.satsignal.eu/ntp/Raspberry-Pi-NTP.html)
This is a thorough description of building a NPT server on a raspberry that syncs to the 'rteal time' using some GPS-module. I don't need that first part, I just need the raspberry servicing the clients/buttons!

Looking and reading I stumble on
[http://raspberrypi.tomasgreno.cz/ntp-client-and-server.html](http://raspberrypi.tomasgreno.cz/ntp-client-and-server.html)
which tells me to install `ntp` by executing `sudo apt-get install ntp`.

STOP: In a phone call to my brother we talked about this and he explained me what 'RTC' means in an ESP: (((info to be added here)))...  

Turns out RTC (~Real Time Clock) is not really real time. Some/all(?) ESPs don't have a physical RT-clock which also ticks when the chip is in low-power mode.

For precise timing:
+ Use millis()
+ Don't let the chip go into low-power (is this an option?)
+ How long will a battery do when not going into low-power? TEST!

[https://raspberrytips.com/time-sync-raspberry-pi/](https://raspberrytips.com/time-sync-raspberry-pi/)





## My system

+ A Raspberry 2 built into an HDMI Pi screen.
+ Raspbian used: 2020-02-12-rpd-x86-buster.iso.


## References

+ [raspberry as NTPserver](https://www.satsignal.eu/ntp/Raspberry-Pi-NTP.html)
