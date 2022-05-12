//
// Created by iroth on 5/11/2022.
//

#include <fstream>
#include <sstream>
#include "Menu.h"

Menu::Menu(int argc, char **argv):files(argc,argv), bus(), rail(),
sprinter(), tram(), generalMap(),commands() {
  mapInit();
}
void getCommand(string& command, string& option, string& source, string& target)
{
  option = command.substr(0,command.find('\t'));
  command = command.substr(command.find('\t') + 1,command.length());

  source = command.substr(0,command.find('\t'));
  command = command.substr(command.find('\t') + 1,command.length());

  target = command.substr(0,command.length());
} // splits the given string into option, source, target

void Menu::startMenu() {
    string command,option,source,target,duration;

    while(true)
    {
        cout << "Please choose an option\n";
        cout << "Menu\n";
        cout << "load - Load an edge\n"; // adds edge - 1 -
        cout << "outbound -  Print available targets from source\n"; // bfs from source to targets - 2 -
        cout << "inbound -  Print available sources from target\n"; // other way around bfs - 3 -
        cout << "uniExpress - Shortest time between target and source\n"; // dijaskra from target to source for each V - 4 -
        cout << "multiExpress - shortest time between target and source using ALL transport\n"; // dijaskra on 5th map - 5 -
        cout << "EXIT - Exits the program\n"; // - 6 -


        cin >> command;
        getCommand(command, option, source, target);


        switch (commands.at(option)) {
          case 1:
            files.LoadFile(option,source,target,duration);
          default:


      }
    }
}

void Menu::config() {
    int time;
    string line, object, cPath;
    cPath = this->files.getConfig();
    if(cPath != ""){
        ifstream cFig(cPath);
        while(getline(cFig,line)){
            istringstream ss(line);
            ss >> object >> time;
            if(object == "bus" ) {
                bus.setStopTime(time);
                break;
            }

            if(object == "rail") {
                rail.setStopTime(time);
                break;
            }
            if(object == "sprinter") {
                sprinter.setStopTime(time);
                break;
            }
            if(object == "tram") {
                tram.setStopTime(time);
                break;
            }
            if(object == "intercity") {
                interCity.setTransTime(time);
                break;
            }

            if(object == "central") {
                central.setTransTime(time);
                break;
            }

            if(object == "stad"){
                stad.setTransTime(time);
                break;
            }

        }

    }

}
void Menu::mapInit() {
  commands.insert({"load",1});
  commands.insert({"outbound",2});
  commands.insert({"inbound",3});
  commands.insert({"uniExpress",4});
  commands.insert({"multiExpress",5});
  commands.insert({"print",6});
  commands.insert({"Exit",7});
}

