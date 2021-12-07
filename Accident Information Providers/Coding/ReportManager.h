#ifndef REPORTMANAGER_H
#define REPORTMANAGER_H

class ReportManager
{
public:
	int insertReport(Report* report);
	Report* displayReport(string IdRep);
	int displaySearchReport(string confirmIdReport);
	bool confirmReportId(string confirmIdReport);
	int lastIdReport();
	int deleteReport(string deleteReportId);
	void updateReport(Report* report);
	void DisplayGraph(int month, int year);
	void AveTotalCost(int month, int year, int& n, double& sum, double& average);
};

#endif // !PROGRAMMANAGER_H
#pragma once
