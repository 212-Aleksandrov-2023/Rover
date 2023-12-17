//
// Created by akiri on 14.10.2023.
//

#ifndef TESTPLACE_ROVER_H
#define TESTPLACE_ROVER_H

#endif //TESTPLACE_ROVER_H
#include <utility>


using namespace std;

class Rover{
    int gear;
    double length , width , height;
    double x_angle , y_angle;
    std::pair<int , int >  vector;
    Pixel road;
    Point Current_location;
    Point Current_angles;
public:
    Rover() = default;
    Rover(double l , double w , double h , double x_angle , double y_angle , Pixel & S);
    void Move();
    void switch_gear(int a){ if ( a < 0 || a >2 ){ } gear = a;};
    void turn_right(){
        int c = vector.first;
        vector.first = -vector.second;
        vector.second = c;
        swap(Current_location.x , Current_location.y);
    };
    void turn_left() {
        turn_right();
        turn_right();
        turn_right();
    }
    void stay(){ gear = 0;};
    void turn_aroud(){ turn_right();turn_right();}
    int GetCurrentSpeed() const { return gear;}
    bool check_boards();
    bool check_slope();
    bool drive(int m);
    double Get_factor() const {return 1 /road.Get_pixel_size();}
    void Change_Current_location(Point & A);
    void GetCurrentLocation1(ofstream & out);
    Point GetCurrentLocation();
    pair<int , int > Getvector(){return vector;};


};

Point Rover::GetCurrentLocation() {
    Point a;
    if(vector.second == 0){return Current_location;}
    else{
        a = Current_location;
        swap(a.x,a.y);
        return a;
    }

}


void Rover::GetCurrentLocation1(ofstream &out ) {
    double x ,y;
    x = Current_location.x* road.Get_pixel_size();
    y = Current_location.y* road.Get_pixel_size();
        if(vector.second == 0){
//            cout << x<< " " << y<< " "<< 0 << "\n";
            out << x << " " << y<< " "<< road.terra.Get_Current_Point_Height(x,y,road.array) << "\n";
//            cout << Current_angles.x << " " << Current_angles.y << "\n";
        }
        else{
//            cout << y << " " << x << " "<< 0 << "\n";
            out << y<< " " << x << " "<< road.terra.Get_Current_Point_Height(y,x,road.array) << "\n";
//            cout << Current_angles.x << " " << Current_angles.y << "\n";
        }
}

void Rover::Change_Current_location(Point & A) {
    Current_location.x = A.x * this -> Get_factor();
    Current_location.y = A.y * this -> Get_factor();
}

class Processor{
    Point start_point ;
    Point end_point;
    Rover Rov;

public:
    Processor() = default;
    Processor(Point & start , Point & end  ,Rover & R);
    bool start_ride(ofstream & out);
    bool ride(ofstream & out);
    bool drive_along_y(ofstream & out);
    bool drive_along_x(ofstream & out);
    bool recurtion(ofstream & out, int * marker);

};

Processor::Processor(Point &start, Point &end, Rover &R) {
    start_point = start;
    end_point = end;
    Rov = R;
}
bool Processor::start_ride(ofstream & out) {
    bool b;
    int marker = 0;
    Rov.Change_Current_location(start_point);
    Rov.GetCurrentLocation1(out);
    cout << "ride started" << "\n";
    if(Rov.GetCurrentLocation().y - end_point.y *Rov.Get_factor() > 0){
        Rov.turn_aroud();
    }
    b = recurtion(out , &marker);
    if(!b){
        return false;
    }
    cout << "route is complete" << "\n";
    Rov.GetCurrentLocation1(out);
    return true;
}


bool Processor::ride(std::ofstream &out) {
    Rov.switch_gear(2);
    bool flag;
    if(Rov.Getvector().first != 0){
        flag = drive_along_y(out);
        if(!flag){return false;}
        if( (end_point.x * Rov.Get_factor() - Rov.GetCurrentLocation().x) *Rov.Getvector().first > 0){Rov.turn_right();}
        else{Rov.turn_left();}
        flag = drive_along_x(out);
        if(!flag){return false;}
        return true;
    }
    else{
        flag = drive_along_x(out);
        if(!flag){return false;}
        if( (end_point.y *Rov.Get_factor() - Rov.GetCurrentLocation().y)*Rov.Getvector().second< 0){Rov.turn_right();}
        else{Rov.turn_left();}
        flag = drive_along_y(out);
        if(!flag){return false;}
        return true;
    }
}
bool Processor::drive_along_x(std::ofstream &out) {
    while(abs(Rov.GetCurrentLocation().x - end_point.x *Rov.Get_factor())>= 2){
        Rov.drive(2);
        Rov.GetCurrentLocation1(out);
        if (!Rov.check_slope() || !Rov.check_boards()){
            cout << "crashed" << "\n";
            Rov.turn_aroud();
            Rov.drive(2);
            Rov.turn_aroud();
            return false;
        }
    }
    return true;
}
bool Processor::drive_along_y(std::ofstream &out) {
    while(abs(Rov.GetCurrentLocation().y - end_point.y*Rov.Get_factor())>= 2){
        Rov.drive(2);
        Rov.GetCurrentLocation1(out);
        if (!Rov.check_slope() || !Rov.check_boards()){
            cout << "crahed" << "\n";
            Rov.turn_aroud();
            Rov.drive(2);
            Rov.turn_aroud();
            return false;
        }
    }
    return true;
}

