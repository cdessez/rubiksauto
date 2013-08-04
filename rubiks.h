#ifndef RUBIKS_H
#define RUBIKS_H

#include "extraction.h"

class Rubiks {

    protected :
    RubiksFace faces[6] ;
    Image<Vec3b> patron ;
    int faceToFill ;

    public :

    Rubiks() : patron(510, 380, CV_8UC3, Scalar(0,0,0)), faceToFill(0) {
        imshow("Resultat", patron) ;
    }

    void setNewFace(const RubiksFace& face){
        faces[faceToFill]= face ;
        int x,y ;
        if (faceToFill < 4){
            y = 130 ;
            x = faceToFill * 130 ;
        } else if (faceToFill==4){
            x = 390 ;
            y = 0 ;
        } else if (faceToFill==5){
            x = 390 ;
            y = 260 ;
        }
        Image<Vec3b> roi(patron, Rect(x, y, 120, 120)) ;
        drawRubiksFace(faces[faceToFill], roi);
        faceToFill++ ;
        imshow("Resultat", patron);
    }



};


#endif
