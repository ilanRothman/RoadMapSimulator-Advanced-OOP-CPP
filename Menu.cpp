//
// Created by iroth on 5/11/2022.
//

#include <fstream>
#include <sstream>
#include "Menu.h"

Menu::Menu(int argc, char **argv): files(argc,argv), bus(), rail(), sprinter(),
tram(), generalMap(), commands(),stationTimes() {
    config();
    mapInit();
}

void getCommand(string& command, string& option)
{
    option = command.substr(0,command.find(' '));
    command = command.substr(command.find(' ') + 1,command.length());
}

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
                files.LoadFile(command, source, target, duration);
                addEdge(command,source,target,duration);
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            default:
                onGoing = false;
                break;
        }
    }

}

void Menu::config() {
    int duration;
    string line, object, cPath;
    cPath = this->files.getConfig();
    if(cPath != ""){
        ifstream cFig(cPath);
        while(getline(cFig,line)){
            istringstream ss(line);
            ss >> object >> duration;

            if(object == "bus" )
                bus.setStopTime(duration);

            if(object == "rail")
                rail.setStopTime(duration);

            if(object == "sprinter")
                sprinter.setStopTime(duration);

            if(object == "tram")
                tram.setStopTime(duration);

            if(object == "intercity")
                stationTimes.find("IC")->second = duration;

            if(object == "central")
                stationTimes.find("CS")->second = duration;

            if(object == "stad")
                stationTimes.find("ST")->second = duration;

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

void Menu::addEdge(string& option, string& source, string& target , string& duration) {
    auto src = createJunc(source);
    auto trg = createJunc(target);


    switch (option[0])
    {
        case 'b':
        {
            bus.addEdge(src,trg,duration);
            break;
        }
        case 's':
        {
            sprinter.addEdge();
            break;
        }
        case 't':
        {
            tram.addEdge();
            break;
        }
        case 'r':
        {
            rail.addEdge();
            break;
        }
    }
}

shared_ptr<Junction> Menu::createJunc(string &name) {
    if(name.rfind("IC",0) == 0)
        return make_shared<Junction>(name,stationTimes.at("IC"));
    if(name.rfind("CS",0) == 0)
        return make_shared<Junction>(name,stationTimes.at("CS"));
    return make_shared<Junction>(name,stationTimes.at("ST"));
}



