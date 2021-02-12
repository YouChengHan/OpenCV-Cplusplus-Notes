#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;
/*
Project1: Virtual Painter
*/

/*
These range can be obtain through ColorPicker.
Since these numbers will be influenced by the environment, resampling is recommended.

green: h:[24, 95], s:[44, 146], v:[112, 255]
pink: h:[153, 177], s:[170, 255], v:[150, 241]

*/

vector<vector<int>> newPoints;

const vector<vector<int>> myColors{
    {24, 95, 44, 146, 112, 255}, 
    {153, 177, 170, 255, 150, 241}
};

const vector<Scalar> myColorValues{
    {0, 255, 0}, 
    {147, 20, 255}
};
const vector<string> name{"green", "pink"};

Point findDrawPoint(Mat src, Mat dst) {
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    findContours(src, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    
    vector<vector<Point>> conPoly(contours.size());
    vector<Rect> boundingBox(contours.size());
    Point myPoint(0, 0);

    for(int i=0; i<contours.size(); ++i) {
        int area=contourArea(contours[i]);
		string objType;

        if(area>1000) {
            float para=arcLength(contours[i], true);
            approxPolyDP(contours[i], conPoly[i], 0.02*para, true);

            cout<<conPoly[i].size()<<endl;

            boundingBox[i]=boundingRect(conPoly[i]);
            myPoint.x=boundingBox[i].x+boundingBox[i].width/2;
            myPoint.y=boundingBox[i].y;

            //drawContours(dst, conPoly, i, Scalar(255, 0, 0), 2);
            rectangle(dst, boundingBox[i], Scalar(255, 0, 255), 5);
        }
    }
    return myPoint;
}

void DrawPoints(Mat img, vector<vector<int>> &drawpoints, const vector<Scalar> &drawvalues) {
    for(int i=0; i<drawpoints.size(); ++i)
        circle(img, Point(drawpoints[i][0], drawpoints[i][1]), 10, drawvalues[drawpoints[i][2]], FILLED);
}

vector<vector<int>> findPoints(Mat img) {

    Mat imgHSV, mask;

    cvtColor(img, imgHSV, COLOR_BGR2HSV);
    for(int i=0; i<myColors.size(); ++i) {
        Scalar lower(myColors[i][0], myColors[i][2], myColors[i][4]), 
            upper(myColors[i][1], myColors[i][3], myColors[i][5]);

        inRange(imgHSV, lower, upper, mask);
        //imshow(name[i], mask);
        Point myPoint=findDrawPoint(mask, img);
        if(myPoint.x!=0&&myPoint.y!=0)
            newPoints.push_back({myPoint.x, myPoint.y, i});
    }
    return newPoints;
    /*
    newPoints should be declared as a global variable, 
    or the trail will not be colored.
    */
}

void cleanCanvas() {
    newPoints.clear();
}

void VirtualPainter() {
    VideoCapture cap(0);
    Mat img;
    while(1) {
        
        cap.read(img);
        flip(img, img, 1);
        /*
        For convenience, the frame has been flipped.

        flipCode>0: flip across y-axis.
        flipCode==0: flip across x-axis.
        flipCode<0: flip across both x and y axis.
        */

        vector<vector<int>> points;
        points=findPoints(img);
        DrawPoints(img, points, myColorValues);

        imshow("Webcam", img);
        if(waitKey(1)==' ') cleanCanvas();
        // An addtional function, press spacebar can clear the canvas.
    }
}
int main() {
    VirtualPainter();
    return 0;
}