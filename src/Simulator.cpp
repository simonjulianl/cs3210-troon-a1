#include "Simulator.h"
#include <iostream>
#include <sstream>

using namespace std;

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

    CreateIdNameIdMapping(num_stations, station_names);
    CreateWaitingPlatformLink(num_stations, popularities, mat);

    AssembleLink(green_station_names, g);
    WaitingArea *firstGreenTerminal, *lastGreenTerminal;
    GetFirstLastTerminals(green_station_names, firstGreenTerminal, lastGreenTerminal);
    terminalGreenForward = firstGreenTerminal;
    terminalGreenBackward = lastGreenTerminal;

    AssembleLink(yellow_station_names, y);
    WaitingArea *firstYellowTerminal, *lastYellowTerminal;
    GetFirstLastTerminals(yellow_station_names, firstYellowTerminal, lastYellowTerminal);
    terminalYellowForward = firstYellowTerminal;
    terminalYellowBackward = lastYellowTerminal;

    AssembleLink(blue_station_names, b);
    WaitingArea *firstBlueTerminal, *lastBlueTerminal;
    GetFirstLastTerminals(blue_station_names, firstBlueTerminal, lastBlueTerminal);
    terminalBlueForward = firstBlueTerminal;
    terminalBlueBackward = lastBlueTerminal;
}

void Simulator::GetFirstLastTerminals(const vector<string> &station_names, WaitingArea *&firstTerminal,
                                      WaitingArea *&lastTerminal) {

    const string &firstGreenStation = station_names[0];
    const string &secondGreenStation = station_names[1];

    size_t firstId = stationNameIdMapping[firstGreenStation];
    size_t secondId = stationNameIdMapping[secondGreenStation];

    const string &lastGreenStation = station_names[station_names.size() - 1];
    const string &secondLastGreenStation = station_names[station_names.size() - 2];

    size_t lastId = stationNameIdMapping[lastGreenStation];
    size_t secondLastId = stationNameIdMapping[secondLastGreenStation];

    firstTerminal = waitingAreaData[firstId][secondId];
    lastTerminal = waitingAreaData[lastId][secondLastId];
}

void Simulator::Simulate() {
    for (size_t tick = 0; tick < ticks; tick++) {
        UpdateAllLinks();
        // in the worst case, the platforms need to do 2 jobs, to push the curren troon to link
        // and take another incoming troon
        PushAllPlatform();

        // summon and push
        SpawnTroons();
        UpdateAllWA();
        UpdateWaitingPlatform();

        if (ticks - tick <= linesToBePrinted) {
            std::stringstream ss;
            ss << tick << ". ";
            for (auto &c: {blueTroons, greenTroons, yellowTroons}) {
                for (auto &t: c) {
                    ss << t->GenerateDescription();
                }
            }

            std::cout << ss.str() << std::endl;
        }
    }

    Clean();
}

void Simulator::SpawnTroons() {
    // g -> y -> b
    if (greenTroonCounter < maxGreenTroon) {
        auto t = new Troon{troonIdCounter, g, WAITING_AREA};
        terminalGreenForward->AddTroon(t);
        troonIdCounter++;
        greenTroonCounter++;
        greenTroons.insert(t);
    }

    if (greenTroonCounter < maxGreenTroon) {
        auto t = new Troon{troonIdCounter, g, WAITING_AREA};
        terminalGreenBackward->AddTroon(t);
        troonIdCounter++;
        greenTroonCounter++;
        greenTroons.insert(t);
    }

    if (yellowTroonCounter < maxYellowTroon) {
        auto t = new Troon{troonIdCounter, y, WAITING_AREA};
        terminalYellowForward->AddTroon(t);
        troonIdCounter++;
        yellowTroonCounter++;
        yellowTroons.insert(t);
    }

    if (yellowTroonCounter < maxYellowTroon) {
        auto t = new Troon{troonIdCounter, y, WAITING_AREA};
        terminalYellowBackward->AddTroon(t);
        troonIdCounter++;
        yellowTroonCounter++;
        yellowTroons.insert(t);
    }

    if (blueTroonCounter < maxBlueTroon) {
        auto t = new Troon{troonIdCounter, b, WAITING_AREA};
        terminalBlueForward->AddTroon(t);
        troonIdCounter++;
        blueTroonCounter++;
        blueTroons.insert(t);
    }

    if (blueTroonCounter < maxBlueTroon) {
        auto t = new Troon{troonIdCounter, b, WAITING_AREA};
        terminalBlueBackward->AddTroon(t);
        troonIdCounter++;
        blueTroonCounter++;
        blueTroons.insert(t);
    }
}

