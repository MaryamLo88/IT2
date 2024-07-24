#pragma once
#include "Simulationsobjekt.h"
#include <list>
#include <memory>
#include <string>
#include "Fahrzeug.h"
#include "Tempolimit.h"
#include <random> 

class Weg; 
class Kreuzung :
    public Simulationsobjekt
{
public: 
    Kreuzung(); 
    Kreuzung(string sName,double dTank);
    virtual ~Kreuzung(); 
    static void vVerbinde(shared_ptr<Kreuzung> kreuzung1 , shared_ptr<Kreuzung> kreuzung2, string sNameH, string sNameR, double dLaenge, bool bUeberholverbot = true, int iGeschwindigkeitsBegrenzung = 3 );
    void vTanken(Fahrzeug& fahrzeug); 
    void vAnnahme(unique_ptr<Fahrzeug> pFahrzeug, double dStartzeitpunkt);
    void vSimulieren(); 
    Weg& pZufaelligerWeg(Weg& weg);
    double getTankinhalt();
    void ZeichneFahrzeuge();
    void vEinlesen(istream& i)override; 

private: 
    double p_dTankstelle; 
    list <shared_ptr<Weg>>p_pWege;
};

