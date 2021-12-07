#include <iostream>
#include <string>
#include <limits>
#include <string.h>
#include <sstream>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <iomanip>
using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);	// used for goto
COORD CursorPosition; // used for goto

#include "Police.h"
#include "PoliceManager.h"
#include "Station.h"
#include "StationManager.h"
#include "Accident.h"
#include "AccidentManager.h"
#include "Report.h"
#include "ReportManager.h"
#include "Driver.h"
#include "DriverManager.h"
#include "Vehicle.h"
#include "VehicleManager.h"


//functions prototype
void gotoXY(int, int); 
void Register();
void Login();
bool is_valid(string Email);
bool isChar(char c);
void Logout();
void MenuProgram();
void AddReport();
void profileInformation();
void AccidentCost(int* a);
int reportDetails(char IdAcc[20], int& totalCost);
void driverDetails(char IdRep[20]);
void vehicleDetails(string nameDriver, char IdRep[20]);
void DeleteReport();
void SearchReport();
void EditStatusReport();
int passWord(char pass[30]);
void statisticGraph();

//global variables
string PoliceId = "";

int main()
{
	system("cls");
	//variable 
	int menu_item = 0, run, x = 7;
	bool running = true;
	cout << "\n\n\n\t\t  =========================================\n";
	cout << "\t\t    Accident Information Providers System";
	gotoXY(18, 5); cout << "=========================================";
	gotoXY(28, 7); cout << "->";
	while (running)
	{
		gotoXY(30, 7);  cout << "1) Register";
		gotoXY(30, 8);  cout << "2) Login";
		gotoXY(30, 9);  cout << "3) Exit";

		system("pause>nul"); // the >nul bit causes it the print no message

		if (GetAsyncKeyState(VK_DOWN) && x != 9) //down button pressed
		{
			gotoXY(28, x); cout << "  ";
			x++;
			gotoXY(28, x); cout << "->";
			menu_item++;
			continue;

		}

		if (GetAsyncKeyState(VK_UP) && x != 7) //up button pressed
		{
			gotoXY(28, x); cout << "  ";
			x--;
			gotoXY(28, x); cout << "->";
			menu_item--;
			continue;
		}
		if (GetAsyncKeyState(VK_RETURN))
		{
			switch (menu_item)
			{
				case 0:
				{
					Register();				//will go to register()
					break;
				}
				case 1:
				{
					Login();				//will go to Login()
					exit(0);		//end the program
				}
				case 2:
				{
					Logout();				//will go to Logout()
					exit(0);		//end the program
				}
			}
		}
	}
	return 0;
}

void Register()																			//Register function
{
	system("cls");
	Police* police = new Police();
	Station* station = new Station();
	StationManager stationManager;
	PoliceManager policeManager;
	string Email, StationId;

	cout << "\n\n\n\t\t=========================================\n";
	cout << "\t\t  Accident Information Providers System" << endl;
	cout << "\t\t            Registration Page"<<endl;
	cout << "\t\t=========================================" << endl;

	cin.ignore(0, '\n');
	cout << "\n\t\tFullname : ";								//enter name
	getline(cin, police->policeName);

	int m = 0;
	string phoneNumPolice;
	while (m == 0)
	{
		cout << "\t\tPhone Number : +601";						//enter number fon
		cin.ignore(0, '\n');
		getline(cin, phoneNumPolice);
		if (phoneNumPolice.size() != 8 && phoneNumPolice.size() != 9)			//check either phone number enough 8 / 9 digits or not
		{
			m = 0;
			cout << "\t\tPlease insert 8 / 9 digits number!!" << endl;				// if not it will repeat again
		}
		else
		{
			for (int n = 0; n < phoneNumPolice.size(); n++)
			{
				if (phoneNumPolice[n] >= '0' && phoneNumPolice[n] <= '9')		//check if all number phone is in numberic
				{
					m = 1;
				}
				else
				{
					m = 0;
					cout << "\t\tEnter numberic only!!" << endl;					//if has alphabetic or symbol it will ask user to cin again
					break;
				}
			}
		}
	}
	police->policePhoneNum = phoneNumPolice;
	
	cout << "\t\tAddress : ";									//enter the address
	cin.ignore(0, '\n');
	getline(cin, police->policeAddress);
	
	int idPolice;
	idPolice = policeManager.lastIdPolice();				//Generate new id after check last id in mySql
	cout << "\t\tPolice ID : " << idPolice << "Pol" << endl;
	char strPol[10] = "Pol";
	char IdPol[20];
	itoa(idPolice, IdPol, 10);								//change int into string
	strcat(IdPol, strPol);									//combine number that was changed with "Pol"
	police->policeId = IdPol;

	char pass[30];											//to store password
	passWord(pass);											//go to functions password to make a new password
	police->policePass = pass;

	cout << "\n\t\tEmail : ";
	cin.ignore(0, '\n');
	getline(cin, Email);
	bool ans = is_valid(Email);								//function Call to check email is valid or not
	if (!ans)
	{
		do													//will loop until the email enter with right format
		{
			cout << "\t\tPlease insert the right email!!";		// error message if don't have @ / .com
			cout << "\n\t\tEmail : ";
			cin.ignore(0, '\n');
			getline(cin, Email);
			ans = is_valid(Email);
		} while (!ans);				
	}
	police->policeEmail = Email;

	cout << "\t\tPolice Station ID: ";							//enter station police
	cin.ignore(0, '\n');
	getline(cin, police->stationId);
	while (!(stationManager.confirmStationId(police->stationId)))				//to identify if station id had registered or not
	{
		cout << "\t\tYou entered wrong Station Id!!\n";
		cout << "\t\tPlease make sure you put BP infront of Station Id!!\n";
		cout << "\t\tList Police Station with Id in Malaysia : \n";
		cout << "\t\t========================================================================================================================" << endl;
		cout << "\t\t| " << setw(10) << "Station Id" << " | " << setw(18) << "Station Name" << "        | "<< setw(13) <<"Station City" << " | "<< setw(37) << "Station Address" << "\t                 | " << endl;
		cout << "\t\t========================================================================================================================" << endl; 
		stationManager.selectStation();									// display semua station
		cout << "\t\t========================================================================================================================" << endl;
		cout << "\t\tPolice Station Id : ";
		cin.ignore(0, '\n');
		getline(cin, police->stationId);
	}

	int status = policeManager.insertPolice(police);							//if done save all information in mySQL

	if (status != 0)
	{
		cout << "\n\n\t\tSuccessfully added your data in system.\n\t\t";
		system("pause");
		main();
	}
	else
		cout << "\n\n\t\tUnable to add a new member." << endl;
}

