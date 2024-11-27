#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <windows.h>  // Pour SetConsoleOutputCP

using namespace std;

// Définition d'une structure pour représenter un contact
struct Contact {
    string nom;       // Nom du contact
    string numero;    // Numéro de téléphone
    string email;     // Adresse email
    string adresse;   // Adresse postale
};

// Fonction pour afficher le menu principal
void afficherMenu() {
    cout << "\n=== Gestion de Contacts ===\n";
    cout << "1. Ajouter un contact\n";
    cout << "2. Modifier un contact\n";
    cout << "3. Rechercher un contact par nom\n";
    cout << "4. Supprimer un contact\n";
    cout << "5. Trier les contacts par nom\n";
    cout << "6. Sauvegarder les contacts dans un fichier\n";
    cout << "7. Charger les contacts depuis un fichier\n";
    cout << "8. Quitter\n";
    cout << "Votre choix: ";
}

// Fonction pour afficher tous les contacts
void afficherTousLesContacts(const vector<Contact>& contacts) {
    if (contacts.empty()) {
        cout << "Aucun contact à afficher.\n";
        return;
    }
    for (const auto& c : contacts) {
        cout << "Nom: " << c.nom << "\n";
        cout << "Numéro: " << c.numero << "\n";
        cout << "Email: " << c.email << "\n";
        cout << "Adresse: " << c.adresse << "\n";
        cout << "--------------------\n";
    }
}

// Fonction pour ajouter un contact
void ajouterContact(vector<Contact>& contacts) {
    try {
        Contact c;
        cout << "Entrez le nom: ";
        cin.ignore();
        getline(cin, c.nom);
        cout << "Entrez le numéro de téléphone: ";
        getline(cin, c.numero);
        cout << "Entrez l'email: ";
        getline(cin, c.email);
        cout << "Entrez l'adresse: ";
        getline(cin, c.adresse);
        contacts.push_back(c);
        cout << "Contact ajouté avec succès!\n";
    } catch (const exception& e) {
        cout << "Erreur lors de l'ajout du contact: " << e.what() << endl;
    }
}

// Fonction pour modifier un contact
void modifierContact(vector<Contact>& contacts) {
    try {
        string nomRecherche;
        cout << "Entrez le nom du contact à modifier: ";
        cin.ignore();
        getline(cin, nomRecherche);

        for (auto& c : contacts) {
            if (c.nom == nomRecherche) {
                cout << "Contact trouvé. Modifiez les informations.\n";
                cout << "Entrez le nouveau nom (ou appuyez sur Entrée pour conserver l'ancien): ";
                string nouveauNom;
                getline(cin, nouveauNom);
                if (!nouveauNom.empty()) c.nom = nouveauNom;

                cout << "Entrez le nouveau numéro de téléphone: ";
                getline(cin, c.numero);

                cout << "Entrez le nouvel email: ";
                getline(cin, c.email);

                cout << "Entrez la nouvelle adresse: ";
                getline(cin, c.adresse);

                cout << "Contact modifié avec succès!\n";
                return;
            }
        }
        cout << "Contact non trouvé.\n";
    } catch (const exception& e) {
        cout << "Erreur lors de la modification du contact: " << e.what() << endl;
    }
}

// Fonction pour rechercher un contact par nom
void rechercherContact(const vector<Contact>& contacts) {
    try {
        string nomRecherche;
        cout << "Entrez le nom à rechercher: ";
        cin.ignore();
        getline(cin, nomRecherche);

        for (const auto& c : contacts) {
            if (c.nom.find(nomRecherche) != string::npos) {
                cout << "Nom: " << c.nom << "\n";
                cout << "Numéro: " << c.numero << "\n";
                cout << "Email: " << c.email << "\n";
                cout << "Adresse: " << c.adresse << "\n";
                return;
            }
        }
        cout << "Aucun contact trouvé.\n";
    } catch (const exception& e) {
        cout << "Erreur lors de la recherche du contact: " << e.what() << endl;
    }
}

