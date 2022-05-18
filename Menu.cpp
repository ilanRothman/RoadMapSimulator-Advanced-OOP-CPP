#include "Menu.h"
#define TEST

//constructor.
Menu::Menu(int argc, char **argv): files(argc,argv), bus(), rail(), sprinter(),
tram(), generalMap(), commands(),stationTimes() {
    config();
    mapInit();
}

//separating the menu option and the command.
void getCommand(string& command, string& option)
{
    option = command.substr(0,command.find(' '));
    command = command.substr(command.find(' ') + 1,command.length());
}

//main menu of program.
void Menu::startMenu() {
    string command,option,source,target,duration;
    bool onGoing = true;
    while(onGoing)
    {
        cout << "\nPlease choose an option\n";
        cout << "Menu:\n";
        cout << "load - Load an edge\n"; // adds edge - 1 -
        cout << "outbound -  Print available targets from source\n"; // bfs from source to targets - 2 -
        cout << "inbound -  Print available sources from target\n"; // other way around bfs - 3 -
        cout << "uniExpress - Shortest time between target and source\n"; // dijaskra from target to source for each V - 4 -
        cout << "multiExpress - shortest time between target and source using ALL transport\n"; // dijaskra on 5th map - 5 -
#ifdef TEST
        cout << "TEST\n"; - 7;

#endif
        cout << "EXIT - Exits the program\n\n"; // - 6 -


        getline(cin,command);
        getCommand(command, option);

        switch (commands.at(option)) {
            case 1:
                files.LoadFile(command, source, target, duration);
                addEdge(command,source,target,duration);
                cout << "\nupdate was successful." << endl;
                break;
            case 2:
                outBound(command);
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                print();
                break;
            case 7:
                onGoing = false;
                break;
#ifdef TEST
            case 8:
                for(auto i: files.loadAll())
                {
                  duration.clear();
                  files.LoadFile(i,source,target,duration);
                  if(duration.empty())
                    continue;
                  addEdge(i,source,target,duration);
                }
                break;
#endif
            default:
              cout << "unknown command";
              break;
        }
    }

}

void Menu::print() const
{
  cout << "Bus:" << endl;
  bus.printMap();
  cout<< "\n\nSprinter: " <<endl;
  sprinter.printMap();
  cout<< "\n\nTram: " << endl;
  tram.printMap();
  cout<< "\n\nRail: " << endl;
  rail.printMap();
  cout<<"\n\nGeneralMap: " <<endl;
  generalMap.printMap();
}

//setting default values according to config file.
void Menu::config() {
    int duration;
    string line, object, cPath;
    cPath = this->files.getConfig();
    if(!cPath.empty()){
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

//menu keys for the menu switch case and junction transit times.
void Menu::mapInit() {

  commands.insert({"load",1});
  commands.insert({"outbound",2});
  commands.insert({"inbound",3});
  commands.insert({"uniExpress",4});
  commands.insert({"multiExpress",5});
  commands.insert({"print",6});
  commands.insert({"Exit",7});
  commands.insert({"TEST",8});

  stationTimes.insert({"IC",15});
  stationTimes.insert({"CS",10});
  stationTimes.insert({"ST",5});
}

//adding an edge to the vehicle map and the general map.
void Menu::addEdge(string& option, string& source, string& target , string& duration) {
    auto src = createJunc(source);
    auto trg = createJunc(target);
    int dur = stoi(duration);

    switch (option[0])
    {
        case 'b':
        {
            bus.addEdge(src,trg,dur);
            break;
        }
        case 's':
        {
            sprinter.addEdge(src,trg,dur);
            break;
        }
        case 't':
        {
            tram.addEdge(src,trg,dur);
            break;
        }
        case 'r':
        {
            rail.addEdge(src,trg,dur);
            break;
        }
    }
    generalMap.addEdge(src,trg, dur);
}

//checking what type of junction and creating it accordingly.
shared_ptr<Junction> Menu::createJunc(string &name) {
    if(name.rfind("IC",0) == 0)
        return make_shared<Junction>(name,stationTimes.at("IC"));
    if(name.rfind("CS",0) == 0)
        return make_shared<Junction>(name,stationTimes.at("CS"));
    return make_shared<Junction>(name,stationTimes.at("ST"));
}

void Menu::outBound(const string &source) const {
  cout<< "bus: ";
  bus.BFS(source);
  cout << "rail: ";
  rail.BFS(source);
  cout << "tram: ";
  tram.BFS(source);
  cout << "sprinter: ";
  sprinter.BFS(source);
}
void Menu::inBound(const string &source) const {

}



