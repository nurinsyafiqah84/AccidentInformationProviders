#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

#include <mysql/jdbc.h>
using namespace sql;

#include "DatabaseConnection.h"
#include "Report.h"
#include "ReportManager.h"
#include "Accident.h"
#include "AccidentManager.h"
#include "Police.h"
#include "PoliceManager.h"
#include "Driver.h"
#include "DriverManager.h"
#include "Vehicle.h"
#include "VehicleManager.h"

int ReportManager::insertReport(Report* report)					//add new report
{
	//cout << "Hello" << endl;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO REPORT VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
	//cout << "Hello" << endl;
	ps->setString(1, report->reportId);
	ps->setInt(2, report->reportDate);
	ps->setInt(3, report->reportTime);
	ps->setString(4, report->reportStatus);
	ps->setInt(5, report->reportCost);
	ps->setString(6, report->reportDetails);
	ps->setString(7, report->accidentId);
	ps->setString(8, report->policeId);
	


	int status = ps->executeUpdate();

	delete ps;

	return status;
}

int ReportManager::lastIdReport()					//detect last id in mySQL, and pass at main.cpp 
{
	//Accident* accident;
	string ReportId;
	int detect = 0;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT reportId FROM Report ");

	ResultSet* rs = ps->executeQuery();
	while (rs->next())
	{
		detect++;
		ReportId = rs->getString(1);
	}
	if (detect == 0)
	{
		ReportId = "30000-Rep";
	}
	//cout << AccidentId;
	int int1 = stoi(ReportId);
	//cout << "\n" << int1;
	delete rs;
	delete ps;

	return ++int1;
}

Report* ReportManager::displayReport(string IdAcc)										//display semua report yang dh ditambah
{
	//Station* station = new Station();
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Report WHERE accidentId = ? ");

	ps->setString(1, IdAcc);

	ResultSet* rs = ps->executeQuery();

	Report* report;
	string IdPolice = "", Date, Time;
	cout << "\t\tSuccessful added data = " << endl;
	while (rs->next())
	{
		report = new Report();
		report->reportId = rs->getString(1);
		Date = rs->getString(2);
		Time = rs->getString(3);
		report->reportStatus = rs->getString(4);
		report->reportCost = rs->getInt(5);
		report->reportDetails = rs->getString(6);
		report->accidentId = rs->getString(7);
		report->policeId = rs->getString(8);

		IdPolice = report->policeId;

		cout << "\t\tReport Id = " << report->reportId << endl;
		cout << "\t\tReport Date = " << Date << endl;
		cout << "\t\tReport Time = " << Time << endl;
		cout << "\t\tReport Status = " << report->reportStatus << endl;
		cout << "\t\tReport Cost = RM " << report->reportCost << endl;
		cout << "\t\tReport Details = " << report->reportDetails << endl;
		cout << "\t\tReport Added by = " << report->policeId << endl << endl;
	}

	AccidentManager accidentManager;
	accidentManager.displayAccident(IdAcc);
	PoliceManager policeManager;
	cout << "\t\tAdded by Police = " << endl;
	policeManager.selectPolice(IdPolice);

	delete rs;
	delete ps;

	return 0;
}

