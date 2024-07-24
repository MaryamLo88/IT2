#include "Fahrrad.h"
#include <cmath>

Fahrrad::Fahrrad() : Fahrzeug()
{
}

Fahrrad::~Fahrrad()
{
}

Fahrrad::Fahrrad(string Name, double MaxGeschwindigkeit) : Fahrzeug(Name,MaxGeschwindigkeit)
{
}
/**
 *
 * @return
 *
 * @brief Diese Formel dient der Berechnung der Geschwindigkeitsabnahme (Abnahme um 10%)
 * Ab 12 km/h beträgt die Geschwindigkeit bleibt die Geschwindigkeit konstant
 */
double Fahrrad::dGeschwindigkeit() const
{
	double a = p_dGesamtStrecke / 20; //pro 20km 
	double b = a; // nur bei ganzen Zahlen hochrechnen
	double dGeschwindigkeitAkt = p_dMaxGeschwindigkeit * pow(0.9, b);//Formel fuer Geschwindigkeitsabnahme

	return (dGeschwindigkeitAkt >= 12) ? dGeschwindigkeitAkt : 12; //minimal 12 km/h
}