int passWord(char pass[30])
{
	char p, rePass[30];							//p for temp char, rePass for confirming pass
	int o = 0, r = 0, s = 0, repeat = 0, t = 0;
	while (r == 0)
	{
		repeat = 0;
		cout << "\t\tEnter pasword (at least 6 alphabet) : ";
		for (o = 0;;)							//infinite loop
		{
			p = getch();						//stores char typed in p
			if (p >= 'a' && p <= 'z' || p >= 'A' && p <= 'Z' || p >= '0' && p <= '9')
			//check if p is numeric or alphabetc
			{
				pass[o] = p;				//stores p in pass
				++o;
				cout << "*";
			}
			if (p == '\b' && o >= 1)		//if user typed backspace , i should greater than 1
			{
				cout << "\b \b";			//delete the character behind the cursor
				--o;
			}
			if (p == '\r')					//if enter is pressed
			{
				pass[o] = '\0';				//end of string
				break;						//break the loop
			}
		}
		if (o <= 5)						//check if password less than 6 digits
		{
			cout << "\n\t\tMinimum 6 alphanumberic needed\n" << endl;
			r = 0;						//will loop for asking the password
		}
		else							//if password more than 6 characters
		{
			while (s == 0)
			{
				cout << "\n\t\tRe-enter password : ";			//asking for re enter the password
				for (o = 0;;)
				{
					p = getch();
					if (p >= 'a' && p <= 'z' || p >= 'A' && p <= 'Z' || p >= '0' && p <= '9')
					{
						rePass[o] = p;
						++o;
						cout << "*";
					}
					if (p == '\b' && o >= 1)
					{
						cout << "\b \b";
						--o;
					}
					if (p == '\r')
					{
						rePass[o] = '\0';
						break;
					}
				}
				t = strcmp(pass, rePass);				//compare pass with repass to make sure there is no different 
				if (t == 0)								//if pass n repass same, it will stop loop
				{
					r = 1;
					s = 1;
					break;
				}
				if (t != 0 && repeat < 3)			//if pass not same with repass, it will ask user to enter again
				{
					cout << "\n\t\tRe-enter Password not same like Password!!";
					repeat++;
					s = 0;
				}
				if (t != 0 && repeat >= 3)			//if user enter the repass more than 3 times, it will ask user to enter again the new pass
				{
					cout << "\n\t\tPlease enter again the password!!" << endl;
					r = 1;
					s = 1;
					passWord(pass);
					break;
				}
			}
		}
	}
	return 0;
}

bool is_valid(string Email)				//function to check email id is valid or not
{
	if (!isChar(Email[0]))				//Check the first character is an alphabet or not
		return 0;						//if it's not an alphabet email id is not valid

	int At = -1, Dot = -1;				//variable to store position of AT and DOT

	for (int i = 0; i < Email.length(); i++)			//Traverse over the email id string to find position of DOT and AT
	{
		if (Email[i] == '@')			//If the character is '@'
		{
			At = i;
		}
		else if (Email[i] == '.')		//if character is '.'
		{
			Dot = i;
		}
	}

	if (At == -1 || Dot == -1)			//If AT or DOT is not present 
		return 0;
	if (At > Dot)						//If Dot is present before AT
		return 0;
	return !(Dot >= (Email.length() - 1));				//If Dot is prsent at the end 

}

bool isChar(char c)					//function  to check the character is an alphabet or not
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

void Login()
{
	system("cls");
	PoliceManager policeManager;
	string registerId;
	char renewPass[30], registerPass[30];
	string PassRegister;
	int u = 0, repeatId = 0, v = 0, w, repeatLogin=0;
	char x;

	cout << "\n\n\n\t\t===================================== " << endl;
	cout << "\t\tAccident Information Providers System" << endl;
	cout << "\t\t            Log In Page" << endl;
	cout << "\t\t=====================================\n" << endl ;
	while (u == 0)
	{
		cout << "\t\t\tPolice Id : ";
		cin.ignore(0, '\n');
		getline(cin, registerId);										//enter id Police
		if (!(policeManager.confirmPoliceId(registerId)))
		{
			cout << "\t\t\tYour enter wrong id!!" << endl;				//error message if enter wrong id
			repeatId++;
			if (repeatId == 2)
			{
				cout << "\t\t\tYou will return to Main Menu if you enter wrong id again!!" << endl;			//reminder if the user enter more than 3 times
			}
			if (repeatId == 3)						//will return to menu if user input wrong id
			{
				main();
				exit(0);
			}
		}
		else										//if register Id in my SQL
		{
			u = 1;
			PoliceId = registerId;
			cout << "\n";
		}
	}
	while (v == 0 && u == 1)
	{
		cout << "\t\t\tPassword : ";
		for (w = 0;;)							//infinite loop
		{
			x = getch();						//stores char typed in p
			if (x >= 'a' && x <= 'z' || x >= 'A' && x <= 'Z' || x >= '0' && x <= '9')
				//check if p is numeric or alphabetc
			{
				registerPass[w] = x;				//stores p in pass
				++w;
				cout << "*";
			}
			if (x == '\b' && w >= 1)		//if user typed backspace , i should greater than 1
			{
				cout << "\b \b";			//delete the character behind the cursor
				--w;
			}
			if (x == '\r')					//if enter is pressed
			{
				registerPass[w] = '\0';				//end of string
				break;						//break the loop
			}
		}
		PassRegister = registerPass;
		if ((!(policeManager.confirmPolicePass(registerId, PassRegister)))&& repeatLogin<3)
		{
			cout << "\n\t\t\tYou enter wrong password!!" << endl;
			repeatLogin++;
		}
		if ((!(policeManager.confirmPolicePass(registerId, PassRegister))) && repeatLogin >= 3)
		{
			cout << "\n\t\tYou need to reset your password!!" << endl;				//need to reset password if wrong 3 times
			passWord(renewPass);													//change old pass
			repeatLogin = 0;
			policeManager.updatePassword(renewPass, PoliceId);						//update new Password 
			cout << "\n\n";
		}
		if (policeManager.confirmPolicePass(registerId, PassRegister))				//if password same in mySQL
		{
			v = 1;
			cout << "\n\t\tSuccessfully logged in as username";
			cout << "\n\t\t";
			system("pause");
			MenuProgram();
			exit(0);
		}
	}
}

