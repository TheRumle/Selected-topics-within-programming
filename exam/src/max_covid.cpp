//
// Created by rasmus on 5/31/2023.
//
#include "reactionNetwork/monitor/monitor.h"
#include "factories/reactionNetworkFactory.h"



int main(){

    std::cout << "\nN_NJ\n";
    const auto res_NJ = MonitorAndGetMaxHospitalized(589755); //112
    std::cout << res_NJ.first << ":  " << res_NJ.second;
    std::cout << "\nN_NJ\n";
    
    std::cout << "\nN_DK\n";
    const auto res_DK = MonitorAndGetMaxHospitalized(5822763);//1211
    std::cout << res_DK.first << ":  " << res_DK.second;
    std::cout << "\nN_DK\n";
    
    return 0;
}