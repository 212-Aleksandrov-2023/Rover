//
// Created by akiri on 14.10.2023.
//





#ifndef TESTPLACE_CONTROL_H
#define TESTPLACE_CONTROL_H

#endif //TESTPLACE_CONTROL_H


#define elipsis "----------------------------------------"
class Control{
private:
    string file_name;
    Surface S;

public:

    Control() = default;
    Control(string & file){file_name = file;}
    int get_command(string & command, ofstream & out1, vector<Hill> & arr, Pixel & P);
    string GetFilename(){return file_name;}



};

void Generator(ofstream &out, double h,double s, double l , int n){
    out << h << "\n";
    out << s << "\n";
    out << l << "\n";
    for ( int i = 0 ; i < h ; i++){
        int k = rand();
        int k1 = rand();
        out << rand() %n << " " << rand() %n << " " << abs(sin(rand()%180)) +0.5<< " "<< abs(sin(rand()%180))+0.5 << " " << rand() %n* pow(-1,k)<< "\n";
    }
    for ( int i = 0 ; i < s ; i++){
        int k = rand();
        out << rand() %n << " " << rand() %n << " " << pow(sin(rand()%180)*0.5, 2)<< "\n";
    }
    for ( int i = 0 ; i < l ; i++){
        int k = rand() %n;
        int k1 = rand() %n;
        int angle = rand() % 180;
        int k2 = rand() % 5 + 1;
        out << k << " " << k1 << " " << k + 1.5* cos(angle) << " " << k1 + 1.5 *sin(angle) << " " << 1.0/k2 << "\n";
    }

}

vector<Hill> Generate_Field(double n1 , double m1_v , double m2_k , double m3_b , Surface & Poverhnost){
    string line;
    double x,y,a,b,h;
    string s;

    ofstream out1;
    out1.open("input.txt");
    ofstream  out;
    out.open("output.txt");
    ofstream out2;
    out2.open("output2.txt");
    Generator(out1, m1_v , m2_k ,m3_b , n1);
    out1.close();

    ifstream in ;
    in.open("input.txt");
    Poverhnost = Surface(n1,n1,n1);
    int  m , v , n;
    in >> n;
    in >> m;
    in >> v;
    cout << n << endl;
    vector<Hill> arr(n+1);
    vector<Stone> arr2(m);
    vector<Log> arr3(v);
    arr[n] = Hill(0,0,1,1,0);
//    vector<Point> arr1(n);
    for ( size_t i = 0 ; i < n; i++) {
        in >> x >> y >> a >> b >> h;

        Hill Hill1 = Hill(x, y, a, b, h);
        arr[i] = Hill1;
//        arr1[i].x = Hill1.GetLenght();
//        arr1[i].y = Hill1.GetWidth();
    }
    for ( size_t i = 0 ; i < m; i++){
        in >> x >> y >> a;

        Stone stone1 = Stone(x,y,a);
        arr2[i] = stone1;
    }
    for ( size_t i = 0 ; i < v; i++) {
        in >> x >> y >> a >> b >> h;
        Log log1 = Log(x,y,a,b,h);
        arr3[i] = log1;
    }

    //Печать в файл
    for (size_t i =0 ; i < m; i++){
        arr2[i].plot_stone(arr,out2);
    }
    for (size_t i =0 ; i < v; i++){
        arr3[i].plot_log(arr,out2);
    }
    Poverhnost.Fill_surface(arr,out);
    in.close();
    out.close();
    out2.close();
    return arr;
}

