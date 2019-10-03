#pragma once
#include <string>

using namespace std;

struct Cours {
	string sigle;
	int NbreEtud;
	Cours* suivant;
	int nbInstance;

	Cours(string sigle, int NbreEtud, Cours* suivant) {
		this->sigle = sigle;
		this->NbreEtud = NbreEtud;
		this->suivant = suivant;
		this->nbInstance = 1;
	}

	Cours() {}

	~Cours() {}
};

struct Professeur {
	string nom;
	int anciennete;
	Cours* listeCours;//tete de la liste
	Professeur* suivant;

	Professeur(string nom, int anciennete) {
		this->nom = nom;
		this->anciennete = anciennete;
		this->listeCours = new Cours();
		this->suivant = NULL;
	}

	~Professeur() {}

	void AjouterCours(string nomCours, int nbEtu) {
		if (this->listeCours->sigle == "")
		{
			this->listeCours = new Cours(nomCours, nbEtu, nullptr);
		}
		else
		{
			Cours* coursCourant = this->listeCours;

			while (coursCourant->suivant != NULL)
			{
				coursCourant = coursCourant->suivant;
			}

			coursCourant->suivant = new Cours(nomCours, nbEtu, nullptr);
		}
	}

	bool ChercherCoursParNom(string sigle) {
		Cours* courant;
		Cours* tete = this->listeCours;
		bool trouver = false;
		
		if (tete != NULL)
		{
			courant = tete;
			
			do
			{
				if (courant->sigle == sigle)
				{
					trouver = true;
				}
				else
				{
					courant = courant->suivant;
				}
			} while (courant != NULL && !trouver);
		}

		return trouver;
	}
};

class DossierProfesseur {
private:
	Professeur* tete; // début de la liste chaînée.
	Professeur* queue; // fin de la liste chainée.
	Professeur* courant; // Position courante dans la liste chainée.
	Professeur* prec; //precedent du courant
public:
	DossierProfesseur(); // construit la liste chaînée en mémoire.
	~DossierProfesseur(); // détruit la liste chaînée existant en mémoire.
	Professeur* AjouterProfesseur(Professeur* prof); // Ajoute un professeur dans le dossier professeur
	void Supprimer(string NOM); // supprime de la liste chaînée le professeur NOM.
	int Commun(string X, string Y); // affiche le nombre de cours en commun entre les profs X et Y.
	Cours* LecoursLeplusDemande(); // affiche le cours le plus demandé de la liste chaînée. En cas de solutions multiples, prendre celui ayant le plus d’étudiants.
	Professeur* ProfesseurLeplusAncien(); // affiche le nom du professeur le plus ancien.
	void Recopier(string Nouveau); // recopie à partir de la liste chaînée le nom, ancienneté et le nombre de cours demandés pour chaque professeur dans le fichier texte Nouveau.
	Professeur* ChercherProfesseur(string nom);
};