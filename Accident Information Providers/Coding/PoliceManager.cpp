#include <iostream>
#include <string>
using namespace std;

#include <mysql/jdbc.h>
using namespace sql;

#include "DatabaseConnection.h"
#include "Police.h"
#include "PoliceManager.h"
#include "Station.h"
#include "StationManager.h"

int PoliceManager::insertPolice(Police* police)							//save police data in MySql at line 218, main.cpp at register()
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO Police VALUES (?, ?, ?, ?, ?, ?, ?)");

	ps->setString(1, police->policeId);
	ps->setString(2, police->policePass);
	ps->setString(3, police->policeName);
	ps->setString(4, police->policePhoneNum);
	ps->setString(5, police->policeAddress);
	ps->setString(6, police->policeEmail);
	ps->setString(7, police->stationId);

	int status = ps->executeUpdate();

	delete ps;

	return status;
}

int PoliceManager::updateName(string name, string PoliceId)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("UPDATE Police SET policeName = ? WHERE policeId = ?");

	ps->setString(1, name);
	ps->setString(2, PoliceId);

	int status = ps->executeUpdate();
	
	delete ps;
	return status;
}

int PoliceManager::updateNumberPhone(string PhoneNumber, string PoliceId)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("UPDATE Police SET policePhoneNum = ? WHERE policeId = ?");

	ps->setString(1, PhoneNumber);
	ps->setString(2, PoliceId);

	int status = ps->executeUpdate();

	delete ps;
	return status;
}

int PoliceManager::updateAddress(string Address, string PoliceId)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("UPDATE Police SET policeAddress = ? WHERE policeId = ?");

	ps->setString(1, Address);
	ps->setString(2, PoliceId);

	int status = ps->executeUpdate();

	delete ps;
	return status;
}

int PoliceManager::updateEmail(string Email, string PoliceId)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("UPDATE Police SET policeEmail = ? WHERE policeId = ?");

	ps->setString(1, Email);
	ps->setString(2, PoliceId);

	int status = ps->executeUpdate();

	delete ps;
	return status;
}

int PoliceManager::updateStationId(string StationId, string PoliceId)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("UPDATE Police SET StationId = ? WHERE policeId = ?");

	ps->setString(1, StationId);
	ps->setString(2, PoliceId);

	int status = ps->executeUpdate();

	delete ps;
	return status;
}

int PoliceManager::updatePassword(string Pass, string PoliceId)							//update password at main.cpp, login()
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("UPDATE Police SET policePass = ? WHERE policeId = ?");

	ps->setString(1, Pass);
	ps->setString(2, PoliceId);

	int status = ps->executeUpdate();

	delete ps;
	return status;
}

bool PoliceManager::confirmPoliceId(string policeId)							//check Police Id dh dftr ke belum at main.cpp Login()
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Police WHERE policeId = ?");

	ps->setString(1, policeId);
	
	ResultSet* rs = ps->executeQuery();

	if (rs->next())
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

bool PoliceManager::confirmPolicePass(string policeId, string policePass)					//at main.cpp, register()
{
	DatabaseConnection dbConn;
	string passGet;
	int y;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT policePass FROM Police WHERE policeId = ?");

	ps->setString(1, policeId);

	ResultSet* rs = ps->executeQuery();

	if (rs->next())
	{
		passGet = rs->getString(1);					//get password for policeId from mySQL
	}
	if (passGet==policePass)										//if password same
	{
		return true;
	}
	else
		return false;

	delete ps;
	delete rs;
}

Police* PoliceManager::selectPolice(string policeId)						//display police information
{
	string StationId;
	Police* police = NULL;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Police WHERE policeId = ?");

	ps->setString(1, policeId);

	ResultSet* rs = ps->executeQuery();

	
	if (rs->next())
	{
		police = new Police();

		police->policeId = rs->getString(1);
		police->policePass = rs->getString(2);
		police->policeName = rs->getString(3);
		police->policePhoneNum = rs->getString(4);
		police->policeAddress = rs->getString(5);
		police->policeEmail = rs->getString(6);
		police->stationId = rs->getString(7);

		cout << "\t\tPolicer id = " << police->policeId << endl;
		cout << "\t\tPolicer Name = " << police->policeName << endl;
		cout << "\t\tPolicer Phone Number = +601" << police->policePhoneNum << endl;
		cout << "\t\tPolicer Address = " << police->policeAddress << endl;
		cout << "\t\tPolicer Email = " << police->policeEmail << endl;
		cout << "\n\t\tPolice Station = " << police->stationId;

		StationId = police->stationId;
		StationManager stationManager;
		stationManager.displayStation(StationId);
	}

	delete rs;
	delete ps;

	return police;
}

int PoliceManager::lastIdPolice()					//detect last id Police at register() at line 146 main.cpp
{
	//Accident* accident;
	string policeId;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT policeId FROM Police ");

	ResultSet* rs = ps->executeQuery();
	int a = 0;
	while (rs->next())							//it will loop until lastId in table
	{
		a++;
		policeId = rs->getString(1);
	}
	int int1 = 0;
	int1 = a + 10000;
	delete rs;
	delete ps;

	return ++int1;
}