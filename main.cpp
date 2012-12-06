// Author: Prateek Joshi

#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <cstdio>

using namespace std;
using namespace cv;

// You need to include the path to the cascade classifier file here. In OpenCV 2.4.3, the file is present here: /opencv/data/haarcascades/haarcascade_frontalface_alt.xml
// The path below is for Mac OS X. Make sure you give the right path.
// If you don't know where it is, you can use the one provided in my git project. After downloading it, assign the path to it below.
String cascadeName = "/opt/local/share/opencv/haarcascades/haarcascade_frontalface_alt.xml";

void FaceDetect(Mat& image, CascadeClassifier& cascade)
{
    int i = 0;
    
    vector<Rect> faces; // Face detector will return faces as a bunch of rectangles
    
    // Different colored rectangles for multiple faces. You can extend it to any number of colors depending on the number of faces.
    const static Scalar rectangleColors[] =  { CV_RGB(255,255,255),
        CV_RGB(255,0,0),
        CV_RGB(0,255,0),
        CV_RGB(0,0,255) } ;
    
    Mat gray;
    
    cvtColor( image, gray, CV_BGR2GRAY );   // Converting to grayscale
    equalizeHist(gray, gray);               // Equalizing the histogram to take care of really bright or really dark conditions
    
    // Detecting the faces
    cascade.detectMultiScale( gray, faces, 1.3, 2, CV_HAAR_SCALE_IMAGE, Size(40, 48), Size(image.cols, image.rows) );

    // Put the rectangles around all the faces
    for( vector<Rect>::const_iterator faceRect = faces.begin(); faceRect != faces.end(); faceRect++, i++ )
    {
        Scalar color = rectangleColors[i%4];
        Point p1(cvRound((faceRect->x)), cvRound((faceRect->y)));
        Point p2(cvRound((faceRect->x + faceRect->width)), cvRound((faceRect->y + faceRect->height)));
        rectangle(image, p1, p2, color, 3, 8, 0);   
    }  
    
    imshow( "Face Detector", image );       // Display the image with rectangles around faces  
}

int main()
{
    CvCapture* capture = cvCaptureFromCAM(0);   // For webcam on the laptop
    Mat frame, frameCopy, image;
    
    CascadeClassifier cascade;      // Face detector class
    
    // Check if the xml file has loaded correctly. If not, you should check "cascadeName" and make sure the assignment is right.
    if( !cascade.load(cascadeName) )
    {
        cerr << "ERROR: Could not load classifier cascade. Make sure the path is correctly assigned to \"cascadeName\"." << endl;
        return -1;
    }
    
    if( capture )
    {
        // Start looping. Press any key to stop.
        for(;;)
        {
            IplImage* curFrame = cvQueryFrame(capture);     // Capture the current frame from the webcam
            frame = curFrame;                   

            // Check if the frame has been captured properly
            if(frame.empty())
            {
                cerr << "ERROR: Unable to capture frame" << endl;
                break;
            }
            
            if( curFrame->origin == IPL_ORIGIN_TL )
                frame.copyTo( frameCopy );
            
            else
                flip( frame, frameCopy, 0 );
            
            FaceDetect( frameCopy, cascade);
            
            if( waitKey( 10 ) >= 0 )
                goto releaseLabel;
        }
        
        waitKey(0);

        releaseLabel:
            cvReleaseCapture( &capture );
    }
    
    cvDestroyWindow("Face Detector");
    
    return 0;
}

