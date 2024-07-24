#pragma once
#include "Weg.h"
#include "Fahrzeug.h"
class Verhalten
{
public: 
	virtual ~Verhalten(); 
	Verhalten(Weg& weg); 
	virtual double dStrecke(Fahrzeug& aFzg, double dZeitIntervall);
	//Weg* getWeg()const;
	double dGeschwindigkeitslimit();

protected: 
	Weg& p_pWeg;

};

/*
 * Abstrakte Oberklasse für das Verhalten der Wagen (Fahren/Parken).
 *
 * [Siehe Fahren.cpp, Parken.cpp]
 *
 */