void Simulator::PushAllPlatform() {
    for (size_t i = 0; i < compactPlatformData.size(); i++) {
        compactPlatformData[i]->ProcessPushPlatform();
    }
}

void Simulator::UpdateWaitingPlatform() {
    for (size_t i = 0; i < compactPlatformData.size(); i++) {
        compactPlatformData[i]->ProcessWaitPlatform();
    }
}

void Simulator::UpdateAllWA() {
    for (size_t i = 0; i < compactWaitingAreaData.size(); i++) {
        compactWaitingAreaData[i]->ProcessWaitingArea();
    }
}

void Simulator::UpdateAllLinks() {
    for (size_t i = 0; i < compactLinkData.size(); i++) {
        compactLinkData[i]->ProcessLink();
    }
}

void Simulator::CreateWaitingPlatformLink(size_t num_stations, const vector<size_t> &popularities,
                                          const adjacency_matrix &mat) {
    for (size_t source = 0; source < num_stations; source++) {
        for (size_t destination = 0; destination < num_stations; destination++) {
            size_t distance = mat[source][destination];
            if (distance == 0) continue;

            string sourceStation = stationIdNameMapping[source];
            string destinationStation = stationIdNameMapping[destination];

            // Source and destination can be used for debugging
            auto *waitingArea = new WaitingArea{sourceStation, destinationStation};
            auto *platform = new Platform{sourceStation, destinationStation, popularities[source]};
            auto *link = new Link{sourceStation, destinationStation, distance};

            waitingArea->nextPlatform = platform;
            platform->nextLink = link;

            waitingAreaData[source][destination] = waitingArea;
            platformData[source][destination] = platform;
            linkData[source][destination] = link;

            compactLinkData.push_back(link);
            compactPlatformData.push_back(platform);
            compactWaitingAreaData.push_back(waitingArea);
        }
    }
}

void Simulator::CreateIdNameIdMapping(size_t num_stations, const vector<string> &station_names) {
    for (size_t i = 0; i < num_stations; i++) {
        stationNameIdMapping[station_names[i]] = i;
        stationIdNameMapping[i] = station_names[i];
    }
}

void Simulator::AssembleLink(const vector<string> &stationNames, Line l) {
    size_t num_trains = stationNames.size();
    string previousStation, currentStation, nextStation;

    // forward direction
    for (size_t i = 1; i < num_trains - 1; i++) {
        previousStation = stationNames[i - 1];
        currentStation = stationNames[i];
        nextStation = stationNames[i + 1];
        LinkStation(previousStation, currentStation, nextStation, l);
    }

    // the end of the forward direction
    previousStation = stationNames[num_trains - 2];
    currentStation = stationNames[num_trains - 1];
    nextStation = stationNames[num_trains - 2];
    LinkStation(previousStation, currentStation, nextStation, l);

    // reverse direction
    for (size_t i = num_trains - 2; i > 0; i--) {
        previousStation = stationNames[i + 1];
        currentStation = stationNames[i];
        nextStation = stationNames[i - 1];
        LinkStation(previousStation, currentStation, nextStation, l);
    }

    previousStation = stationNames[1];
    currentStation = stationNames[0];
    nextStation = stationNames[1];
    LinkStation(previousStation, currentStation, nextStation, l);
}

void
Simulator::LinkStation(const string &previousStation, const string &currentStation, const string &nextStation, Line l) {
    size_t prevId = stationNameIdMapping[previousStation];
    size_t currentId = stationNameIdMapping[currentStation];
    size_t nextId = stationNameIdMapping[nextStation];

    Link *previousLink = linkData[prevId][currentId];
    WaitingArea *currentWaiting = waitingAreaData[currentId][nextId];

    switch (l) {
        case g:
            previousLink->nextWaGreen = currentWaiting;
            break;
        case b:
            previousLink->nextWaBlue = currentWaiting;
            break;
        case y:
            previousLink->nextWaYellow = currentWaiting;
            break;
    }
}

void Simulator::Clean() {
    for (auto &m: compactWaitingAreaData) {
        delete m;
    }

    for (auto &m: compactPlatformData) {
        delete m;
    }

    for (auto &m: compactLinkData) {
        delete m;
    }

    for (auto &m: {blueTroons, yellowTroons, greenTroons}) {
        for (auto &c: m) {
            delete c;
        }
    }
}