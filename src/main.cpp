//Code to check the OpenCV installation on Raspberry Pi and measure frame rate
//Author: Samarth Manoj Brahmbhatt, University of Pennsyalvania
//Modified: George Profenza
#include "cap.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

PiCapture cap;
int brightness,effect;
void onBrightness( int, void* ){
    cap.setBrightness(brightness);
}
void onEffect(int, void* ){
    cap.setImageFX((MMAL_PARAM_IMAGEFX_T)effect);
}
int main(int argc,char **argv) {
    bool isColor = argc >= 2;
	namedWindow("Hello");
    cap.open(320, 240, isColor ? true : false);
	Mat im;
	double time = 0;
	unsigned int frames = 0;
    createTrackbar("brightness","Hello",&brightness,100,onBrightness);
    createTrackbar("image effect","Hello",&effect,23,onEffect);
    while(char(waitKey(1)) != 'q') {
		double t0 = getTickCount();
		im = cap.grab();
		frames++;
        if(!im.empty()) {
            imshow("Hello", im);
            if(isColor){
                cvtColor(im,im,CV_RGB2BGR);
                imshow("Hey there",im);
            }
        }
        else cout << "Frame dropped" << endl;
        time += (getTickCount() - t0) / getTickFrequency();
        cout << frames / time << " fps" << endl;
	}
	return 0;
}
