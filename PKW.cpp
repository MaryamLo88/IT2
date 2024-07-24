// file:	PKW.cpp
// author:	Abd Alhadi Kamrddin
// date:	01.11.2023

#include "PKW.h"

#include <iomanip>
#include <iostream>

using namespace std;


PKW::PKW()
	: Fahrzeug()
{
}

PKW::PKW(const PKW& rhs)
	: Fahrzeug(rhs), p_dVerbrauch(rhs.p_dVerbrauch), p_dTankvolumen(rhs.p_dTankvolumen), p_dTankinhalt(rhs.p_dTankinhalt)
{
}

PKW::PKW(const string sName, const double dMaxGeschwindigkeit, const double dVerbrauch)
	: Fahrzeug(sName, dMaxGeschwindigkeit), p_dVerbrauch(dVerbrauch), p_dTankvolumen(55), p_dTankinhalt(55.0 / 2)
{
}

PKW::PKW(const string sName, const double dMaxGeschwindigkeit, const double dVerbrauch, const double dTankvolumen)
	: Fahrzeug(sName, dMaxGeschwindigkeit), p_dVerbrauch(dVerbrauch), p_dTankvolumen(dTankvolumen), p_dTankinhalt(dTankvolumen / 2)
{
}

PKW::~PKW()
{
}

void PKW::vAusgeben() const
{
	Fahrzeug::vAusgeben();
	cout << setprecision(2) << resetiosflags(ios::left) << setiosflags(ios::right)
		<< "  " << setw(12) << dVerbrauch() << " " << setw(12) << p_dTankinhalt;
}

ostream& PKW::ostreamAusgabe(ostream& out) const
{
	Fahrzeug::ostreamAusgabe(out) << setprecision(2) << resetiosflags(ios::left) << setiosflags(ios::right)
		<< "  " << setw(12) << dVerbrauch() << " " << setw(12) << p_dTankinhalt;
	return out;
}

void PKW::vAbfertigung()
{
	// PKWs fahren nur, wenn Kraftstoff vorhanden ist
	if (p_dTankinhalt > 0)
	{
		double dGesamtStreckeTemp = p_dGesamtStrecke; // Streckenz�hler zwischenspeichern

		Fahrzeug::vAbfertigung(); // Fahrzeug fahren lassen

		p_dTankinhalt -= (p_dGesamtStrecke - dGesamtStreckeTemp) * p_dVerbrauch / 100; // Verbrauch nachrechnen

		if (p_dTankinhalt < 0) p_dTankinhalt = 0; // keine negativen F�llst�nde zulassen
	}
}

double PKW::dVerbrauch() const
{
	return (p_dGesamtStrecke * p_dVerbrauch / 100);
}

double PKW::dTanken(double dMenge)
{
	double dMaxTankbar = p_dTankvolumen - p_dTankinhalt;

	if ( (dMenge != -1.0) && (dMenge < dMaxTankbar) )
	{
		// Normaler Tankvorgang
		p_dTankinhalt += dMenge;
	}
	else
	{
		// Volltanken
		dMenge = dMaxTankbar;
		p_dTankinhalt = p_dTankvolumen;
	}

	return dMenge;
}

PKW& PKW::operator = (const PKW& rhs)
{
	Fahrzeug::operator=(rhs);
	p_dVerbrauch = rhs.p_dVerbrauch;
	p_dTankvolumen = rhs.p_dTankvolumen;
	p_dTankinhalt = rhs.p_dTankinhalt;
	return *this;
}



/**
 * @fn void vSimulieren()
 * @brief
 *
 */

void PKW::vSimulieren() {
    // Überprüfen, ob der PKW noch Kraftstoff im Tank hat
    if (p_dTankinhalt > 0.0) {
        double globaleZeit = dGlobaleZeit;

        // Berechnen Sie die verstrichene Zeit seit dem letzten Simulationszeitpunkt
        double deltaTime = globaleZeit - p_dZeit;

        // Berechnen Sie die zurückgelegte Strecke mit maximaler Geschwindigkeit
        double zurueckgelegteStrecke = p_dMaxGeschwindigkeit * deltaTime;

        // Aktualisieren Sie die Gesamtstrecke
        p_dGesamtStrecke += zurueckgelegteStrecke;

        // Berechnen Sie den Verbrauch während dieser Zeit
        double verbrauch = zurueckgelegteStrecke * p_dVerbrauch / 100.0;

        // Reduzieren Sie den Tankinhalt um den Verbrauch
        p_dTankinhalt -= verbrauch;

        // Stellen Sie sicher, dass der Tankinhalt nicht negativ wird
        if (p_dTankinhalt < 0.0) {
            p_dTankinhalt = 0.0;
        }

        // Aktualisieren Sie die Zeit
        p_dZeit = globaleZeit;
    }
}

