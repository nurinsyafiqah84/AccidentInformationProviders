#ifndef DRIVERMANAGER_H
#define DRIVERMANAGER_H

class DriverManager
{
public:
	int insertDriver(Drive* driver);
	int searchDriverName(string searchDriverId);
	void selectDriver(string IdRep);
	int deleteDriver(string deleteReportId);
};

#endif // !PROGRAMMANAGER_H
