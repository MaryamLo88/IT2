#pragma once
#include "Fahrausnahme.h"
#include "Weg.h"
class Losfahren :
    public Fahrausnahme
{
public: 
    void vBearbeiten() override;
    virtual ~Losfahren(); 
    Losfahren(Fahrzeug& fahrzeug, Weg& weg); 

};

/*Diese Funktion gibt die Exception bzw. Ausnahme,
dass ein Wagen zu einem bestimmten Zeitpunkt losfährt.
P.s.: Hier wird nur eine Meldung ausgegeben.
*/
