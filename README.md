# Mini_Clock

**This is a work in progress although I have a working clock.**

 Clock with two displays -- a big red HT16K33 which is easy to read from many angles and a
 smaller TFT to display temperature, humidity etc. The clock gets the time from the
 NTP service. The project is based on my earlier Dual Clock which used a GPS receiver
 to get the time. This wasn't as successful as I hoped as it isn't always possible to
 get a strong enough GPS signal indoors.

 The clock is still in developent and not all features are complete.

 Many mods are possible to suit different hardware.

 The version I am building uses a Wemos/Lolin D1 Mini clone with an ESP8266. The code
 & configuration fit comfortably in this useful little microcontroller.

 Much more info to follow. Questions welcome.

## Code

As an experiment, I implemented everything using namespaces instead of classes. I'd
heard some harsh criticism of OOP and wanted to experiment with the alternatives. I
actually prefer this approach when there is only going to one instance of a thing.
The code seems to be shorter and easier to understand. Each namespace is decoupled
from the others -- everything is tied together in main.cpp.

The code is written in, and designed for, vscode & PlatformIO. A bit of moving &
renaming of main.cpp would probably be all that's needed to compile it in Arduino IDE. 
But why?

## Parts

Find the Parts List in the [Wiki](https://github.com/MikeTheGent/Mini_Clock/wiki)

## WiFi & Alexa

By default, the clock connects to WiFi and then to Alexa using the
Espalexa library. The displays turned off using Alexa. This
feature can be easily removed in main.cpp.

## Case

You can download my case design from the
[Wiki](https://github.com/MikeTheGent/Dual_Clock/wiki)
FIXME: this is for the older clock project

## TFT_eSPI configutation

Move resources/User_Setup.h to your TFT_eSPI directory which will be somwhere in 
.pio/libdeps. You will need to edit this file to suit your MCU & TFT unless you 
are using exactly the same devices as me.

## WiFi & time zone configuration

Create a data directory at the project's top level. Move resources/settings.json to 
this directory. Edit settings.json for your WiFi & time zone.
