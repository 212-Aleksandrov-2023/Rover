//
// Created by akiri on 14.10.2023.
//

#ifndef TESTPLACE_STONE_H
#define TESTPLACE_STONE_H

#endif //TESTPLACE_STONE_H

#define max_x 25
#define max_y 25
#define max_z 25
#define e 1.1
class StoneEx{};

class Stone{
private:
    double x;
    double y;
    double radius;
public:


    Stone() = default;
    Stone(double x1, double y1, double r);

    double GetRadius() const;
    double GetHeight() const;
    void plot_stone(vector<Hill> & arr, ofstream & out);
};

double Stone::GetRadius() const {
    return this->radius;
}

Stone::Stone (double x1, double y1,double r){
    if (r < 0 || x1 < 0 ||  y1 < 0){
        throw StoneEx();
    }
    if (x1 > max_x){
        throw StoneEx();
    }
    if ( y1 > max_y){
        throw StoneEx();
    }

    x = x1;
    y = y1;
    radius = r;
}

void Stone:: plot_stone(vector<Hill> &arr ,ofstream & out){
    double result;
    double k = 0;
    for (double i = x - radius*e; i < x + radius*e; i+=0.1){
        for (double j = y - radius*e ; j < y + radius*e ; j += 0.1){
            result = radius * radius  - (i -x) * (i - x) - (j-y) * (j - y);
            for ( size_t l = 0 ; l < arr.size(); l++){
                k += arr[l].GaussColon(i,j);
            }
            if (result > 0){
                out << i << " " << j <<" " << sqrt(result) + k << "\n";
            }
            else{
                out << i << " " << j <<" " << k << "\n";

            }
            k = 0;

        }
        out <<"\n";
    }
    out <<"\n";
}