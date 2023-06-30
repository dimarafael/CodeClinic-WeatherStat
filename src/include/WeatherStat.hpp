#ifndef WEATHERSTAT_H_
#define WEATHERSTAT_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <ctime>
#include <string>
#include <iomanip>
#include <map>

#define RES_PATH "./resources/"
using namespace std;

class WeatherStat
{
private:
    map<time_t, double> _mapData;
    void loadFiles();
public:
    WeatherStat();
    time_t strToTime(string date, string time);
    float slopeCoeff(time_t start, time_t end);
};


#endif //WEATHERSTAT_H_