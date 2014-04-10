PiCapture
=========

Simple OpenCV wrapper for the Raspberry PI Camera Module

This is based on Samarth Brahmbatt's code listed on his title:
Practical OpenCV.
Slightly Modified by George Profenza for a simpler colour callback
and added camera settings. The setter methods are minimally commented
to include ranges for the available parameters.

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
mkdir build && cd build
cmake ..
make
./main
```
By default this will open the camera in grayscale mode.
Pass any command line argument to main and it will start in colour

