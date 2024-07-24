#include "Verhalten.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "Fahrausnahme.h"
#include "Streckenende.h"

Verhalten::Verhalten(Weg& weg) : p_pWeg(weg)
{

}

Verhalten::~Verhalten()
{

}

double Verhalten::dStrecke(Fahrzeug& aFzg, double dZeitIntervall)
{
	return 0; 

}

double Verhalten::dGeschwindigkeitslimit()
{
	return p_pWeg.getTempolimit();
}










/*double Verhalten::dStrecke(Fahrzeug& aFahrzeug, double dZeitIntervall)
{
	if ((p_pWeg.getLaenge() - aFahrzeug.getAbschnittStrecke()) > 0)
	{
		if ((dZeitIntervall * aFahrzeug.dGeschwindigkeit()) <= (p_pWeg.getLaenge() - aFahrzeug.getAbschnittStrecke()))
		{
			return (dZeitIntervall * aFahrzeug.dGeschwindigkeit());
		}
		return (p_pWeg.getLaenge() - aFahrzeug.getAbschnittStrecke());
	}
	else
	{
		//throw Streckenende(aFahrzeug, p_pWeg);
		return 0;
	}
}*/

