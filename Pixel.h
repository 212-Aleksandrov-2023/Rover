//
// Created by akiri on 14.10.2023.
//

#ifndef TESTPLACE_PIXEL_H
#define TESTPLACE_PIXEL_H

#endif //TESTPLACE_PIXEL_H

class Pixel{
    int resolution{};
    double pixel_size;
public:
    vector<Hill> array;
    Surface terra{};
    Pixel() = default;
    Pixel( int n , Surface & s, const vector<Hill> &  a);
    Pixel(int n  , Surface &  s );
    int Get_resolution() const{return resolution;}
    double Get_pixel_size() const {return pixel_size;}
};

Pixel::Pixel(int n  , Surface &  s ,  const vector<Hill>  & a) {
    resolution = n;
    terra = s;
    array = a;
    pixel_size =  terra.GetLenght() / resolution;

}
Pixel::Pixel(int n  , Surface &  s ) {
    resolution = n;
    terra = s;
    pixel_size =  terra.GetLenght() / resolution;
}