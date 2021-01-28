#include <string>


using namespace std;

#ifndef __Reboot_h__
#define __Reboot_h__


class Reboot
{

	public: 
		Reboot();
		Reboot(int anbreReboot, string adateHeure);
		Reboot(const Reboot& orig);
		virtual ~Reboot(){};

		int getNumber();
		string getDateHour();

		void setDateHour(string adateHour);
		void setNumber(int anumber);

	private: 
		string dateHour;
		int number;
};

#endif
