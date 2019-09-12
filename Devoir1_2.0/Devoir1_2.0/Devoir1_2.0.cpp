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

		while (getline(myFile, output))
		{
			cout << output << endl;
		}
	}

	myFile.close();

	return 0;
}
