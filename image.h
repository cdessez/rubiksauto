#ifndef IMAGE_H
#define IMAGE_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

template <class T>
class Image : public Mat {

    public :

    Image<T>(){}
    Image<T>(int w, int h, int type) : Mat(h,w,type) {}
    Image<T>(int w, int h, int type, Scalar s) : Mat(h,w,type,s) {}
    Image<T>(const Mat& A) : Mat(A) {}
    Image<T>(const Mat& A, const Rect& roi) : Mat(A,roi){}

    inline T operator()(int x, int y) const {
        return at<T>(y,x) ;
    }

    inline T& operator()(int x, int y) {
        return at<T>(y,x) ;
    }

    inline int width() const { return cols ; }
    inline int height() const { return rows ; }


} ;

#endif
