// Devoir1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <fstream>
#include <string>
#include "DossierProfesseur.h"
using namespace std;

string removeDupWord(string str)
{
	string word = "";
	for (auto x : str)
	{
		if (x == ' ')
		{
			return word;
		}
		else
		{
			word = word + x;
		}
	}
}

int main()
{
	ifstream myFile("Fichiers textes/FP.txt");
	string output;
	int cpt = 0;
	string nom, nomCours;
	int anciennete;
	DossierProfesseur* dp = new DossierProfesseur();
	Professeur* prof = new Professeur("Temporaire", 99);

	if (myFile.is_open())
	{
		std::cout << "The file is open!" << endl;
		
		while (getline(myFile, output, '\n'))
		{

			switch (cpt)
			{
			case 0://nom
			{
				nom = output;
				cpt++;
				break;
			}
			case 1://anciennete
			{
				cpt++;
				prof = dp->AjouterProfesseur(new Professeur(nom, std::stoi(output)));
				break;
			}
			case 2://nomCours
			{
				if (output.find('&') != std::string::npos)
				{
					cpt = 0;
				}
				else
				{
					nomCours = output;
					cpt++;
				}

				break;
			}
			case 3://nbEtu
			{
				prof->AjouterCours(nomCours, std::stoi(output));
				cpt--;
				break;
			}
			default:
				break;
			}

			// std::cout << output << endl;
		}
	}
	myFile.close();


	ifstream cmdFile("Fichiers textes/FT.txt");
	string output2;

	if (cmdFile.is_open())
	{
		std::cout << "The command file is open!" << endl;
		while (getline(cmdFile, output2, '\n'))
		{
			string eval = output2.substr(0, 1);

			if (eval == "%")
			{
				string nomProf = output2.substr(2);
				dp->Supprimer(nomProf);
			}
			else if (eval == "&")
			{
				string prof1, prof2;
				output2 = output2.substr(2);
				prof1 = removeDupWord(output2);
				int test = prof1.size() + 1;
				output2 = output2.substr(test);
				prof2 = removeDupWord(output2);

				test = dp->Commun(prof1, prof2);
				cout << "Le nombre de cours commun est: " << test << endl;
			}
			else if (eval == "+")
			{
				Cours* coursDemande;
				coursDemande = dp->LecoursLeplusDemande();
				cout << "Le cours le plus demande est: " << coursDemande->sigle << endl;
			}
			else if (eval == "*")
			{
				Professeur* profAncien;
				profAncien = dp->ProfesseurLeplusAncien();
				cout << "Le prof le plus ancien est: " << profAncien->nom << endl;
			}
			else if (eval == "$")
			{
				dp->Recopier(output2.substr(2));
			}
			else
			{
				cout << "Commande invalide!" << endl;
			}
		}
	}
	myFile.close();

	
	return 0;
}