int Control::get_command(std::string & command, ofstream & out1, vector<Hill> & arr , Pixel & P) {



    size_t pos = command.find(" : ");
    std::string function  = command.substr(0, pos);
    std::string arguments = command.substr(pos + 3);
    std::stringstream ss(arguments);

    out1 << elipsis <<"\n";
    cout << function << "\n";
    out1 << "command accepted:" << " " << command << "\n";
    if (function == "GaussColon"){
        double x, y;
        Hill Hill1 = Hill(1, 1, 0.5, 2, 3);
        ss >> x;
        ss >> y;
        double result  = Hill1.GaussColon(x, y);
        out1 << "command completed: " << command << "\n";
        return 1;
    }
    else if(function == "Generate_Field"){
        double x ,y ,z ,n;
        ifstream in("config.txt");
        ss>>n;
        ss>>x;
        ss>>y;
        ss>>z;
        if ( n < 0 || x < 0 || y < 0 || z < 0 ){
            return 0;
        }
//        Pixel T = Pixel();
        string s1;
        while(std::getline(in, s1)){
            size_t l = s1.find(" - ");
            if( s1.substr(0 , l) == "resolution_value"){
                s1 = s1.substr(l+3);
                break;
            }
        }

        int resol;
        std::stringstream res(s1);
        res >> resol;
        arr = Generate_Field(n,x,y,z, S);
        cout << S.GetLenght() << "\n";
        out1 << "command completed: " << command << "\n";
        P = Pixel(resol , S , arr);
//        cout << resol << "\n";
        in.close();
        return 1;
    }
    else if( function == "Plot_log"){
        double m , x ,y ,z ,n;
        ofstream out("output2.txt",ios::app);
        ss>>n;
        ss>>x;
        ss>>y;
        ss>>z;
        ss>>m;
        try{
            Log l = Log(n , x , y ,z ,m);
            l.plot_log(arr , out);}
        catch (LogEx & ex){
            out1 << "command not executed: " << command << " - wrong arguments" <<"\n";
            return 3;

        }
        if(arr.empty()){
            out1 << "command not executed: " << command << " - surface didn't generated " <<"\n";
            return 2;
        }

        out1 << "command completed: " << command << "\n";
        out.close();
        return 1;
    }
    else if( function == "Plot_stone"){
        double x ,y ,n;
        ofstream out("output2.txt",ios::app);
        ss>>n;
        ss>>x;
        ss>>y;
        if(arr.empty()){
            out1 << "command not executed: " << command << " - surface didn't generated " <<"\n";
            return 2;
        }
        try {Stone l = Stone(n, x, y);
            l.plot_stone(arr , out);
        }
        catch ( StoneEx & ex){
            out1 << "command not executed: " << command << " - wrong arguments" <<"\n";
            return 3;
        }

        out1 << "command completed: " << command << "\n";
        out.close();
        return 1;
    }
    else if(function == "MakeRover"){
        Point A, B;
        double m , x ,y ,z ,n;
        ifstream in("config.txt");
        ofstream out5("road.txt");
        ss>>n;
        ss>>x;
        ss>>y;
        ss>>z;
        ss>>m;

        if(arr.empty()){
            out1 << "command not executed: " << command << " - surface didn't generated " <<"\n";
            return 2;
        }
        Rover R = Rover(n,x,y,z,m,P);
        string s1;
        string s2;
        string s3;
        int k = 0;
        while(std::getline(in, s1)){
            size_t l = s1.find(" - ");
            if( s1.substr(0 , l) == "starting_point"){
                s3 = s1.substr(l+3);
                k+=1;
            }
            if(s1.substr(0 , l) == "ending_point"){
                s2 = s1.substr(l+3);
                k+=1;
                break;
            }
        }
        if (k == 2) {
            std::stringstream ss1(s3);

            ss1 >> n;
            ss1 >> m;
            A.x = n;
            A.y = m;
            std::stringstream ss2(s2);
            ss2 >> n;
            ss2 >> m;
            B.x = n;
            B.y = m;}

        else{
            out1 << "command not executed: " << command  << " there is no starting or ending point"<<"\n";
            return 4;
        }
        in.close();
        Processor Proc = Processor(A , B , R);
        bool result;
        result = Proc.start_ride(out5);
        if (result){
            out1 << "Rover have reached destination" << "\n";

        }
        else{
            out1 << "Rover can't reach destination" << "\n";
        }

        out1 << "command completed: " << command << "\n";
        return 1;
    }
    else{
        return 0;
    }
}
