#include "extraction.h"

#define square(x) ((x)*(x))


vector<Image<uchar> > colorsExtraction(const Image<Vec3b>& image) {

    Image<Vec3b> hsv ;
    cvtColor(image, hsv, CV_BGR2HSV) ;

    // Réglages des lissages
    const int filterSize = 7 ;
    const int filterSize2 = 3 ;
    Mat element(filterSize,filterSize,CV_8U,Scalar(1)) ;
    Mat element2(filterSize,filterSize,CV_8U,Scalar(1)) ;

    Image<uchar> white(hsv.width(), hsv.height(), CV_8U) ;
    const uchar maxswhite = 100, minvwhite = 150 ;
    Image<uchar> green(hsv.width(), hsv.height(), CV_8U) ;
    const uchar hgreen = 75, hdgreen = 15 ;
    const uchar minsgreen = 140, minvgreen = 100 ;
    Image<uchar> orange(hsv.width(), hsv.height(), CV_8U) ;
    const uchar horange = 14, hdorange = 8 ;
    const uchar minsorange = 120, minvorange = 110, maxvorange = 255 ;
    Image<uchar> red(hsv.width(), hsv.height(), CV_8U) ;
    const uchar hred = 178, hdred = 7 ;
    const uchar minsred = 120, minvred = 110, maxvred = 255 ;
    Image<uchar> blue(hsv.width(), hsv.height(), CV_8U) ;
    const uchar hblue = 110, hdblue = 15 ;
    const uchar minsblue = 128, minvblue = 100, maxvblue = 255 ;
    Image<uchar> yellow(hsv.width(), hsv.height(), CV_8U) ;
    const uchar hyellow = 35, hdyellow = 15 ;
    const uchar minsyellow = 110, minvyellow = 130, maxvyellow = 255 ;

    for(size_t x=0 ; x<hsv.width() ; x++){
        for(size_t y=0 ; y<hsv.height() ; y++){
            Vec3b pix = hsv(x, y) ;
            // rouge
            if ((pix[0]<=hred+hdred-180 || pix[0]>=hred-hdred) && pix[1]>minsred && pix[2]>minvred && pix[2]<maxvred)
                red(x,y) = 255 ;
            else
                red(x,y) = 0 ;
            // vert
            if (abs(pix[0]-hgreen)<=hdgreen && pix[1]>minsgreen && pix[2]>minvgreen)
                green(x,y) = 255 ;
            else
                green(x,y) = 0 ;
            // orange
            if (abs(pix[0]-horange)<=hdorange && pix[1]>minsorange && pix[2]>minvorange && pix[2]<=maxvorange)
                orange(x,y) = 255 ;
            else
                orange(x,y) = 0 ;
            // bleu
            if (abs(pix[0]-hblue)<=hdblue && pix[1]>minsblue && pix[2]>minvblue && pix[2]<maxvblue)
                blue(x,y) = 255 ;
            else
                blue(x,y) = 0 ;
            // jaune
            if (abs(pix[0]-hyellow)<=hdyellow && pix[1]>minsyellow && pix[2]>minvyellow && pix[2]<maxvyellow)
                yellow(x,y) = 255 ;
            else
                yellow(x,y) = 0 ;
            // blanc
            if (pix[1]<=maxswhite && pix[2]>=minvwhite)
                white(x,y) = 255 ;
            else
                white(x,y) = 0 ;
        }
    }

    //*
    morphologyEx(red,red,MORPH_OPEN,element) ;
    morphologyEx(yellow,yellow,MORPH_OPEN,element) ;
    morphologyEx(blue,blue,MORPH_OPEN,element) ;
    morphologyEx(orange,orange,MORPH_OPEN,element) ;
    morphologyEx(white, white, MORPH_OPEN,element2) ;
    morphologyEx(green,green,MORPH_OPEN,element) ; //*/
    //*
    morphologyEx(red,red,MORPH_OPEN,element) ;
    //morphologyEx(yellow,yellow,MORPH_OPEN,element) ;
    morphologyEx(blue,blue,MORPH_OPEN,element) ;
    morphologyEx(orange,orange,MORPH_OPEN,element) ;
    //morphologyEx(white, white, MORPH_OPEN,element) ;
    morphologyEx(green,green,MORPH_OPEN,element) ; //*/

    vector<Image<uchar> > colors(6) ;
    colors[0] = blue ;
    colors[1] = green ;
    colors[2] = red ;
    colors[3] = white ;
    colors[4] = yellow ;
    colors[5] = orange ;
    return colors;
}


