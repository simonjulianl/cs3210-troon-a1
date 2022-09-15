#include "Simulator.h"
#include <iostream>
#include <sstream>

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
) : ticks{ticks}, linesToBePrinted{num_lines}, maxGreenTroon{num_green_trains}, maxYellowTroon{num_yellow_trains},
    maxBlueTroon{num_blue_trains} {

    createIdNameIdMapping(num_stations, station_names);
    createWaitingPlatformLink(num_stations, popularities, mat);

    assembleLink(green_station_names);
    assembleLink(yellow_station_names);
    assembleLink(blue_station_names);
}

void Simulator::Simulate() {
    for (size_t tick = 0; tick < ticks; tick++) {
        // simulate here
        // check if you need to spawn
        // check to update all the links
        // check to update all the waiting area (summon + push)
        // check to update the platform

        if (ticks - tick <= linesToBePrinted) {
            std::stringstream ss;
            ss << tick << ". ";
            for (auto &c: {blueTroons, greenTroons, yellowTroons}) {
                for (auto &t: c) {
                    ss << t.GenerateDescription();
                }
            }

            std::cout << ss.str() << std::endl;
        }
    }

    Clean();
}

void Simulator::createWaitingPlatformLink(size_t num_stations, const vector<size_t> &popularities,
                                          const adjacency_matrix &mat) {
    for (size_t source = 0; source < num_stations; source++) {
        for (size_t destination = 0; destination < num_stations; destination++) {
            size_t distance = mat[source][destination];
            if (distance == 0) continue;

            string sourceStation = stationIdNameMapping[source];
            string destinationStation = stationIdNameMapping[destination];

            auto *mtx = new std::mutex;
            mutexArray.push_back(mtx);

            WaitingArea waitingArea = WaitingArea{sourceStation, destinationStation, mtx};
            Platform platform = Platform{popularities[source]};
            Link link = Link{distance};

            waitingArea.nextPlatform = &platform;
            platform.nextLink = &link;

            waitingAreaData[source].insert(std::pair(destination, waitingArea));
            platformData[source].insert(std::pair(destination, platform));
            linkData[source].insert(std::pair(destination, link));
        }
    }
}

void Simulator::createIdNameIdMapping(size_t num_stations, const vector<string> &station_names) {
    for (size_t i = 0; i < num_stations; i++) {
        stationNameIdMapping[station_names[i]] = i;
        stationIdNameMapping[i] = station_names[i];
    }
}

void Simulator::assembleLink(const vector<string> &stationNames) {
    size_t num_trains = stationNames.size();
    string previousStation, currentStation, nextStation;

    // forward direction
    for (size_t i = 1; i < num_trains - 1; i++) {
        previousStation = stationNames[i - 1];
        currentStation = stationNames[i];
        nextStation = stationNames[i + 1];
        linkStationMiddle(previousStation, currentStation, nextStation);
    }

    // the end of the forward direction
    previousStation = stationNames[num_trains - 2];
    currentStation = stationNames[num_trains - 1];
    nextStation = stationNames[num_trains - 1];
    linkStationMiddle(previousStation, currentStation, nextStation);

    // reverse direction
    for (size_t i = num_trains - 2; i > 0; i++) {
        previousStation = stationNames[i + 1];
        currentStation = stationNames[i];
        nextStation = stationNames[i - 1];
        linkStationMiddle(previousStation, currentStation, nextStation);
    }

    // the end of the reverse direction
    previousStation = stationNames[1];
    currentStation = stationNames[0];
    nextStation = stationNames[1];
    linkStationMiddle(previousStation, currentStation, nextStation);
}

void
Simulator::linkStationMiddle(const string &previousStation, const string &currentStation, const string &nextStation) {
    size_t prevId = stationNameIdMapping[previousStation];
    size_t currentId = stationNameIdMapping[currentStation];
    size_t nextId = stationNameIdMapping[nextStation];

    Link previousLink = linkData[prevId].at(currentId);
    WaitingArea currentWaiting = waitingAreaData[currentId].at(nextId);
    previousLink.nextWa = &currentWaiting;
}

void Simulator::SpawnTroons() {

}

void Simulator::Clean() {
    for (auto &m: mutexArray) {
        free(m);
    }
}