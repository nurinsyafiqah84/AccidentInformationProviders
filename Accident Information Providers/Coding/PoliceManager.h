#ifndef POLICEMANAGER_H
#define POLICEMANAGER_H

class PoliceManager
{
public:
	int insertPolice(Police* police);
	bool confirmPoliceId(string policeId);
	Police* selectPolice(string policeId);
	int updateName(string Name, string PoliceId);
	int updateNumberPhone(string PhoneNumber, string PoliceId);
	int updateAddress(string Address, string PoliceId);
	int updateEmail(string Email, string PoliceId);
	int updateStationId(string StationId, string PoliceId);
	int lastIdPolice();
	bool confirmPolicePass(string policeId, string policePass);
	int updatePassword(string Pass, string PoliceId);
};

#endif // !PROGRAMMANAGER_H
