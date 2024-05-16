/****************************************************************************
*Author: Cindy Rocha
*Class CS141, Fall 2023
*Date: Nov. 11 2023
*Program 4: The goal of this assigment is to get an understanding of classes,
* functions, constructors, accessors, searching and mutators. This program 
* analyzes and presents data of some restaurants in Chicago area including 
* of 4 displays of data, including risk percentages, overall inspection 
* information and, inspection information. 
*Environment: zyBooks Lab
*****************************************************************************/
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class Restaurant {
    private:
        string restaurantName;
        string address;
        string inspectionDate;
        string riskType;
        string inspectionPFC;
        string neighborhood;

    public:
        // default constructor
        Restaurant();
        //fully qualified constructor
        Restaurant(string newRestaurantName, string newAddress, string newInspectionDate, string newRiskType, string newInspectionPFC, string newNeighborhood);
        //mutators
        void setRestaurantName(string newName);
        void setAddress(string newAddress);
        void setInspectionDate(string newInspectionDate);
        void setInspectionPFC(string newInspectionPFC);
        void setRiskType(string newRiskType);
        void setNeighborhood(string newNeighborhood);
        //accessors
        string getRestaurantName();
        string getAddress();
        string getInspectionDate();
        string getInspectionPFC();
        string getRiskType();
        string getNeighborhood();
};

//default constructor with unknown string values
Restaurant::Restaurant() {
    restaurantName = "Unknown";
    address =  "Unknown";
    inspectionDate = "Unknown";
    riskType = "Unknown";
    inspectionPFC = "Unknown";
    neighborhood = "Unknown";
}
//fully qualified constructor, for later use in creating a restaurant object with all the variables assigned 
Restaurant::Restaurant(string newRestaurantName, string newAddress, string newInspectionDate, string newRiskType, string newInspectionPFC, string newNeighborhood) {
    restaurantName = newRestaurantName;
    address = newAddress;
    inspectionDate = newInspectionDate;
    riskType = newRiskType;
    inspectionPFC = newInspectionPFC;
    neighborhood = newNeighborhood;
}
// mutator functions
/*
* Description: The following 6 mutator functions allow for the user to modify the original data membe to new data members
* Parameters: the string correcponding data member
* Return: nothing
*/
void Restaurant::setRestaurantName(string newRestaurantName) {
    restaurantName = newRestaurantName;
}

void Restaurant::setAddress(string newAddress) {
    address = newAddress;
}

void Restaurant::setInspectionDate(string newInspectionDate) {
    inspectionDate = newInspectionDate;
}

void Restaurant::setInspectionPFC(string newInspectionPFC) {
    inspectionPFC = newInspectionPFC;
}

void Restaurant::setRiskType(string newRiskType) {
    riskType = newRiskType;
}

