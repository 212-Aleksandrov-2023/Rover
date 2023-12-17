#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <cmath>


#include "Hill.h"
#include "Surface.h"
#include "Log.h"
#include "Stone.h"
#include "Pixel.h"
#include "Rover.h"
#include "Control.h"
#include "Boundary.h"
using namespace std;


int main() {
    ifstream in(("command.txt"));
    ifstream config("config.txt");
    ifstream commands;
    if (!in.is_open()) {
        cout << "Can't open the command file" << endl;
        return 1;
    }
    string line;
    std::map<string, string> myDict;

    while (getline(config, line)) {
        size_t separatorPos = line.find(" - ");
        if (separatorPos != string::npos) {
            std::string key = line.substr(0, separatorPos);
            std::string value = line.substr(separatorPos + 3);

            myDict[key] = value;

        }
        else{
            cout << "False input in config file" << endl;
            return 1;
        }
    }
    string log_c;
    string log_b;
    for (const auto& entry  : myDict){
        if (entry.first == "boundary_file"){
            log_b = entry.second;
        }
        else if(entry.first == "control_file"){
            log_c = entry.second;
        }
        else if(entry.first == "commands_file"){
            commands.open(entry.second);
            if (!commands.is_open()){
                cout << "Can't open the commands file" << endl;
                return 1;
            }
        }
//        else{
//
//            cout<< "False input in command file"<< endl;
//            return 1;
//        }
    }
    std::map<string, string> Commands_List;

    while(getline(commands , line )){
        size_t separatorPos = line.find(" : ");
        if (separatorPos != string::npos) {
            std::string key = line.substr(0, separatorPos);
            std::string value = line.substr(separatorPos + 3);

            Commands_List[key] = value;

        }
        else{
            cout << "False input in command list file" << endl;
            return 1;
        }
    }
    commands.close();
    config.close();
    Control Control1 = Control(log_c);
    Boundary Boundary1 = Boundary(log_b,Commands_List, Control1 );
    Boundary1.read_command(in);
}
