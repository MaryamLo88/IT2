#include "Simulation.h"
#include <memory>
#include <vector>
#include <iomanip>
#include <map>

Simulation::Simulation() {
}

Simulation::~Simulation() {
}

void Simulation::vEinlesen(istream &i, bool bMitGrafik) {
	if (bMitGrafik) //Grafik benutzen ?
	{
		bInitialisiereGrafik(1000, 1000);
	}
	int z = 0; //Zaehler
	while (!i.eof()) //Nicht Ende der Datei
	{
		z++; //hochzaehlen fuer Zeile
		string sObjektTyp;
		i >> sObjektTyp;

		if (sObjektTyp == "KREUZUNG") {
			shared_ptr<Kreuzung> pKreuzung = make_shared<Kreuzung>(); //Pointer wird erstellt
			i >> *pKreuzung; //das was im pointer gespeichert ist wird eingelsen
			pKreuzungMap[pKreuzung->getName()] = pKreuzung; //Speichern Kreuzung in die Map 
			if (bMitGrafik) {
				double dKoordinateX, dKoordinateY;
				i >> dKoordinateX >> dKoordinateY; //Einlesen der Koordinaten 
				bZeichneKreuzung(dKoordinateX, dKoordinateY); //Kreuzung wird gezeichnet
			}
		}

		else if (sObjektTyp == "PKW") {

			//das Einlesen erfolgt analog zu oben.
			std::string sName = "";
			i >> sName;

			double dGeschwindigkeit = 0;
			i >> dGeschwindigkeit;

			double dVerbrauch = 0;
			i >> dVerbrauch;

			double dTankvolumen = 55;
			i >> dTankvolumen;

			std::string sStartKrz = "";
			i >> sStartKrz;

			double dStartzeit = 0;
			i >> dStartzeit;

			auto it4 = pKreuzungMap.find(sStartKrz);
			if (it4 == pKreuzungMap.end()) //wenn Kreuzung nicht gefunden
					{
				throw std::runtime_error("Die Startkreuzung existiert nicht!");
			}

			else {
				//Erstellen des Autos anhanf der oberen Daten
				std::unique_ptr<PKW> car = std::make_unique<PKW>(sName,
						dGeschwindigkeit, dVerbrauch, dTankvolumen);
				//dann einfuegen in die eingelesene Kreuzung
				pKreuzungMap[sStartKrz]->vAnnahme(move(car), dStartzeit);
			}
		}


		else if (sObjektTyp == "FAHRRAD") {

			std::string sName = "";
			i >> sName;

			double dGeshwindigkeit = 0;
			i >> dGeshwindigkeit;

			std::string sStartKrz = "";
			i >> sStartKrz;

			double dStartzeit = 0;
			i >> dStartzeit;

			auto it5 = pKreuzungMap.find(sStartKrz);
			if (it5 == pKreuzungMap.end()) //wenn Kreuzung nicht gefunden
					{
				throw std::runtime_error("Die Startkreuzung existiert nicht!");
			}

			else {
				//Erstellen und einfuegen erfolgt wie bei PKW
				std::unique_ptr<Fahrrad> bike = std::make_unique<Fahrrad>(sName,
						dGeshwindigkeit);
				pKreuzungMap[sStartKrz]->vAnnahme(move(bike), dStartzeit);
			}
		}

		else if (sObjektTyp == "STRASSE") {
			string NameQ, NameZ, NameW1, NameW2;
			double Laenge;
			int Tempolimit;
			int iUeberholverbot;
			bool Ueberholverbot;

			i >> NameQ >> NameZ >> NameW1 >> NameW2 >> Laenge >> Tempolimit
					>> iUeberholverbot;

			if (iUeberholverbot == 1 || iUeberholverbot == 0) //Ueberolverbot Bedingung
					{
				Ueberholverbot = iUeberholverbot;
			} else {
				string sZaehler = to_string(z);
				throw runtime_error(
						"Fehler in Ueberholverbot in Zeile: " + sZaehler);
			}

			if ((pKreuzungMap.count(NameQ) > 0)
					&& (pKreuzungMap.count(NameZ) > 0)) {
				Kreuzung::vVerbinde(pKreuzungMap[NameQ], pKreuzungMap[NameZ],
						NameW1, NameW2, Laenge, Ueberholverbot, Tempolimit); //Kreuzungen werden verbunden
			} else {
				string sZaehler = to_string(z);
				throw runtime_error(
						"Kreuzung konnte nicht gefunden werden. Fehler in Zeile: "
								+ sZaehler);
			}

			if (bMitGrafik) {
				int iAnzahlKP; //Anzahl Koordinatenpaare
				i >> iAnzahlKP;
				vector<int> feld;
				for (int a = 0; a < iAnzahlKP * 2; a++) //Koordinaten werden ins Feld eingelesen und hinzugef�gt
						{
					int iKoordinate;
					i >> iKoordinate;
					feld.push_back(iKoordinate);
				}
				int *adresse = &feld[0]; //Zeiger der auf das erste element von Feld zeigt
				bZeichneStrasse(NameW1, NameW2, Laenge, iAnzahlKP, adresse); //Strasse wird gezeichnet
			}
		} else {
			string sZaehler = to_string(z);
			throw runtime_error(
					"Fehler beim Einlesen des Objekttyps in Zeile: "
							+ sZaehler);
		}

	}
}