void Restaurant::setNeighborhood(string newNeighborhood) {
    neighborhood = newNeighborhood;
}
//accessors
/*
* Description: The following 6 acccessor functions allow for the user to access the data members
* Parameters: nothing
* Return: the corresponding string for each getter function
*/
string Restaurant::getRestaurantName() {
    return restaurantName;
}
string Restaurant::getAddress() {
    return address;
}
string Restaurant::getInspectionDate() {
    return inspectionDate;
}
string Restaurant::getInspectionPFC() {
    return inspectionPFC;
}
string Restaurant::getRiskType() {
    return riskType;
}
string Restaurant::getNeighborhood() {
    return neighborhood;
}
/*
* Description: The TaskOne function does the first menu item which is to get/calculate the total number 
* of restaurants, the number of restaurants that have passed inspection, and the most recent
* passing inspection from the file that was input by the user. 
* Parameters: A vector of the Restaurants
* Outputs the total number of restaurants, the number of passed inspections & most recently passed inspection
*/
void TaskOne(vector<Restaurant> restaurantVect) {
    int counter = 0;
    string mostRecentDate = "00-00-0000";   //initialize most recent date string
    string recentName;

    for (size_t i = 0; i < restaurantVect.size(); i++) {
        // mm-dd-yyyy --> yyyymmdd
        string cur = restaurantVect.at(i).getInspectionDate(); // gets the current interation of the restaurant vector and specifically gets the inspection date of that restaurant
        // checks if the restaurant inspection status is pass or has passed with certain conditions
        if ((restaurantVect.at(i).getInspectionPFC() == "Pass") || (restaurantVect.at(i).getInspectionPFC() == "Conditional")) {
            counter++;
            // compares the substrings of the year + month + day 
            if (cur.substr(6, 4) + cur.substr(0, 2) + cur.substr(3, 2) > mostRecentDate.substr(6, 4) + mostRecentDate.substr(0, 2) + mostRecentDate.substr(3, 2)) {
                mostRecentDate = cur;
                recentName = restaurantVect.at(i).getRestaurantName();
            }
        }
    }
    //outputs
    cout << "Number of restaurants: " << restaurantVect.size() << endl;
    cout << "Number that pass: " << counter << endl; 
    cout << "Most recent passing inspection was of " << recentName << " on " << mostRecentDate << endl;
}
/*
* Description: The TaskTwo function does the second menu item which is to calculate the percentages of each 
* risk and then round the percentage to one demical place.  
* Parameters: A vector of the Restaurants
* Outputs the high risk percentage, medium risk percentage, and low risk percentage.
*/
void TaskTwo(vector<Restaurant> restaurantVect) {
    double totalRestList = 0.0;
    double counterH = 0.0;
    double counterM = 0.0;
    double counterL = 0.0;

    // looks for risk types High, Medium, and Low respectively and counts how many restaurants are in each risk category
    for (size_t j = 0; j < restaurantVect.size(); j++) {
        string riskType = restaurantVect.at(j).getRiskType();
        totalRestList++;
        if (riskType == "H") {
            counterH++;
        } else if (riskType == "M") {
            counterM++;
        } else if (riskType == "L") {
            counterL++;
        }
    }

    //risk calculations: high, medium, low respectively
    double percentageH = (counterH/totalRestList) * 100;
    double percentageM = (counterM/totalRestList) * 100;
    double percentageL = (counterL/totalRestList) * 100;

    // outputs risk calculations set to one decimal place
    cout << "High risk: " << fixed << setprecision(1) << percentageH << '%' << endl;
    cout << "Medium risk: "  << percentageM << '%' << endl;
    cout << "Low risk: " << percentageL << '%' << endl;
}
/*
* Description: The TaskThree function does the third menu item which is to get the total number 
* of restaurants in each neighborhood. It also uses a vector of strings to store the neighborhoods into.
* Parameters: A vector of Restaurants
* Outputs a table with the neighborhood name and how many passed, failed, or passed with conditions per
* neighborhood
*/
void TaskThree(vector<Restaurant> restaurantVect) {
    bool exist = false;
    vector<string> neighborhoodsVect; //a vector that holds the neighbohood strings
    for (size_t i = 0; i < restaurantVect.size(); i++) {
        for(size_t j = 0; j < neighborhoodsVect.size(); j++) {
            // identifies if the strings are equal in both vector of restaurants and the respective neighborhood, and the neighborhoods vector 
            if (neighborhoodsVect.at(j) == restaurantVect.at(i).getNeighborhood()) {
               exist = true;
            } 
        }
        if(exist == false) { // if it is not in the neighborhood vector already, then it will add it to the vector 
            neighborhoodsVect.push_back(restaurantVect.at(i).getNeighborhood());
        }
        exist = false;
    }
    // outputs the category title and borders of the table
    cout << "Neighborhood" << setfill(' ') << setw(14) << "Passed" << ' '  << "Cond. Pass" << setw(11) << "Failed" << endl;
    cout << "============" << setfill(' ') << setw(14) << "======" << ' ' <<  "==========" << setw(11) <<  "======" << endl;

    for(size_t j = 0; j < neighborhoodsVect.size(); j++) {
        // counters for each inspection test status
        int passCounter = 0, condCounter = 0, failCounter = 0;
        for (size_t h = 0; h < restaurantVect.size(); h++) {
            if (restaurantVect.at(h).getNeighborhood() == neighborhoodsVect.at(j)) {
                if ((restaurantVect.at(h).getInspectionPFC() == "Pass")) {
                    passCounter++;
                } else if ((restaurantVect.at(h).getInspectionPFC() == "Conditional")) {
                    condCounter++;
                } else if ((restaurantVect.at(h).getInspectionPFC() == "Fail")) {
                    failCounter++;
                }
            }
        }
        // outputs the numerical contents of the table.
        cout << neighborhoodsVect.at(j) << setw(26 - neighborhoodsVect.at(j).length()) << passCounter << setw(11)  << condCounter << setw(11) << failCounter << endl;
    }
}

