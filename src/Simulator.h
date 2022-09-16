#ifndef CS3210_A1_A1_A0196678A_A0219768L_SIMULATOR_H
#define CS3210_A1_A1_A0196678A_A0219768L_SIMULATOR_H

#include <vector>
#include <string>
#include <map>
#include <tuple>
#include "Troon.h"
#include "PlatformUnit.h"

using std::vector;
using std::string;
using std::map;
using std::tuple;

using adjacency_matrix = vector<vector<size_t>>;

class Simulator {
private:
    size_t ticks = 0;
    size_t linesToBePrinted = 0;
    int troonIdCounter = 0;

    vector<Troon *> greenTroons;
    vector<Troon *> yellowTroons;
    vector<Troon *> blueTroons;

    size_t greenTroonCounter = 0;
    size_t yellowTroonCounter = 0;
    size_t blueTroonCounter = 0;

    size_t maxGreenTroon;
    size_t maxYellowTroon;
    size_t maxBlueTroon;

    map<string, size_t> stationNameIdMapping;
    map<size_t, string> stationIdNameMapping;

    map<size_t, map<size_t, WaitingArea *>> waitingAreaData;
    map<size_t, map<size_t, Platform *>> platformData;
    map<size_t, map<size_t, Link *>> linkData;

    vector<Platform *> compactPlatformData;
    vector<WaitingArea *> compactWaitingAreaData;
    vector<Link *> compactLinkData;

    WaitingArea *terminalGreenForward;
    WaitingArea *terminalGreenBackward;
    WaitingArea *terminalYellowForward;
    WaitingArea *terminalYellowBackward;
    WaitingArea *terminalBlueForward;
    WaitingArea *terminalBlueBackward;

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

    void Simulate();

    void Clean();

private:
    void CreateIdNameIdMapping(size_t num_stations, const vector<string> &station_names);

    void
    CreateWaitingPlatformLink(size_t num_stations, const vector<size_t> &popularities, const adjacency_matrix &mat);

    void LinkStation(const string &previousStation, const string &currentStation, const string &nextStation, Line l);

    void AssembleLink(const vector<string> &stationNames, Line l);

    void UpdateAllLinks();

    void UpdateAllWA();

    void UpdateWaitingPlatform();

    void GetFirstLastTerminals(const vector<string> &station_names, WaitingArea *&firstTerminal,
                               WaitingArea *&lastTerminal);

    void PushAllPlatform();
};


#endif //CS3210_A1_A1_A0196678A_A0219768L_SIMULATOR_H
