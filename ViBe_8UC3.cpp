/*

This simple example program takes a path to a video sequence as an argument.
When it is executed, two windows are opened: one displaying the input sequence, and one displaying the segmentation maps produced by ViBe.
This is the 3-channel (RGB for example) version of ViBe.


*/
#include <inttypes.h>
#include <cstddef>
#include <ctime>
#include <iostream>

#include "cv.h"
#include "highgui.h"

#include <opencv2/opencv.hpp>
#include "opencv2/videoio.hpp"
#include "opencv2/imgproc/imgproc.hpp"


#include <libvibe++/ViBe.h>
#include <libvibe++/distances/Manhattan.h>
#include <libvibe++/system/types.h>

using namespace std;
using namespace cv;
using namespace ViBe;

int main(int argc, char** argv) {
  if (argc != 2) {
    cerr << "A video file must be given as an argument to the program!";
    cerr << endl;

    return EXIT_FAILURE;
  }

  /* Parameterization of ViBe. */
  typedef ViBeSequential<3, Manhattan<3> >                                ViBe;

  /* Random seed. */
  srand(time(NULL));

  cv::VideoCapture decoder(argv[1]);
  cv::Mat frame;

  //int32_t height = 
  //int32_t width = 

  int32_t height = decoder.get(CV_CAP_PROP_FRAME_HEIGHT);
  int32_t width  = decoder.get(CV_CAP_PROP_FRAME_WIDTH);

  printf("%" PRId32"\n", height );
  printf("%" PRId32"\n", width );

  ViBe* vibe = NULL;
  cv::Mat segmentationMap(height, width, CV_8UC3);
  bool firstFrame = true;

  while (decoder.read(frame)) {
    if (firstFrame) {
      /* Instantiation of ViBe. */
      vibe = new ViBe(height, width, frame.data);
      firstFrame = false;
    }

    /* Segmentation and update. */
    vibe->segmentation(frame.data, segmentationMap.data);
    vibe->update(frame.data, segmentationMap.data);

    //rectangle(frame, cv::Point(10,2), cv::Point(100, 20), cv::Scalar(255, 255, 255), -1);

    //post-processing using the Gaussian Blur


    /*
    for(int i = 1; i<5; i+=2)
    {
      GaussianBlur(segmentationMap, segmentationMap, Size(i, i), 0, 0);
    }
    cv::imshow("GaussianBlur", segmentationMap);
    */

    /* Post-processing: 5X5 median filter. */
    medianBlur(segmentationMap, segmentationMap, 5);
    
    /*
    Size size(860, 860);
    cv::resize(frame, frame, size);
    cv::resize(segmentationMap, segmentationMap, size);
    */
  

    cv::imshow("Input video", frame);
    cv::imshow("Segmentation by ViBe", segmentationMap);

    cvWaitKey(1);
  }

  delete vibe;

  cvDestroyAllWindows();
  decoder.release();

  return EXIT_SUCCESS;
}
