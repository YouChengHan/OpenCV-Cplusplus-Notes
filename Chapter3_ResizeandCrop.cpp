#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;
/*
Resize and Crop
*/
void Func() {
    string path="Resources/test.png";
    Mat img=imread(path);
    Mat imgResize, imgCrop;

    cout<<img.size()<<endl; //768*559
    resize(img, imgResize, Size(), 0.5, 0.5); // Size(640, 480)

    Rect roi(200, 100, 300, 300); //region of interest parameter: x, y, width, height
    imgCrop=img(roi);

    imshow("Image", img);
    imshow("Resize Image", imgResize);
    imshow("Crop Image", imgCrop);

    waitKey(0);
}
int main() {
    Func();
    return 0;
}