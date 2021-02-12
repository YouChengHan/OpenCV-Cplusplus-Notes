#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
using namespace std;
using namespace cv;
/*
Number Plate Detector
*/

void Func() {
    VideoCapture cap(0);
    Mat img;
    
    CascadeClassifier plateCascade;
    plateCascade.load("Resources/haarcascade_russian_plate_number.xml");
    if(plateCascade.empty()) cout<<"XML file not loaded."<<endl;

    vector<Rect> plates;

    while(1) {
        cap.read(img);

        plateCascade.detectMultiScale(img, plates, 1.1, 10);

        for(int i=0; i<plates.size(); ++i) {
            Mat imgCrop=img(plates[i]);
            //imshow("Plate number"+to_string(i+1), imgCrop);
            imwrite("Resources/Plates/Plate number"+to_string(i+1)+".png", imgCrop);
            rectangle(img, plates[i], Scalar(0, 255, 0), 5);
        }
        
        imshow("Image", img);

        waitKey(1);
    }
}
int main() {
    Func();
    return 0;
}