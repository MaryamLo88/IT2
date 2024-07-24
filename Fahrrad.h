#pragma once
#include "Fahrzeug.h"
class Fahrrad :
    public Fahrzeug
{
public : 
    Fahrrad();
    virtual ~Fahrrad(); 
    Fahrrad(string Name, double MaxGeschwindigkeit);
    double dGeschwindigkeit() const override ; 

};

