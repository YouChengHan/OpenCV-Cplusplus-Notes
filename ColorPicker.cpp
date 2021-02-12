#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;
/*
Color Picker
for Project 1 to capture the numbers of HSV.
adjust the trackbar to fit in the different color range.
*/
int hmin=0, smin=0, vmin=0;
int hmax=179, smax=255, vmax=255;

void Func() {
    namedWindow("Trackbars", (640, 200));

    createTrackbar("Hue Min", "Trackbars", &hmin, 179);
    createTrackbar("Hue Max", "Trackbars", &hmax, 179);

    createTrackbar("Sat Min", "Trackbars", &smin, 255);
    createTrackbar("Sat Max", "Trackbars", &smax, 255);

    createTrackbar("Val Min", "Trackbars", &vmin, 255);
    createTrackbar("Val Max", "Trackbars", &vmax, 255);

    VideoCapture cap(0);
    Mat img, imgHSV, mask;
    while(1) {
        cap.read(img);
        cvtColor(img, imgHSV, COLOR_BGR2HSV);
        Scalar lower(hmin, smin, vmin), upper(hmax, smax, vmax);
        inRange(imgHSV, lower, upper, mask);

        imshow("Image", img);
        imshow("Mask", mask);
        cout<<"h:["<<hmin<<", "<<hmax<<"], s:["<<smin<<", "<<smax<<"], v:["<<vmin<<", "<<vmax<<']'<<endl;

        waitKey(1);

    }
}
int main() {
    Func();
    return 0;
}