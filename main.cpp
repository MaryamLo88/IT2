// file:	main.cpp
// author:	Abd Alhadi Kamrddin
// date:	01.11.2023

#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include <memory>    // Für std::unique_ptr und std::make_unique

#include "Fahrrad.h"
#include "Fahrzeug.h"
#include "PKW.h"

// Vergleichsfunktion f�r zwei double-Werte mit Fehlertoleranz.

inline bool bEqual(double x, double y)
{
	return (std::fabs(x - y) < 1e-6);
}

// "Globale Uhr"
double dGlobaleZeit = 0.0;

// Aufgabenstellung 1 aus Block 1
void vAufgabe_1()
{
	Fahrzeug *fz1 = new Fahrzeug("Auto", 60);
	Fahrzeug fz2("Motorwagen", 20);
	
	string sName = "";
	cout << "Bitte geben Sie den Namen Ihres Fahrzeuges ein: ";
	cin >> sName;

	Fahrzeug *fz3 = new Fahrzeug(sName, 42.4);
	Fahrzeug fz4;

	double dInterval = 0.0;
	cout << "Bitte geben Sie das Abfertigungsinterval ein: ";
	cin >> dInterval;
	cout << endl;

	Fahrzeug::vKopf();
	for (dGlobaleZeit = 0; dGlobaleZeit < 5; dGlobaleZeit += dInterval)
	{
		fz1->vAbfertigung();
		fz2.vAbfertigung();
		fz3->vAbfertigung();
		fz4.vAbfertigung();
		cout << "GlobaleZeit = " << dGlobaleZeit << endl;
		fz1->vAusgeben(); cout << endl;
		fz2.vAusgeben(); cout << endl;
		fz3->vAusgeben(); cout << endl;
		fz4.vAusgeben(); cout << endl;
		cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	}

	delete fz1;
	delete fz3;
}

// Aufgabenstellung 1 mit Debugger aus Block 1


void vAufgabe_1a()
{
    std::vector<std::unique_ptr<Fahrzeug>> fahrzeuge;

    fahrzeuge.push_back(std::make_unique<Fahrzeug>("Moped", 50));
    fahrzeuge.push_back(std::make_unique<Fahrzeug>("Tesla", 80));
    fahrzeuge.push_back(std::make_unique<Fahrzeug>("E-Bike", 25));

    double zeittakt = 0.25; // Zeittakt in Stunden (beispielsweise 15 Minuten)

    for (double t = 0.0; t < 1.0; t += zeittakt)
    {
        // Aktualisieren der globalen Uhr
        dGlobaleZeit += zeittakt;

        Fahrzeug::vKopf();
        for (const auto& fahrzeug : fahrzeuge)
        {
            // Fahrzeug simulieren
            fahrzeug->vSimulieren();

            // Fahrzeugdaten ausgeben

            fahrzeug->vAusgeben();
            cout << endl;
        }
    }
}




