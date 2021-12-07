#include <string>
using namespace std;

#ifndef REPORT_H
#define REPORT_H

class Report
{
public:
	string reportId = "", reportStatus = "", reportDetails = "", accidentId = "", policeId = "";
	int reportDate = 0, reportTime = 0, reportCost = 0;
};

#endif