void Simulation::vSimulieren(double dDauer, double dZeitschritt) {
	while (dDauer > dGlobaleZeit) //Es wird fuer eine Dauer simuliert
	{
		dGlobaleZeit += dZeitschritt; //Schritte
		cout << "Aktuelle Zeit: " << dGlobaleZeit << endl;
		vSetzeZeit(dGlobaleZeit); // Zeit wird gesetzt
		for (auto it = pKreuzungMap.begin(); it != pKreuzungMap.end(); it++) {
			it->second->vSimulieren(); //it->second gibt mir die Kreuzung zurueck
			it->second->ZeichneFahrzeuge();
		}
//vSleep(200);
	}
	vBeendeGrafik();
}

























/*
else if (sObjektTyp == "PKW") {
			/*string NameS; // Name der Startkreuzung
			 double dStartZeitpunkt;

			 unique_ptr<PKW> pPKW = make_unique<PKW>();
			 i >> *pPKW;

			 i >> NameS;

			 i >> dStartZeitpunkt;
			 if (pKreuzungMap.count(NameS) > 0) //Kreuzung mit passendem key wird gesucht
			 {
			 shared_ptr<Kreuzung> pStartKreuzung = pKreuzungMap[NameS]; //Zwischenspeicherung
			 pStartKreuzung->vAnnahme(move(pPKW), dStartZeitpunkt); //PKW wird auf Weg gesetzt
			 } else {
			 string sZaehler = to_string(z); //Umwandlung int in string
			 throw runtime_error(
			 "Kreuzung konnte nicht gefunden werden. Fehler in Zeile: "
			 + sZaehler); //Error
			 }
}



else if (sObjektTyp == "FAHRRAD") {
			unique_ptr<Fahrrad> pFahrrad = make_unique<Fahrrad>();
			 i >> *pFahrrad;
			 string NameS; // Name der Startkreuzung
			 i >> NameS;
			 double dStartZeitpunkt;
			 i >> dStartZeitpunkt;
			 if (pKreuzungMap.count(NameS) > 0)
			 {
			 pKreuzungMap[NameS]->vAnnahme(move(pFahrrad), dStartZeitpunkt); //Fahrrad wird auf Weg gesetzt
			 }
			 else
			 {
			 string sZaehler = to_string(z);
			 throw runtime_error("Kreuzung konnte nicht gefunden werden. Fehler in Zeile: " + sZaehler);
			 }*/
