#include "Fahren.h"
#include "Weg.h"

Fahren::Fahren(Weg& weg) : Verhalten(weg)
{

}

Fahren::~Fahren()
{

}
/**
 *
 * @param aFzg
 * @param dZeitIntervall
 * @return
 *
 * @brief Diese Funktion bestimmt die bereits gefahrene und die noch zu fahrende Strecke
 *
 * Hier wird die Geschwindigkeit und die damit zu fahrende Strecke zusammengerechnet
 */
double Fahren::dStrecke(Fahrzeug& aFzg, double dZeitIntervall)
{
	if (p_pWeg.getLaenge() > aFzg.getAbschnittStrecke())
	{
		double dMoeglicheStrecke = dZeitIntervall * aFzg.dGeschwindigkeit();
		double schranke = p_pWeg.getVirtuelleSchranke();
		double dAbstandStrecke = schranke - aFzg.getAbschnittStrecke();	//die restliche Strecke eines Weges.
																		//durch die Zeile ist restliche Strecke gleich dem Abstand
																		//zwischen dem ersten Fahrzeug und dem naechsten.
		if (dMoeglicheStrecke <= dAbstandStrecke)
		{
			p_pWeg.setVirtuelleSchranke(dMoeglicheStrecke+aFzg.getAbschnittStrecke());
			return dMoeglicheStrecke;
		}
		return dAbstandStrecke;
	}
	else
	{
		cout << " " << aFzg.getName() << " ist am Ende des Weges angekommen" << endl;
		Streckenende* streckenende= new Streckenende(aFzg,p_pWeg);
		throw streckenende; 
	}
}
