#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;
/*
Warp the Perspective
*/

const float w=250, h=350;

void Func() {
    string pth="Resources/cards.jpg";
    Mat img=imread(pth);
    Mat matrix, imgWarp[4];

    Point2f src[4][4]=
    {
        {{529, 142}, {771, 190}, {405, 395}, {674, 457}}, // King
        {{61, 320}, {341, 276}, {87, 638}, {406, 576}}, // Queen
        {{774, 104}, {1021, 82}, {839, 360}, {1119, 334}}, // Jack
        {{738, 381}, {1028, 434}, {642, 712}, {970, 786}}  // Cube9
    };
    // four coordinates of cards.

    Point2f dst[4]={{0.0f, 0.0f}, {w, 0.0f}, {0.0f, h},{w, h}};
    // width and height of the projection image


    for(int i=0; i<4; ++i) {
        matrix=getPerspectiveTransform(src[i], dst);
        warpPerspective(img, imgWarp[i], matrix, Point(w, h));
    }

    double rgb[4][3]=
    {
        {255, 0, 0}, 
        {0, 0, 255}, 
        {0, 69, 255}, 
        {255, 255, 0}
    };
    string name[4]={"King", "Queen", "Jack", "Cube9"};

    for(int i=0; i<4; ++i)
        for(int j=0; j<4; ++j) circle(img, src[i][j], 10, Scalar(rgb[i][0], rgb[i][1], rgb[i][2]), FILLED);

    imshow("Image", img);
    for(int i=0; i<4; ++i)
        imshow(name[i], imgWarp[i]);
    
    /*

    To show pictures in different windows, the name of the window should also be different,
    or it will only display the last image.

    There is also another option:

    for(int i=0; i<4; ++i) {
        imshow("Image", imgWarp[i]);
        waitKey(0);
    }

    But in this way, the click is needed to display the next picture.
    That is, it will only show an image in the same time.

    */

    waitKey(0);
}
int main() {
    Func();
    return 0;
}