bool ReportManager::confirmReportId(string confirmIdReport)							//check Police Id dh dftr ke belum
{
	//userDetails* registration = NULL;
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Report WHERE reportId = ?");

	ps->setString(1, confirmIdReport);

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

int ReportManager::displaySearchReport(string confirmIdReport)										//display untuk search report
{
	//Station* station = new Station();
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Report WHERE reportId = ? ");

	ps->setString(1, confirmIdReport);

	ResultSet* rs = ps->executeQuery();
	Report* report;
	AccidentManager accidentManager;
	DriverManager driverManager;
	VehicleManager vehicleManager;
	string IdAcc, IdRep;
	string IdPolice = "", Date, Time;

	if (rs->next())
	{
		cout << "\n\n\t\tSearch added data = " << endl;
		report = new Report();
		report->reportId = rs->getString(1);
		Date = rs->getString(2);
		Time = rs->getString(3);
		report->reportStatus = rs->getString(4);
		report->reportCost = rs->getInt(5);
		report->reportDetails = rs->getString(6);
		report->accidentId = rs->getString(7);
		report->policeId = rs->getString(8);

		cout << "\t\tReport Id = " << report->reportId << endl;
		cout << "\t\tReport Date = " << Date << endl;
		cout << "\t\tReport Time = " << Time << endl;
		cout << "\t\tReport Status = " << report->reportStatus << endl;
		cout << "\t\tReport Cost = RM " << report->reportCost << endl;
		cout << "\t\tReport Details = " << report->reportDetails << endl << endl;
		IdAcc = report->accidentId;
		IdRep = report->reportId;
		IdPolice = report->policeId;
	}

	driverManager.selectDriver(IdRep);
	vehicleManager.selectVehicle(IdRep);
	accidentManager.displayAccident(IdAcc);
	PoliceManager policeManager;
	cout << "\t\tAdded by Police = " << endl;
	policeManager.selectPolice(IdPolice);

	delete rs;
	delete ps;

	return 0;
}

int ReportManager::deleteReport(string deleteReportId)									//tanya madam mcm mana pasal delete
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("DELETE FROM Report WHERE reportId = ?");

	ps->setString(1, deleteReportId);

	//ResultSet* rs = ps->executeQuery();
	int status = ps->executeUpdate();
	delete ps;
	return status;
}

void ReportManager::updateReport(Report* report)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("UPDATE Report SET reportDate = ?, reportTime = ?, reportStatus = ?, policeId = ? WHERE reportId = ?");
	
	ps->setInt(1, report->reportDate);
	ps->setInt(2, report->reportTime);
	ps->setString(3, report->reportStatus);
	ps->setString(4, report->policeId);
	ps->setString(5, report->reportId);

	int status = ps->executeUpdate();
	delete ps;
}

