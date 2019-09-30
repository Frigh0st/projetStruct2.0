#include "DossierProfesseur.h"

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

						while (courant != NULL && !trouver)//comparer le cours courant à la grosseListeCours (.compare)
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

								coursCourant2->suivant = new Cours(coursCourant->sigle, coursCourant->NbreEtud, nullptr);
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

	
	return lePlusDemande;
}

char* DossierProfesseur::ProfesseurLeplusAncien()
{
	return nullptr;
}

void DossierProfesseur::Recopier(char* Nouveau)
{
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