#pragma once
#include "Fahrausnahme.h"
#include "SimuClient.h"
#include "Kreuzung.h"
class Streckenende :
    public Fahrausnahme
{
public: 
    void vBearbeiten() override; 
    virtual ~Streckenende(); 
    Streckenende(Fahrzeug& fahrzeug, Weg& weg);
};

