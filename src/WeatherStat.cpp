#include "./include/WeatherStat.hpp"


WeatherStat::WeatherStat(){
    loadFiles();
    
}

time_t WeatherStat::strToTime(string date, string time){
    istringstream iss(date + " " + time);
    struct tm tm;
    iss >> get_time(&tm, "%Y_%m_%d %H:%M:%S");
    if(iss.fail()){
        cout<<"Error parse date and time: " << iss.str() << endl;
        return -1;
    }
    return mktime(&tm);
}

//Calculation coefficient of slope for linear refression
float WeatherStat::slopeCoeff(time_t start, time_t end){
    long n = _mapData.size();
    double sumTime;
    double sumVal;
    double sumTimeMulVal;
    double sumSqrTime;

    cout << "\nCalculating slope for linear regression \n"
    << "Start time: " << ctime(&start)
    << "End time: " << ctime(&end) << endl;

    cout << "Dataset start " << ctime(&_mapData.begin()->first)
    << "dataset end " << ctime(&_mapData.rbegin()->first);

    if(start > _mapData.rbegin()->first){
        cerr << "Start time (" << start << ") bigger then last record in data"
        << _mapData.rbegin()->first << endl;
        return -1;
    }

    if(end < _mapData.begin()->first){
        cerr << "End time (" << end << ") smoller then first record in data "
        << _mapData.begin()->first << endl;

        return -1;
    }

    for(auto item: _mapData){
        if(item.first >= start && item.first <= end){
            sumTime += item.first;
            sumVal += item.second;
            sumTimeMulVal += item.first*item.second;
            sumSqrTime += item.first*item.first;
        }
    }
    
    double numerator = n * sumTimeMulVal - sumTime * sumVal;
    double denominator = n * sumSqrTime - sumTime * sumVal;

    // cout << "numerator=" << numerator << " denominator=" << denominator
    // << " result=" << numerator / denominator << endl;

    return numerator / denominator;
}

void WeatherStat::loadFiles(){
    for(int year = 2012; year <=2015; year++){
        string fileName = (string)RES_PATH
            + "Environmental_Data_Deep_Moor_"
            + to_string(year)  + ".txt";
        ifstream ifs;
        ifs.open(fileName);
        if(!ifs){
            cerr<<"File on opened: "<<fileName<<endl;
        } else{
            cout << "Loading file: " << fileName << endl;
            string line;
            getline(ifs, line); //top line
            while (getline(ifs, line))
            {
                string date, time;
                double pres;
                
                istringstream iss(line);
                iss >> date >> time >> pres >> pres;
                time_t t = strToTime(date, time);
                if(t < 0){
                    cerr << "Error parse in file " << date << " " << time << endl;
                } else {
                    _mapData[t] = pres;
                }
            }
            cout << "Loaded records: " << _mapData.size() << endl;
        }
        ifs.close();
    }
}