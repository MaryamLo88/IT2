

#include "Simulationsobjekt.h"

int Simulationsobjekt::p_iMaxID = 0; 

Simulationsobjekt::Simulationsobjekt() : p_iID(p_iMaxID)
{
	p_iMaxID++; 

}

//Standardkonstruktor
Simulationsobjekt::Simulationsobjekt(string Name) : p_sName(Name),p_iID(p_iMaxID)
{
	p_iMaxID++; 

}

//Destruktor
Simulationsobjekt::~Simulationsobjekt()
{
	cout << "#Name des geloeschten Simulationsobjekts: " << p_sName << endl; 
	cout << "#ID des geloeschten Simulationsobjekts: " << p_iID << endl; 

}

//Ausgabe
void Simulationsobjekt::vAusgeben(ostream& o )const
{
	o << setiosflags(ios::left) << setw(9) << p_iID << setw(17) << p_sName ; 

}

//ueberladung
ostream& operator<<(ostream& o, const Simulationsobjekt& simulationsobjekt)
{
	simulationsobjekt.vAusgeben(o); 
	return o; 	
}

//ueberladung
bool Simulationsobjekt::operator==(const Simulationsobjekt& simulationsobjekt)
{
	return (this->p_iID == simulationsobjekt.p_iID);
}

//Simulieren
void Simulationsobjekt::vSimulieren()
{
}

//Name zurückgeben
string Simulationsobjekt::getName()
{
	return p_sName; 
}

void Simulationsobjekt::vEinlesen(istream& i)
{
	if (p_sName == "")
	{
		i >> p_sName;
	}

	else
	{
		throw runtime_error("Es ist ein Fehler beim Einlesen aufgetreten");
	}
}

istream& operator>>(istream& i, Simulationsobjekt& simulationsobjekt1)
{
	simulationsobjekt1.vEinlesen(i);
	return i;
}

