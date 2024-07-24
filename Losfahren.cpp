#include "Losfahren.h"
#include "Fahrausnahme.h"
#include "Weg.h"

void Losfahren::vBearbeiten()
{
	cout << "Name des Fahrzeuges in der die Ausnahme auftitt: " << p_pFahrzeug1.getName() << endl;
	cout << "Weg auf dem sich das Fahrzeug befindet: " << p_pWeg1.getName() << endl;
	cout << "Art der Ausnahme: Losfahren " << endl;
	p_pWeg1.vAnnahme(p_pWeg1.pAbgabe(p_pFahrzeug1));
}

Losfahren::~Losfahren()
{
}

Losfahren::Losfahren(Fahrzeug& fahrzeug, Weg& weg) : Fahrausnahme(fahrzeug, weg)
{	
}
