#include<iostream>
#include <istream>
#include <memory>
#include <vector>
#include <iomanip>
#include <map>
#include <random>
#include <fstream>

#include"Fahrzeug.h"
#include "PKW.h"
#include "Fahrrad.h"
#include "Simulationsobjekt.h"
#include "Weg.h"
#include "Simulationsobjekt.h"
#include "SimuClient.h"
#include "vertagt_liste.h"
#include "Kreuzung.h"
#include "Simulation.h"

double dGlobaleZeit = 0.0;
using namespace std;

void vAufgabe_1()
{
	Fahrzeug f1;
	Fahrzeug f2;

	Fahrzeug* f3 = new Fahrzeug();
	Fahrzeug* f4 = new Fahrzeug();

	delete f3;
	delete f4;

	auto f5 = make_unique<Fahrzeug>();
	auto f6 = make_unique<Fahrzeug>();
	auto f7 = make_shared<Fahrzeug>();
	auto f8 = make_shared<Fahrzeug>();
	cout << f8.use_count() << endl;
	shared_ptr<Fahrzeug> f8_1 = f8;
	cout << f8.use_count() << endl;

	vector<unique_ptr<Fahrzeug>> v1;
	v1.push_back(move(f6));

	v1.clear();

	vector<shared_ptr<Fahrzeug>> v2;

	cout << "Besitzer f7 vor pushback(ohne move): " << f7.use_count() << endl;
	v2.push_back(f7);
	cout << "Besitzer f7 nach pushback(ohne move): " << f7.use_count() << endl;

	cout << "Besitzer f8 vor pushback(mit move): " << f8.use_count() << endl;
	v2.push_back(move(f8));
	cout << "Besitzer f8 nach pushback(mit move): " << v2.back().use_count() << endl;

	v2.clear();

	Fahrzeug f9("PKW1", 40);
	Fahrzeug f10("AUTO3", 30);

	Fahrzeug::vKopf();
	f9.vAusgeben();
	cout << endl;
	f10.vAusgeben();
	cout << endl;

}
void vAufgabe_1a()
{
	vector<unique_ptr<Fahrzeug>> v3;

	for (int i = 1; i < 4; i++)
	{
		string sName;
		double dMaxGeschwindigkeit;

		cout << "Bitte geben Sie den Namen des Fahrzeuges ein: " << endl;
		cin >> sName;
		cout << "Bitte geben Sie die maximale Geschwindigkeit ihres Fahrzeuges ein: " << endl;
		cin >> dMaxGeschwindigkeit;
		auto fi = make_unique<Fahrzeug>(sName, dMaxGeschwindigkeit);
		v3.push_back(move(fi));
	}

	for (int j = 0; j < 10; j++)
	{
		dGlobaleZeit += 0.20;

		cout << "Aktuelle Zeit: " << dGlobaleZeit << endl;
		Fahrzeug::vKopf();
		for (auto it = v3.begin(); it != v3.end(); it++)
		{
			(*it)->vSimulieren();
			(*it)->vAusgeben();
			cout << endl;
		}
		cout << endl;
	}

}
void vAufgabe_2()
{
	vector<unique_ptr<Fahrzeug>> v4;

	cout << "Anzahl der zu erstellenden PKWs: " << endl;
	int ipAnzahl;
	cin >> ipAnzahl;
	for (int i = 0; i < ipAnzahl; i++)
	{
		string sName;
		double dMaxGeschwindigkeit;
		double dVerbrauch;
		double dTankvolumen;

		cout << "Geben Sie den Namen des PKWs ein: " << endl;
		cin >> sName;
		cout << "Geben Sie die maximale Geschwindigkeit des PKWs ein: " << endl;
		cin >> dMaxGeschwindigkeit;
		cout << "Geben Sie den Verbauch ihres PKWs ein (Liter/100km): " << endl;
		cin >> dVerbrauch;
		cout << "Geben Sie den Tankvolumen ihres PKWs ein: " << endl;
		cin >> dTankvolumen;
		auto pi = make_unique<PKW>(sName, dMaxGeschwindigkeit, dVerbrauch, dTankvolumen);
		v4.push_back(move(pi));
	}
	cout << "Anzahl der zu erstellenden Fahrr鋎er: " << endl;
	int ifAnzahl;
	cin >> ifAnzahl;
	for (int j = 0; j < ifAnzahl; j++)
	{
		string sName;
		double dMaxGeschwindigkeit;
		double dVerbrauch;
		double dTankvolumen;

		cout << "Geben Sie den Namen des Fahrrads ein: " << endl;
		cin >> sName;
		cout << "Geben Sie die maximale Geschwindigkeit des Fahrrads ein: " << endl;
		cin >> dMaxGeschwindigkeit;
		auto fj = make_unique<Fahrrad>(sName, dMaxGeschwindigkeit);
		v4.push_back(move(fj));
	}
	for (int a = 0; a < 10; a++)
	{
		dGlobaleZeit += 0.5; // Zeitschritte
		cout << "Aktuelle Zeit: " << dGlobaleZeit << endl;
		Fahrzeug::vKopf();
		for (auto it = v4.begin(); it != v4.end(); it++)
		{
			(*it)->vSimulieren();

			if (dGlobaleZeit == 3) // Nach 3 Stunden tanken
			{
				(*it)->dTanken();
			}
			(*it)->vAusgeben();
		}
		cout << endl;

	}
}

