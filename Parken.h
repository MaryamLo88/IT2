#pragma once
#include "Verhalten.h"
#include "Losfahren.h"
class Parken :
    public Verhalten
{
public: 
    virtual ~Parken();
    Parken(Weg& weg, double dStartzeitpunkt);
    double dStrecke(Fahrzeug& aFzg, double dZeitIntervall);

private: 
    double p_dStartzeitpunkt; 

};

