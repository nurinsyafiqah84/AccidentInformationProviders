#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

#include <mysql/jdbc.h>
using namespace sql;

#include "DatabaseConnection.h"
#include "Station.h"
#include "StationManager.h"


Station* StationManager::selectStation()										//display semua station semasa register, at line 212 main.cpp
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Station ");

	ResultSet* rs = ps->executeQuery();

	while (rs->next())
	{
		Station* station = new Station();
		station->stationId = rs->getString(1);
		station->stationName = rs->getString(2);
		station->stationCity = rs->getString(3);
		station->stationAddress = rs->getString(4);

		cout << "\t\t| " << setw(8) << station->stationId << "   | " << setw(25) << station->stationName << " | " << setw(13) << station->stationCity << " | " << setw(60) << station->stationAddress << " | " << endl;
	}

	delete rs;
	delete ps;
	return 0;
}

bool StationManager::confirmStationId(string stationId)				//to check the station id in the table or not, at line 207 main.cpp
{
	Station* station = NULL;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Station WHERE stationId = ?");

	ps->setString(1, stationId);

	ResultSet* rs = ps->executeQuery();

	if (rs->next())					//if found, it will return tru
	{
		return true;
	}
	else
	{
		return false;
	}

	delete ps;
	delete rs;
}

Station* StationManager::displayStation(string StationId)
{
	Station* station = NULL;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Station WHERE StationId = ?");

	ps->setString(1, StationId);

	ResultSet* rs = ps->executeQuery();

	if (rs->next())
	{
		station = new Station();
		station->stationId = rs->getString(1);
		station->stationName = rs->getString(2);
		station->stationCity = rs->getString(3);
		station->stationAddress = rs->getString(4);

		cout << "\n\t\tStation Name = " << station->stationName << endl;
		cout << "\t\tStation City = " << station->stationCity << endl;
		cout << "\t\tStation Address = " << station->stationAddress<< endl;
		
	}

	delete rs;
	delete ps;

	return station;
}