void Logout()					//just output before console terminated
{
	system("cls");
	cout << "\n\n\n\t\t===================================== " << endl;
	cout << "\t\tAccident Information Providers System" << endl;
	cout << "\t\t            Logout Page" << endl;
	cout << "\t\t===================================== " << endl << endl;
	cout << "\tThank you for using this Accident Information Providers Program!!\n";
	cout << "\t\t\tTill We Meet Again!!\n";
	cout << "\t              ***        **   *******\n";
	cout << "\t             **  **      **   **    **\n";
	cout << "\t            **    **     **   **     **\n";
	cout << "\t           **      **    **   **    **\n";
	cout << "\t          ************   **   *******\n";
	cout << "\t          **        **   **   **\n";
	cout << "\t          **        **   **   **\n";
}

void MenuProgram()
{
	system("cls");
	//variable 
	int menu_item = 0, run, x = 8;
	bool running = true;
	cout << "\n\n\n\t\t  =========================================\n";
	cout << "\t\t    Accident Information Providers System\n";
	cout << "\t\t                Menu Program";
	gotoXY(18, 6); cout << "=========================================";
	gotoXY(21, 8); cout << "->";
	while (running==true)
	{
		//display menu details
		gotoXY(23, 8);  cout << "1) Add new Accident and Report Details";						
		gotoXY(23, 9);  cout << "2) Search Report";
		gotoXY(23, 10); cout << "3) Edit Status Report";
		gotoXY(23, 11);	cout << "4) Delete Report Details";
		gotoXY(23, 12);	cout << "5) Statistics Monthly";
		gotoXY(23, 13); cout << "6) Profile Information";
		gotoXY(23, 14); cout << "7) Logout";

		system("pause>nul"); // the >nul bit causes it the print no message

		if (GetAsyncKeyState(VK_DOWN) && x != 14) //down button pressed
		{
			gotoXY(21, x); cout << "  ";
			x++;
			gotoXY(21, x); cout << "->";
			menu_item++;
			continue;
		}
		if (GetAsyncKeyState(VK_UP) && x != 8) //up button pressed
		{
			gotoXY(21, x); cout << "  ";
			x--;
			gotoXY(21, x); cout << "->";
			menu_item--;
			continue;
		}
		if (GetAsyncKeyState(VK_RETURN))// Enter key pressed
		{
			switch (menu_item)
			{
				case 0:
				{
					AddReport();
					exit(0);
				}
				case 1:
				{
					SearchReport();
					running = false;
					break;
				}
				case 2:
				{
					EditStatusReport();
					exit(0);
				}
				case 3:
				{
					DeleteReport();
					exit(0);
				}
				case 4:
				{
					statisticGraph(); 
					exit(0);
				}
				case 5:
				{
					profileInformation();
					exit(0);
				}
				case 6:
				{
					Logout();
					exit(0);
				}
			}
		}
	}
}

void AddReport()
{
	system("cls");
	Accident* accident = new Accident();
	AccidentManager accidentManager;
	DriverManager driverManager;
	PoliceManager policeManager;
	ReportManager reportManager;
	StationManager stationManager;
	VehicleManager vehicleManager;

	/*
	* Police fill up the accident details
	*/
	int IdAccident, m = 0;
	string peopleInvolve;

	cout << "\n\n\n\t\t=================================== " << endl;
	cout << "\t\t   Accident Information Providers" << endl;
	cout << "\t\t        Add Accident Details " << endl;
	cout << "\t\t=================================== " << endl;
	IdAccident = accidentManager.lastId();										//to get Accident Id
	cout << "\n\t\tAccident Id = " << IdAccident << "-AIP" << endl;				//display accident id

	char strAIP[10] = "-AIP";
	char IdAcc[20];
	itoa(IdAccident, IdAcc, 10);												//change int to char
	strcat(IdAcc, strAIP);														//copy string with -AIP

	while (m == 0)
	{
		cout << "\t\tEnter number people that involve in accident = ";					//ask for people involve
		cin.ignore(0, '\n');
		getline(cin, peopleInvolve);
		for (int n = 0; n < peopleInvolve.size(); n++)
		{
			if (peopleInvolve[n] >= '0' && peopleInvolve[n] <= '9')		//check if all number phone is in numberic
			{
				m = 1;
			}
			else
			{
				m = 0;
				cout << "\t\tEnter numberic only!!" << endl;					//if has alphabetic or symbol it will ask user to cin again
				break;
			}
		}
	}
	accident->accidentPeopleInvolve = peopleInvolve;
	cout << "\t\tStreet name = ";
	cin.ignore(0, '\n');
	getline(cin, accident->accidentStreetName );
	cout << "\t\tState name = ";
	cin.ignore(0, '\n');
	getline(cin, accident->accidentState);
	accident->accidentTotalCost = 0;
	accident->accidentId = IdAcc;
	accidentManager.insertAccident(accident);				//save data accident details in mySQL
	
	int totalCost=0;
	reportDetails(IdAcc, totalCost);					//go to report() to fill up details and get total cost
	accidentManager.updateCostTotal(totalCost, IdAcc);			//update total cost for an accident
	cout << "\t\t";
	system("pause");
	system("cls");
	cout << "\n\n\n\t\t=================================== " << endl;
	cout << "\t\t   Accident Information Providers" << endl;
	cout << "\t\t      Display Accident Details " << endl;
	cout << "\t\t=================================== " << endl;
	reportManager.displayReport(IdAcc);			//display accident report with details lps dh save everything
	
	cout << "\t\t";
	system("pause");
	system("cls");
	MenuProgram();								//if done, it will go back to menu program
}

