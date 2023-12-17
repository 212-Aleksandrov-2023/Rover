//
// Created by akiri on 14.10.2023.
//

#ifndef TESTPLACE_BOUNDARY_H
#define TESTPLACE_BOUNDARY_H

#endif //TESTPLACE_BOUNDARY_H

#define elipsis "----------------------------------------"


int countletters(string & s);

int countnumbers(string  s);




class Boundary{
private:
    string file_name;
    map<string, string> commands_file;
    Control C;
public:
    Boundary() = default;
    Boundary(string & out  ,map<string, string> & commads , Control & L);


    void read_command(ifstream & in);
    bool checker(string &line);

};




void Boundary::read_command(ifstream & in){
    string line;
    bool flag;
    vector<Hill> arr;
    Pixel P;
    ofstream out(this->file_name);
    ofstream out1(C.GetFilename());
    if(!out1.is_open()){
        cout << "exeption2" << endl;
    }
    if(!out.is_open()){
        cout << "exeption1" << endl;
    }

    while(getline(in, line)){
        flag = this->checker(line);
        if(flag){
//            cout << line << "\n";
            out << elipsis <<"\n";
            out << "command accepted:" << " " << line << "\n";
            int p = C.get_command(line, out1, arr, P);
            if(p == 1 ){
                out << "command completed:" << " " << line << "\n";
            }
            else if(p == 2 ){
                out << "command not executed: " << line << "- surface didn't generated " << "\n";
            }
            else if (p == 3){
                out << "command not executed: " << line << " - wrong arguments" <<"\n";
            }
            else if( p == 4){
                out << "command not executed: " << line  << " there is no starting or ending point"<<"\n";
            }


        }
        else{
            out << elipsis <<"\n";
            out << "no coincidences, wrong command or arguments : "<< line <<"\n";
        }
    }
}

bool Boundary::checker(std::string &line) {
    size_t sepPos = line.find(" : ");
    if (sepPos != string::npos) {
        map<string, string> d = this->commands_file;
        if(countletters(d[line.substr(0,sepPos)]) == countnumbers(line.substr(sepPos+3)))
        {
            return true;
        }
        else{
            return false;
        }

    }
    return false;
}

Boundary::Boundary(std::string & out, map<std::string, std::string>  & commands, Control & L) {
    file_name = out;
    commands_file = commands;
    C = L;
}

int countletters(string & s){
    int k = 0;
    for ( char c : s){
        if(isalpha(c)){
            k+=1;
        }
    }
    return k;
}

int countnumbers(string s){

    int k = 0;
    double a;
    std::stringstream ss(s);
    while(ss >> a){
        k+=1;
    }
    return k;
}