void vAufgabe_3()
{
	PKW schnell("Schnell", 50, 5);
	PKW lahm("Lahm", 30, 5);

	dGlobaleZeit = 1;

	schnell.vSimulieren();
	lahm.vSimulieren();

	PKW::vKopf();
	cout << lahm;
	cout << schnell;

	if (lahm < schnell)
	{
		cout << "Lahm hat eine geringere Strecke zurueckgelegt" << endl;
	}
	else
	{
		cout << "Schnell hat eine geringere Strecke zurueckgelegt" << endl;
	}


	PKW original("Original", 50,6);
	PKW kopie;

	kopie = original;

	PKW::vKopf();
	cout << original;
	cout << kopie;
}

void vAufgabe_4()
{

	Weg weg("weg",100);
	cout << weg << endl; 
	cout << endl; 
}

void vAufgabe_5()
{
	Weg weg ("weg", 100, 2);
	unique_ptr<Fahrzeug>f1 = make_unique<Fahrzeug>("BMW", 100); 
	unique_ptr<Fahrzeug>f2 = make_unique<Fahrzeug>("Audi", 50); 
	unique_ptr<Fahrzeug>f3 = make_unique<Fahrzeug>("BMX", 40);
	unique_ptr<Fahrzeug>f4 = make_unique<Fahrzeug>("VW", 80);
	//cout << weg << endl; 
	weg.vAnnahme(move(f1));
	weg.vAnnahme(move(f2));
	weg.vAnnahme(move(f3));
	weg.vAnnahme(move(f4),2.5);
	weg.vSimulieren();
	cout<<weg<<endl<<endl;
	int iZaehler=0;
	for(; dGlobaleZeit<5; dGlobaleZeit+=0.5)
	{
		iZaehler++;
		cout << iZaehler << ". Abfertigung" << endl;
		weg.vSimulieren();
		weg.vAusgeben();
		cout<<endl;
	}
	
}

void vAufgabe_6()
{

	bInitialisiereGrafik(800,500);
		Weg weg1("Landstr1", 100,3);
		Weg weg2("Landstr2", 100, 3);

		int iKoordinaten[] = { 700, 250, 100, 250 };
		bZeichneStrasse(weg1.getName(), weg2.getName(), weg1.getLaenge(), 2, iKoordinaten);
		weg1.vAnnahme(make_unique<PKW>("Audi", 120, 30, 60), 1); //fahrendes Fahrzeug /*neu: Zeitpunkt 1
		weg1.vAnnahme(make_unique<PKW>("Volvo", 60, 30, 60), 3); //parkendes Fahrzeug, faehrt zum Zeitpunkt dGLobalezeit = 3 los
		weg1.vAnnahme(make_unique<PKW>("BMW", 30, 30, 60)); //fahrendes Fahrzeug
		weg1.vAnnahme(make_unique<Fahrrad>("CityBike", 25)); //fahrendes Fahrrad
		weg2.vAnnahme(make_unique<Fahrrad>("BMX", 25));
		weg2.vAnnahme(make_unique<Fahrrad>("Mountainbike", 25),4);


		cout << endl;
		for (int i = 0; i <= 20; i++)
		{
			if (i == 10)
			{
				weg1.vAnnahme(make_unique<PKW>("VW", 80, 7, 100),6);
			}
			dGlobaleZeit += 0.5;
			cout << "Aktuelle Zeit: " << dGlobaleZeit << endl;
			vSetzeZeit(dGlobaleZeit);
			weg1.vSimulieren();
			weg2.vSimulieren();
			weg1.vZeichneFahrzeuge();
			weg2.vZeichneFahrzeuge();
			cout << weg1 << endl;
			cout << weg2 << endl;
			vSleep(200);

		}
		vBeendeGrafik();
}

