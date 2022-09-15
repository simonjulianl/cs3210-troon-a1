#include "Simulator.h"

Simulator::Simulator(
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
) : ticks{ticks},
    greenTroonSize{num_green_trains},
    yellowTroonSize{num_yellow_trains},
    blueTroonSize{num_blue_trains} {

    for (size_t i = 0; i < num_stations; i++) {
        this->stationNameIdMapping[station_names[i]] = i;
    }

}

void Simulator::SpawnTroons() {

}
