#include "PKW.h"
#include "Fahrzeug.h"
#include "Verhalten.h"
#include "SimuClient.h"

PKW::PKW() : Fahrzeug()
{
}

PKW::~PKW()
{
}

PKW::PKW(string Name, double MaxGeschwindigkeit, double Verbrauch, double Tankvolumen) : Fahrzeug(Name,MaxGeschwindigkeit),p_dTankvolumen(Tankvolumen),p_dVerbrauch(Verbrauch),p_dTankinhalt(Tankvolumen/2)
{
}

double PKW::dTanken(double dMenge)
{
	double dTankFrei = p_dTankvolumen - p_dTankinhalt;//frei verf黦barer Platz im Tank 
	if (dTankFrei > dMenge) // es passt noch was rein 
	{
		p_dTankinhalt += dMenge; // Tankinhalt wird mit der Menge aufgef黮lt 
		return dMenge; 
	}
	else//Tankinhalt ist kleiner als zubef黮lende Menge 
	{
		p_dTankinhalt += dTankFrei; 
		return dTankFrei; 
	}


}

/**
 * @brief Hier wird der Tankinhalt eines Wagens geprüft. Wenn nichts mehr übrig ist,
 * dann bleibt der Wagen stehen
 *
 */
void PKW::vSimulieren()
{
	 
	if (p_dTankinhalt > 0) // es beinhaltet noch Brennstoff
	{
		Fahrzeug::vSimulieren(); //Fahrzeug f鋒rt 
		double dVerbrauchTank = p_dStreckeGefahren * p_dVerbrauch / 100; // gibt an wieviel verbraucht wird
		p_dTankinhalt -= dVerbrauchTank; //Tankinhalt wird reduziert 
	}
	else
	{
		p_dZeit = dGlobaleZeit; //Fahrzeug bleibt stehen 
	}

}

//ueberladen des Ausgabeoperators
void PKW::vAusgeben(ostream& o)const
{
	Fahrzeug::vAusgeben(o); 
	o << setw(20) << p_dGesamtStrecke * p_dVerbrauch / 100 << setw(25) << p_dTankinhalt << endl; 

}

//ueberladen des = Operators
PKW& PKW::operator=(const PKW& pkw)
{
	Fahrzeug::operator=(pkw);
	return *this;
}

/**
 *
 * @return
 *
 * @brief Hier wird die aktuelle Geschwindigkeit abhängig vom Verhalten des
 * Fahrzeugs bestimmt
 *
 */
double PKW::dGeschwindigkeit()const 
{
	if (p_pVerhalten != nullptr)
	{
		if (p_dMaxGeschwindigkeit > p_pVerhalten->dGeschwindigkeitslimit())
		{
			return p_pVerhalten->dGeschwindigkeitslimit();
		}
		else
		{
			return p_dMaxGeschwindigkeit;
		}
	}
	else
	{
		return p_dMaxGeschwindigkeit;
	}
}

void PKW::vZeichnen(Weg& aWeg) const
{
	double dRelPosition = p_dAbschnittStrecke / aWeg.getLaenge();
	if (dRelPosition < 0) dRelPosition = 0;
	if (dRelPosition > 1) dRelPosition = 1;
	bZeichnePKW(p_sName, aWeg.getName(), dRelPosition, dGeschwindigkeit(), p_dTankinhalt);
}

void PKW::vEinlesen(std::istream& i)
{
	//std::cout << "PKW: \n";
	Fahrzeug::vEinlesen(i);
	i >> this->p_dVerbrauch >> this->p_dTankvolumen;
}

