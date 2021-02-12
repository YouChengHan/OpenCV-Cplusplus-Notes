#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;
/*
Display video and use the webcam
*/
void Test() {
    string pth="Resources/test.png";
    Mat img=imread(pth);
    imshow("Test Image", img);
    waitKey(0);
    /*
    From OpenCV official website:

    int waitKey(int delay = 0): waits for a pressed key.

    delay <= 0: waits for infinitely.
    otherwise, wait for delay milliseconds.

    When display an image, waitKey(0) is needed, or the window will not reserved.
    When play a video, waitkey() with a positive delay is suitable.
    With less delay, the video will play faster.
    On the other hand, the video will be slower.
    
    */
}
void Video() {
    string pth="Resources/test_video.mp4";
    VideoCapture cap(pth);
    Mat img;
    while(1) {
        cap.read(img);
        imshow("Video", img);
        waitKey(25);
    }
}
void Webcam() {
    VideoCapture cap(0); //the id number of the webcam, 0 in most of the time.
    Mat img;
    while(1) {
        cap.read(img);
        imshow("Webcam", img);
        waitKey(1);
    }
}
int main() {
    Test();
    //Video();
    Webcam();
    return 0;
}