void ReportManager::DisplayGraph(int month, int year)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Report WHERE MONTH(reportDate) = ? AND YEAR(reportDate) = ?");

	ps->setInt(1, month);
	ps->setInt(2, year);

	ResultSet* rs = ps->executeQuery();

	string reportId, reportDate, reportTime, reportStatus, accidentId, policeId, reportDetails;
	int kiraan[4], n=0, reportCost, m=1;
	for (int i = 0; i < 4; i++)
	{
		kiraan[i] = 0;
	}
	while (rs->next())
	{
		reportId = rs->getString(1);
		reportDate = rs->getString(2);
		reportTime = rs->getString(3);
		reportStatus = rs->getString(4);
		reportCost = rs->getInt(5);
		reportDetails = rs->getString(6);
		accidentId = rs->getString(7);
		policeId = rs->getString(8);


		if (reportDetails == "First category (taxi) = All type vehicle including motorcycle")
		{
			kiraan[0]++;
			reportDetails = "First Category";
			//n++;
		}
		if ((reportDetails == "Second Category (Active faults) = All type vehicle") || (reportDetails == "Second Category (Active faults) = Motorcycle under 250cc"))
		{
			kiraan[1]++;
			reportDetails = "Second Category";
			//n++;
		}
		if ((reportDetails == "Third Category (Passive faults) = All type vehicle") || (reportDetails == "Third Category (Passive faults) = Motorcycle under 250cc"))
		{
			kiraan[2]++;
			reportDetails = "Third Category";
			//n++;
		}
		if ((reportDetails == "Others category = All type vehicle") || (reportDetails == "Others category = Motorcycle under 250cc"))
		{
			kiraan[3]++;
			reportDetails = "Others Category";
			//n++;
		}
		cout << "\n\t\t\t | " << setw(4) << m << " | " << setw(10) << reportId << " | " << setw(11) << reportDate << " | " << setw(20) << reportDetails << " | " << setw(11) << accidentId << " | " << setw(10) << policeId << " | ";
		m++;
	}
	cout << "\n\t\t\t |___________________________________________________________________________________|";
	double sum, average;
	AveTotalCost( month, year, n, sum, average);
	int max = kiraan[0], min = kiraan[0];
	for (int a = 0; a < 4; a++)
	{
		if (max <= kiraan[a])
		{
			max = kiraan[a];
		}
		if (min >= kiraan[a])
		{
			min = kiraan[a];
		}
	}
	float percent1 = kiraan[0], percent2 = kiraan[1], percent3 = kiraan[2], percent4 = kiraan[3], percent[5];
	string category[4];
	cout << "\n\n\t\t\t\tThis is graph for this month report in Malaysia" << endl;
	cout << "\n\t\t\t\t\t" << "Types Category" << endl;
	cout << "\t\t\t" << setw(20) << " " << " ^ " << endl;
	cout << "\t\t\t" << setw(20) << " " << " | ";
	for (int i = 0; i < 4; i++)
	{
		if (i == 0)
		{
			category[0] = "First Category";
			cout << "\n\t\t\t" << setw(20) << category[i] << " | ";
			percent[0] = (percent1 / n * 100);

		}
		if (i == 1)
		{
			category[1] = "Second Category";
			cout << "\n\t\t\t" << setw(20) << category[i] << " | ";
			percent[1] = (percent2 / n * 100);
		}
		if (i == 2)
		{
			category[2] = "Third Category";
			cout << "\n\t\t\t" << setw(20) << category[i] << " | ";
			percent[2] = (percent3 / n * 100);
		}
		if (i == 3)
		{
			category[3] = "Others Category";
			cout << "\n\t\t\t" << setw(20) << category[i] << " | ";
			percent[3] = (percent4 / n * 100);
		}
		
		for (int j = 0; j < kiraan[i]; j++)
		{
			cout << " x ";
		}
		cout << "\t" << percent[i] << "%";				//find percent each case
		cout << "\n\t\t\t" << setw(20) << " " << " | ";
	}
	cout << "\n\t\t\t" << setw(20) << " " << " |--";
	for (int i = 0; i <= max; i++)
	{
		cout << "|--";
	}
	cout << "> Numbers of reports";
	cout << "\n\t\t\t" << setw(20) << " " << "    ";
	for (int i = 0; i <= max; i++)
	{
		cout << i+1 << "  ";
	}
	cout << "\n\n\t\t\tNumbers of report was reported for this month = " << n;
	cout << "\n\t\t\tMost Category was reported = ";
	for (int i = 0; i < 4; i++)
	{
		if (max == kiraan[i])
		{
			cout << category[i] << " ( " << percent[i] << "% ) ";
		}
	}
	cout << "\n\t\t\tLeast Category was reported = ";
	for (int i = 0; i < 4; i++)
	{
		if (min == kiraan[i])
		{
			cout << category[i] << " ( " << percent[i] << "% ) ";
		}
	}
	cout << "\n\t\t\tTotal Cost Report was reported for this month = RM " << sum;
	cout << "\n\t\t\tAverage Total Cost Report was reported for this month = RM " << average;
	delete rs;
	delete ps;
}

void ReportManager::AveTotalCost(int month, int year, int& n, double& sum, double& average)
{
	DatabaseConnection dbConn;
	PreparedStatement* ps = dbConn.prepareStatement("SELECT COUNT(reportId), SUM(reportCost), AVG(reportCost) FROM Report WHERE MONTH(reportDate) = ? AND YEAR(reportDate) = ?");

	ps->setInt(1, month);
	ps->setInt(2, year);

	ResultSet* rs = ps->executeQuery();
	if (rs->next())
	{
		n = rs->getInt(1);
		sum = rs->getDouble(2);
		average = rs->getDouble(3);
	}

	delete rs;
	delete ps;
}