bool Processor::recurtion(std::ofstream &out, int * marker) {
    bool flag;
    flag = ride(out);
    *marker += 1;
//    cout << *marker << "marker \n";
    if(*marker >= 100){
        return false;
    }
    if (flag) {
        return true;
    } else {
        Rov.turn_right();
        for (size_t i = 0; i < 3; i++) { Rov.drive(2); }
        Rov.turn_left();
        if (Rov.check_boards() && Rov.check_slope() && *marker < 50) {
            flag = recurtion(out, marker);
            if(flag){
                return true;
            }
            if(*marker >= 100){
                return false;
            }
        } else {
            Rov.turn_left();
            for (size_t i = 0; i < 3; i++) { Rov.drive(2); }
            Rov.turn_right();
            flag = recurtion(out, marker);
            if(flag){
                return true;
            }
            if(*marker >= 100){
                return false;
            }
        }
    }
}


Rover ::Rover(double l, double w, double h, double x, double y, Pixel & S) {
    if (  l < 0 || w < 0 || h < 0 || x < 0 || y < 0){
        throw StoneEx();
    }
    length = l;
    width = w;
    height = h;
    x_angle = x;
    y_angle = y;
    vector.first = 1;
    vector.second = 0;
    road = S;
    Current_location.x = width / 2;
    Current_location.y = length / 2;
    Current_angles.x = 0;
    Current_angles.y = 0;
}

bool Rover::drive(int m) {
    if (gear == 2){
        m +=3;
    }
    double  amount_of_pixels =  4 * road.Get_pixel_size();
//      cout << amount_of_pixels << "\n";
    if (vector.first == 1 || vector.second == 1) {
        switch (m) {
            case 1:
                Current_location.x -= amount_of_pixels;
                Current_location.y += amount_of_pixels;
                break;
            case 2:
                Current_location.y += amount_of_pixels;
                break;
            case 3:
                Current_location.x += amount_of_pixels;
                Current_location.y += amount_of_pixels;
                break;
            case 4:
                Current_location.x += amount_of_pixels;
                Current_location.y += amount_of_pixels;
                Current_location.y += amount_of_pixels;
                break;
            case 5:
                Current_location.y += amount_of_pixels;
                Current_location.y += amount_of_pixels;
                break;
            case 6:
                Current_location.x -= amount_of_pixels;
                Current_location.y += amount_of_pixels;
                Current_location.y += amount_of_pixels;
                break;
        }
    }
    if(vector.first == -1 || vector.second == -1){
        switch (m) {
            case 1:
                Current_location.x += amount_of_pixels;
                Current_location.y -= amount_of_pixels;
                break;
            case 2:
                Current_location.y -= amount_of_pixels;
                break;
            case 3:
                Current_location.x -= amount_of_pixels;
                Current_location.y -= amount_of_pixels;
                break;
            case 4:
                Current_location.x -= amount_of_pixels;
                Current_location.y -= amount_of_pixels;
                Current_location.y -= amount_of_pixels;
                break;
            case 5:
                Current_location.y -= amount_of_pixels;
                Current_location.y -= amount_of_pixels;
                break;
            case 6:
                Current_location.x += amount_of_pixels;
                Current_location.y -= amount_of_pixels;
                Current_location.y -= amount_of_pixels;
                break;
        }
    }
    if (!this->check_boards()){
        return false;
    }
    return true;

}

bool Rover::check_boards() {

    if (vector.first != 0){
        if ( Current_location.x - width / 2 < 0 ){
            return false;
        }
        if (Current_location.x + width / 2  > road.Get_resolution()  ){
            return false;
        }
        if (Current_location.y + length/2 > road.Get_resolution()  )  {
            return false;
        }
        if (Current_location.y - length/2 < 0 ){
            return false;
        }
    }
    if (vector.second != 0){
        if ( GetCurrentLocation().x - width / 2 < 0 ){
            return false;
        }
        if (GetCurrentLocation().x + width / 2 > road.Get_resolution()   ){
            return false;
        }
        if (GetCurrentLocation().y + length/2 > road.Get_resolution()  ){
            return false;
        }
        if (GetCurrentLocation().y - length/2 < 0 ){
            return false;
        }
    }
    return true;
}

bool Rover::check_slope() {
    Point p1;
    Point p2;
    Point p3;
    p1.x = this->GetCurrentLocation().x * road.Get_pixel_size();
    p1.y = this->GetCurrentLocation().y * road.Get_pixel_size();
    p2.x = (this->GetCurrentLocation().x+ width) * road.Get_pixel_size();
    p2.y = this->GetCurrentLocation().y* road.Get_pixel_size();
    p3.x = this->GetCurrentLocation().x* road.Get_pixel_size();
    p3.y = (this->GetCurrentLocation().y + width)* road.Get_pixel_size();
    if (!road.array.empty()) {
        double v1, v2, v3;
        v1 = road.terra.Get_Current_Point_Height(p1.x, p1.y, road.array);
        v2 = road.terra.Get_Current_Point_Height(p2.x, p2.y, road.array);
        v3 = road.terra.Get_Current_Point_Height(p3.x, p3.y, road.array);
        double angle1, angle2;
        angle1 = (v2 - v1) / (width * road.Get_pixel_size()) ;
        angle2 = (v3 - v1) / (width * road.Get_pixel_size());
        if (abs(angle1) > x_angle || abs(angle2) > y_angle) {
//            cout << " i'm crashed in : "<<angle1 << " " << angle2 << "\n";
//            cout << Current_location.x << " " << Current_location.y << "\n";
            return false;
        } else {
            Current_angles.x = angle1;
            Current_angles.y = angle2;
            return true;
        }
    }
    else{
        return true;
    }
}

