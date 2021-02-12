#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;
/*
Document Scanner
*/

const float w=420, h=596; // Has been multiplied by 2 since the original size is too small.

Mat preProcessing(Mat img) {

    Mat imgGray, imgBlur, imgCanny, imgDilate, imgErode;

    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
    Canny(imgBlur, imgCanny, 25, 75);
    
    Mat kernel=getStructuringElement(MORPH_RECT, Size(3, 3));
    dilate(imgCanny, imgDilate, kernel);
    //erode(imgDilate, imgErode, kernel);
    return imgDilate;
}

vector<Point> getContours(Mat imgOrg, Mat imgThre) {
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    vector<Point> biggest(4);
    int MaxArea=0;

    findContours(imgThre, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    
    vector<vector<Point>> conPoly(contours.size());

    for(int i=0; i<contours.size(); ++i) {
        int area=contourArea(contours[i]);

        if(area>1000) {
            float para=arcLength(contours[i], true);
            approxPolyDP(contours[i], conPoly[i], 0.02*para, true);

            if(area>MaxArea&&conPoly[i].size()==4) { // maintain the max rectangle
                //drawContours(imgOrg, conPoly, i, Scalar(255, 0, 0), 5);
                for(int j=0; j<4; ++j) biggest[j]=conPoly[i][j];
                MaxArea=area;
            }

        }
    }
    return biggest;
}

vector<Point> reorder(vector<Point> points) {
    vector<Point> newPoints(4);
    vector<int> sumPoints(4), subPoints(4);
    for(int i=0; i<4; ++i) {
        sumPoints[i]=points[i].x+points[i].y;
        subPoints[i]=points[i].x-points[i].y;
    }
    newPoints[0]=points[min_element(sumPoints.begin(), sumPoints.end())-sumPoints.begin()]; // 0
    newPoints[1]=points[max_element(subPoints.begin(), subPoints.end())-subPoints.begin()]; // 1
    newPoints[2]=points[min_element(subPoints.begin(), subPoints.end())-subPoints.begin()]; // 2
    newPoints[3]=points[max_element(sumPoints.begin(), sumPoints.end())-sumPoints.begin()]; // 3

    return newPoints;
}

void drawPoints(Mat img, vector<Point> points, Scalar color) {
    for(int i=0; i<points.size(); ++i) {
        circle(img, points[i], 10, color, FILLED);
        putText(img, to_string(i), Point(points[i].x+10, points[i].y-10), FONT_HERSHEY_DUPLEX, 1, color, 2);
    }
}

Mat getWarp(Mat img, vector<Point> points, const float w, const float h) {
    Mat imgWarp, matrix;

    Point2f src[4]={points[0], points[1], points[2], points[3]};
    Point2f dst[4]={{0.0f, 0.0f}, {w, 0.0f}, {0.0f, h},{w, h}};

    matrix=getPerspectiveTransform(src, dst);
    warpPerspective(img, imgWarp, matrix, Point(w, h));

    return imgWarp;
}

void DocumentScanner() {

    VideoCapture cap(0);
    Mat imgOrg, imgThre, imgWarp, imgCrop;
    while(1) {
        cap.read(imgOrg);
        //resize(imgOrg, imgOrg, Size(), 0.5, 0.5);
        vector<Point> initPoints, docPoints;

        //Preprocessing
        imgThre=preProcessing(imgOrg);

        //Get Contours (assume the A4 paper is the biggest object in the frame)
        initPoints=getContours(imgOrg, imgThre);

        docPoints=reorder(initPoints);
        //drawPoints(imgOrg, docPoints, Scalar(0, 255, 0));

        //Warp
        imgWarp=getWarp(imgOrg, docPoints, w, h);

        //Crop
        int CropVal=5;
        Rect roi(CropVal, CropVal, w-2*CropVal, h-2*CropVal);
        imgCrop=imgWarp(roi);

        imshow("Image", imgOrg);
        imshow("Dilation Image", imgThre);
        imshow("Warp Image", imgWarp);
        imshow("Crop Image", imgCrop);

        waitKey(1);
    }
}

int main() {
    DocumentScanner();
    return 0;
}