#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "interface/mmal/mmal.h"
#include "interface/mmal/util/mmal_default_components.h"
#include "interface/mmal/util/mmal_connection.h"
#include "interface/mmal/util/mmal_util.h"
#include "interface/mmal/util/mmal_util_params.h"

class PiCapture {
	private:
		MMAL_COMPONENT_T *camera;
		MMAL_COMPONENT_T *preview;
		MMAL_ES_FORMAT_T *format;
		MMAL_STATUS_T status;
		MMAL_PORT_T *camera_preview_port, *camera_video_port, *camera_still_port;
		MMAL_PORT_T *preview_input_port;
		MMAL_CONNECTION_T *camera_preview_connection;
        bool color;
	public:
		static cv::Mat image;
		static int width, height;
		static MMAL_POOL_T *camera_video_port_pool;
		static void set_image(cv::Mat _image) {image = _image;}
        PiCapture();
        PiCapture(int, int, bool);
        void open(int,int,bool);
		cv::Mat grab() {return image;}

        //settings
        typedef struct
        {
           int enable;       /// Turn colourFX on or off
           int u,v;          /// U and V to use
        } MMAL_PARAM_COLOURFX_T;
        typedef struct
        {
           double x;
           double y;
           double w;
           double h;
        } PARAM_FLOAT_RECT_T;


        /**
         * @brief setSaturation
         * @param saturation (-100,100)
         * @return
         */
        int setSaturation(int saturation);
        /**
         * @brief setSharpness
         * @param sharpness (-100,100)
         * @return
         */
        int setSharpness(int sharpness);
        /**
         * @brief setContrast
         * @param contrast (-100,100)
         * @return
         */
        int setContrast(int contrast);
        /**
         * @brief setBrightness
         * @param brightness (0,100)
         * @return
         */
        int setBrightness(int brightness);
        /**
         * @brief setISO
         * @param ISO (100,800) - default is 300
         * @return
         */
        int setISO(int ISO);
        /**
         * @brief setExposureMeteringMode
         * @param m_mode (0,4)
         * @return
         */
        int setExposureMeteringMode(MMAL_PARAM_EXPOSUREMETERINGMODE_T m_mode);
        /**
         * @brief setVideoStabilisation
         * @param vstabilisation (1 is on, 0 is off)
         * @return
         */
        int setVideoStabilisation(int vstabilisation);
        /**
         * @brief setExposureCompensation
         * @param exp_comp (-10,10)
         * @return
         */
        int setExposureCompensation(int exp_comp);
        /**
         * @brief setExposureMode
         * @param mode (0,13)
         * @return
         */
        int setExposureMode(MMAL_PARAM_EXPOSUREMODE_T mode);
        /**
         * @brief setAWBMode
         * @param awb_mode (0,10)
         * @return
         */
        int setAWBMode(MMAL_PARAM_AWBMODE_T awb_mode);
        /**
         * @brief setAWBGains
         * @param r_gain (0.0,1.0)
         * @param b_gain (0.0,1.0)
         * @return
         */
        int setAWBGains(float r_gain,float b_gain);
        /**
         * @brief setImageFX
         * @param imageFX (0,23)
         * @return
         */
        int setImageFX(MMAL_PARAM_IMAGEFX_T imageFX);//TODO example
        int setColourFX(MMAL_PARAM_COLOURFX_T *colourFX);//TODO example
        /**
         * @brief setRotation
         * @param rotation (0,359) try 0,90,180,270
         * @return
         */
        int setRotation(int rotation);
        /**
         * @brief setFlips
         * @param hflip (0,1) treat as bool
         * @param vflip (0,1) treat as bool
         * @return
         */
        int setFlips(int hflip,int vflip);
        /**
         * @brief setROI
         * @param rect (has x,y,w,h and expects normalized values)
         * @return
         */
        int setROI(PARAM_FLOAT_RECT_T rect);
        /**
         * @brief setShutterSpeed
         * @param speed (0,330000) in microseconds, 0 is auto
         * @return
         */
        int setShutterSpeed(int speed);

        int mmal_status_to_int(MMAL_STATUS_T status)
        {
           if (status == MMAL_SUCCESS)
              return 0;
           else
           {
              switch (status)
              {
              case MMAL_ENOMEM :   printf("Out of memory"); break;
              case MMAL_ENOSPC :   printf("Out of resources (other than memory)"); break;
              case MMAL_EINVAL:    printf("Argument is invalid"); break;
              case MMAL_ENOSYS :   printf("Function not implemented"); break;
              case MMAL_ENOENT :   printf("No such file or directory"); break;
              case MMAL_ENXIO :    printf("No such device or address"); break;
              case MMAL_EIO :      printf("I/O error"); break;
              case MMAL_ESPIPE :   printf("Illegal seek"); break;
              case MMAL_ECORRUPT : printf("Data is corrupt \attention FIXME: not POSIX"); break;
              case MMAL_ENOTREADY :printf("Component is not ready \attention FIXME: not POSIX"); break;
              case MMAL_ECONFIG :  printf("Component is not configured \attention FIXME: not POSIX"); break;
              case MMAL_EISCONN :  printf("Port is already connected "); break;
              case MMAL_ENOTCONN : printf("Port is disconnected"); break;
              case MMAL_EAGAIN :   printf("Resource temporarily unavailable. Try again later"); break;
              case MMAL_EFAULT :   printf("Bad address"); break;
              default :            printf("Unknown status error"); break;
              }

              return 1;
           }
        }

};

static void color_callback(MMAL_PORT_T *, MMAL_BUFFER_HEADER_T *);
static void gray_callback(MMAL_PORT_T *, MMAL_BUFFER_HEADER_T *);