Image<Vec3b> printColors(const vector<Image<uchar> >& colors){

    Image<uchar> black(colors[0].width(), colors[0].height(), CV_8U, Scalar(0)) ;
    vector<Mat> bgrVect(3), whiteVect(3), yellowVect(3), orangeVect(3) ;
    bgrVect[0] = colors[0] ;
    bgrVect[1] = colors[1] ;
    bgrVect[2] = colors[2] ;
    whiteVect[0] = colors[3] ;
    whiteVect[1] = colors[3] ;
    whiteVect[2] = colors[3] ;
    yellowVect[0] =  black ;
    yellowVect[1] = colors[4] ;
    yellowVect[2] = colors[4] ;
    orangeVect[0] = black ;
    orangeVect[1] = colors[5]/2 ;
    orangeVect[2] = colors[5] ;
    Image<Vec3b> bgr, white, yellow, orange ;
    merge(bgrVect, bgr) ;
    merge(whiteVect, white) ;
    merge(yellowVect, yellow) ;
    merge(orangeVect, orange) ;
    add(bgr, white, bgr) ;
    add(bgr, yellow, bgr) ;
    add(bgr, orange, bgr) ;
    return bgr ;
}


vector<Contour> getBlobs(const vector<Image<uchar> >& colors, int minSize, int maxSize){

    vector<Contour> res ;
    for(int c=0 ; c<6 ; c++){
        vector<vector<Point> > contours;
        findContours(colors[c], contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE) ;
        int n = contours.size() ;
        for(size_t i=0 ; i<n ; i++) {
            if (contours[i].size() <= maxSize && contours[i].size() >= minSize){
                RotatedRect r = minAreaRect(contours[i]) ;
                double d = r.size.width / r.size.height ;
                if (d>0.75 && d<1.3333)
                    res.push_back(Contour(contours[i], c, r.center, (d>1.0 ? r.size.width : r.size.height)));
            }
        }
    }

    return sortBlobs(res) ;
}


Image<Vec3b> drawBlobs(const vector<Contour> &contours, int width, int height){
    Image<Vec3b> res(width, height, CV_8UC3, Scalar(0,0,0)) ;
    size_t n= contours.size() ;
    for(size_t i=0 ; i<n ; i++){
        size_t m= vector<Point>(contours[i]).size() ;
        for(size_t j=0 ; j<m ; j++){
            int x = contours[i][j].x, y = contours[i][j].y ;

            switch (contours[i].color) {
                case BLUE :
                res(x,y)[0]=255 ;
                break;
                case GREEN :
                res(x,y)[1]=255 ;
                break;
                case RED :
                res(x,y)[2]=255 ;
                break;
                case WHITE :
                res(x,y)[0]=255 ;
                res(x,y)[1]=255 ;
                res(x,y)[2]=255 ;
                break;
                case YELLOW :
                res(x,y)[1]=255 ;
                res(x,y)[2]=255 ;
                break;
                case ORANGE :
                res(x,y)[1]=128 ;
                res(x,y)[2]=255 ;
                break;
            }
            circle(res, contours[i].center, contours[i].width/2, colorToScalar(contours[i].color), 3) ;
        }
    }
    return res ;
}


vector<Contour> sortBlobs(vector<Contour> &contours){
    int n = contours.size() ;
    for(size_t i=0 ; i<n ; i++){
        for(size_t j=i+1 ; j<n ; j++){
            double cote = (contours[i].width < contours[j].width ? contours[i].width : contours[j].width) ; // plus petite largeur
            if (square(contours[i].center.x-contours[j].center.x)+square(contours[i].center.y-contours[j].center.y)
                > square(2.7*cote)    // distance entre les deux centre supérieure à 2.5*cote
                || (contours[i].width>contours[j].width ? contours[i].width/contours[j].width : contours[j].width/contours[i].width) > 1.3 )
                // rapport de largeur des facettes extérieures
                continue ;
            Point2f mid((contours[i].center.x+contours[j].center.x)/2., (contours[i].center.y+contours[j].center.y)/2.) ;
            for(size_t k=0 ; k<n ; k++){
                if (k==i || k==j
                    || (contours[k].width<cote ? cote/contours[k].width : contours[k].width/cote) > 1.3)
                    continue ;
                if (square(mid.x-contours[k].center.x)+square(mid.y-contours[k].center.y) < square(0.3*cote)){
                    // tolérance concernant le placement du centre du carré du milieu
                    contours[i].isExt++;
                    contours[j].isExt++;
                    contours[k].isMid++;
                }
            }
        }
    }
    vector<Contour> res ;
    for(size_t i=0 ; i<n ; i++){
        if (contours[i].isExt>=2 || contours[i].isMid>=2 || (contours[i].isExt>=1 && contours[i].isMid>=1)){
            //contours[i].display = true ;
            res.push_back(contours[i]);
        } /*else if (contours[i].isExt>0 || contours[i].isMid>0) {
            res.push_back(contours[i]);
        } */
    }
    return res ;
}