/*
* Description: The TaskFour function does the fourth menu item which is that it asks for user input of a
* restaurant to search and searches the vector what was input. It uses the input as a keyword and displays
* all the restaurants with a specific keyword or by exact name.
* Parameters: A vector of Restaurants
* Outputs the restauran name, address, inspection date, and inspection result of each restaurant that
* is a possible match for the keyword input.
*/
void TaskFour(vector<Restaurant> restaurantVect) {
    string userInput;
    cout << "Enter restaurant to search for: ";
    cin.ignore();
    getline(cin, userInput);
    // Converts each character in the userInput string to an uppercase letter if lowercase
    for(size_t j = 0; j < userInput.length(); j++) {
        userInput[j] = toupper(userInput[j]);
    }
    for(size_t i = 0; i < restaurantVect.size(); i++) {
        if (restaurantVect.at(i).getRestaurantName().find(userInput) != string::npos) {
            cout << "Restaurant: " << restaurantVect.at(i).getRestaurantName() << endl;
            cout << "Address: " << restaurantVect.at(i).getAddress() << endl;
            cout << "Inspection Date: " << restaurantVect.at(i).getInspectionDate() << endl;
            cout << "Inspection Result: " << restaurantVect.at(i).getInspectionPFC() << endl << endl;
        }
    }
}

int main() {
    string fileName;
    string rName;   // restaurant name
    string location; //address of the restaurant
    string inspectDate; //inspection date of the restaurant
    string rType; // risk type of the restaurant
    string inspectLevel; // inspection status (pass, conditional pass, fail)
    string region;  // neighborhood of where the restaurant is
    int userChoice; // this is for the user input selection of menu item

    //  prompt user to insert a file name
    cout << "Enter the data file to use: ";
    cin >> fileName;

    // vector for restaurants to be stored into
    vector<Restaurant> restaurantList;

    // reading from file
    fstream areaFile;
    areaFile.open(fileName);

    // gathers file data and assigns it to variables
    if(areaFile.is_open()) {
        while (!areaFile.eof()) {
            getline(areaFile, rName, ',');
            getline(areaFile, location, ',');
            getline(areaFile, inspectDate, ',');
            getline(areaFile, rType, ',');
            getline(areaFile, inspectLevel, ',');
            getline(areaFile, region);

            // loads restaurant attributes into vector as a single restaurant object
            Restaurant r1(rName, location, inspectDate, rType, inspectLevel, region);
            restaurantList.push_back(r1); // adds each restaurant into the vector
        }

        // user must input 5 to quit the program, meanwhile if 5 is not picked,
        // then continue to prompt user to insert a menu item 
        while (userChoice != 5) {
            cout << endl << "Select a menu option: " << endl;
            cout << "   1. Display overall inspection information" << endl;
            cout << "   2. Display risk percentages" << endl;
            cout << "   3. Display passing numbers by neighborhood" << endl;
            cout << "   4. Search for restaurant by name" << endl;
            cout << "   5. Exit" << endl;
            cout << "Your choice: ";
            cin >> userChoice;
            // for spacing purposes
            cout << endl;
            // this switch case then allows for the user input to execute accordingly
            // and execute the corresponding function depending on the menu item.
            switch(userChoice) {
                case 1:
                    TaskOne(restaurantList); //menu item 1
                    break;
                case 2:
                    TaskTwo(restaurantList); //menu item 2
                    break;
                case 3:
                    TaskThree(restaurantList); // menu item 3
                    break;
                case 4:
                    TaskFour(restaurantList); //menu item 4
                    break;
                case 5:
                    exit(0); // menu item 5
                    break;
                default: // i just put a default asking the user to insert a number 1-5. 
                    cout << "You did not pick a number from 1-5 from the menu. Please, try again." << endl;

            }
        }
    }
    return 0;
}