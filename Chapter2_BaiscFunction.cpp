#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;
/* 
The Basic Function of OpenCV 
1. Color Space Conversion: cvtColor()
2. Image Filtering: GaassianBlur()
3. Edge Detection: Canny()
4. Dilation of Edges: dilate()
5. Erosion of Edges: erode()
*/
void Func() {
    string pth="Resources/test.png";
    Mat img=imread(pth);
    Mat imgGray, imgBlur, imgCanny, imgDilate, imgErode;

    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
    /*
    The number of the Size() (ksize) is odd in most of the time.
    The selection of the number depends on the ratio of width and height of the image. (test.png is approximately 1:1)
    the follow two parameters (sigmaX, sigmaY) is the standard deviation of the method.
    If sigmaY==0, it will be set as same as sigmaX.
    If both equal to 0, it will be calculate by ksize.
    */
    Canny(imgBlur, imgCanny, 50, 150);
    /*
    The common processing order:
    1. Blur the image.
    2. Convert to gray scale image.
    3. Detect the edges by Canny algorithm.

    The image should be blurred before detecting the edge, or the result will be interfered by noises easily.
    Larger thresholds will capture less edges.
    Usually, the ratio of threshold1 and threshold2 will between 1/2 and 1/3.
    */

    Mat kernel=getStructuringElement(MORPH_RECT, Size(5, 5));
    dilate(imgCanny, imgDilate, kernel);
    erode(imgDilate, imgErode, kernel);
    /*
    These two functions will be called  togother usually.
    It can capture the important edges and reduce the influence of the noises.

    The effect will be more obvious with bigger kernel.
    Dilate: Expand edges in the regions. It will become thicker.
    Erode: The opposition of Dilate. Decrease the thickness and remove the noises. The result will be thinner.
    */

    imshow("Image", img);
    imshow("GrayScale Image", imgGray);
    imshow("Blur Image", imgBlur);
    imshow("Canny Image", imgCanny);
    imshow("Dilate Image", imgDilate);
    imshow("Erode Image", imgErode);

    waitKey(0);
}
int main() {
    Func();
    return 0;
}