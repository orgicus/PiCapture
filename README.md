PiCapture
=========

Simple OpenCV wrapper for the Raspberry PI Camera Module

This is based on Samarth Brahmbatt's code listed on his title:
Practical OpenCV.
Modified by George Profenza for a simpler/faster colour callback
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

Note
====
For the BGR encoding mode make sure you have updated your Pi to the latest version
```
sudo rpi-update
```
The color mode has been tested with firmware 3.10.36+ #665
and the conversion is on the GPU in this case.

If for some reason you don't want to update, you can use this color callback:
```
static void color_callback(MMAL_PORT_T *port, MMAL_BUFFER_HEADER_T *buffer) {
	MMAL_BUFFER_HEADER_T *new_buffer;
	mmal_buffer_header_mem_lock(buffer);
	unsigned char* pointer = (unsigned char *)(buffer -> data);
	int w = PiCapture::width, h = PiCapture::height;
	Mat y(h, w, CV_8UC1, pointer);
	pointer = pointer + (h*w);
	Mat u(h/2, w/2, CV_8UC1, pointer);
	pointer = pointer + (h*w/4);
	Mat v(h/2, w/2, CV_8UC1, pointer);
	resize(u, u, Size(), 2, 2, INTER_NEAREST);
	resize(v, v, Size(), 2, 2, INTER_NEAREST);
	int from_to[] = {0, 0};
	mixChannels(&y, 1, &image, 1, from_to, 1);
	from_to[1] = 1;
	mixChannels(&v, 1, &image, 1, from_to, 1);
	from_to[1] = 2;
	mixChannels(&u, 1, &image, 1, from_to, 1);
	cvtColor(image, image, CV_YCrCb2BGR);
	int from_to[] = {0, 0};
	 mixChannels(&r, 1, &image, 1, from_to, 1);
    	from_to[1] = 1;
    	mixChannels(&g, 1, &image, 1, from_to, 1);
    	from_to[1] = 2;
    	mixChannels(&b, 1, &image, 1, from_to, 1);
	PiCapture::set_image(image);
}
```
and you need to make sure you are using YUV encoding in the constructor (I420 instead of RGB24) 
```
		format->encoding = MMAL_ENCODING_I420;
		format->encoding_variant = MMAL_ENCODING_I420;

```
This would be a wee bit slower as the conversion is done on the CPU, but will work on older firmware