#pragma once
#include <fstream> 
#include <iostream>
#include "PKW.h"
#include "Fahrrad.h"
#include "Weg.h"
#include "Kreuzung.h"
#include "vertagt_aktion.h"
#include <map>
#include <memory>
#include <vector>

using namespace std; 

class Simulation
{
public: 
	Simulation();
	virtual ~Simulation();
	void vEinlesen(istream& i, bool bMitGrafik = false);
	void vSimulieren(double dDauer, double dZeitschritt);

private: 
	map <string, shared_ptr<Kreuzung>> pKreuzungMap;
};


