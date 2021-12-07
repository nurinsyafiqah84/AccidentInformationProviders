#include <iostream>
#include <string>
using namespace std;

#include <mysql/jdbc.h>
using namespace sql;

#include "DatabaseConnection.h"
#include "Driver.h"
#include "DriverManager.h"
#include "Report.h"
#include "ReportManager.h"

int DriverManager::insertDriver(Drive* driver)
{
	//cout << "Hello" << endl;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO Driver VALUES (?, ?, ?, ?, ?)");
	//cout << "Hello" << endl;
	ps->setString(1, driver->driverId);
	ps->setString(2, driver->driverName);
	ps->setInt(3,driver->driverAge);
	ps->setString(4, driver->driverSex);
	ps->setString(5, driver->reportId);


	int status = ps->executeUpdate();

	delete ps;

	return status;
}

int DriverManager::searchDriverName(string searchDriverId)							
{
	Drive* drive;
	DatabaseConnection dbConn;
	
	PreparedStatement* ps = dbConn.prepareStatement("SELECT reportId FROM Driver WHERE driverId = ?");

	ps->setString(1, searchDriverId);

	ResultSet* rs = ps->executeQuery();

	ReportManager reportManager;
	string idReport;
	while (rs->next())
	{
		cout << "\n\t\tThis is report where involves this owner ic = ";
		drive = new Drive();
		drive->reportId = rs->getString(1);
		idReport = drive->reportId;
		reportManager.displaySearchReport(idReport);
		return 1;
	}
	if(!(rs->next()))
		return 0;
	delete ps;
	delete rs;
}

void DriverManager::selectDriver(string IdRep)
{
	Drive* drive;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Driver WHERE reportId = ?");

	ps->setString(1, IdRep);

	ResultSet* rs = ps->executeQuery();

	if (rs->next())
	{
		drive = new Drive();

		drive->driverId = rs->getString(1);
		drive->driverName = rs->getString(2);
		drive->driverAge = rs->getInt(3);
		drive->driverSex = rs->getString(4);
		drive->reportId = rs->getString(5);

		cout << "\t\tDriver name = " << drive->driverName << endl;
		cout << "\t\tDriver Id = " << drive->driverId << endl;
		cout << "\t\tDriver Age = " << drive->driverAge << endl;
		cout << "\t\tDriver Sex = " << drive->driverSex << endl << endl;
	}

	delete rs;
	delete ps;
}

int DriverManager::deleteDriver(string deleteReportId)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("DELETE FROM Driver WHERE reportId = ?");

	ps->setString(1, deleteReportId);

	//ResultSet* rs = ps->executeQuery();
	int status = ps->executeUpdate();
	delete ps;
	return status;
}