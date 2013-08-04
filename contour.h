#ifndef CONTOUR_H
#define CONTOUR_H


enum RubColor {
  BLUE=0, GREEN=1, RED=2, WHITE=3, YELLOW=4, ORANGE=5, BLACK=6
};


inline Scalar colorToScalar(int color){
    switch (color){
        case BLUE : return Scalar(255,0,0) ;
        case GREEN : return Scalar(0,255,0) ;
        case RED : return Scalar(0,0,255) ;
        case WHITE : return Scalar(255,255,255) ;
        case YELLOW : return Scalar(0,255,255) ;
        case ORANGE : return Scalar(0,128,255) ;
        case BLACK : return Scalar(0,0,0) ;
    }
}


class Contour : public vector<Point> {

    public :

    int color ;
    Point center ;
    float width ;
    int isExt, isMid ;

    inline Contour(vector<Point> v, RubColor color) :  vector<Point>(v), color(color), isExt(0), isMid(0) {} ;
    inline Contour(vector<Point> v, int color) :  vector<Point>(v), color(color), isExt(0), isMid(0) {} ;
    inline Contour(vector<Point> v, int color, Point center) :  vector<Point>(v), color(color), center(center), isExt(0), isMid(0) {} ;
    inline Contour(vector<Point> v, int color, Point center, double w) :  vector<Point>(v), color(color), center(center), width(w), isExt(0), isMid(0) {} ;

    protected :


};



class RubiksFace {

    protected :
    int cases[3][3] ;

    public :
    RubiksFace() {
        for(size_t x = 0 ; x<3 ; x++)
            for(size_t y=0 ; y<3 ; y++)
                cases[x][y] = BLACK ;
    }

    inline RubiksFace(const RubiksFace& face){
        for(size_t x = 0 ; x<3 ; x++)
            for(size_t y=0 ; y<3 ; y++)
                cases[x][y] = face(x,y) ;
    }

    inline int& operator()(int x, int y) { return cases[x][y] ; }
    inline int operator()(int x, int y) const { return cases[x][y] ; }

    inline bool operator==(RubiksFace face2) {
        for(size_t x = 0 ; x<3 ; x++)
            for(size_t y=0 ; y<3 ; y++)
                if (cases[x][y]!=face2(x,y))
                    return false ;
        return true ;
    }

};





#endif
