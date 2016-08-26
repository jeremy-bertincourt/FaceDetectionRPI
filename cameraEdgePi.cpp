#include <iostream>                   // Console I/O
#include <sstream>                    // String to number conversion
#include <stdio.h>
#include <opencv2/core/core.hpp>      // Basic OpenCV structures
#include <opencv2/imgproc/imgproc.hpp>// Image processing methods for the CPU
#include <opencv2/highgui/highgui.hpp>// Read images
#include "opencv2/objdetect/objdetect.hpp"
#include <raspicam/raspicam_cv.h>

 using namespace std;
 using namespace cv;

 /** Function Headers */
void detectAndDisplay( Mat& frame,   std::vector<Rect> &faces,  std::vector<Rect> &eyes );

 /** Global variables */
 String face_cascade_name = "lbpcascade_frontalface.xml";
 String eyes_cascade_name = "haarcascade_eye.xml";
 CascadeClassifier face_cascade;
 CascadeClassifier eyes_cascade;
 CascadeClassifier body_cascade;
 string window_name = "Capture - Face detection";
 RNG rng(12345);
double t;

 /** @function main */
 int main( int argc, const char** argv )
 {
   raspicam::RaspiCam_Cv Camera;
   Camera.set( CV_CAP_PROP_FORMAT, CV_8UC1 );
   Camera.set( CV_CAP_PROP_EXPOSURE, 50);
   Camera.set( CV_CAP_PROP_WHITE_BALANCE_RED_V, 50);
   Camera.set( CV_CAP_PROP_WHITE_BALANCE_BLUE_U, 50);

  if ( !Camera.open()){
  	cout  << "Could not open reference " << endl;
  	return -1;
  }
   Mat frame;
   Mat frame_gray;
  std::vector<Rect> faces;
  std::vector<Rect> eyes;

  namedWindow(window_name, WINDOW_AUTOSIZE);

   //-- 1. Load the cascades
   if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };
   if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };
   int k;
   for(;;k++)
    {
		t = (double)getTickCount();
 		Camera.grab();
       		Camera.retrieve(frame_gray);
		//cvtColor(frame, frame_gray, cv::COLOR_BGR2GRAY);

   //-- 3. Apply the classifier to the frame
      if( !frame_gray.empty()){
		if(k % 6 == 0){
       			detectAndDisplay( frame_gray, faces, eyes); 
		}
		else{
			  for( size_t i = 0; i < faces.size(); i++ ){
    				Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
   				ellipse( frame_gray, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
    				for( size_t j = 0; j < eyes.size(); j++ ){
       					Point center( faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5 );
      					int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
       					circle( frame_gray, center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
				}
			 }
     		}
	}
       else
       { printf(" --(!) No captured frame -- Break!"); break; }
	
		t = 1000*((double)getTickCount() - t)/getTickFrequency();
		cout << "Times passed in milliseconds: " << t << endl;
		 
	   //-- Show what you got
 	   imshow( window_name, frame_gray );
    	
	   if( waitKey(1) > 0 ) { break; }
     }

   Camera.release();
   return 0;
 }

/** @function detectAndDisplay */
void detectAndDisplay( Mat& frame,   std::vector<Rect> &faces,  std::vector<Rect> &eyes )
{
  
  //equalizeHist( frame_gray, frame_gray );
							   						   
  //-- Detect faces
  face_cascade.detectMultiScale( frame, faces, 1.5, 4, 0|CV_HAAR_SCALE_IMAGE, Size(50, 50) );

  for( size_t i = 0; i < faces.size(); i++ )
  {
    Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
    ellipse( frame, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );

    Mat faceROI = frame( faces[i] );
   

    //-- In each face, detect eyes
   eyes_cascade.detectMultiScale( faceROI, eyes, 1.5, 4, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );

    for( size_t j = 0; j < eyes.size(); j++ )
     {
       Point center( faces[i].x + eyes[j].x + eyes[j].width*0.5, faces[i].y + eyes[j].y + eyes[j].height*0.5 );
       int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
       circle( frame, center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
     }
  }
 }
