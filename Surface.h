//
// Created by akiri on 14.10.2023.
//

#ifndef TESTPLACE_SURFACE_H
#define TESTPLACE_SURFACE_H

#endif //TESTPLACE_SURFACE_H

using namespace std;

class Surface{
private:
    double lenght;
    double width;
    double height_s;

public:
    class MyExeption{};

    Surface() = default;
    Surface(double x , double y, double z);


    void Fill_surface(vector<Hill> & arr , ofstream &out);
    double Get_Current_Point_Height(double x, double y,vector<Hill> & arr);
    double GetLenght() const{return lenght;}
    double GetWidth() const{return width;}
    double GetHeigt() const{return height_s;}


};

Surface::Surface(double x, double y, double z) {

    height_s = z;
    lenght = x;
    width = y;

}

double Surface::Get_Current_Point_Height(double x, double y, vector<Hill> & arr) {
    double k = 0;
    for ( size_t l = 0 ; l < arr.size(); l++){
        k += arr[l].GaussColon(x,y);
    }
    return k;
}
void Surface::Fill_surface(vector<Hill> &arr, std::ofstream &out) {
    double k = 0;

    for ( double i = 0 ; i < this->GetLenght(); i += 0.2){
        for ( double j = 0; j < this->GetWidth(); j += 0.2){
            for ( size_t l = 0 ; l < arr.size(); l++){
                k += arr[l].GaussColon(i,j);

            }
            out << i << " " << j << " " << k << "\n";
            k = 0;
        }
        out << "\n";
    }
}
