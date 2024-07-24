#pragma once
#include <exception>
#include "Fahrzeug.h"
#include "Weg.h"
using namespace std; 
class Fahrausnahme : public exception
{
public: 
	Fahrausnahme(Fahrzeug& fahrzeug1, Weg& weg1);
	virtual void vBearbeiten()=0;
	
protected: 
	Fahrzeug& p_pFahrzeug1 ; 
	Weg& p_pWeg1 ; 
};

