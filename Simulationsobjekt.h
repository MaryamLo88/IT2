#pragma once
#include <iostream>
#include <string>
#include <iomanip>
using namespace std; 
class Simulationsobjekt
{
public: 
	Simulationsobjekt(); 
	Simulationsobjekt(string Name);
	virtual ~Simulationsobjekt();
	Simulationsobjekt(const Simulationsobjekt&) = delete; 
	virtual void vAusgeben(ostream& o = cout)const; 
	bool operator==(const Simulationsobjekt& simulationsobjekt);
	virtual void vSimulieren() = 0; 
	string getName(); 
	virtual void vEinlesen(istream& i = cin);

protected: 
	string p_sName = "";//Name des Fahrzeugs
	const int p_iID;
	double p_dZeit = 0;

private: 
	static int p_iMaxID;//Zaehler

};
ostream& operator <<(ostream& o, const Simulationsobjekt& simulationsobjekt);
istream& operator >>(istream& i, Simulationsobjekt& simulationsobjekt1);


