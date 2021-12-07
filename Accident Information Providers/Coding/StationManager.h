#ifndef STATIONMANAGER_H
#define STATIONMANAGER_H

class StationManager
{
public:
	Station* selectStation();
	bool confirmStationId(string stationId);
	Station* displayStation(string StationId);
};

#endif // !PROGRAMMANAGER_H
