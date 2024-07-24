#pragma once
#include "Verhalten.h"
#include "Streckenende.h"
class Fahren :
    public Verhalten
{
public: 
    Fahren(Weg& weg); 
    virtual ~Fahren(); 
    double dStrecke(Fahrzeug& aFzg, double dZeitIntervall);

};

