#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <queue>
#include <limits>
#include <unordered_map>
#include <set>
#include <filesystem>
#include <algorithm>

using namespace std;
namespace fs = std::filesystem;

extern string map_rpt_filename;
extern string route_rpt_filename;
extern string IdealRoute;
extern string VehicleType;
extern string input;
extern string Display_Map;

//for best route
double bestShieldEnergy = numeric_limits<double>::max();
vector<pair<int, int>> bestRoute;
pair<int, int> bestStart, bestEnd;
ostringstream bestFormula;
string bestShieldBreakdownStr;
int bestPreferredCount = 0;
int bestGridCount = 0;
unordered_map<char, int> bestPreferredCountMap;

unordered_map<char, int> costGeneric;
set<char> preferredTerrains;

//new
class Vehicle {
public:
    virtual string getName() const = 0;
    virtual set<char> getPreferredTerrains() const = 0;
    virtual double computeDiscount(char terrain, int cost) const = 0;
    virtual ~Vehicle() {}
};

class Highlander : public Vehicle {
public:
    string getName() const override { return "Highlander"; }
    set<char> getPreferredTerrains() const override { return {'h', 'M'}; }
    double computeDiscount(char t, int cost) const override {
        return (t == 'h' || t == 'M') ? 0.5 * cost : 0.0;
    }
};

class Dragonfly : public Vehicle {
public:
    string getName() const override { return "Dragonfly"; }
    set<char> getPreferredTerrains() const override { return {'w', '~'}; }
    double computeDiscount(char t, int cost) const override {
        return (t == 'w' || t == '~') ? 0.5 * cost : 0.0;
    }
};

class ShieldHero : public Vehicle {
public:
    string getName() const override { return "ShieldHero"; }
    set<char> getPreferredTerrains() const override { return {'X'}; }
    double computeDiscount(char t, int cost) const override {
        return (t == 'X') ? 0.5 * cost : 0.0;
    }
};


bool isPreferred(char t) {
    return preferredTerrains.count(t);
}

vector<pair<int,int>> findShortestPathWithWT(const vector<vector<char>>& map, pair<int,int> start, pair<int,int> end);
vector<pair<int,int>> findLeastEnergyPath(const vector<vector<char>>& map, pair<int,int> start, pair<int,int> end);

