#include "Parken.h"
#include "Losfahren.h"

Parken::~Parken()
{
}

Parken::Parken(Weg& weg, double dStartzeitpunkt) : Verhalten(weg), p_dStartzeitpunkt(dStartzeitpunkt)
{
}

/**
 *
 * @param aFzg
 * @param dZeitIntervall
 * @return
 *
 * @brief Diese Funtkion bestimmt das Verhalten der parkkenden Wagen, die zu einem
 * bestimmten Zeitpunkt (p_dStartZeitpunkt) losfahren sollen.
 */
double Parken::dStrecke(Fahrzeug& aFzg, double dZeitIntervall)
{
	if (dGlobaleZeit >= p_dStartzeitpunkt)
	{
		cout << " " << aFzg.getName() << " hat Startzeitpunkt erreicht" << endl;
		Losfahren* losfahren= new Losfahren(aFzg, p_pWeg);
		throw losfahren;
	}
	else
	{	
		return 0; 
	}
}
