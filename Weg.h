#pragma once
#include "Simulationsobjekt.h"
#include <list>
#include <memory>
#include "Tempolimit.h"
#include "vertagt_liste.h"
#include <string>
#include <limits>


using namespace std; 
class Fahrzeug; 
class Fahrausnahme;
class Kreuzung;

class Weg :
    public Simulationsobjekt
{
public: 
    Weg(); //Standardkonstruktor
    Weg(string Name, double Laenge, bool bUeberholverbot = true,int iTempolimit = 3);
    virtual ~Weg(); 
    double getTempolimit(); 
    virtual void vSimulieren();
    static void vKopf(); 
    void vAusgeben(ostream& o = cout)const override; 
    double getLaenge(); 
    void vAnnahme(unique_ptr<Fahrzeug> pFahrzeug); 
    void vAnnahme(unique_ptr<Fahrzeug> pFahrzeug, double dStartzeitpunkt);
    void vZeichneFahrzeuge();
    unique_ptr<Fahrzeug>pAbgabe(const Fahrzeug& fahrzeug);
    double getVirtuelleSchranke();
    void setVirtuelleSchranke(double dVirtuelleSchranke);
    void setZielKreuzung(weak_ptr<Kreuzung> pZielKreuzung);
    void setRueckWeg(weak_ptr<Weg> pRueckWeg);
    weak_ptr<Kreuzung> getZielKreuzung();
    weak_ptr<Weg> getRueckWeg();

private: 
    double p_dLaenge = 0; 
    //list<unique_ptr<Fahrzeug>> p_pFahrzeuge;
    vertagt::VListe<unique_ptr<Fahrzeug>> p_pFahrzeuge;
    Tempolimit p_eTempolimit;
    const int p_iTempolimit;
    bool p_bUeberholverbot;
    double p_dVirtuelleSchranke;
    weak_ptr<Kreuzung> p_pZielKreuzung ;
    weak_ptr<Weg> p_pRueckWeg;
};


