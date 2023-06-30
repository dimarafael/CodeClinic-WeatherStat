#include<iostream>
#include "./include/WeatherStat.hpp"

using namespace std;

int main(){

    WeatherStat ws;

    string s_startDate, s_startTime;
    cout << "Enter start date YYYY_MM_DD ";
    cin >> s_startDate;
    cout << "Enter start time HH:MM:SS ";
    cin >> s_startTime;
    time_t t_startTime = ws.strToTime(s_startDate, s_startTime);
    if(t_startTime < 0) return -1;

    string s_endDate, s_endTime;
    cout << "Enter end date YYYY_MM_DD ";
    cin >> s_endDate;
    cout << "Enter end time HH:MM:SS ";
    cin >> s_endTime;
    time_t t_endTime = ws.strToTime(s_endDate, s_endTime);
    if(t_endTime < 0) return -1;

    float slope =ws.slopeCoeff(t_startTime, t_endTime);

    cout << "Result " << slope << endl;

    return 0;
}