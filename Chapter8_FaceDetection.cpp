#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
using namespace std;
using namespace cv;
/*
Face Detection
*/

void Func() {
    string pth="Resources/test.png";
    Mat img=imread(pth);
    
    CascadeClassifier faceCascade;
    faceCascade.load("Resources/haarcascade_frontalface_default.xml");
    if(faceCascade.empty()) cout<<"XML file not loaded."<<endl;

    vector<Rect> faces;
    faceCascade.detectMultiScale(img, faces, 1.1, 10);
    /*
    scaleFactor means the reduce ratio of the image size at each image scale.

    minNeighbors means the threshold quantity of each candidate rectangle's neighbor that will be detected as a face.
    That is, bigger minNeighbors raise the quality of candidate rectangles and decrease the number of candidate rectangles.
    set 0 can find out all the candidate rectangles that has been detected as a face.
    */

    for(int i=0; i<faces.size(); ++i)
        rectangle(img, faces[i], Scalar(0, 255, 0), 5);
        //rectangle(img, faces[i].tl(), faces[i].br(), Scalar(0, 255, 0), 5);

    imshow("Image", img);
    
    waitKey(0);
}
int main() {
    Func();
    return 0;
}