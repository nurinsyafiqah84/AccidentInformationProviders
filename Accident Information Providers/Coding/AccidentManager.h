#ifndef ACCIDENTMANAGER_H
#define ACCIDENTMANAGER_H

class AccidentManager
{
public:
	int insertAccident(Accident* accident);
	bool comfirmAccidentId(string AccidentId);
	int lastId();
	int updateCostTotal(int totalCost, string IdAcc);
	Accident* displayAccident(string IdAcc);
};

#endif // !PROGRAMMANAGER_H