void vAufgabe_6a()
{
		static mt19937 device(0);
		uniform_int_distribution<int> dist(1, 10);
		//int zuf = dist(device);
		vertagt::VListe<int> liste1;
		for (int i = 0; i < 10; i++)
		{
			liste1.push_back(dist(device));
		}
		liste1.vAktualisieren();
		cout << "Liste mit einlesen der Zahlen nach aktualisieren:  " << endl;
		for (auto it = liste1.begin(); it != liste1.end(); it++)
		{
			cout << *it << endl;
		}
		cout << endl;
		for (auto it = liste1.begin(); it != liste1.end(); it++)
		{
			if (*it > 5)
			{
				liste1.erase(it);
			}
		}
		cout << "Liste nach erase vor aktualisieren: " << endl;
		for (auto it = liste1.begin(); it != liste1.end(); it++)
		{
			cout << *it << endl;
		}
		cout << endl;
		cout << "Liste nach erase nach aktualsieren: " << endl;
		liste1.vAktualisieren();
		for (auto it = liste1.begin(); it != liste1.end(); it++)
		{
			cout << *it << endl;
		}
		cout << endl;
		liste1.push_front(9);
		liste1.push_back(2);
		liste1.vAktualisieren();
		cout << "Liste nach Einfuehen der Zahlen und nach aktualisieren: " << endl;
		for (auto it = liste1.begin(); it != liste1.end(); it++)
		{
			cout << *it << endl;
		}
		cout << endl;

}

