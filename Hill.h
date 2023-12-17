//
// Created by akiri on 14.10.2023.
//

#ifndef TESTPLACE_HILL_H
#define TESTPLACE_HILL_H

#endif //TESTPLACE_HILL_H


class Hill{
private:
    double x, y, sigma1 , sigma2, height_h;

public:

    Hill() = default;
    Hill(double x, double y, double sigma1, double sigma2, double height);


    double GaussColon(double x, double y);
    double GetLenght() const{return x;}
    double GetWidth() const{return y;}
    double GetHeight() const{return height_h;}
    double GetSigma1() const{return sigma1;}
    double GetSigma2() const{return sigma2;}


};

Hill::Hill (double x1, double y1, double sigma11, double sigma22, double height1) {
    if( x1  > this->x){

    }
    if ( y1 > this->y){

    }
    if ( height1 > this->height_h){

    }
    x = x1;
    y = y1;
    sigma1 = sigma11;
    sigma2 = sigma22;
    height_h = height1;
}

double Hill::GaussColon(double x1, double y1) {
    double e;
    e = exp( -1 * ((x1 -x)*(x1-x) / 2*sigma1*sigma1 + (y1-y)*(y1-y) / 2*sigma2*sigma2 ) );
    return height_h * e;
}