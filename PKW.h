#pragma once
#include "Fahrzeug.h"
#include "SimuClient.h"
#include <limits>
#include <iomanip>

class PKW : public Fahrzeug
{
public: 
    PKW();
    PKW(string Name, double MaxGeschwindigkeit, double Verbrauch, double Tankvolumen = 55);
    virtual ~PKW();
    double dTanken(double dMenge = numeric_limits<double>::infinity()) override ; 
    void vSimulieren() override; 
    void vAusgeben(ostream& o = cout)const override; 
    PKW& operator=(const PKW& pkw);
    virtual double dGeschwindigkeit()const override ;
    virtual void vZeichnen(Weg& aWeg) const override;
    void vEinlesen(std::istream& i);
private:
    double p_dVerbrauch = 0; 
    double p_dTankvolumen = 0; 
    double p_dTankinhalt = 0; 
    
};

