#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;
/*
Draw shapes and text
*/
void Func() {
    //Create Blank Image
    Mat img(512, 512, CV_8UC3, Scalar(255, 255, 255));
    //CV_8UC3: 8: value of each pixel (2^8). U: unsigned integer. C3: 3 channel (RGB). 
    // Scalar(Blue, Green, Red)

    circle(img, Point(256, 256), 155, Scalar(0, 69, 255), FILLED);
    circle(img, Point(256, 256), 200, Scalar(255, 0, 0), 10);
    rectangle(img, Point(130, 226), Point(382, 286), Scalar(255, 255, 255), FILLED);
    /*
    Point(130, 226), Point(382, 286) can also be written as Rect(130, 226, 252, 60).
    The two point mean the top left point and the bottom right point.
    The parameters of Rect represent x, y, width, height.
    */
    line(img, Point(130, 296), Point(382, 296), Scalar(255, 255, 255), 2);
   
    putText(img, "Just Play!", Point(150, 262), FONT_HERSHEY_SCRIPT_COMPLEX, 1.5, Scalar(255, 0, 255), 1.5);

    imshow("Image", img);

    waitKey(0);
}
int main() {
    Func();
    return 0;
}