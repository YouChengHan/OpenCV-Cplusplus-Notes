#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;
/*
Shapes Detection
*/

void getContours(Mat src, Mat dst) {
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    findContours(src, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    //drawContours(dst, contours, -1, Scalar(255, 0, 0), 2);
    /*
    Grayscale is accepted, but usually use the binary image.
    contours[i] means i-th contour, and the elements of contours[i] is the pixels of the contour.
    Vec4i: a vector with four elements.
    The four integers imply the serial number of different contours.
    */

    vector<vector<Point>> conPoly(contours.size());
    vector<Rect> boundingBox(contours.size());

    for(int i=0; i<contours.size(); ++i) {
        int area=contourArea(contours[i]);
        cout<<area<<endl;
		string objType;

        if(area>1000) { // filter the noise

            //drawContours(dst, contours, i, Scalar(255, 0, 0), 2); // draw the contours

            float para=arcLength(contours[i], true);
            approxPolyDP(contours[i], conPoly[i], 0.02*para, true); // capture the shape of polygons

            cout<<conPoly[i].size()<<endl; // the corners of the polygons

            boundingBox[i]=boundingRect(conPoly[i]);

			int objCor=(int)conPoly[i].size();
			if(objCor==3) objType="Triangle";
			else if(objCor==4) {
                float aspRatio=(float)boundingBox[i].width/(float)boundingBox[i].height;
                cout<<aspRatio<<endl;

                if(aspRatio>0.95&&aspRatio<1.05) objType="Square";
                else objType="Rectangle";
            }
			else if(objCor>4) objType="Circle";

            drawContours(dst, conPoly, i, Scalar(255, 0, 0), 2); // draw the shapes of polygons
            rectangle(dst, boundingBox[i], Scalar(255, 0, 255), 5);
            /*
            another option:
            rectangle(dst, boundingBox[i].tl(), boundingBox[i].br(), Scalar(0, 69, 255), 5);

            Same format in Chapter4.
            Rect.tl(): the top left point. Rect.br(): the bottom right point.
            */
			putText(dst, objType, {boundingBox[i].x, boundingBox[i].y-5}, FONT_HERSHEY_PLAIN, 1, Scalar(255, 0, 255), 1.7);
        }
    }
    /*
    When to use double, long double, float:
    double is always the recommended choice, while long double for more range or accuracy than double.
    float for a lot of floating-point numbers operation (at least 1k or more).
    But sometimes the precision is not the main concern, which represents the use of 
    precious resources (CPU cache, RAM, ...) can be reduced.

    discussion: 
    https://softwareengineering.stackexchange.com/
    questions/316822/why-are-floats-still-part-of-the-java-language-when-doubles-are-mostly-recommend
    */
}

void Func() {
    string pth="Resources/shapes.png";
    Mat img=imread(pth);
    Mat imgGray, imgBlur, imgCanny, imgDilate;

    // Preprocessing
    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
    Canny(imgBlur, imgCanny, 25, 75);
    Mat kernel=getStructuringElement(MORPH_RECT, Size(3, 3));
    dilate(imgCanny, imgDilate, kernel);
    /*
    Using dilate image to detect the contour of objects will cause better result. 
    Since the edges captured by canny will be expanded by dilation, the little flaw will be filled.
    */
    getContours(imgDilate, img);

    imshow("Image", img);
    /*
    imshow("GrayScale Image", imgGray);
    imshow("Blur Image", imgBlur);
    imshow("Canny Image", imgCanny);
    imshow("Dilate Image", imgDilate);
    */

    waitKey(0);
}
int main() {
    Func();
    return 0;
}