void vAufgabe_7()
{
	string sStr1hin = "Str1Hin";
	string sStr1rueck = "Str1Rueck";

	string sStr2hin = "Str2Hin";
	string sStr2rueck = "Str2Rueck";

	string sStr3hin = "Str3Hin";
	string sStr3rueck = "Str3Rueck";

	string sStr4hin = "Str4Hin";
	string sStr4rueck = "Str4Rueck";

	string sStr5hin = "Str5Hin";
	string sStr5rueck = "Str5Rueck";

	string sStr6hin = "Str6Hin";
	string sStr6rueck = "Str6Rueck";

	double dLaengeStr1 = 40;
	double dLaengeStr2 = 115;
	double dLaengeStr3 = 40;
	double dLaengeStr4 = 55;
	double dLaengeStr5 = 85;
	double dLaengeStr6 = 130;

	int iTempolimitStr1 = 1;
	int iTempolimitStr2 = 3;
	int iTempolimitStr3 = 1;
	int iTempolimitStr4 = 1;
	int iTempolimitStr5 = 3;
	int iTempolimitStr6 = 2;

	bool bUeberholverbotStr1 = true;
	bool bUeberholverbotStr2 = false;
	bool bUeberholverbotStr3 = true;
	bool bUeberholverbotStr4 = true;
	bool bUeberholverbotStr5 = false;
	bool bUeberholverbotStr6 = false;

	auto Kr1 = std::make_shared<Kreuzung>("Kreuzung1", 0);
	auto Kr2 = std::make_shared<Kreuzung>("Kreuzung2", 1000);
	auto Kr3 = std::make_shared<Kreuzung>("Kreuzung3", 0);
	auto Kr4 = std::make_shared<Kreuzung>("Kreuzung4", 0);

	Kreuzung::vVerbinde(Kr1, Kr2, sStr1hin, sStr1rueck, dLaengeStr1, bUeberholverbotStr1 ,iTempolimitStr1);
	Kreuzung::vVerbinde(Kr2, Kr3, sStr2hin, sStr2rueck, dLaengeStr2, bUeberholverbotStr2, iTempolimitStr2);
	Kreuzung::vVerbinde(Kr2, Kr3, sStr3hin, sStr3rueck, dLaengeStr3, bUeberholverbotStr3, iTempolimitStr3);
	Kreuzung::vVerbinde(Kr4, Kr2, sStr4hin, sStr4rueck, dLaengeStr4, bUeberholverbotStr4, iTempolimitStr4);
	Kreuzung::vVerbinde(Kr4, Kr3, sStr5hin, sStr5rueck, dLaengeStr5, bUeberholverbotStr5, iTempolimitStr5);
	Kreuzung::vVerbinde(Kr4, Kr4, sStr6hin, sStr6rueck, dLaengeStr6, bUeberholverbotStr6, iTempolimitStr6);

	int iKoordinatenStr1[] = { 680,40,680,300 };
	int iKoordinatenStr2[] = { 680,300,850,300,970,390,970,500,850,570,680,570 };
	int iKoordinatenStr3[] = { 680,300,680,570 };
	int iKoordinatenStr4[] = { 320,300,680,300 };
	int iKoordinatenStr5[] = { 320,300,320,420,350,510,500,570,680,570 };
	int iKoordinatenStr6[] = { 320,300,320,150,200,60,80,90,70,250,170,300,320,300 };

	bInitialisiereGrafik(1000, 600);
	bZeichneStrasse(sStr1hin, sStr1rueck, dLaengeStr1, 2, iKoordinatenStr1);
	bZeichneStrasse(sStr2hin, sStr2rueck, dLaengeStr2, 6, iKoordinatenStr2);
	bZeichneStrasse(sStr3hin, sStr3rueck, dLaengeStr3, 2, iKoordinatenStr3);
	bZeichneStrasse(sStr4hin, sStr4rueck, dLaengeStr4, 2, iKoordinatenStr4);
	bZeichneStrasse(sStr5hin, sStr5rueck, dLaengeStr5, 5, iKoordinatenStr5);
	bZeichneStrasse(sStr6hin, sStr6rueck, dLaengeStr6, 7, iKoordinatenStr6);
	bZeichneKreuzung(680, 40);
	bZeichneKreuzung(680, 300);
	bZeichneKreuzung(680, 570);
	bZeichneKreuzung(320, 300);

	auto fahrzeug1i = make_unique<PKW>("PKW1i", 140, 7, 50);
	auto fahrzeug2i = make_unique<PKW>("PKW2i", 60, 7.4, 30);
	auto fahrzeug3i = make_unique<PKW>("PKW3i", 80, 7.6, 34);
	auto fahrzeug1l = make_unique<PKW>("PKW1l", 140, 7, 50);
	auto fahrzeug2l = make_unique<PKW>("PKW2l", 60, 7.4, 30);
	auto fahrzeug3l = make_unique<PKW>("PKW3l", 80, 7.6, 34);
	Kr1->vAnnahme(move(fahrzeug1i), 1.5);
	Kr2->vAnnahme(move(fahrzeug2i), 1.25);
	Kr3->vAnnahme(move(fahrzeug3i), 1);
	Kr4->vAnnahme(move(fahrzeug1l), 1.75);
	Kr3->vAnnahme(move(fahrzeug2l), 0.5);
	Kr4->vAnnahme(move(fahrzeug3l), 0.75);

	auto fahrzeug4i = make_unique<PKW>("PKW4i", 50, 7, 50);
	auto fahrzeug5i = make_unique<PKW>("PKW5i", 60, 7.4, 30);
	auto fahrzeug6i = make_unique<PKW>("PKW6i", 80, 7.6, 34);
	auto fahrzeug4l = make_unique<PKW>("PKW4l", 50, 7, 50);
	auto fahrzeug5l = make_unique<PKW>("PKW5l", 60, 7.4, 30);
	auto fahrzeug6l = make_unique<PKW>("PKW6l", 80, 7.6, 34);
	auto fahrzeug7l = make_unique<Fahrrad>("Fahrrad7l", 60);
	Kr1->vAnnahme(move(fahrzeug4i), 2);
	Kr2->vAnnahme(move(fahrzeug5i), 2.5);
	Kr2->vAnnahme(move(fahrzeug6i), 2.25);
	Kr1->vAnnahme(move(fahrzeug4l), 2.75);
	Kr3->vAnnahme(move(fahrzeug5l), 3);
	Kr4->vAnnahme(move(fahrzeug6l), 3.5);
	Kr1->vAnnahme(move(fahrzeug7l), 0.25);

	for (int i = 0; i < 100; i++)
	{
		dGlobaleZeit += 0.5;
		Kr1->vSimulieren();
		Kr2->vSimulieren();
		Kr3->vSimulieren();
		Kr4->vSimulieren();
		Kr1->ZeichneFahrzeuge();
		Kr2->ZeichneFahrzeuge();
		Kr3->ZeichneFahrzeuge();
		Kr4->ZeichneFahrzeuge();
		//vSleep(500);
		vSetzeZeit(dGlobaleZeit);
		cout << "Aktuelle Zeit:" << dGlobaleZeit << endl;

	}

	vBeendeGrafik();


}