void fonduReelContours(const Image<Vec3b>& reel, const Image<Vec3b>& contours, Image<Vec3b>& output){
    for(size_t x=0 ; x<output.width() ; x++)
        for(size_t y=0 ; y<output.height() ; y++){
            if (contours(x,y)[0]==0 && contours(x,y)[1]==0 && contours(x,y)[2]==0)
                output(x,y) = reel(x,y) ;
            else
                output(x,y) = contours(x,y) ;
        }
}


bool extractRubiks(vector<Contour> contours, RubiksFace& output) {
    vector<Contour*> corners, centers, edges ;
    for(size_t i=0 ; i<contours.size() ; i++){
        if (contours[i].isExt>=2)
            corners.push_back(&contours[i]) ;
        if (contours[i].isMid>=2)
            centers.push_back(&contours[i]) ;
        if (contours[i].isExt>=1 && contours[i].isMid>=1)
            edges.push_back(&contours[i]) ;
    }
    if (centers.size()<1 || centers.size()>2 || corners.size()!=4 || edges.size()!=4)
        return false ;

    // couleur du centre
    if (centers.size()==2 && centers[0]->color!=centers[1]->color)
        return false ;
    output(1,1)=centers[0]->color ;

    // couleur des coins
    int minYX=corners[0]->center.y-corners[0]->center.x, maxYX=minYX ;
    int minXY=corners[0]->center.y+corners[0]->center.x, maxXY=minXY ;
    int hg=0, hd=0, bg=0, bd=0 ;
    for(int i=1 ; i<corners.size() ; i++){
        int yx = corners[i]->center.y-corners[i]->center.x ;
        if (yx<minYX){
            minYX=yx ;
            hd=i ;
        } else if (yx>maxYX) {
            maxYX=yx ;
            bg=i ;
        }
        yx = corners[i]->center.y+corners[i]->center.x ;
        if (yx<minXY){
            minXY=yx ;
            hg=i ;
        } else if (yx>maxXY) {
            maxXY=yx ;
            bd=i ;
        }
    }
    output(0,0) = corners[hg]->color ;
    output(0,2) = corners[bg]->color ;
    output(2,0) = corners[hd]->color ;
    output(2,2) = corners[bd]->color ;

    // couleur des edges
    int minX=edges[0]->center.x, maxX=minX, minY=edges[0]->center.y, maxY=minY ;
    int haut=0, bas=0, gauche=0, droite=0 ;
    for(int i=1 ; i<edges.size() ; i++){
        if (edges[i]->center.x<minX){
            minX=edges[i]->center.x ;
            gauche=i ;
        } else if (edges[i]->center.x>maxX) {
            maxX=edges[i]->center.x ;
            droite=i ;
        }
        if (edges[i]->center.y<minY){
            minY=edges[i]->center.y ;
            haut=i ;
        } else if (edges[i]->center.y>maxY) {
            maxY=edges[i]->center.y ;
            bas=i ;
        }
    }
    output(1,0) = edges[haut]->color ;
    output(1,2) = edges[bas]->color ;
    output(0,1) = edges[gauche]->color ;
    output(2,1) = edges[droite]->color ;

    return true ;
}



void drawRubiksFace(const RubiksFace& face, Image<Vec3b>& res) {
    // l'image ou le ROI res donné en entrée doit être au format 120*120 en CV_8U3C
    for(int x=0 ; x<3 ; x++)
        for(int y=0 ; y<3 ; y++){
            rectangle(res,
                      Point(x*40+1, y*40+1),
                      Point((x+1)*40-2, (y+1)*40-2),
                      colorToScalar(face(x,y)),
                      -1);
        }
}




