#ifndef EXTRACTION_H
#define EXTRACTION_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/calib3d/calib3d.hpp>

#include "image.h"
#include "contour.h"

using namespace cv;
using namespace std;

vector<Image<uchar> > colorsExtraction(const Image<Vec3b>& image) ;
Image<Vec3b> printColors(const vector<Image<uchar> >& colors) ;
vector<Contour> getBlobs(const vector<Image<uchar> >& colors, int minSize, int maxSize) ;
Image<Vec3b> drawBlobs(const vector<Contour> &contours, int width, int height) ;
vector<Contour> sortBlobs(vector<Contour> &contours) ;
void fonduReelContours(const Image<Vec3b>& reel, const Image<Vec3b>& contours, Image<Vec3b>& output) ;
bool extractRubiks(vector<Contour> contours, RubiksFace& output) ;
void drawRubiksFace(const RubiksFace& face, Image<Vec3b>& res) ;


#endif
