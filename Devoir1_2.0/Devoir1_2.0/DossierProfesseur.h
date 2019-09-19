#pragma once

struct Professeur {
	char* nom;
	int anciennete;
	Cours* listeCours = new Cours[];
	Professeur* suivant;
};

struct Cours {
	char* sigle;
	int NbreEtud;
	Cours* suivant;
};

class DossierProfesseur {
private:
	Professeur* tete; // début de la liste chaînée.
public:
	DossierProfesseur(char* FP); // construit la liste chaînée en mémoire à partir du fichier FP.
	~DossierProfesseur(); // détruit la liste chaînée existant en mémoire.
	void Supprimer(char* NOM); // supprime de la liste chaînée le professeur NOM.
	int Commun(char* X, char* Y); // affiche le nombre de cours en commun entre les profs X et Y.
	char* LecoursLeplusDemande() const; // affiche le cours le plus demandé de la liste chaînée. En cas de solutions multiples, prendre celui ayant le plus d’étudiants.
	char* ProfeseurLeplusAncien() const; // affiche le nom du professeur le plus ancien.
	void Recopier(char* Nouveau); // recopie à partir de la liste chaînée le nom, ancienneté et le nombre de cours demandés pour chaque professeur dans le fichier texte Nouveau.
};