// Fonction pour supprimer un contact
void supprimerContact(vector<Contact>& contacts) {
    try {
        string nomRecherche;
        cout << "Entrez le nom du contact à supprimer: ";
        cin.ignore();
        getline(cin, nomRecherche);

        auto it = remove_if(contacts.begin(), contacts.end(),
                            [&nomRecherche](const Contact& c) { return c.nom == nomRecherche; });

        if (it != contacts.end()) {
            contacts.erase(it, contacts.end());
            cout << "Contact supprimé avec succès!\n";
        } else {
            cout << "Contact non trouvé.\n";
        }
    } catch (const exception& e) {
        cout << "Erreur lors de la suppression du contact: " << e.what() << endl;
    }
}

// Fonction pour trier les contacts par nom
void trierContacts(vector<Contact>& contacts) {
    try {
        sort(contacts.begin(), contacts.end(),
             [](const Contact& a, const Contact& b) { return a.nom < b.nom; });
        cout << "Contacts triés par nom avec succès!\n";
    } catch (const exception& e) {
        cout << "Erreur lors du tri des contacts: " << e.what() << endl;
    }
}

// Fonction pour sauvegarder les contacts dans un fichier
void sauvegarderContacts(const vector<Contact>& contacts) {
    try {
        string nomFichier;
        cout << "Entrez le nom du fichier pour sauvegarder les contacts : ";
        cin.ignore();
        getline(cin, nomFichier);

        ofstream fichier(nomFichier);
        if (!fichier.is_open()) {
            throw runtime_error("Impossible d'ouvrir le fichier.");
        }

        for (const auto& c : contacts) {
            fichier << "Nom: " << c.nom << "\n";
            fichier << "Numéro: " << c.numero << "\n";
            fichier << "Email: " << c.email << "\n";
            fichier << "Adresse: " << c.adresse << "\n";
            fichier << "--------------------\n";
        }
        fichier.close();
        cout << "Contacts sauvegardés dans le fichier " << nomFichier << " avec succès!\n";
    } catch (const exception& e) {
        cout << "Erreur lors de la sauvegarde des contacts: " << e.what() << endl;
    }
}

// Fonction pour charger les contacts depuis un fichier
void chargerContacts(vector<Contact>& contacts) {
    try {
        string nomFichier;
        cout << "Entrez le nom du fichier pour charger les contacts : ";
        cin.ignore();
        getline(cin, nomFichier);

        ifstream fichier(nomFichier);
        if (!fichier.is_open()) {
            throw runtime_error("Impossible d'ouvrir le fichier.");
        }

        contacts.clear();
        string ligne, nom, numero, email, adresse;
        while (getline(fichier, ligne)) {
            if (ligne.find("Nom: ") == 0) nom = ligne.substr(5);
            if (getline(fichier, ligne) && ligne.find("Numéro: ") == 0) numero = ligne.substr(8);
            if (getline(fichier, ligne) && ligne.find("Email: ") == 0) email = ligne.substr(7);
            if (getline(fichier, ligne) && ligne.find("Adresse: ") == 0) adresse = ligne.substr(9);

            contacts.push_back({nom, numero, email, adresse});
            getline(fichier, ligne); // Ignorer la ligne de séparation
        }
        fichier.close();
        cout << "Contacts chargés depuis le fichier " << nomFichier << " avec succès!\n";

        afficherTousLesContacts(contacts); // Afficher les contacts chargés
    } catch (const exception& e) {
        cout << "Erreur lors du chargement des contacts: " << e.what() << endl;
    }
}

// Fonction principale
int main() {
    // Configure la console pour utiliser UTF-8
    SetConsoleOutputCP(CP_UTF8);
    vector<Contact> contacts; // Liste des contacts
    int choix;

    do {
        afficherMenu(); // Afficher le menu
        cin >> choix;

        try {
            switch (choix) {
            case 1: ajouterContact(contacts); break;
            case 2: modifierContact(contacts); break;
            case 3: rechercherContact(contacts); break;
            case 4: supprimerContact(contacts); break;
            case 5: trierContacts(contacts); break;
            case 6: sauvegarderContacts(contacts); break;
            case 7: chargerContacts(contacts); break;
            case 8: cout << "Au revoir!\n"; break;
            default: throw invalid_argument("Choix invalide, réessayez.");
            }
        } catch (const exception& e) {
            cout << "Erreur: " << e.what() << endl;
        }

    } while (choix != 8);

    return 0;
}
