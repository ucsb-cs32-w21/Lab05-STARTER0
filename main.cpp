#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <iomanip>
#include "dataAQ.h"
#include "demogData.h"
#include "comboDemogData.h"
#include "comboHospitalData.h"
#include "countyDemogData.h"
#include "comboHospitalData.h"
#include "hospitalData.h"
#include "cityHospitalData.h"
#include "parse.h"

using namespace std;

int main() {

	dataAQ theAnswers;

    cout << std::setprecision(2) << std::fixed;

    //read in the helper file to map city to county
    theAnswers.read_csvCityCounty("simple_uscities.csv");

    //read in the hospital data
    std::vector<shared_ptr<placeData>> theHospitalData = read_csv(
            "hospitals.csv", HOSPITAL);
   
    //read in the demographic data
    std::vector<shared_ptr<placeData>> theCountyDemogData = read_csv(
            "county_demographics.csv", DEMOG); 

    //create the state demographic data
    theAnswers.createStateDemogData((std::vector<shared_ptr<demogData>>&)theCountyDemogData);

    //create the state hospital data
    theAnswers.createStateHospData((std::vector<shared_ptr<hospitalData>>&)theHospitalData);

     //create the county hospital data   
    theAnswers.createCountyHospData((std::vector<shared_ptr<hospitalData>>&)theHospitalData);

    cout << "Special report on the number of states with more than 20 percent below poverty"

    //Use visitor pattern to create report
    theAnswers.stateReport(20);
    
    return 0;
}

