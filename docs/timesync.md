# Time Sync


For v1:
When a button is turned on a (mobile) hotspot called 'abc' with connection to the internet should be in the air.
The button will contact 'abc' and sync time via the ntp-protocol.


## NTP / internet

Internet (more specific an 'ntp'-server) is needed for that.
Ultimately we want to be independent of internet. Some options:

+ our server contains an NTP-service of its own (not necessarely synced to the innternet).
+ Button is synced with own server at the start (own protocol...?).
