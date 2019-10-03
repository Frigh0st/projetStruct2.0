#include "DossierProfesseur.h"
#include <iostream>
#include <fstream>
#include <string>

DossierProfesseur::DossierProfesseur()
{
}

DossierProfesseur::~DossierProfesseur()
{
}

Professeur* DossierProfesseur::AjouterProfesseur(Professeur* prof)
{
	if (queue != NULL)
	{
		queue->suivant = prof;
	}
	else
	{
		tete = prof;
	}
	
	queue = prof;

	return prof;
}

void DossierProfesseur::Supprimer(string NOM)
{
	if (tete != NULL)
	{
		courant = tete;
		bool continuer = true;
		do
		{
			if (courant->nom == NOM)
			{
				if (prec == NULL)
				{
					delete courant;
				}
				else
				{
					prec->suivant = courant->suivant;
					delete courant;
				}
				continuer = false;
			}
			else
			{
				prec = courant;
				courant = courant->suivant;
			}
		} while (courant != NULL && continuer);
	}
}

int DossierProfesseur::Commun(string X, string Y)
{
	int commun = 0;
	Professeur* prof1;
	Professeur* prof2;

	prof1 = ChercherProfesseur(X);
	prof2 = ChercherProfesseur(Y);

	Cours* courant = prof1->listeCours;

	while (courant != NULL)
	{
		if (prof2->ChercherCoursParNom(courant->sigle))
		{
			commun++;
		}
		courant = courant->suivant;
	}

	return commun;
}

Cours* DossierProfesseur::LecoursLeplusDemande()
{
	Cours* lePlusDemande;
	Cours* grosseListeCours = new Cours();

	if (tete != NULL)
	{
		Professeur* profCourant = tete;
		while (profCourant != NULL)//foreach prof
		{		
			Cours* coursCourant;
			Cours* teteCours = profCourant->listeCours;

			if (teteCours != NULL)
			{
				coursCourant = teteCours;

				while (courant != NULL)//foreach cours
				{
					Cours* coursCompare;
					Cours* teteCompare = grosseListeCours;

					if (teteCompare != NULL)
					{
						coursCompare = teteCompare;
						bool trouver = false;

						while (coursCourant != NULL && !trouver)//comparer le cours courant à la grosseListeCours (.compare)
						{
							if (coursCompare->sigle == coursCourant->sigle)
							{							
								trouver = true;
							}
							else
							{
								coursCompare = coursCompare->suivant;
							}						
						}

						if (trouver)
						{
							coursCompare->nbInstance++;
						}
						else
						{
							if (grosseListeCours->sigle == "")
							{
								grosseListeCours = new Cours(coursCourant->sigle, coursCourant->NbreEtud, nullptr);
							}
							else
							{
								Cours* coursCourant2 = grosseListeCours;

								while (coursCourant2->suivant != NULL)
								{
									coursCourant2 = coursCourant2->suivant;
								}

								coursCourant2->suivant = new Cours(coursCourant->sigle, coursCourant->NbreEtud, nullptr);//VERIF est ce que grosseListeCours va réellement etre a jour ou coursCourant2 va devenir la nouvelle grosseListeCours
							}
						}
					}

					coursCourant = coursCourant->suivant;
				}
			}

			profCourant = profCourant->suivant;			
		}
	}

	//Trouver lePlusDemande en bouclant dans la grosse liste et garder le maximum en variable. Si egal comparer les nbEtu

	Cours* current = grosseListeCours;
	lePlusDemande = current;

	while (current->suivant != NULL)
	{
		if (current->nbInstance > lePlusDemande->nbInstance)
		{
			lePlusDemande = current;
		}
		else if (current->nbInstance == lePlusDemande->nbInstance)
		{
			if (current->NbreEtud > lePlusDemande->NbreEtud)
			{
				lePlusDemande = current;
			}
		}
		current = current->suivant;
	}
	
	return lePlusDemande;
}

void viderListeAncien(Professeur* listeAncien) 
{
	Professeur* curProf;

	while (listeAncien != NULL)
	{
		curProf = listeAncien;
		listeAncien = listeAncien->suivant;
		delete curProf;
	}

}

Professeur* DossierProfesseur::ProfesseurLeplusAncien()
{
	Professeur* professeurCourant = tete;
	Professeur* listeAncien = professeurCourant;

	while (professeurCourant->suivant != NULL)
	{
		if (professeurCourant->anciennete > listeAncien->anciennete)
		{
			viderListeAncien(listeAncien);//vider tous mes maximums et garder celui qui est plus vieux
			listeAncien = professeurCourant;
		}
		else if (professeurCourant->anciennete == listeAncien->anciennete)
		{
			//ajouter professeurCourant à la fin de liste Ancien
			while (listeAncien->suivant != NULL)
			{
				listeAncien = listeAncien->suivant;
			}

			listeAncien->suivant = professeurCourant;
		}
		
		professeurCourant = professeurCourant->suivant;
	}

	return listeAncien;//il faudra boucler pour afficher tous les profs les plus anciens
}


void DossierProfesseur::Recopier(string Nouveau)
{
	std::ofstream outFile;
	outFile.open(Nouveau);
	Cours* coursCourant;
	Professeur* courant = tete;
	int it;
	bool stop = false;

	if (tete != 0) {
		while (courant != nullptr)
		{
			it = 0;
			outFile << courant->nom << endl;
			outFile << courant->anciennete << endl;
			if (courant->listeCours != NULL) {
				coursCourant = courant->listeCours;
				while (coursCourant != NULL) {
					coursCourant = coursCourant->suivant;
					it++;
				}
			}

			outFile << it << endl;
			outFile << "&" << endl;
			courant = courant->suivant;

		}
	}


	outFile.close();



}

Professeur* DossierProfesseur::ChercherProfesseur(string nom)
{
	Professeur* prof = new Professeur("",99);

	if (tete != NULL)
	{
		courant = tete;
		bool continuer = true;
		do
		{
			if (courant->nom == nom)
			{
				prof = courant;
				continuer = false;
			}
			else
			{
				courant = courant->suivant;
			}
		} while (courant != NULL && continuer);
	}

	return prof;
}