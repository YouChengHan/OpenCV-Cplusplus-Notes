#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;
/*
Color Detection
*/

int hmin=0, smin=0, vmin=0;
int hmax=179, smax=255, vmax=255;
/*
default value for lambo.png:

hmin = 0, smin = 110, vmin = 153
hmax = 19, smax = 240, vmax = 255

*/

void Func() {
    string pth="Resources/shapes.png";
    Mat img=imread(pth);
    Mat imgHSV, mask;
    cvtColor(img, imgHSV, COLOR_BGR2HSV);

    namedWindow("Trackbars", (640, 200));
    //Create a window. Use WINDOW_NORMAL for second parameter can create a resizable window.

    createTrackbar("Hue Min", "Trackbars", &hmin, 179);
    createTrackbar("Hue Max", "Trackbars", &hmax, 179);

    createTrackbar("Sat Min", "Trackbars", &smin, 255);
    createTrackbar("Sat Max", "Trackbars", &smax, 255);

    createTrackbar("Val Min", "Trackbars", &vmin, 255);
    createTrackbar("Val Max", "Trackbars", &vmax, 255);

    while(1) {

        Scalar lower(hmin, smin, vmin), upper(hmax, smax, vmax);
        inRange(imgHSV, lower, upper, mask);

        imshow("Image", img);
        imshow("HSV", imgHSV);
        imshow("Mask", mask);

        waitKey(1);

    }
}
int main() {
    Func();
    return 0;
}