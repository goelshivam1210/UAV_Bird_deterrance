/*

This simple example program takes a path to a video sequence as an argument.
When it is executed, two windows are opened: one displaying the input sequence, and one displaying the segmentation maps produced by ViBe.
This is the 3-channel (RGB for example) version of ViBe.


*/

/*
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp""
#include "opencv2/imgproc/imgproc.hpp"
#include "iostream"
using namespace cv;
using namespace std;

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
#include "opencv2/imgcodecs.hpp"


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
  typedef ViBeSequential<3, Manhattan<3> > ViBe;

  /* Random seed. */
  srand(time(NULL));

  cv::VideoCapture decoder(argv[1]);
  cv::Mat frame, output, processedOutput, finalIm, dilatedIm;

  //int32_t height = 
  //int32_t width = 

  int32_t height = decoder.get(CV_CAP_PROP_FRAME_HEIGHT);
  int32_t width  = decoder.get(CV_CAP_PROP_FRAME_WIDTH);

  printf("%" PRId32"\n", height );
  printf("%" PRId32"\n", width );

  ViBe* vibe = NULL;
  cv::Mat segmentationMap(height, width, CV_8UC1);
  bool firstFrame = true;

  while (decoder.read(frame)) {
    //printf("%sFrame No\n",frame );
    if (firstFrame) {
      /* Instantiation of ViBe. */
      vibe = new ViBe(height, width, frame.data);
      firstFrame = false;
    }

    /* Segmentation and update. */
    vibe->segmentation(frame.data, segmentationMap.data);
    vibe->update(frame.data, segmentationMap.data);
    medianBlur(segmentationMap, processedOutput, 3);
    dilate(processedOutput,dilatedIm , 0, Point(-1, -1), 2, 1, 1);


    int largest_area = 0;
    int largest_contour_index=0;
    Rect bounding_rect;
    vector<vector<Point> > contours; // Vector for storing contour
    vector<Vec4i> hierarchy;
    findContours( dilatedIm, contours, hierarchy,CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );
    // iterate through each contour.
    for( int i = 0; i< contours.size(); i++ )
    {
        //  Find the area of contour
        double a=contourArea( contours[i],false); 
        if(a>5){
            largest_area=a;cout<<i<<" area  "<<a<<endl;
            // Store the index of largest contour
            largest_contour_index=i;               
            // Find the bounding rectangle for biggest contour
            bounding_rect=boundingRect(contours[i]);
        }
    }
    Scalar color( 255,255,255);  // color of the contour in the
    //Draw the contour and rectangle
    drawContours( frame, contours,largest_contour_index, color, CV_FILLED,8,hierarchy);
    rectangle(frame, bounding_rect,  Scalar(0,0,255),2, 8,0);
    namedWindow( "Display window", CV_WINDOW_AUTOSIZE );
    imshow( "Display window", frame );    
    //waitKey(0);                                         
    //return 0;
    
    imshow("ViBe", segmentationMap);
    imshow("processedOutput", processedOutput);

    waitKey(1);                                         
    //return 0;

  } 

//medianBlur(segmentationMap, processedOutput, 3);



    //post-processing using the Gaussian Blur


    /*
    for(int i = 1; i<5; i+=2)
    {
      GaussianBlur(segmentationMap, segmentationMap, Size(i, i), 0, 0);
    }
    cv::imshow("GaussianBlur", segmentationMap);
    
    
    /*
    Size size(860, 860);
    cv::resize(frame, frame, size);
    cv::resize(segmentationMap, segmentationMap, size);
    */
  
    //cv::imshow()
    //cv::imshow("Input video", frame);
    //cv::imshow("Segmentation by ViBe", segmentationMap);

    //do post processing
    
    //cv::morphologyEx(segmentationMap, postprocessMap, MORPH_OPEN, Mat());
    /* Post-processing: 5X5 median filter. */
    //medianBlur(segmentationMap, processedOutput, 3);
    //cv::imshow("Processed Output", processedOutput);
    //cv::imshow("Contours", drawing);

    //cnts = cv2.findContours

    //cvWaitKey(1);

    //Rect boundingRect()






  delete vibe;

  cvDestroyAllWindows();
  decoder.release();

  return EXIT_SUCCESS;

}