void vAufgabe_8()
{
	ifstream infile("VO.dat");

	unique_ptr<PKW> pPKW1 = make_unique<PKW>();
	unique_ptr<Fahrrad> pFahrrad1 = make_unique<Fahrrad>();
	shared_ptr<Kreuzung> pKreuzung1 = make_shared<Kreuzung>();

	try
	{
		infile >> *pPKW1;
		infile >> *pFahrrad1;
		infile >> *pKreuzung1;
	}

	catch(runtime_error& Fehler)
	{
		cout << Fehler.what() << endl;
	}
}

void vAufgabe_9()
{
	ifstream infile("SimuK.dat");
	Simulation simulation;
	try
	{
		simulation.vEinlesen(infile);
	}

	catch(runtime_error& Fehler)
	{
		cout << Fehler.what() << endl;
		exit(0);
	}
	simulation.vSimulieren(10, 0.5);
}

void vAufgabe_9a()
{
	ifstream infile("SimuDisplay.dat");
	Simulation simulation;
	try
	{
		simulation.vEinlesen(infile, true);
	}

	catch (runtime_error& Fehler)
	{
		cout << Fehler.what() << endl;
		exit(0);
	}
	simulation.vSimulieren(10, 0.125);
}


typedef void(*aufgabe_t)();
int main(void)
{
	// STL-Map mit allen Aufgaben als Funktionspointer
	map<string, aufgabe_t> aufgaben;
	aufgaben["1"] = vAufgabe_1;
	aufgaben["1a"] = vAufgabe_1a;
	aufgaben["2"] = vAufgabe_2;
	aufgaben["3"] = vAufgabe_3;
	aufgaben["4"] = vAufgabe_4;
	aufgaben["5"] = vAufgabe_5;
	aufgaben["6"] = vAufgabe_6;
	aufgaben["6a"] = vAufgabe_6a;
	aufgaben["7"] = vAufgabe_7;
	aufgaben["8"] = vAufgabe_8;
	aufgaben["9"] = vAufgabe_9;
	aufgaben["9a"] = vAufgabe_9a;

	string sChoose = "";
	do
	{
		cout << "Praktikum Informatik II (WS23-24) - Strassenverkehr Block 1" << endl;
		cout << "Bitte waehlen Sie die Abkuerzung der Aufgabe:" << endl;
		cout << "1  : vAufgabe_1()" << endl
			 << "1a : vAufgabe_1_deb()" << endl
			 << "2  : vAufgabe_2()" << endl
			 << "3  : vAufgabe_3()" << endl
			 << "4  : vAufgabe_4()" << endl
			 << "5  : vAufgabe_5()" << endl
			 << "6  : vAufgabe_6()" << endl
			 << "6a  : vAufgabe_6a()" << endl
			 << "7  : vAufgabe_7()" << endl
			 << "8  : vAufgabe_8()" << endl
			 << "9  : vAufgabe_9()" << endl
			 << "9a  : vAufgabe_9a()" << endl
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
