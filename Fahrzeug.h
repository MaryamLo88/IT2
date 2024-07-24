#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include "Simulationsobjekt.h"
#include "Weg.h"

class Verhalten; 
class Fahren;
class Parken; 
using namespace std;

extern double dGlobaleZeit ;

class Fahrzeug : public Simulationsobjekt
{
public:
	Fahrzeug(string Name);//Konstruktor mit Parameter
	Fahrzeug();//Standardkonstruktor 
	Fahrzeug(string Name, double MaxGeschwindigkeit);
	virtual ~Fahrzeug();//Destruktor 
	virtual void vAusgeben(ostream& o = cout)const;
	static void vKopf();
	virtual void vSimulieren();
	virtual double dTanken(double dMenge = numeric_limits<double>::infinity());
	virtual double dGeschwindigkeit() const;
	bool operator<(const Fahrzeug& fahrzeug)const;
	Fahrzeug(const Fahrzeug&) = delete;
	virtual Fahrzeug& operator=(const Fahrzeug& fahrzeug);
	void vNeueStrecke(Weg& weg);
	void vNeueStrecke(Weg& weg, double dStartzeitpunkt);
	double getAbschnittStrecke(); 
	virtual void vZeichnen(Weg& weg) const;

protected:
	double p_dMaxGeschwindigkeit = 0;
	double p_dGesamtStrecke = 0;
	double p_dGesamtZeit = 0;
	double p_dAbschnittStrecke = 0;
	double p_dStreckeGefahren = 0; 
	//Verhalten* p_pVerhalten = nullptr;
	unique_ptr<Verhalten> p_pVerhalten;
	//Weg* p_paWeg; // Aktueller Weg 

};