string toLower(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

void resetBestRouteStats() {
    bestShieldEnergy = numeric_limits<double>::max();
    bestRoute.clear();
    bestStart = {0, 0};
    bestEnd = {0, 0};
    bestFormula.str("");
    bestFormula.clear();
    bestShieldBreakdownStr.clear();
    bestPreferredCount = 0;
    bestGridCount = 0;
    bestPreferredCountMap.clear();
}

void SimulationRun() 
{
    char start_time[50];
    char stop_time[50];
    struct tm * datetime;
    time_t start;
    time_t end;
    
    resetBestRouteStats();

    ofstream null_stream("/dev/null");
    streambuf* original_buf = std::cout.rdbuf();

    cout << "\t[Start Simulation]\n\n";
    cout << "\tINPUT map details filename  = "<< map_rpt_filename << "\n";
    cout << "\tOUTPUT route report         = " <<route_rpt_filename<< "\n";
    cout << "\tIdeal Route Criteria        = "<< IdealRoute <<"\n";
    cout << "\tVehicle Type                = " <<VehicleType<< "\n\n";

    if  (!fs::exists(map_rpt_filename)) {
        cout << "\tScenario file name ("<< map_rpt_filename << ") not found. \n\n"; 
        return;
    }

    ofstream outfile(route_rpt_filename);
    if  (fs::exists(route_rpt_filename) && !outfile.is_open()) {
        cout << "\tUnable to create"<< route_rpt_filename << "\n\n";
        return;
    }

    do {
        cout << "\tWhen simulation ends, do you wish to display map report on ubuntu terminal? (Y/N) : ";
        getline(cin,Display_Map);
        Display_Map[0] = toupper(Display_Map[0]);
    } while(Display_Map != "Y"&&Display_Map != "N");   
    cout <<"\n";

    do {
        cout << "\tBEGIN NOW? (Y): ";
        getline(cin,input);
        input[0] = toupper(input[0]);
    } while(input != "Y");
    
    cout <<"\n";

    time(&start);
    datetime = localtime(&start);
    strftime(start_time, 50, "%d/%m/%y, %H:%M:%S", datetime);
    cout << "\tRoute Simulation STARTED!\tStart datetime stamp = " << start_time << "\n\n";
    cout << "\t\tSIMULATION IN PROGRESS..PLEASE DO NOT END PROGRAM !\n\n";

    outfile << "INPUT map details filename  = "<< map_rpt_filename << "\n";
    outfile << "OUTPUT route report         = " <<route_rpt_filename<< "\n";
    outfile << "Ideal Route Criteria        = "<< IdealRoute <<"\n";
    outfile << "Vehicle Type                = " <<VehicleType<< "\n\n";
    outfile << "Start datetime stamp    = " << start_time << "\n";

    /*preferredTerrains.clear();
    string type = toLower(VehicleType);
    if (type == "highlander") {
        preferredTerrains.insert('h');
        preferredTerrains.insert('M');
    } else if (type == "dragonfly") {
        preferredTerrains.insert('w');
        preferredTerrains.insert('~');
    } else if (type == "shieldhero") {
        preferredTerrains.insert('X');
    }*/
    //Hierarchy start
    Vehicle* vehicle = nullptr;
	string type = toLower(VehicleType);
	if (type == "highlander") 
	{
    	vehicle = new Highlander();
	} 
	else if (type == "dragonfly") 
	{
    	vehicle = new Dragonfly();
	} 
	else if (type == "shieldhero")
	{
    	vehicle = new ShieldHero();
	} 
	else 
	{
    	cerr << "Unknown vehicle type: " << VehicleType << "\n";
    	return;
	}
	preferredTerrains = vehicle->getPreferredTerrains();
	//Herachy end


    ifstream file(map_rpt_filename);
    if (!file.is_open()) {
        cerr << "Failed to open " << map_rpt_filename << "\n";
        return;
    }

    string line;
    for (int i = 0; i < 10; i++) {
        if (!getline(file, line)) {
            cerr << "Not enough header lines.\n";
            return;
        }
    }

    vector<vector<char>> fullMap;
    while (true) {
        streampos curPos = file.tellg();
        if (!getline(file, line)) break;
        if (line.find("Terrain") != string::npos) {
            file.seekg(curPos);
            break;
        }

        size_t first = line.find_first_not_of(' ');
        if (first != string::npos && isdigit(line[first])) {
            size_t space = line.find(' ', first);
            string rowData = line.substr(space + 1);

            vector<char> rowVec;
            for (size_t i = 1; i < rowData.size(); i += 3) {
                rowVec.push_back(rowData[i]);
            }
            fullMap.push_back(rowVec);
        }
    }

    int rows = fullMap.size();
    int cols = fullMap[0].size();

    getline(file, line);
    getline(file, line);

    costGeneric.clear();
    while (getline(file, line)) {
        if (line.empty()) break;

        if (line.size() >= 3 && line[0] == '\'' && line[2] == '\'') {
            char symbol = line[1];
            int movt = 0, shld = 0;
            string energyPart = line.substr(4);
            istringstream iss(energyPart);
            if (iss >> movt >> shld) {
                costGeneric[symbol] = movt;
            }
        }
    }
    file.close();

    time(&end);
    datetime = localtime(&end);
    strftime(stop_time, 50, "%d/%m/%y, %H:%M:%S", datetime);
    cout << "\tRoute Simulation ENDED!\tEnd datetime stamp = " << stop_time << "\n\n";
    int Mapping_Dur = difftime(end, start);
    cout << "\n\tTotal Simulation Duration: "<<Mapping_Dur/3600 <<"hr "<<(Mapping_Dur%3600)/60 <<"min " <<(Mapping_Dur%3600)%60 <<"sec \n\n";
    outfile << "End datetime stamp      = " << stop_time << "\n\n";
    outfile << "Total Mapping Duration: "<<Mapping_Dur/3600 <<"hr "<<(Mapping_Dur%3600)/60 <<"min " <<(Mapping_Dur%3600)%60 <<"sec \n\n";
    cout << "	Route report save to : "<< route_rpt_filename <<" \n\n";
    
    if (Display_Map == "N" )								// if display map is N, cout will be masked off and nothing will be printed.
	{
   	 	cout.rdbuf(null_stream.rdbuf());
	}
	else if (Display_Map == "Y")												//display map on ubuntu if user enter Y
	{
		cout << "	Displaying contents of "<< route_rpt_filename <<" on ubuntu terminal \n\n";
		cout <<"\n";
	}

    vector<pair<int, int>> starts, ends;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (fullMap[r][c] == 'S') starts.push_back({r, c});
            else if (fullMap[r][c] == 'E') ends.push_back({r, c});
        }
    }

    if (starts.empty() || ends.empty()) {
        cout << "No S or E found in the map.\n";
        return;
    }

    int pathId = 1;
    for (auto& s : starts) {
        for (auto& e : ends) {
            vector<pair<int, int>> path;

            if (IdealRoute == "shortest distance from Start to End locations") {
                path = findShortestPathWithWT(fullMap, s, e);
            } else if (IdealRoute == "minimized total energy expenditure") {
                path = findLeastEnergyPath(fullMap, s, e);
            } else {
                cout << "Skipping simulation — unknown IdealRoute: '" << IdealRoute << "'\n";
                return;
            }

            if (path.empty()) {
                cout << "Path " << pathId++ << " from [" << s.first << "," << s.second << "] to [" << e.first << "," << e.second << "]: No valid path found\n\n";
                continue;
            }

            int gridCount = 0, totalGeneric = 0, preferredCount = 0;
            double shieldDiscount = 0.0;
            ostringstream formula;
            bool firstTerm = true;
            unordered_map<char, int> preferredCountMap;

            vector<vector<string>> cleared(rows, vector<string>(cols, "   "));

            for (auto& p : path) {
                char original = fullMap[p.first][p.second];
                cleared[p.first][p.second] = (original == ' ')
    										? " _ "
    										: " " + string(1, original) + " ";

            }

            for (auto [r, c] : path) {
                char t = fullMap[r][c];
                int costVal = costGeneric.count(t) ? costGeneric[t] : 0;

                /*if (isPreferred(t)) {
                    shieldDiscount += 0.5 * costVal;
                    preferredCount++;
                    preferredCountMap[t]++;
                }*/
                //Hierarchy start
                double discount = vehicle->computeDiscount(t, costVal);
				if (discount > 0.0) 
				{
    				shieldDiscount += discount;
    				preferredCount++;
   					preferredCountMap[t]++;
				}
				//Hierarchy end


                if (t == 'S' || t == 'E') continue;

                gridCount++;
                if (!firstTerm) formula << " + ";
                formula << (t == ' ' ? "_" : string(1, t)) << "(" << costVal << ")";
                firstTerm = false;
                totalGeneric += costVal;
            }

            double shieldHero = totalGeneric - shieldDiscount;
            //to choose best route
        	ostringstream shieldBreakdown;
			string shieldBreakdownStr = shieldBreakdown.str();

			if (shieldHero < bestShieldEnergy) 
			{
    			bestShieldEnergy = shieldHero;
   				 bestRoute = path;
  				 bestStart = s;
  				 bestEnd = e;
  				 bestFormula.str("");
  				 bestFormula.clear();
  				 bestFormula << formula.str();
    			 bestShieldBreakdownStr = shieldBreakdownStr;
  				 bestPreferredCount = preferredCount;
    			 bestGridCount = gridCount;
    			bestPreferredCountMap = preferredCountMap;
    		}


            cout << "Route " << setw(2) << pathId << " from [" << s.first << "," << s.second << "] to [" << e.first << "," << e.second << "]: \n\n";
            cout << setfill(' ');
            cout << "Sequence : ";
            for (size_t i = 0; i < path.size(); ++i) {
                cout << "[" << path[i].first << ", " << path[i].second << "]";
                if (i != path.size() - 1) cout << ", ";
            }
            cout << "\n\n";
            cout << "Tot. No. of PREFERRED TERRAIN explored = " << preferredCount << "\n";
            cout << "Tot. No. of grid area travelled (excluding ‘S’ and ‘E’) = " << gridCount << "\n";
            cout << "Tot. Movt Energ Reqd (Generic Veh) = " << formula.str() << " = " << totalGeneric << "\n";

            bool first = true;
            for (auto& [symbol, count] : preferredCountMap) {
                if (!first) shieldBreakdown << " + ";
                shieldBreakdown << count << " * 0.5(" << costGeneric[symbol] << ")";
                first = false;
            }
            cout << fixed << setprecision(1);
            cout << "Tot. Movt Energ Reqd (" << VehicleType << ") = " << totalGeneric
                 << " - [ " << shieldBreakdown.str() << " ] = " << (shieldHero) << "\n\n";

            cout << " ";
            for (int c = 0; c < cols; c++) cout << setw(3) << c;
            cout << "\n";
            for (int r = 0; r < rows; r++) {
                cout << setw(2) << r;
                for (int c = 0; c < cols; c++) {
                    char ch = fullMap[r][c];
                    if (cleared[r][c] != "   ")
                        cout << cleared[r][c];
                    else if (ch == 'S' || ch == 'E' || ch == '#')
                        cout << " " << ch << " ";
                    else
                        cout << "   ";
                }
                cout << "\n";
            }

            outfile << "Route " << setw(2) << setfill('0') << pathId++ << " from [" << s.first << "," << s.second << "] to [" << e.first << "," << e.second << "]: \n\n";
            outfile << setfill(' ');
            outfile << "Sequence : ";
            for (size_t i = 0; i < path.size(); ++i) {
                outfile << "[" << path[i].first << ", " << path[i].second << "]";
                if (i != path.size() - 1) outfile << ", ";
            }
            outfile << "\n\n";
            outfile << "Tot. No. of PREFERRED TERRAIN explored = " << preferredCount << "\n";
            outfile << "Tot. No. of grid area travelled (excluding ‘S’ and ‘E’) = " << gridCount << "\n";
            outfile << "Tot. Movt Energ Reqd (Generic Veh) = " << formula.str() << " = " << totalGeneric << "\n";
            outfile << fixed << setprecision(1);
            outfile << "Tot. Movt Energ Reqd (" << VehicleType << ") = " << totalGeneric
                    << " - [ " << shieldBreakdown.str() << " ] = " << (shieldHero) << "\n\n";
            outfile << "  ";
            for (int c = 0; c < cols; c++) outfile << setw(3) << c;
            outfile << "\n";
            for (int r = 0; r < rows; r++) {
                outfile << setw(2) << r;
                for (int c = 0; c < cols; c++) {
                    char ch = fullMap[r][c];
                    if (cleared[r][c] != "   ")
                        outfile << cleared[r][c];
                    else if (ch == 'S' || ch == 'E' || ch == '#')
                        outfile << " " << ch << " ";
                    else
                        outfile << "   ";
                }
                outfile << "\n";
            }
            outfile << "\n";
            cout << "\n";
        }
        
    }
    //choosing best route
	ostringstream shieldOut;
	bool firstShield = true;
	for (auto& [symbol, count] : bestPreferredCountMap) 
	{
    	if (!firstShield) shieldOut << " + ";
    	shieldOut << count << " * 0.5(" << costGeneric[symbol] << ")";
    	firstShield = false;
	}
	bestShieldBreakdownStr = shieldOut.str();
	cout << "======================================================================================================================================================\n\n";
	int genericEnergy = 0;
	if (!bestRoute.empty()) 
	{
		cout << IdealRoute << " for vehicle type " << VehicleType <<"\n";
    	cout << "Best Route from [" << bestStart.first << "," << bestStart.second << "] to ["
         	 << bestEnd.first << "," << bestEnd.second << "]: \n\n";

    	cout << setfill(' ');
    	cout << "Sequence : ";
    	for (size_t i = 0; i < bestRoute.size(); ++i) 
    	{
        	cout << "[" << bestRoute[i].first << ", " << bestRoute[i].second << "]";
        	if (i != bestRoute.size() - 1) cout << ", ";
    	}
    	cout << "\n\n";

    	cout << "Tot. No. of PREFERRED TERRAIN explored = " << bestPreferredCount << "\n";
    	cout << "Tot. No. of grid area travelled (excluding ‘S’ and ‘E’) = " << bestGridCount << "\n";
    	cout << "Tot. Movt Energ Reqd (Generic Veh) = " << bestFormula.str();

    	//calculate energy
   		/*
    	for (size_t i = 1; i < bestRoute.size(); ++i) 
    	{
        	char t = fullMap[bestRoute[i].first][bestRoute[i].second];
        	if (t != 'S' && t != 'E') 
        	{
            	genericEnergy += costGeneric.count(t) ? costGeneric[t] : 0;
        	}
    	}*/
    	//Hierarchy start
    	double bestShieldDiscount = 0.0;
		for (size_t i = 1; i < bestRoute.size(); ++i) 
		{
    		char t = fullMap[bestRoute[i].first][bestRoute[i].second];
    		if (t != 'S' && t != 'E') 
    		{
        		int cost = costGeneric.count(t) ? costGeneric[t] : 0;
        		genericEnergy += cost;
        		bestShieldDiscount += vehicle->computeDiscount(t, cost);
    		}
		}
		//Hierarchy end


    	cout << " = " << genericEnergy << "\n";
    	cout << fixed << setprecision(1);

    	cout << "Tot. Movt Energ Reqd (" << VehicleType << ") = "
         	 << genericEnergy << " - [ " << bestShieldBreakdownStr << " ] = " << bestShieldEnergy << "\n\n";
	}
	// print out best route
	vector<vector<string>> cleared(rows, vector<string>(cols, "   "));

	for (auto& p : bestRoute) 
	{
    	char original = fullMap[p.first][p.second];
    	cleared[p.first][p.second] = (original == ' ')
    								? " _ "
    								: " " + string(1, original) + " ";
	}

	// print map
	cout << " ";
	for (int c = 0; c < cols; c++) cout << setw(3) << c;
	cout << "\n";
	for (int r = 0; r < rows; r++) 
	{
    	cout << setw(2) << r;
    	for (int c = 0; c < cols; c++) 
    	{
        	char ch = fullMap[r][c];
        	if (cleared[r][c] != "   ")
            	cout << cleared[r][c];
        	else if (ch == 'S' || ch == 'E' || ch == '#')
            	cout << " " << ch << " ";
        	else
            	cout << "   ";
    	}
   	 	cout << "\n";
	}
	cout << "\n";
	cout << "======================================================================================================================================================\n\n";
	//print to file
	outfile << "======================================================================================================================================================\n\n";
	outfile << IdealRoute << " for vehicle type " << VehicleType <<"\n";
	outfile << "Best Route from [" << bestStart.first << "," << bestStart.second << "] to ["
         	 << bestEnd.first << "," << bestEnd.second << "]: \n\n";

    outfile << setfill(' ');
    outfile << "Sequence : ";
    for (size_t i = 0; i < bestRoute.size(); ++i) 
    {
       	outfile << "[" << bestRoute[i].first << ", " << bestRoute[i].second << "]";
       	if (i != bestRoute.size() - 1) outfile << ", ";
    }
    outfile << "\n\n";
    outfile << "Tot. No. of PREFERRED TERRAIN explored = " << bestPreferredCount << "\n";
    outfile << "Tot. No. of grid area travelled (excluding ‘S’ and ‘E’) = " << bestGridCount << "\n";
    outfile << "Tot. Movt Energ Reqd (Generic Veh) = " << bestFormula.str();
    outfile << " = " << genericEnergy << "\n";
    outfile << fixed << setprecision(1);
    	
    outfile << "Tot. Movt Energ Reqd (" << VehicleType << ") = "
         	 << genericEnergy << " - [ " << bestShieldBreakdownStr << " ] = " << bestShieldEnergy << "\n\n";
    
    outfile << "\n";
    outfile << " ";
    outfile << " ";
	for (int c = 0; c < cols; c++) outfile << setw(3) << c;
	outfile << "\n";
	for (int r = 0; r < rows; r++) 
	{
    	outfile << setw(2) << r;
    	for (int c = 0; c < cols; c++) 
    	{
        	char ch = fullMap[r][c];
        	if (cleared[r][c] != "   ")
            	outfile << cleared[r][c];
        	else if (ch == 'S' || ch == 'E' || ch == '#')
            	outfile << " " << ch << " ";
        	else
            	outfile << "   ";
    	}
   	 	outfile << "\n";
	}
	outfile << "\n";
	outfile << "======================================================================================================================================================\n\n";
	outfile.close();
	cout.rdbuf(original_buf); 								//put cout to normal
	//finish printing
    do
	{
		cout << "	Press <Enter> to go back to main menu ... ";
		getline(cin,input);
	}while(!input.empty());
	delete vehicle;
	cout << "\n\tGoing back to main menu ... \n\n";
}

