#include "statisical_analysis_1.h"

statisical_analysis_1::statisical_analysis_1()
{


}

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>


using namespace std;

int main(){

    ifstream inputFile("C:\\Users\\Alvaro\\Downloads\\texasholdem.txt");

    if (!inputFile.is_open()) {
        cerr <<"Unable to open the file."<< endl;
        return 1;
    }

    string line;

    while (getline(inputFile, line)) {

        cout << line << endl;
    }

    inputFile.close();

    return 0 ;
}