int reportDetails(char IdAcc[20], int& totalCost)
{
	cout << "\t\t";
	system("pause");
	system("cls");
	int idReport;
	Report* report = new Report();
	ReportManager reportManager;
	cout << "\n\n\n\t\t=================================== " << endl;
	cout << "\t\t   Accident Information Providers" << endl;
	cout << "\t\t        Add Report Details" << endl;
	cout << "\t\t=================================== " << endl;

	idReport = reportManager.lastIdReport();
	cout << "\n\t\tReport Id = " << idReport << "-Rep" << endl;
	char strRep[10] = "-Rep";
	char IdRep[20];
	itoa(idReport, IdRep, 10);
	strcat(IdRep, strRep);

	time_t t = time(NULL);
	tm* timePtr = localtime(&t);
	int Date, Time, hour, min, sec, year, month, day;
	Date = ((timePtr->tm_year) + 1900) * 10000 + ((timePtr->tm_mon) + 1) * 100 + (timePtr->tm_mday);
	Time = ((timePtr->tm_hour)) * 10000 + ((timePtr->tm_min)) * 100 + (timePtr->tm_sec);
	cout << "\t\tDate = " << Date << endl;
	cout << "\t\tTime = " << Time << endl;

	char const statusReport[] = "Added & Process";

	int i, a[7], cost[7], harga=0;
	string maklumat = "";
	cost[0] = 300;
	cost[1] = 150;
	cost[2] = 100;
	cost[3] = 100;
	cost[4] = 50;
	cost[5] = 70;
	cost[6] = 40;
	char costDetail[7][1000] = { "First category (taxi) = All type vehicle including motorcycle",
	"Second Category (Active faults) = All type vehicle",
	"Second Category (Active faults) = Motorcycle under 250cc",
	"Third Category (Passive faults) = All type vehicle",
	"Third Category (Passive faults) = Motorcycle under 250cc",
	"Others category = All type vehicle",
	"Others category = Motorcycle under 250cc" };
	
	AccidentCost(a);
	for (i = 0; i < 7; i++)
	{
		if (a[i] != 0)
		{
			totalCost += cost[i];			//to get total cost
			maklumat = costDetail[i];
			harga = cost[i];
		}
	}
	report->accidentId = IdAcc;
	report->policeId = PoliceId;
	report->reportDate = Date;
	report->reportId = IdRep;
	report->reportStatus = statusReport;
	report->reportTime = Time;
	report->reportDetails = maklumat;
	report->reportCost = harga;
	reportManager.insertReport(report);

	driverDetails(IdRep);

	char pilihanReport;
	cout << "\n\t\t1. Add new report" << endl;
	cout << "\t\t2. Done" << endl;
	cout << "\t\tYour choice = ";
	cin >> pilihanReport;
	
	while (pilihanReport != '1' && pilihanReport != '2')		//if user enter others number beside 1 and 2
	{
		cout << "\t\tYou enter wrong number" << endl;
		cout << "\n\t\t1. Add new report" << endl;
		cout << "\t\t2. Done" << endl;
		cout << "\t\tYour choice = ";
		cin >> pilihanReport;
	}
	if (pilihanReport == '1')
	{
		reportDetails(IdAcc, totalCost);					//will go again to report details()
	}

	return totalCost;
}

void vehicleDetails(string nameDriver, char IdRep[20])
{
	Vehicle* vehicle = new Vehicle();
	VehicleManager vehicleManager;

	string numberPlate;
	int e,f=0;
	while (f == 0)
	{
		cin.ignore(0, '\n');
		cout << "\n\t\tVehicle plate number : ";
		getline(cin, numberPlate);
		for (e = 0; e < numberPlate.size(); e++)					//to validate vehicle number plate. if user enter symbol it will ask user to enter again
		{
			if (numberPlate[e] >= '0' && numberPlate[e] <= '9' || numberPlate[e] >= 'A' && numberPlate[e] <= 'Z' || numberPlate[e] >= 'a' && numberPlate[e] <= 'z')
			{
				f = 1;
			}
			else
			{
				f = 0;
				cout << "\t\tEnter number and alphabetics only!!" << endl;
				break;
			}
		}
	}
	
	string ownerName;
	int b = 0;
	char optionOwnerName;
	while (b == 0)
	{
		cout << "\t\t1. Owner vehicle Name same like driver's name" << endl;
		cout << "\t\t2. Other name" << endl;
		cout << "\t\tOption : ";
		cin >> optionOwnerName;
		if (optionOwnerName != '1' && optionOwnerName != '2')				//if user not enters 1 and 2
		{
			b = 0;
			cout << "\t\tPlease enter correct number!!" << endl;
		}
		else
		{
			b = 1;
			if (optionOwnerName == '1')
			{
				ownerName = nameDriver;
				cout << "\t\tOwner vehicle name = " << ownerName << endl;
			}
			else
			{
				cin.ignore(1, '\n');
				cout << "\t\tOwner vehicle name = ";
				getline(cin, ownerName);
			}
			break;
		}
	}

	vehicle->vehicleNum = numberPlate;
	vehicle->vehicleOwnerName = ownerName;
	vehicle->reportId = IdRep;
	vehicleManager.insertVehicle(vehicle);
}

