// Devoir1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <fstream>
#include <string>
#include "DossierProfesseur.h"
using namespace std;


int main()
{
	ifstream myFile("Fichiers textes/FP.txt");
	string output;

	if (myFile.is_open())
	{
		cout << "The file is open!" << endl;
		int cpt = 0;
		string nom, nomCours;
		int anciennete;
		Professeur* prof;
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
				prof = new Professeur(nom, std::stoi(output));
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

			cout << output << endl;
		}
	}

	myFile.close();

	return 0;
}
