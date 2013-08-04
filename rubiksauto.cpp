#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/calib3d/calib3d.hpp>

#include <iostream>
#include "image.h"
#include "rubiks.h"
#include "extraction.h"
#include "contour.h"

using namespace cv;
using namespace std;


int main(){

    VideoCapture capture ;
    capture.open(0);

    Image<Vec3b> frame0, frame ;
    namedWindow("AutoRubiks", 1);

    int faceNum = 1 ;
    int recFaceNum ;
    RubiksFace facePrecedente ;
    bool faceDetectee ;
    Rubiks rubiks ;
    bool detectionTerminee = false ;

    while(!detectionTerminee){

        capture >> frame0 ;
        if (frame0.empty()) continue ;
        flip(frame0, frame, 1);
        vector<Image<uchar> > colors = colorsExtraction(frame) ;
        //imshow("Colors", printColors(colors)) ;
        vector<Contour> blobs = getBlobs(colors, 100, 250) ;

        //imshow("Contours", drawBlobs(blobs, frame.width(), frame.height())) ;
        Image<Vec3b> contoursImg = drawBlobs(blobs, frame.width(), frame.height()) ;
        Image<Vec3b> camContours(frame.width(), frame.height(), CV_8UC3, Scalar(0,0,0)) ;
        fonduReelContours(frame, contoursImg, camContours) ;
        imshow("AutoRubiks", camContours) ;

        RubiksFace face ;
        Image<Vec3b> faceImg(120,120, CV_8UC3, Scalar(0,0,0)) ;

        if (extractRubiks(blobs, face)) {
            if (faceDetectee && facePrecedente==face){
                recFaceNum++;
                facePrecedente = face ;
                if (recFaceNum==12){
                    cout << "Face n°" << faceNum << " détectée" << endl ;
                    rubiks.setNewFace(face);
                    if (faceNum==6)
                        detectionTerminee = true ;
                    faceNum++ ;
                }
            } else {
                facePrecedente = face ;
                recFaceNum = 1 ;
                faceDetectee = true ;
            }
        }

        drawRubiksFace(face, faceImg);
        imshow("face courante", faceImg) ;
        //imshow("initial", frame);

        switch(waitKey(2)){
            case 27 :

            case 'q' :
            return 0 ;
            break ;
        }
    }

	waitKey();
	return 0;
}
