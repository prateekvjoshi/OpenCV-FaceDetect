# OpenCV-FaceDetect

This code is for real time face detection using OpenCV. Make sure you have OpenCV installed.
You will need "haarcascade_frontalface_alt.xml" to run this code. It is already included in your
OpenCV package. In OpenCV 2.4.3, the file is present here: /opencv/data/haarcascades/haarcascade_frontalface_alt.xml.
If you are not able to find it, you can use the one I have included in this project. 
On line 16 in the .cpp file, you need to specify the path to the .xml file. I have specified the path for Mac OS X. 
If you are using a different OS, change it accordingly. This is the only change required 
to get the face detection code up and running.