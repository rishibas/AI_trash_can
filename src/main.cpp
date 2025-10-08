#include <iostream>
#include "opencv2/opencv.hpp"

using namespace cv;

int main(int, char**){
    VideoCapture cap(0);//open the default camera using default API 
    if (!cap.isOpened()){
        std::cerr << "Unable to open camera!\n"; //send mesage for screan
        return -1;
    }
    
    // cap.set(CAP_PROP_FRAME_WIDTH, 100);
    // cap.set(CAP_PROP_FRAME_HEIGHT, 50);

    Mat frame; //cv:Mat is N-dimensional dense numerical array. hold images, matrix data.
    namedWindow("edges", 1);//move, resize, close that window...
    for(;;){
        cap >> frame;
        // cvtColor(frame, edges, COLOR_BGR2GRAY);
        // Canny(edges, edges, 0, 30, 3);//take a grayscale input image and produce an outupt image where the edges are highlights
        imshow("edges", frame);
        if (waitKey(30) >= 0) break;
    }
    return 0;
}