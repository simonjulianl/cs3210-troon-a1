//
// Created by lauwsj on 15/9/22.
//

#ifndef CS3210_A1_A1_A0196678A_A0219768L_SIMULATOR_H
#define CS3210_A1_A1_A0196678A_A0219768L_SIMULATOR_H

#include <vector>
#include <string>
#include <map>
#include "../Train/Troon.h"

using std::vector;
using std::string;
using std::map;
using adjacency_matrix = std::vector<std::vector<size_t>>;

class Simulator {
private:
    size_t ticks = 0;

    size_t greenTroonSize;
    size_t yellowTroonSize;
    size_t blueTroonSize;

    vector<Troon> greenTroons;
    vector<Troon> yellowTroons;
    vector<Troon> blueTroons;

    map<string, size_t> stationNameIdMapping;

public:
    Simulator(
            size_t num_stations,
            const vector<string> &station_names,
            const vector<size_t> &popularities,
            const adjacency_matrix &mat,
            const vector<string> &green_station_names,
            const vector<string> &yellow_station_names,
            const vector<string> &blue_station_names,
            size_t ticks,
            size_t num_green_trains,
            size_t num_yellow_trains,
            size_t num_blue_trains,
            size_t num_lines
    );

    void SpawnTroons();
};


#endif //CS3210_A1_A1_A0196678A_A0219768L_SIMULATOR_H