void driverDetails(char IdRep[20])
{
	Drive* drive = new Drive();
	DriverManager driverManager;

	string nameDriver;
	cin.ignore(1, '\n');
	cout << "\n\t\tDriver name = ";
	getline(cin, nameDriver);

	//validate ic is correct or not
	int a = 0, bulanIc = 0, hariIc = 0, tahunIc = 0, tahunKini = 0, tahunLompat = 0;
	string icNumber;
	time_t t = time(NULL);
	tm* timePtr = localtime(&t);
	while (a == 0)
	{
		cout << "\t\tIdentity Card number(without '-') = ";
		cin.ignore(0, '\n');
		getline(cin, icNumber);
		if (icNumber.size() != 12)			//will detect ic enough digit or not
		{
			a == 0;
			cout << "\t\tPlease insert 12 digit numbers only!!" << endl;
		}
			
		else
		{
			for (int i = 0; i < icNumber.size(); i++)				
			{
				if (icNumber[i] >= '0' && icNumber[i] <= '9')				//check semua ic nombor atau tak
				{
					a = 1;
					if (i == 0)												//to get year from ic
					{
						tahunIc = ((int)icNumber[i] - 48) * 10;
					}
					if (i == 1)
					{
						tahunIc = tahunIc + ((int)icNumber[i] - 48);
						tahunKini = ((timePtr->tm_year) + 1900);
						if ((tahunIc + 2000) > tahunKini)
						{
							tahunIc += 1900;
						}
						else
							tahunIc += 2000;
						tahunLompat = tahunIc % 4;
					}
					if (i == 2)												//check bulan betul ke tak
					{
						bulanIc = (((int)icNumber[2] - 48) * 10);
					}
					if (i == 3)
					{
						bulanIc = bulanIc + ((int)icNumber[3] - 48);
						if (bulanIc < 1 || bulanIc > 12)
						{
							a = 0;	//kalau bulan lebih 12 atau kurang 1 akan keluar error message
						}
					}
					if (i == 4)												//check hari
					{
						hariIc = (((int)icNumber[i] - 48) * 10);
					}
					if (i == 5)
					{
						hariIc = hariIc + ((int)icNumber[i] - 48);
						if (bulanIc == 2)
						{
							if (tahunLompat == 0)
							{
								if (hariIc > 29 || hariIc < 0)
								{
									a = 0;
								}
							}
							else
							{
								if (hariIc > 28 || hariIc < 0)
								{
									a = 0;
								}
							}
						}
						if (bulanIc == 4 || bulanIc == 6 || bulanIc == 9 || bulanIc == 11)
						{
							if (hariIc > 30 || hariIc < 1)
							{
								a = 0;
							}
						}
						else
						{
							if (hariIc > 31 || hariIc < 1)				
							{
								a = 0;
							}
						}
					}
					if (a == 0)
					{

						cout << "\t\tPlease insert the correct number ic" << endl;
						break;
					}
				}
				else
				{
					a = 0;
					cout << "\t\tPlease insert numbers only!!" << endl;
				}
			}

		}
	}

	//to fix the age of driver
	int age=0;
	age = tahunKini - tahunIc;
	cout << "\t\tDriver age = " << age << endl;

	//to fix the sex of driver
	int noAkhirIc = icNumber[11];
	string sex = "";
	if (noAkhirIc % 2 == 0)
	{
		sex = "Woman";
	}
	else
	{
		sex = "Man";
	}
	cout << "\t\tDriver sex = " << sex << endl;

	drive->driverName = nameDriver;
	drive->driverAge = age;
	drive->driverId = icNumber;
	drive->driverSex = sex;
	drive->reportId = IdRep;
	driverManager.insertDriver(drive);

	vehicleDetails(nameDriver, IdRep);
}

void AccidentCost(int* a)				//to get total cost for each report
{
	int i, cost[7];
	char pilihan;
	
	char CostDetail[7][1000] = { " First category (taxi) = All type vehicle including motorcycle",
	"Second Category (Active faults) = All type vehicle",
	"Second Category (Active faults) = Motorcycle under 250cc",
	"Third Category (Passive faults) = All type vehicle",
	"Third Category (Passive faults) = Motorcycle under 250cc",
	"Others category = All type vehicle",
	"Others category = Motorcycle under 250cc" };
	
	for (i = 0; i < 7; i++)
	{
		a[i] = 0;
		cost[i] = 0;
	}

	cout << "\n\t\tAccident Cost" << endl;					//display cost category
	cout << "\t\t1. First category (taxi) " << endl;
	cout << "\t\t2. Second Category (Active faults = driver negative behaviour or vehicle technical faults)" << endl;
	cout << "\t\t3. Third Category (Passive faults = vehicles technical faults)" << endl;
	cout << "\t\t4. Others category" << endl;
	cout << "\t\tOption : ";
	cin >> pilihan;

	switch (pilihan)
	{
		case '1':
		{
			char num1;
			cout << "\t\tFirst category (taxi) " << endl;
			cout << "\t\tAll type vehicle including motorcycle = RM 300" << endl;
			cost[0] = 300;
			cout << "\t\tAre you sure want to add this compaund to this accident report. If Yes press 1 otherwise press any numbers : ";
			cin >> num1;
			if (num1 == '1')
			{
				a[0]++;
			}
			else
				AccidentCost(a);
			break;
		}
		case '2':
		{
			char secondCategory;
			cout << "\t\tSecond Category (Active faults = driver negative behaviour or vehicle technical faults)" << endl;
			cout << "\t\t1. All type vehicle" << endl;
			cout << "\t\t2. Motorcycle under 250cc" << endl;
			cout << "\t\tEnter number 1 or 2 otherwise back to Accident cost Menu : ";
			cin >> secondCategory;
			cost[1] = 150;
			cost[2] = 100;
			switch (secondCategory)
			{
				case '1':
				{
					char num2;
					cout << "\t\tAre you sure want to add this compaund to this accident report. If Yes press 1 otherwise press any numbers : ";
					cin >> num2;
					if (num2 == '1')
					{
						a[1]++;
					}
					else
						AccidentCost(a);
					break;
				}
				case '2':
				{
					char num3;
					cout << "\t\tAre you sure want to add this compaund to this accident report. If Yes press 1 otherwise press any numbers : ";
					cin >> num3;
					if (num3 == '1')
					{
						a[2]++;
					}
					else
						AccidentCost(a);			
					break;
				}
				default:
				{
					AccidentCost(a);
					break;
				}
				break;
			}
			break;
		}
		case '3':
		{
			char thirdCategory;
			cout << "\t\tThird Category (Passive faults = driver negative behaviour or vehicle technical faults)" << endl;
			cout << "\t\t1. All type vehicle" << endl;
			cout << "\t\t2. Motorcycle under 250cc" << endl;
			cout << "\t\tEnter number 1 or 2 otherwise back to Accident cost Menu : ";
			cin >> thirdCategory;
			cost[3] = 100;
			cost[4] = 50;
			switch (thirdCategory)
			{
				case '1':
				{
					char num4;
					cout << "\t\tAre you sure want to add this compaund to this accident report. If Yes press 1 otherwise press any numbers : ";
					cin >> num4;
					if (num4 == '1')
					{
						a[3]++;
					}
					else
						AccidentCost(a);
					break;
				}
				case '2':
				{
					char num5;
					cout << "\t\tAre you sure want to add this compaund to this accident report. If Yes press 1 otherwise press any numbers : ";
					cin >> num5;
					if (num5 == '1')
					{
						a[4]++;
					}
					else
						AccidentCost(a);
					break;
				}
				default:
				{
					AccidentCost(a);
					break;
				}
				break;
			}
			break;
		}
		case '4':
		{
			char fourthCategory;
			cout << "\t\tOther Category" << endl;
			cout << "\t\t1. All type vehicle" << endl;
			cout << "\t\t2. Motorcycle under 250cc" << endl;
			cout << "\t\tEnter number 1 or 2 otherwise back to Accident cost Menu : ";
			cin >> fourthCategory;
			cost[5] = 70;
			cost[6] = 40;
			switch (fourthCategory)
			{
				case '1':
				{
					char num6;
					cout << "\t\tAre you sure want to add this compaund to this accident report. If Yes press 1 otherwise press any numbers : ";
					cin >> num6;
					if (num6 == '1')
					{
						a[5]++;
					}
					else
						AccidentCost(a);
					break;
				}
				case '2':
				{
					char num7;
					cout << "\t\tAre you sure want to add this compaund to this accident report. If Yes press 1 otherwise press any numbers : ";
					cin >> num7;
					if (num7 == '1')
					{
						a[6]++;
					}
					else
						AccidentCost(a);
					break;
				}
				default:
				{
					AccidentCost(a);
					break;
				}
				break;
			}
			break;
		}
		default:
		{
			cout << "\t\tYou entered wrong number!!" << endl;
			AccidentCost(a);
			break;
		}
		break;
	}
}

