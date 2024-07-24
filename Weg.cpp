#include "Weg.h"
#include "Fahrzeug.h"
#include "Fahrausnahme.h"
#include "Simulationsobjekt.h"
#include "vertagt_liste.h"
#include <iomanip>
using namespace std; 

Weg::Weg() : Simulationsobjekt(),p_iTempolimit(3)
{

}

//Destruktor
Weg::~Weg()
{

}

//Standardkonstruktor
Weg::Weg(string Name, double Laenge, bool bUeberholverbot ,int iTempolimit):Simulationsobjekt(Name),p_iTempolimit(iTempolimit),p_dLaenge(Laenge), p_bUeberholverbot(bUeberholverbot), p_dVirtuelleSchranke(p_dLaenge)
{

}

//Tempolimit bestimmen
double Weg::getTempolimit()
{
	switch (p_iTempolimit)
	{
	case 1:
	{
		return double(Tempolimit::Innerorts);
		break;
	}
	case 2:
	{
		return double(Tempolimit::Landstrasse);
		break;
	}
	case 3:
	{
		return double(Tempolimit::Autobahn);
	}
	}
}


/**
 * @brief Simulation der Fahrzeuge, die sich auf einem Weg befinden.
 * Diese Simulation ist die des Wegen, doch in Abhängigkeit vom Verhalten der
 * jeweiligen Wagen.
 */
void Weg::vSimulieren()
{
	p_dVirtuelleSchranke=p_dLaenge;
		p_pFahrzeuge.vAktualisieren();
		for (auto& it : p_pFahrzeuge)
		{
			try
			{
				(it)->vSimulieren();
			}

			catch (Fahrausnahme* fahrausnahme)
			{
				fahrausnahme->vBearbeiten();
				//delete fahrausnahme;
			}
			p_pFahrzeuge.vAktualisieren();
			for (auto& it : p_pFahrzeuge) { (it)->vZeichnen(*this);}
			
		}

}

//Kopf der Ausgabetabelle des Weges
void Weg::vKopf()
{
	cout << setiosflags(ios::left) << setw(7) << "ID" << " | " << setw(15) << "Name" << " | " << setw(20) << "Laenge" << " | " << setw(30) << "Fahrzeuge" << endl;
	cout << "--------------------------------------------------------------------------------------------------------------------";
}

//Die Ausgabe des Weges mit einer Liste von den Wagen
void Weg::vAusgeben(ostream& o) const
{
	Weg::vKopf(); 
	cout << endl; 
	Simulationsobjekt::vAusgeben(); 
	o << setw(6) << ":" << setw(20) << p_dLaenge << "(";
	for (auto& it : p_pFahrzeuge)
	{
		o << (it)->getName() << " ";

	}
	o << ")";
	cout << endl; 
	cout << endl; 
	Fahrzeug::vKopf();
	for (auto& it : p_pFahrzeuge)
	{
		o << *it << endl;

	}
}

double Weg::getLaenge()
{
	return p_dLaenge; 
}

void Weg::vAnnahme(unique_ptr<Fahrzeug> pFahrzeug)
{
	pFahrzeug->vNeueStrecke(*this);
	p_pFahrzeuge.push_back(move(pFahrzeug));
}

void Weg::vAnnahme(unique_ptr<Fahrzeug> pFahrzeug, double dStartzeitpunkt)
{
	pFahrzeug->vNeueStrecke(*this, dStartzeitpunkt);
	p_pFahrzeuge.push_front(move(pFahrzeug));
}

void Weg::vZeichneFahrzeuge()
{
	if (!p_pFahrzeuge.empty())
	{
		for (auto& it : p_pFahrzeuge)
		{
			it->vZeichnen(*this);
			//vSleep(300);
		}
	}
}
unique_ptr<Fahrzeug> Weg::pAbgabe(const Fahrzeug& fahrzeug)
{
	for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); it++)
	{
		if ((*it != nullptr) && (**it == fahrzeug))
		{
			unique_ptr<Fahrzeug>pFahrzeugLokal = move(*it); //Zwischenspeicherung
			p_pFahrzeuge.erase((it)); //Listenelement wird geloecht
			return pFahrzeugLokal;
		}
	}
	return nullptr;
}
double Weg::getVirtuelleSchranke() //Zugriff auf Virtuelle Schranke
{
	if(p_bUeberholverbot == true)
	{
		return p_dVirtuelleSchranke;
	}
	else
	{
	return p_dLaenge; // Wenn kein Ueberholverbot -> virtuelle Schranke wird auf L鋘ge des Weges gesetzt ->virtuelle Schranke "nicht existent"
	}
}


void Weg::setVirtuelleSchranke(double dVirtuelleschranke) //Virtuelle schranke wird gesetzt
{
	p_dVirtuelleSchranke = dVirtuelleschranke;

}

void Weg::setZielKreuzung(weak_ptr<Kreuzung> pZielKreuzung)
{
	p_pZielKreuzung = pZielKreuzung;
}

void Weg::setRueckWeg(weak_ptr<Weg> pRueckWeg)
{
	p_pRueckWeg = pRueckWeg;
}

weak_ptr<Kreuzung> Weg::getZielKreuzung()
{
	return p_pZielKreuzung;
}

weak_ptr<Weg> Weg::getRueckWeg()
{
	return p_pRueckWeg;
}
