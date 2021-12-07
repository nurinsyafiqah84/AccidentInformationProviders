#ifndef VEHICLEMANAGER_H
#define VEHICLEMANAGER_H

class VehicleManager
{
public:
	int insertVehicle(Vehicle* vehicle);
	void selectVehicle(string IdRep);
	int deleteVehicle(string deleteReportId);
};

#endif // !PROGRAMMANAGER_H
