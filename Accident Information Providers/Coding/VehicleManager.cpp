#include <iostream>
#include <string>
using namespace std;

#include <mysql/jdbc.h>
using namespace sql;

#include "DatabaseConnection.h"
#include "Vehicle.h"
#include "VehicleManager.h"

int VehicleManager::insertVehicle(Vehicle* vehicle)
{
	//cout << "Hello" << endl;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO Vehicle VALUES (?, ?, ?)");
	//cout << "Hello" << endl;
	ps->setString(1, vehicle->vehicleNum);
	ps->setString(2, vehicle->vehicleOwnerName);
	ps->setString(3, vehicle->reportId);


	int status = ps->executeUpdate();

	delete ps;

	return status;
}

void VehicleManager::selectVehicle(string IdRep)
{
	Vehicle* vehicle;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Vehicle WHERE reportId = ?");

	ps->setString(1, IdRep);

	ResultSet* rs = ps->executeQuery();

	if (rs->next())
	{
		vehicle = new Vehicle();
		vehicle->vehicleNum = rs->getString(1);
		vehicle->vehicleOwnerName = rs->getString(2);
		vehicle->reportId = rs->getString(3);
		
		cout << "\t\tVehicle Involved = " << endl;
		cout << "\t\tVehicle number = " << vehicle->vehicleNum << endl;
		cout << "\t\tVehicle Owner Name = " << vehicle->vehicleOwnerName << endl << endl;
	}

	delete rs;
	delete ps;
}

int VehicleManager::deleteVehicle(string deleteReportId)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("DELETE FROM Vehicle WHERE reportId = ?");

	ps->setString(1, deleteReportId);

	//ResultSet* rs = ps->executeQuery();
	int status = ps->executeUpdate();
	delete ps;
	return status;
}