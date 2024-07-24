#include "Fahrzeug.h" 
#include "Verhalten.h"
#include "Fahren.h"
#include "Parken.h"
/*
* Initialsierung des ID Zaehlers
*/
//

Fahrzeug::Fahrzeug(string Name) : Simulationsobjekt(Name)
{
	cout << "Konstruktor" << endl;
	cout << "# erzeugtes Fahrzeug: " << p_sName << endl;
	cout << "ID#: " << p_iID << endl;
}
//Standardkonstruktor
Fahrzeug::Fahrzeug(): Simulationsobjekt()
{
	cout << "Default Konstruktor" << endl; 
	cout << "# erzeugtes Fahrzeug: " << p_sName << endl;
	cout << "ID#: " << p_iID << endl;
}
//Destruktor
Fahrzeug::~Fahrzeug()
{
	cout << "# geloeschtes Fahrzeug: " << p_sName << endl;
	cout << "ID#: " << p_iID << endl;
}
//Standardkonstruktor mit Maximalgeschwindigkeit
Fahrzeug::Fahrzeug(string Name, double MaxGeschwindigkeit) : Simulationsobjekt(Name) , p_dMaxGeschwindigkeit((MaxGeschwindigkeit>0)? MaxGeschwindigkeit:0)
{
	cout << "Default Konstruktor" << endl;
	cout << "# erzeugtes Fahrzeug: " << p_sName << endl;
	cout << "ID#: " << p_iID << endl;
}
//Kopf der Ausgabetabelle
void Fahrzeug::vKopf()
{
	cout << setiosflags(ios::left) <<setw(4) << "ID" << setw(15) << "Name" << setw(20)
			<< "MaxGeschwindigkeit" << setw(20) << "Gesamtstrecke" << setw(30) << "Aktuelle Geschwindigkeit"
			<< setw(20) << "Gesamtverbrauch" << setw(20) << "aktueller Tankinhalt" << endl;
	cout << "---------------------------------------------------------------------------------------------------------------------------------" << endl;
	
}
//Ausgabe der Wagen mit den Eigenschaften
void Fahrzeug::vAusgeben(ostream& o)const
{
	o << setiosflags(ios::left) << setw(4) << p_iID << setw(15) << p_sName << setw(20) << p_dMaxGeschwindigkeit << setw(20) << p_dGesamtStrecke << setw(30) << dGeschwindigkeit();
}
/**
 * @brief Diese Funktion simuliert die Bewegung der Wagen abhämgig von ihrem Verhalten
 */
void Fahrzeug::vSimulieren()
{
	if (dGlobaleZeit > p_dZeit) // Zeit hat sich veraedert, d.h wir bewegen uns
	{
		double dZeitAbstand = dGlobaleZeit - p_dZeit; // vergangene Zeit
		p_dStreckeGefahren = p_pVerhalten->dStrecke(*this, dZeitAbstand); 

		p_dGesamtStrecke += p_dStreckeGefahren; // Weg = Zeit * Geschwindigkeit
		p_dAbschnittStrecke += p_dStreckeGefahren; 
		p_dGesamtZeit += dZeitAbstand; // Zeit aktualisieren bzw. anpassen 
		p_dZeit = dGlobaleZeit; // aktuelle Zeit
	}

}

double Fahrzeug::dTanken( double dMenge )
{
	return 0; 
}

double Fahrzeug::dGeschwindigkeit() const
{
	return p_dMaxGeschwindigkeit; 
}

//ueerladen  stream operator
ostream& operator<<(ostream& o,const Fahrzeug& fahrzeug)
{
	fahrzeug.vAusgeben(o); 
	return o; 
}

// ueberladen  < operator
bool Fahrzeug::operator<(const Fahrzeug& fahrzeug)const
{
	return (this->p_dGesamtStrecke < fahrzeug.p_dGesamtStrecke);
}

//ueberladen = Operator
Fahrzeug& Fahrzeug::operator=(const Fahrzeug& fahrzeug)
{
	p_sName = fahrzeug.p_sName;
	p_dMaxGeschwindigkeit = fahrzeug.p_dMaxGeschwindigkeit;


	return *this;
}
/**
 *
 * @param weg
 *
 * @brief Diese Funtktion erzeugt für den auf dem Weg fahrenden Wagen eine Liste
 */
void Fahrzeug::vNeueStrecke(Weg& weg)
{
	p_pVerhalten = make_unique<Fahren>(weg);	
	p_dAbschnittStrecke = 0;

}

double Fahrzeug::getAbschnittStrecke()
{
	return p_dAbschnittStrecke;
}
 /**
  *
  * @param weg
  * @param dStartzeitpunkt
  *
  * @brief Diese Funktion erzeugt eine Liste von den auf dem Weg parkenden Wagen
  */
void Fahrzeug::vNeueStrecke(Weg& weg, double dStartzeitpunkt)
{
	p_pVerhalten = make_unique<Parken>(weg, dStartzeitpunkt);
	p_dAbschnittStrecke = 0; 
}

void Fahrzeug::vZeichnen(Weg& weg) const
{
}
