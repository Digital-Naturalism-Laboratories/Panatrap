# Panatrap
This is an open-source collection of design files and code for turning commercially available 360 "VR" cameras into panoramic camera traps for studying wildlife in natural environments.
These are created in Gamboa, Panama, at Digital Naturalism Laboratories by Andrew Quitmeyer and Danielle Hoogendijk. Work on this project has been supported by:
- The Digital Naturalism Conference (www.dinacon.org)
- Conservation X Labs

## Cameras
The collection currently consists of 2 camera trap setups based on the

- Xiaomi Misphere (MADV in the USA)
 - Full electronic functional control over 
  - Turning camera ON/OFF
  - Switching camera from Video to Photo Mode
  - Trigger a photo or video recording

- Ricoh Theta V
 - Full electronic functional control over
  - Turning the camera on (waking from sleep mode)
  - Triggering a photo or video to begin recording

as we hack more cameras we will add them and their files to this list and repository.
We hacked the Ricoh Theta S and posted detailed instructions here:
but this was quite a destructive hack (we literally ripped the camera apart and soldered things to its button). The Panatrap project focuses on non-destructive, reversible hacks to turn your 360 camera into a cool trap

## Key Challenges
Loosely defined, camera traps are simply photographic instruments that can be remotely triggered by wildlife. Typically this is done with a PIR motion sensor triggering a camera to snap a photo.
Thus when transforming commercially available cameras to become camera traps, the key abilities we need are:
- Remote Triggering
 - The ability to tell the camera to snap a photo or start recording a video
- Low power consumption
 - Typically this is the ability to remotely turn the camera ON/OFF, or at least bring the camera in and out of a low power "sleep mode", and to remotely charge it
- Speedy Capture
 - We were told that a typical camera trap aims to go from sensing an animal's presence to capturing the creature in under 1/2 second
 - This ability is often at odds with the "Low power consumption" goal, since many cameras have a not-insignificant amount of wake up time when starting.
- Image quality
 - An ideal camera trap will provide a high resolution image of the captured animal
- Outdoor Readiness
 - The camera trap needs to be able to withstand being left alone for several days or weeks in its target environment.
 - Camera Traps face challenges from the elements (such as rain, heat, wind, and cold)
 - They also face challenges from local creatures (such as small insect destruction, or elephant smashing)


## Xiaomi Misphere
The first camera that we hacked because it has decent image quality, and importantly it has two exposed electrodes on the camera that make hacking very easy!

They made an interface on the bottom of the camera for the camera to be easily controlled with their included "selfie stick." It's just two metal electrodes that when connected it sends a message to the camera(the original selfie stick has a 220 ohm resistor connected to a button).
From our examinations, the 3 messages you can send to the camera with this interface are:
- Long Press (5 seconds)
 - Camera ON/OFF
- Medium Press (2 seconds)
 - Toggle Recording Mode (Video to Photo, or Photo to Video)
- Short press
 - Shutter Button (Take a photo, or start or stop a video)


## Ricoh Theta V
This camera was substantially more locked up  in our attempts to remotely operate it (especially in a way that allows for long term use and have a decently quick trigger).

The camera runs android, and has an acessible USB Api (to recieve PTP commands) and in theory has all the abilities to remotely A) Turn ON/OFF and B)Trigger a Photo Capture. But the firmware blocks some of these features (even if you switch into developer mode).

Luckily we discovered that sending an emulated Keyboard command (through something like a Teensy Arduino 3.2), can remotely wake up the camera (even though this feature is not documented anywhere!), and then we just need to trigger the photo.
The photo triggering is then done by a small servo connected to the arduino which manually taps the shutter button of the camera. The servo is shut down in between photos to reduce power consumption.
