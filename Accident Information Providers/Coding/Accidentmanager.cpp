#include <iostream>
#include <string>
using namespace std;

#include <mysql/jdbc.h>
using namespace sql;

#include "DatabaseConnection.h"
#include "Accident.h"
#include "AccidentManager.h"

int AccidentManager::insertAccident(Accident* accident)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO ACCIDENT VALUES (?, ?, ?, ?, ?)");

	ps->setString(1, accident->accidentId);
	ps->setString(2, accident->accidentPeopleInvolve);
	ps->setString(3, accident->accidentStreetName);
	ps->setString(4, accident->accidentState);
	ps->setInt(5, accident->accidentTotalCost);


	int status = ps->executeUpdate();

	delete ps;

	return status;
}

bool AccidentManager::comfirmAccidentId(string accidentId)							//check Accident Id dh dftr ke belum //tak de guna lagi dlm main
{
	Accident* accident = NULL;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT accidentId FROM Accident WHERE ?");

	ps->setString(1, accidentId);

	ResultSet* rs = ps->executeQuery();

	if (rs->next())
	{
		//system("cls");
		return true;
	}
	else
	{
		//system("cls");
		return false;
	}


	delete ps;
	delete rs;
}

int AccidentManager::lastId()				//detect last id accident kat localHost, n pass at main.cpp, addReport()
{
	//Accident* accident;
	string AccidentId;
	int detect = 0;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT accidentId FROM Accident ");

	ResultSet* rs = ps->executeQuery();
	while (rs->next())
	{
		detect++;
		AccidentId = rs->getString(1);
	}
	if (detect == 0)
	{
		AccidentId = "20000Acc";
	}
	//cout << AccidentId;
	int int1 = stoi(AccidentId);
	//cout << "\n" << int1;
	delete rs;
	delete ps;

	return ++int1;
}

int AccidentManager::updateCostTotal(int totalCost, string IdAcc)			//update cost Total
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("UPDATE Accident SET accidentCostTotalPrice = ? WHERE accidentId = ?");
	ps->setInt(1, totalCost);
	ps->setString(2, IdAcc);

	ResultSet* rs = ps->executeQuery();
	if (rs->next())
		return true;
	else
		return false;
	delete ps;
	delete rs;
}

Accident* AccidentManager::displayAccident(string IdAcc)										//display semua report yang dh ditambah
{
	//Station* station = new Station();
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Accident WHERE accidentId = ? ");

	ps->setString(1, IdAcc);

	ResultSet* rs = ps->executeQuery();

	cout << "\t\tUnder Accident Details = " << endl;
	while (rs->next())
	{
		Accident* accident = new Accident();
		accident->accidentId = rs->getString(1);
		accident->accidentPeopleInvolve = rs->getString(2);
		accident->accidentStreetName = rs->getString(3);
		accident->accidentState = rs->getString(4);
		accident->accidentTotalCost = rs->getInt(5);

		cout << "\t\tAccident Id = " << accident->accidentId << endl;
		cout << "\t\tPeople Involve = " << accident->accidentPeopleInvolve << endl;
		cout << "\t\tStreet Name = " << accident->accidentStreetName << endl;
		cout << "\t\tState = " << accident->accidentState << endl;
		cout << "\t\tAccident Total Cost = RM " << accident->accidentTotalCost << endl << endl;
	}

	delete rs;
	delete ps;

	return 0;
}