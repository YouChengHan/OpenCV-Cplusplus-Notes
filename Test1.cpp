#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
using namespace std;
using namespace cv;
// Test1: Face Detection and Webcam
void Func() {
    VideoCapture cap(0);
    vector<Rect> faces;
    Mat img;
    CascadeClassifier faceCascade;
    faceCascade.load("Resources/haarcascade_frontalface_default.xml");
    if(faceCascade.empty()) cout<<"XML file not loaded."<<endl;
    while(1) {
        faces.clear();
        cap.read(img);
        faceCascade.detectMultiScale(img, faces, 1.1, 5);
        for(int i=0; i<faces.size(); ++i) {
            rectangle(img, faces[i], Scalar(0, 69, 255), 5);
            putText(img, "Face", {faces[i].x+5, faces[i].y-5}, FONT_HERSHEY_DUPLEX, 1, Scalar(0, 69, 255), 2);
        }
        imshow("Webcam", img);
        waitKey(1);
    }
}
int main() {
    Func();
    return 0;
}