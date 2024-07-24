#include "Kreuzung.h"
#include "Weg.h"
#include <cmath>
#include <random>

Kreuzung::Kreuzung() : Simulationsobjekt()
{
	cout << "Default Konstruktor" << endl;
	cout << "# erzeugte Kreuzung: " << p_sName << endl;
	cout << "ID#: " << p_iID << endl;
}

Kreuzung::Kreuzung(string sName, double dTank) :Simulationsobjekt(sName), p_dTankstelle(dTank)
{
	cout << "Konstruktor" << endl;
	cout << "# erzeugte Kreuzung: " << p_sName << endl;
	cout << "ID#: " << p_iID << endl;
}

Kreuzung::~Kreuzung()
{
}

void Kreuzung::vVerbinde(shared_ptr<Kreuzung> kreuzung1, shared_ptr<Kreuzung> kreuzung2, string sNameH, string sNameR, double dLaenge, bool bUeberholverbot, int iGeschwindigkeitsBegrenzung)
{
	shared_ptr<Weg> pWegH = make_shared<Weg>(sNameH, dLaenge, bUeberholverbot, iGeschwindigkeitsBegrenzung); //Hinweg
	shared_ptr<Weg> pWegR = make_shared<Weg>(sNameR, dLaenge, bUeberholverbot, iGeschwindigkeitsBegrenzung); //Rueckweg

	weak_ptr<Weg> pWegHW = pWegH; 
	weak_ptr<Weg> pWegRW = pWegR; 

	weak_ptr<Kreuzung> pKreuzung1W = kreuzung1; 
	weak_ptr<Kreuzung> pKreuzung2W = kreuzung2;

	pWegH->setRueckWeg(pWegRW); //Rueckweg wird gesetzt 
	pWegR->setRueckWeg(pWegHW); 

	pWegH->setZielKreuzung(pKreuzung2W); // setzen der Zielkreuzung
	pWegR->setZielKreuzung(pKreuzung1W);

	kreuzung1->p_pWege.push_back(pWegH); // kreuzung1 bekommt WegH
	kreuzung2->p_pWege.push_back(pWegR); // kreuzung2 bekommt WegR 

}

void Kreuzung::vTanken(Fahrzeug& fahrzeug)
{
	if (p_dTankstelle > 0)
	{
		double dMenge = fahrzeug.dTanken(); //Tanken 

		p_dTankstelle -= dMenge; 

		if (p_dTankstelle < 0)
		{
			p_dTankstelle = 0; 
		}
	}
	
}

void Kreuzung::vAnnahme(unique_ptr<Fahrzeug> pFahrzeug, double dStartzeitpunkt)
{
	pFahrzeug->dTanken();//Tanken
	p_pWege.front()->vAnnahme(move(pFahrzeug), dStartzeitpunkt); //Fahrzeug wird auf ersten Weg gesetzt 
}

void Kreuzung::vSimulieren()
{
	for (auto it = p_pWege.begin(); it != p_pWege.end(); it++)
	{
		(*it)->vSimulieren();
	}
}

Weg& Kreuzung::pZufaelligerWeg(Weg& weg)
{
	static mt19937 device(0); //Zufallszahlen 
	uniform_int_distribution<int> dist(1,p_pWege.size());

	if (p_pWege.size() == 1) //Liste nur ein Element -> Sackgasse 
	{
		return *p_pWege.front();
	}
	else
	{
		while (true) //Unendlich Schleife 
		{
			int zuf = dist(device); //Zufallszahl 
			int i = 1;
			shared_ptr<Weg> pWegNeu;

			for (auto it = p_pWege.begin(); it != p_pWege.end(); it++, i++) //Liste durchgehen und hochzaelen
			{
				if (i == zuf) //es wird zufallszahl-mal iteriert 
				{
					pWegNeu = *it; //gefundener Weg wird in pWegNeu zwischengespeichert 
					break;
				}
			}
			if (pWegNeu != weg.getRueckWeg().lock()) //Ist das nicht Rueckweg ? 
			{
				return *pWegNeu; // Wenn Ruekweg -> Wiederholung --- wenn nicht Ruekweg -> gefundenen Weg zuruekgegeben
			}
		}
	}	
}

double Kreuzung::getTankinhalt()
{
	return p_dTankstelle;
}

void Kreuzung::ZeichneFahrzeuge()
{
	for (auto it = p_pWege.begin(); it != p_pWege.end(); it++)
	{
		(*it)->vZeichneFahrzeuge();
	}
}

void Kreuzung::vEinlesen(istream& i)
{
	Simulationsobjekt::vEinlesen(i);
	i >> p_dTankstelle; 	
}

