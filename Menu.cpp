#include "Menu.h"
//#define TEST

//constructor.
Menu::Menu(int argc, char **argv): files(argc,argv), bus(), rail(), sprinter(),
tram(), generalMap(), commands(),stationTimes() {
    stopTimes = {{'b',1},{'r',5},{'s',3},{'t',2}};
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
    while(onGoing) {
        cout << "\nPlease choose an option\n";
        cout << "Menu:\n";
        cout << "load - Load an edge\n";
        cout << "outbound -  Print available targets from source\n";
        cout << "inbound -  Print available sources from target\n";
        cout << "uniExpress - Shortest time between target and source\n";
        cout << "multiExpress - shortest time between target and source using ALL transport\n";
        cout << "print - for printing all the graphs. \n";
        cout << "EXIT - Exits the program\n";

#ifdef TEST
        cout << "TEST\n"; - 7;

#endif
        getline(cin,command); // getting the command from the user.
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
                inBound(command);
                break;
            case 4:
                uniExpress(command);
                break;
            case 5:
                multiExpress(command);
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

void Menu::print() const {
    cout << "Bus:" << endl;
    bus.printMap();
    cout << "\n\nSprinter: " << endl;
    sprinter.printMap();
    cout << "\n\nTram: " << endl;
    tram.printMap();
    cout << "\n\nRail: " << endl;
    rail.printMap();
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

            if(object == "bus" ) {
              bus.setStopTime(duration);
              stopTimes.at('b') = duration;
            }

            if(object == "rail") {
              rail.setStopTime(duration);
              stopTimes.at('r') = duration;
            }

            if(object == "sprinter"  ) {
              sprinter.setStopTime(duration);
              stopTimes.at('s') = duration;
            }

            if(object == "tram") {
              tram.setStopTime(duration);
              stopTimes.at('t') = duration;
            }

            if(object == "intercity")
                stationTimes.find("IC")->second = duration;

            if(object == "central")
                stationTimes.find("CS")->second = duration;

            if(object == "stad")
                stationTimes.find("ST")->second = duration;

        }

    }

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
            generalMap.addEdge(src,trg,dur,'b',stopTimes);
            break;
        }
        case 's':
        {
            sprinter.addEdge(src,trg,dur);
            generalMap.addEdge(src,trg,dur,'s',stopTimes);
            break;
        }
        case 't':
        {
            tram.addEdge(src,trg,dur);
            generalMap.addEdge(src,trg,dur,'t',stopTimes);
            break;
        }
        case 'r':
        {
            rail.addEdge(src,trg,dur);
            generalMap.addEdge(src,trg,dur,'r' ,stopTimes);
            break;
        }
    }
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
    bus.BFS(source,bus.getGraph());
    cout << "rail: ";
    rail.BFS(source, rail.getGraph());
    cout << "tram: ";
    tram.BFS(source,tram.getGraph());
    cout << "sprinter: ";
    sprinter.BFS(source,sprinter.getGraph());
}
void Menu::inBound(const string &source){
    cout<< "bus: ";
    bus.updateTurnedGraph();
    bus.BFS(source,bus.getTurnedGraph());
    cout << "rail: ";
    rail.updateTurnedGraph();
    rail.BFS(source,rail.getTurnedGraph());
    cout << "tram: ";
    tram.updateTurnedGraph();
    tram.BFS(source,tram.getTurnedGraph());
    cout << "sprinter: ";
    sprinter.updateTurnedGraph();
    sprinter.BFS(source,sprinter.getTurnedGraph());
}

void Menu::uniExpress(const string &command) {
    string source,target;


    stringstream ss(command);
    ss >> source >> target;

    if(ss.rdbuf()->in_avail() || ss.fail()){
      throw runtime_error("wrong amount of arguments.\n");
    }

    cout<< "bus: ";
    bus.dijkstra(source,target);
    cout << "rail: ";
    rail.dijkstra(source, target);
    cout << "tram: ";
    tram.dijkstra(source, target);
    cout << "sprinter: ";
    sprinter.dijkstra(source, target);
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

    stopTimes.insert({'b',1});
    stopTimes.insert({'t',2});
    stopTimes.insert({'r',5});
    stopTimes.insert({'s',3});
}

void Menu::multiExpress(string command) {
    string source,target;
    stringstream ss(command);
    ss >> source >> target;
    if(ss.rdbuf()->in_avail() || ss.fail()){
        throw runtime_error("wrong amount of arguments.\n");
    }
    generalMap.dijkstra(source,target , stopTimes);

}


