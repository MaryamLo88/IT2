#include "Streckenende.h"

Streckenende::~Streckenende()
{
}

Streckenende::Streckenende(Fahrzeug& fahrzeug, Weg& weg) : Fahrausnahme(fahrzeug, weg)
{
}

void Streckenende::vBearbeiten()
{
	shared_ptr<Kreuzung> pKreuzung = p_pWeg1.getZielKreuzung().lock(); //Zwischenspeicherung der Zielkreuzung
	cout << "Name des Fahrzeuges in der die Ausnahme auftitt: " << p_pFahrzeug1.getName() << endl;
	cout << "Weg auf dem sich das Fahrzeug befindet: " << p_pWeg1.getName() << endl;
	cout << "Art der Ausnahme: Streckenende " << endl;

	bLoescheFahrzeug(p_pFahrzeug1.getName());
	//p_pWeg1.pAbgabe(p_pFahrzeug1);
	unique_ptr<Fahrzeug> pFahrzeug1Kopie = p_pWeg1.pAbgabe(p_pFahrzeug1);
	Weg& weg = pKreuzung->pZufaelligerWeg(p_pWeg1);
	pKreuzung->vTanken(p_pFahrzeug1);//Fahrzeug wird aufgetankt
	weg.vAnnahme(move(pFahrzeug1Kopie));//auf Weg setzen
	cout << "====================================================================================" << endl;
	cout << setiosflags(ios::left) << setw(14) << "ZEIT" << setw(40) << ": "+ to_string(dGlobaleZeit) << endl
		<< setw(14) << "KREUZUNG" << setw(40) << ": " + pKreuzung->getName() + "; der Inhalt ist " + to_string(pKreuzung->getTankinhalt()) + "l" << endl
		<< setw(14) << "WECHSEL" << setw(40) << ": " + p_pWeg1.getName() + " -> " + weg.getName() << endl
		<< setw(14) << "FAHRZEUG" << setw(40) << ": " + p_pFahrzeug1.getName() << endl;
	cout << "====================================================================================" << endl;
}

/*
 * Meldung darüber ausgeben, dass ein Weg endete
 *
 */