void SearchReport()
{
	system("cls");
	ReportManager reportManager;
	DriverManager driverManager;
	cout << "\n\n\n\t\t=================================== " << endl;
	cout << "\t\t    Accident Information Providers" << endl;
	cout << "\t\t      Search Accident Report " << endl;
	cout << "\t\t=================================== " << endl;

	char searchId, searchOption;
	cout << "\t\t1. Search by id report " << endl;
	cout << "\t\t2. Search by Ic number" << endl;
	cout << "\t\t3. Back to menu" << endl;
	cout << "\t\tOption = ";
	cin >> searchId;

	string searchIdReport, searchSymbol = "%", searchDriverIc;
	switch (searchId)
	{
		case '1':
		{
			cin.ignore(1, '\n');
			cout << "\t\tInsert ID Report : ";
			getline(cin, searchIdReport);
			if (!(reportManager.confirmReportId(searchIdReport)))				//it will search id report in database
			{
				cout << "\t\tYour entered wrong id report!!\n\t\tPlease put in format(XXXXX-Rep)\n\n\t\t";
				system("pause");
				SearchReport();
				break;
			}
			else
			{
				reportManager.displaySearchReport(searchIdReport);
				cout << "\n\t\tDo you want to search again ?? If YES(Press 1), NO(Press any number) " << endl;
				cout << "\t\tOption = ";
				cin >> searchOption;
				if (searchOption == '1')
				{
					SearchReport();
				}
				else
				{
					MenuProgram();
				}
				break;
			}
			break;
		}
		case '2':
		{
			cin.ignore(1, '\n');
			cout << "\t\tInsert ic number : ";
			getline(cin, searchDriverIc);
			if (!(driverManager.searchDriverName(searchDriverIc)))						//it will search in database at table driver
			{
				cout << "\t\tDriver's ic number that you inserted did not found in data. Please insert again\n\t\t";
				system("pause");
				SearchReport();
				break;
			}
			else
			{
				cout << "\n\t\tDo you want to search again ?? If YES(Press 1), NO(Press any number) " << endl;
				cout << "\t\tOption = ";
				cin >> searchOption;
				if (searchOption == '1')			//if user want to continue search
				{
					SearchReport();
				}
				else
				{
					MenuProgram();
				}
			}
			break;
		}
		case '3':						//if usser want to go back to menu
		{
			MenuProgram();
			break;
		}
		default:
		{
			cout << "\t\tEntered the right number!!\n\t\t";
			system("pause");
			SearchReport();
			break;
		}
	}
}

