# freerunbuttons

This started as a project at FHICT in Eindhoven for commit040 to create a Timing System for freerunners.

This page is best viewed at: [https://freerunbuttons.github.io/freerunbuttons/](https://freerunbuttons.github.io/freerunbuttons/),

however if you want to see/use the sources go to:
[https://github.com/freerunbuttons/freerunbuttons](https://github.com/freerunbuttons/freerunbuttons).

The goal is first a system that works(!), after that it should be easy to use!

# Status

## Current issues


+ [How to sync the buttons?](https://freerunbuttons.github.io/freerunbuttons/docs/timesync)


## Button

The code for the button can be found in dir 'ESP_3rd_gen'. Created with Aruino IDE. The site is built

Minor: At the moment there is no difference between the buttons: a click is a click!


## Server

+ [How to make sure the site refreshes automatically?](https://freerunbuttons.github.io/freerunbuttons/docs/auto-refresh)

A simple (web)server for showing the times is being built in Seaside for Pharo. At the moment it uses my old laptop. In the near future I hope to switch to a raspberry.

## Ideas

+ Making a led blink every 10 seconds (when millisecs ends in 0000): this way you can easily see if the buttons are still in sync!
