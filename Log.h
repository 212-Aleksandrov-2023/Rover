//
// Created by akiri on 14.10.2023.
//

#ifndef TESTPLACE_LOG_H
#define TESTPLACE_LOG_H

#endif //TESTPLACE_LOG_H

#define max_x 25
#define max_y 25
#define max_z 25


struct Point{
    double x, y;
};

class LogEx{};
class Log{
private:
    double radius;
    Point n1;
    Point n2;
public:
    Log() = default;
    Log(double x1,double y1 ,double  x2 ,double y2 ,double r);

    double GetRadius() const;
    void plot_log(vector<Hill> & arr,ofstream & out);


};

double Log::GetRadius() const {
    return this->radius;
}

Log::Log(double x1,double y1 ,double  x2 ,double y2 ,double r){
    if (r > 2){
        throw LogEx();
    }
    if (x1 >  max_x || x2 > max_x || y1 > max_y || y2 > max_y ){
        throw LogEx();
    }

    n1.x = x1;
    n1.y = y1;
    n2.x =x2;
    n2.y = y2;
    radius = r;

}
Point move(double x, double y,Point n1 , Point n2 , Point m ){
    Point result;
    double a , b, a1 ,b1;
    a = n2.x - n1.x;
    b = n2.y - n1.y;
    a1 = n1.y - n2.y;
    b1 = n2.x - n1.x;
    result.x = a* x + a1 * y + m.x;
    result.y = b * x + b1 * y + m.y;
    return result;
}

void Log::plot_log(vector<Hill> &arr, std::ofstream &out){
    double result;
    double k = 0;
    Point mid;
    mid.x = (n1.x + n2.x) / 2;
    mid.y = (n1.y + n2.y) / 2;
    double distance = sqrt( (n1.x - n2.x)*(n1.x - n2.x) + (n1.y - n2.y)*(n1.y - n2.y) ) /2;
    Point f;

    for (double i = -distance    ; i < distance   ; i += 0.05){
        for (double j = -radius  ; j < radius ; j += 0.05){
            f = move(i, j, n1, n2 , mid);
            result = radius * radius  - pow(((n2.y - n1.y) * f.x + (n1.x - n2.x)*f.y + (n2.x - n1.x)*n1.y - (n2.y - n1.y)*n1.x),2);

            for ( size_t l = 0 ; l < arr.size(); l++){
                k += arr[l].GaussColon(f.x,f.y);
            }
            if (result > 0){
                out << f.x << " " << f.y <<" " << sqrt(result) +k  << "\n";
            }
            else{
                out << f.x << " " << f.y <<" " << k<< "\n";

            }
            k = 0;

        }
        out <<"\n";
    }
    out <<"\n";

}
