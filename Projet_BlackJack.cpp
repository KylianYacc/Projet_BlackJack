#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

class Carte {
public:
    string couleur;
    string valeur; 
    int valeurNum;

    Carte(string c, string v, int val) : couleur(c), valeur(v), valeurNum(val) {}

    void afficherCarte(){
        cout << couleur << " de " << valeur;
    }

    int getValeur(){
        return valeurNum;
    }
};

Carte tirerCarte(){
        int valeurNum;
        vector<string> valeurs = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "AS", "ROI", "DAME", "VALET"};
        vector<string> couleurs = {"cœur", "carreau", "pique", "trèfle"};
        string valeur = valeurs[rand() % valeurs.size()];
        string couleur = couleurs[rand() % couleurs.size()];

        if (valeur == "AS"){
            valeurNum = 11;
        }else if (valeur == "ROI" || valeur == "DAME" || valeur == "VALET" || valeur == "ROI"){
            valeurNum = 10;
        }else {
            valeurNum = stoi(valeur);
        }

    return Carte(valeur, couleur, valeurNum);
}


class Joueur {
public:
    string nomJoueur;
    int ageJoueur;
    vector<Carte> main;

    void player() {
        cout << "Votre nom : " << nomJoueur << endl << "Votre age : " << ageJoueur << endl;
    }

    void afficheMain(){
        cout << nomJoueur << " a : ";

        for (Carte& carte : main){
            carte.afficherCarte();
            cout <<", ";
        }
        cout << "Total : " << calculerTotal() << endl;
    }

    int calculerTotal() {
        int total = 0;
        int nombreAS = 0;  

        for (Carte& carte : main){
            total += carte.getValeur();
            if (carte.valeur == "AS"){
                nombreAS++ ;
            }
        }

        while(total > 21 && nombreAS > 0){
            total -=10;
            nombreAS--;
        }

        return total;
    }
};

class Croupier {
public:
    string nomCroupier;
    vector<Carte> main;

    Croupier() {
        nomCroupier = "Steve";
    }

    void table() {
        cout << "Nom du Croupier : " << nomCroupier << endl;
        cout << "Vous jouez sur la table 1" << endl;
        cout << endl;
    }

    void afficheMain() {
        cout << nomCroupier << " a : ";
        for (Carte& carte : main) {
            carte.afficherCarte();
            cout << ", ";
        }
        cout << "Total : " << calculerTotal() << endl;
    }

    int calculerTotal() {
        int total = 0;
        int nombreAS = 0;

        for (Carte& carte : main) {
            total += carte.getValeur();
            if (carte.valeur == "AS") {
                nombreAS++;
            }
        }

        while (total > 21 && nombreAS > 0) {
            total -= 10;
            nombreAS--;
        }

        return total;
    }
};

int main(){
    
    srand(time(0));
    int BlackJack = 21;
    Joueur joueur1;
    Croupier croupier1;

    cout << "Choisissez votre nom : ";
    cin >> joueur1.nomJoueur;

    cout << "Entrer votre âge : ";
    cin >> joueur1.ageJoueur;

    joueur1.player();
    croupier1.table();

    joueur1.main.push_back(tirerCarte());
    joueur1.main.push_back(tirerCarte());
    croupier1.main.push_back(tirerCarte());

    croupier1.afficheMain();
    cout << endl;

    if (joueur1.calculerTotal() == 21){
        cout << "BLackJack !!! Vous gagnez la partie" << endl;
        return 0;
    }

    char choix;
    while (true){
        joueur1.afficheMain();
        cout << "Voulez vous tirez une carte (T) ou rester (R) ?";
        cin >> choix;

        if (choix == 'T' || choix == 't'){
            joueur1.main.push_back(tirerCarte());
            joueur1.afficheMain();
            if (joueur1.calculerTotal() > BlackJack){
                cout << "Vous avez dépassé 21 ! Vous avez perdu !" << endl;
                return 0;
            }
        else if (choix == 'R' || choix == 'r'){
            break;
        }
        else {
            cout << "Choix invalide !" << endl;
        }
        }
   
    }
    
    cout << "Le croupier joue..." << endl;

    while (croupier1.calculerTotal() < 17) {
        cout << "Le croupier tire une carte..." << endl;
        croupier1.main.push_back(tirerCarte());
        croupier1.afficheMain();
    }

    int totalJoueur = joueur1.calculerTotal();
    int totalCroupier = croupier1.calculerTotal();

    if (totalCroupier > 21 || totalJoueur > totalCroupier) {
        cout << "Vous gagnez !" << endl;
    } else if (totalJoueur < totalCroupier) {
        cout << "Le croupier gagne !" << endl;
    } else {
        cout << "Égalité !" << endl;
    }

    return 0;
}