PiCapture
=========

Simple OpenCV wrapper for the Raspberry PI Camera Module

This is Samarth Brahmbatt'code listed on his title:
Practical OpenCV

How to use the sample
=====================

First you need to fetch the [userland repo](http://github.com/raspberypi/userland)

```
git clone https://github.com/raspberrypi/userland.git
```

Then replace USERLAND_DIR in CMakeLists.txt with the path to the userland repo
you just downloaded/cloned.

Finally, build the demo:

```
cd build
cmake ..
make
./main
```
By default this will open the camera in grayscale mode.
Pass any command line argument to main and it will start in colour