void EditStatusReport()
{
	system("cls");
	ReportManager reportManager;
	string searchIdReport;
	char editOption, editStatus;
	int j = 0, l=0, z=0;
	char k;
	
	time_t t = time(NULL);
	tm* timePtr = localtime(&t);
	int DateEditStatus, TimeEditStatus;
	DateEditStatus = ((timePtr->tm_year) + 1900) * 10000 + ((timePtr->tm_mon) + 1) * 100 + (timePtr->tm_mday);
	TimeEditStatus = ((timePtr->tm_hour)) * 10000 + ((timePtr->tm_min)) * 100 + (timePtr->tm_sec);

	cout << "\n\n\n\t\t=================================== " << endl;
	cout << "\t\t    Accident Information Providers" << endl;
	cout << "\t\t     Edit Accident Status Report " << endl;
	cout << "\t\t=================================== " << endl;

	cin.ignore(1, '\n');
	cout << "\n\t\tInsert ID Report : ";
	getline(cin, searchIdReport);
	if (!(reportManager.confirmReportId(searchIdReport)))
	{
		cout << "\t\tYour entered wrong id report!!\n\t\tPlease put in format(XXXXX-Rep)\n\n\t\t";
		system("pause");
		EditStatusReport();
	}
	else
	{
		reportManager.displaySearchReport(searchIdReport);
		while (z == 0)
		{
			cout << "\t\t1. Want change status report " << endl;
			cout << "\t\t2. Back to menu" << endl;
			cout << "\t\tPlease choose the number = ";
			cin >> editOption;
			switch (editOption)
			{
				case '1':				//if user want to continue searching
				{
					while (j == 0)
					{
						z = 1;
						Report* report = new Report();
						cout << "\n\n\n\t\tChoose one status that you want to change the status " << endl;
						cout << "\t\t1. In investigation" << endl;
						cout << "\t\t2. Completed" << endl;
						cout << "\t\t3. Go back menu" << endl;
						cout << "\t\tOption = ";
						cin >> editStatus;
						if (editStatus == '1' || editStatus == '2')
							{
							j = 1;
							if (editStatus == '1')
							{
								report->reportStatus = "In investigation";
							}
							if (editStatus == '2')
							{
								report->reportStatus = "Completed";
							}
							report->reportId = searchIdReport;
							report->policeId = PoliceId;				
							report->reportDate = DateEditStatus;
							report->reportTime = TimeEditStatus;
							reportManager.updateReport(report);		//update in database at table report

							system("cls");
							cout << "\n\n\n\t\t=================================== " << endl;
							cout << "\t\t    Accident Information Providers" << endl;
							cout << "\t\t     Edit Accident Status Report " << endl;
							cout << "\t\t=================================== " << endl;
							reportManager.displaySearchReport(searchIdReport);				//display again report that have been changed
							
							while (l == 0)
							{
								cout << "\n\t\t1. If want to change status for others report" << endl;
								cout << "\t\t2. If want back to menu" << endl;
								cout << "\t\tOption : ";
								cin >> k;
								if (k == '1')
								{
									EditStatusReport();
									l = 1;
									break;
								}
								if (k == '2')
								{
									system("cls");
									MenuProgram();
									l = 1;
									break;
								}
								else
								{
									l = 0;
									cout << "\t\tYou insert wrong number!!" << endl;
								}
							}
							break;
						}
						if (editStatus == '3')
						{
							j = 1;
							system("cls");
							MenuProgram();
							break;
						}
						else
						{
							j = 0;
							cout << "\t\tInsert the right number!!" << endl;
						}
					}
				}
				case '2':					//if user want to go back to menu program
				{
					z = 1;
					system("cls");
					MenuProgram();
					break;
				}
				default:
				{
					z = 0;
				}
			}
		}
	}	
}

void DeleteReport()
{
	system("cls");
	ReportManager reportManager;
	DriverManager driveManager;
	VehicleManager vehicleManager;
	string deleteIdReport;
	int d = 0, h=0;
	char deleteOption, g;
	cout << "\n\n\n\t\t=================================== " << endl;
	cout << "\t\t    Accident Information Providers" << endl;
	cout << "\t\t             Delete Report " << endl;
	cout << "\t\t=================================== " << endl;
	cin.ignore(1, '\n');
	cout << "\t\tInsert ID Report : ";
	getline(cin, deleteIdReport);
	if (!(reportManager.confirmReportId(deleteIdReport)))
	{
		cout << "\t\tYour entered wrong id report!!\n\t\tPlease put in format(XXXXX-Rep)\n\n\t\t";
		system("pause");
		DeleteReport();
	}
	else
	{
		reportManager.displaySearchReport(deleteIdReport);
		while (d == 0)
		{
			cout << "\t\tDid you want to delete this report ??" << endl;
			cout << "\t\tIf YES(1), Main Menu(2) : ";
			cin >> deleteOption;
			if (deleteOption == '1')
			{
				d = 1;
				driveManager.deleteDriver(deleteIdReport);
				vehicleManager.deleteVehicle(deleteIdReport);
				reportManager.deleteReport(deleteIdReport);
				cout << "\n\t\tSuccessfully delete report id!!" << endl;
				
				while (h == 0)
				{
					cout << "\t\tIf you want to delete another report, press 1" << endl;
					cout << "\t\tIf you want to go back to Menu, press 2 " << endl;
					cout << "\t\tOption : ";
					cin >> g;

					if (g == '1')
					{
						DeleteReport();
						h = 1;
						d = 1;
					}
					if (g == '2')
					{
						h = 1;
						d = 1;
						MenuProgram();
					}
					else
					{
						cout << "\t\tEnter the right number!!" << endl;
						h = 0;
						d = 1;
					}
				}
				
				
			}
			if (deleteOption == '2')
			{
				d = 1;
				MenuProgram();
				break;
			}
			if (deleteOption != '1' && deleteOption != '2')
			{
				d = 0;
				cout << "\t\tEntered the right number!!" << endl;
			}
		}
	}
}