// Aufgabenstellung 2 aus Block 1
void vAufgabe_2()
{
	int iNumPKW = 0;
	int iNumFahrrad = 0;

	cout << "Wie viele PKWs sollen erzeugt werden? ";
	cin >> iNumPKW;
	cout << "Wie viele Fahrraeder sollen erzeugt werden? ";
	cin >> iNumFahrrad;

	vector<Fahrzeug*> vecFahrzeuge;

	// PKWs erzeugen
	for (int i = 1; i <= iNumPKW; i++)
	{
		PKW *pkwTemp = new PKW("AUTO " + to_string(i), 60, 5);
		vecFahrzeuge.push_back(pkwTemp);
	}

	// Fahrr�der erzeugen
	for (int i = 1; i <= iNumFahrrad; i++)
	{
		Fahrrad *frdTemp = new Fahrrad("FAHRRAD " + to_string(i), 24);
		vecFahrzeuge.push_back(frdTemp);
	}

	double dInterval = 0.0;
	cout << "Bitte geben Sie das Abfertigungsinterval ein: ";
	cin >> dInterval;
	cout << endl;

	bool bGetankt = false;
	Fahrzeug::vKopf();
	for (dGlobaleZeit = 0; dGlobaleZeit < 10; dGlobaleZeit += dInterval)
	{
		// vector<Fahrzeug*>::iterator it;
		for (auto it = vecFahrzeuge.begin(); it != vecFahrzeuge.end(); it++)
		{
			if ( (bEqual(dGlobaleZeit, 3.0) || dGlobaleZeit > 3.0) && !bGetankt )
			{
				(*it)->dTanken();	// Zum Zeitpunkt 3:00 Autos nachtanken
				bGetankt = true;
			}
			
			(*it)->vAbfertigung();	// Fahrzeuge fahren lassen
			(*it)->vAusgeben();		// Fahrzeugdaten ausgeben
			cout << endl;
		}

		cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	}

	// vector<Fahrzeug*>::iterator it;
	for (auto it = vecFahrzeuge.begin(); it != vecFahrzeuge.end(); it++)
	{
		delete *it; // Dynamische Objekte l�schen
	}
}

// Aufgabenstellung 3 aus Block 1
void vAufgabe_3()
{
	PKW car("Golf", 60, 5);
	Fahrrad bike("Cube", 24);
	Fahrzeug boat("Tanker", 15);

	// Ein wenig fahren
	dGlobaleZeit += 2.5;
	car.vAbfertigung();
	bike.vAbfertigung();
	boat.vAbfertigung();

	// Alles ausgeben
	Fahrzeug::vKopf();
	cout << car << endl << bike << endl << boat << endl << endl;

	// Vergleichsoperator testen
	if (bike < boat)
	{
		cout << "Das Schiff ist bereits weiter gefahren." << endl << endl;
	}
	else
	{
		cout << "Das Fahrrad ist bereits weiter gefahren." << endl << endl;
	}

	// Kopiermechanismen testen
	PKW carcopy1;
	PKW carcopy2 = car;	// mit Kopierkonstruktor
	carcopy1 = car;		// mit Zuweisungsoperator

	Fahrzeug::vKopf();
	cout << carcopy1 << endl << carcopy2 << endl;
}








#include <iostream>
#include <vector>
#include <iomanip>
#include "PKW.h"
#include "Fahrrad.h"

using namespace std;
extern double dGlobaleZeit;
double dEpsilon = 0.001;



// Typedef f�r Funktionspointer auf eine Aufgabe
typedef void(*aufgabe_t)();

// Hauptprogramm
int main(void)
{
	// STL-Map mit allen Aufgaben als Funktionspointer
	map<string, aufgabe_t> aufgaben;
	aufgaben["1"] = vAufgabe_1;
	aufgaben["1a"] = vAufgabe_1a;
	aufgaben["2"] = vAufgabe_2;
	aufgaben["3"] = vAufgabe_3;

	string sChoose = "";
	do
	{
		cout << "Praktikum Informatik II (WS23-24) - Strassenverkehr Block 1" << endl;
		cout << "Bitte waehlen Sie die Abkuerzung der Aufgabe:" << endl;
		cout << "1  : vAufgabe_1()" << endl
			 << "1a : vAufgabe_1_deb()" << endl
			 << "2  : vAufgabe_2()" << endl
			 << "3  : vAufgabe_3()" << endl
			 << "e  : Programm beenden." << endl;

		cin >> sChoose;
		cout << endl;

		auto it = aufgaben.find(sChoose);

		if (it != aufgaben.end())
		{
			(*it->second)(); // Funktionspointer aufrufen
		}
		else if(sChoose != "e")
		{
			cout << "Eingabe konnte nicht zugeordnet werden." << endl;
		}
		cout << endl;

	} while (sChoose != "e");

	return 0;
}