void profileInformation()
{
	system("cls");
	Police* police = new Police();
	PoliceManager policeManager;
	StationManager stationManager;
	

	char choosing, changeNum;
	string Name, PhoneNumber, Address, Email, StationId;
	//int status;
	cout << "\n\n\n\t\t=================================== " << endl;
	cout << "\t\t    Accident Information Providers" << endl;
	cout << "\t\t         Information Police " << endl;
	cout << "\t\t=================================== " << endl;

	policeManager.selectPolice(PoliceId);

	cout << "\n\t\t1. Want change information " << endl;
	cout << "\t\t2. Back to menu" << endl;
	cout << "\t\tPlease choose the number = ";
	cin >> choosing;

	switch (choosing)
	{
		case '1':
		{
			cout << "\n\t\t1. Name" << endl;
			cout << "\t\t2. Phone Number" << endl;
			cout << "\t\t3. Address" << endl;
			cout << "\t\t4. Email" << endl ;
			cout << "\t\t5. Station Id" << endl;
			cout << "\t\t6. Password" << endl;
			cout << "\t\tPlease choose number of information that you want to change = ";
			cin >> changeNum;

			switch (changeNum)
			{
				case '1':
				{
					cin.ignore(1, '\n');
					cout << "\t\tPlease enter new name = ";
					getline(cin, Name);
	
					int status1 = policeManager.updateName(Name, PoliceId);
					if (status1 != 0)
					{
						cout << "\t\tSuccessfully update your name in system.\n\t\t";

						system("pause");
						system("cls");
						profileInformation();
					}
					else
						cout << "\t\tUnable to update your name in system." << endl;
					break;
				}
				
				case '2':
				{
					int m = 0;
					while (m == 0)
					{
						cout << "\t\tPhone Number : +601";						//enter number fon
						cin.ignore(0, '\n');
						getline(cin, PhoneNumber);
						if (PhoneNumber.size() != 8 && PhoneNumber.size() != 9)			//check either phone number enough 8 / 9 digits or not
						{
							m = 0;
							cout << "\t\tPlease insert 8 / 9 digits number!!" << endl;				// if not it will repeat again
						}
						else
						{
							for (int n = 0; n < PhoneNumber.size(); n++)
							{
								if (PhoneNumber[n] >= '0' && PhoneNumber[n] <= '9')		//check if all number phone is in numberic
								{
									m = 1;
								}
								else
								{
									m = 0;
									cout << "\t\tEnter numberic only!!" << endl;					//if has alphabetic or symbol it will ask user to cin again
									break;
								}
							}
						}
					}
				}
				
				case '3':
				{
					cin.ignore(1, '\n');
					cout << "\t\tPlease enter new address = ";
					getline(cin, Address);
					int status3 = policeManager.updateAddress(Address, PoliceId);
					if (status3 != 0)
					{
						cout << "\t\tSuccessfully update your address in system.\n\t\t";
						system("pause");
						system("cls");
						profileInformation();
					}
					else
						cout << "\t\tUnable to update your address in system." << endl;
					break;
				}
				
				case '4':
				{
					cin.ignore(1, '\n');
					cout << "\t\tPlease enter new email = ";
					getline(cin, Email);
					bool ans = is_valid(Email);								//function Call to check email is valid or not
					if (!ans)
					{
						do													//will loop until the email enter with right format
						{
							cout << "\t\tPlease insert the right email!!";		// error message if don't have @ / .com
							cout << "\n\t\tEmail : ";
							cin.ignore(0, '\n');
							getline(cin, Email);
							ans = is_valid(Email);
						} while (!ans);
					}
					int status4 = policeManager.updateEmail(Email, PoliceId);
					if (status4 != 0)
					{
						cout << "\t\tSuccessfully update your email in system.\n\t\t";
						system("pause");
						system("cls");
						profileInformation();
					}
					else
						cout << "\t\tUnable to update your email in system." << endl;
					break;
				}
				
				case '5':
				{
					cin.ignore(1, '\n');
					cout << "\t\tPlease enter new station id = ";
					getline(cin, StationId);
					while (!(stationManager.confirmStationId(StationId)))				//to identify if station id had registered or not
					{
						cout << "\n\t\tYou entered wrong Station Id!!\n";
						cout << "\t\tPlease make sure you put BP infront of Station Id!!\n";
						cout << "\t\tList Police Station with Id in Malaysia : \n";
						cout << "\t\t========================================================================================================================" << endl;
						cout << "\t\t| " << setw(10) << "Station Id" << " | " << setw(18) << "Station Name" << "        | " << setw(13) << "Station City" << " | " << setw(37) << "Station Address" << "\t                 | " << endl;
						cout << "\t\t========================================================================================================================" << endl;
						stationManager.selectStation();									// display semua station
						cout << "\t\t========================================================================================================================" << endl;
						cout << "\t\tPolice Station Id : ";
						cin.ignore(0, '\n');
						getline(cin, StationId);
					}
					int status5 = policeManager.updateStationId(StationId, PoliceId);
					if (status5 != 0)
					{
						cout << "\t\tSuccessfully update your station id in system.\n\t\t";
						system("pause");
						system("cls");
						profileInformation();
					}
					else
						cout << "\t\tUnable to update your station id in system." << endl;
					break;
				}
				case '6':
				{
					char newPass[30];
					passWord(newPass);
					int status6 = policeManager.updatePassword(newPass, PoliceId);
					if (status6 != 0)
					{
						cout << "\n\t\tSuccessfully update your password in system.\n\t\t";
						system("pause");
						system("cls");
						profileInformation();
					}
					else
						cout << "\t\tUnable to update your password in system." << endl;
					break;
				}
			default:
				{
					cout << "\t\tYou entered wrong numbered\n\t\t";
					system("pause");
					system("cls");
					profileInformation();
					break;
				}	
			}
		break;
		}
		case '2':
		{
			system("cls");
			MenuProgram();
			break;
		}
		default:
		{
			cout << "\t\tYou entered wrong number!!\n\t\t";
			system("pause");
			profileInformation();
			break;
		}
	}
	
}

void gotoXY(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

void statisticGraph()
{
	system("cls");
	//variable 
	ReportManager reportManager;
	int month, year;
	cout << "\n\n\n\t\t\t\t\t=========================================\n";
	cout << "\t\t\t\t\t    Accident Information Providers System\n";
	cout << "\t\t\t\t\t           Statistic Report Monthly" << endl;
	cout << "\t\t\t\t\t=========================================" << endl;
	cout << "\n\t\t\t\tThis is table for this month report in Malaysia" << endl;
	cout << "\n\t\t\t  ___________________________________________________________________________________";
	cout << "\n\t\t\t | " << setw(4) << "Num." << " | " << setw(10) << "Report Id" << " | " << setw(10) << "Report Date" << " | " << setw(20) << "Report Details" << " | " << setw(10) << "Accident Id" << " | " << setw(10) << "Police Id" << " | ";
	cout << "\n\t\t\t |-----------------------------------------------------------------------------------|";
	time_t t = time(NULL);
	tm* timePtr = localtime(&t);
	month = (timePtr->tm_mon) + 1;
	year = (timePtr->tm_year) + 1900;
	reportManager.DisplayGraph(month, year);			//will go reportManager.h
	cout << "\n\t\t\t";
	system("pause");
	MenuProgram();
}