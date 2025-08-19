// Projet : chiffrement d'une phrase en MAJUSCULES (inspiration Vignère Cipher : https://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher ) 
// Fichier : encrypt.cpp
// Autrice : Amani Ben Abdeljaoued
// Date_1.0 : 13.08.2025
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//-Révision_1.2 : 18.08.2025 de la fonction calcul_cle()                                                                                           //
//-Révision_2.0 : 19.08.2025 de la fonction calcul_cle():                                                                                          //
// tester sur plutôt toute la longueur que longueur / 2 pour éviter quand la clé est à son max et qu'on a motif de 4 qui se répéte vers la fin     //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// librairies nécessaires
#include <iostream> //cout, cin
#include <cstdio> // FILE & co
#include <cstdlib> //exit 
#include <cstring> //strlen, strcp, strcat 

using namespace std; //cout ,cin, strlen 

//fonctions
//Décalage : fonction() //////////////////////////////////////////////////

void decalage(const char phrase[], const char cle[], char cle_tampon[]) {
    int len_phrase = strlen(phrase);
    int len_cle = strlen(cle);

    cout << "Décalage :\t";
    for (int i = 0; i < len_phrase; i++) {
        cle_tampon[i] = cle[i % len_cle]; // répéter la clé
        cout << (cle_tampon[i] - 'A') << " "; // affichage du décalage
    }
    cout << endl;
}
////////////////////////////////////////////////////////////////////////////////
//Cryptage : fonction () ///////////////////////////////////////////////////////
void cryptage(const char phrase[], const char cle_tampon[], char cryptee[]) {
    int len_phrase = strlen(phrase);
    cout << "Chiffrement :\t";
    for (int i = 0; i < len_phrase; i++) {
        cryptee[i] = ((phrase[i] - 'A') + (cle_tampon[i] - 'A')) % 26 + 'A';
        cout << cryptee[i];
    }
    cryptee[len_phrase] = '\0'; // terminer la chaîne
    cout << endl;
}
///////////////////////////////////////////////////////////////////////////////////
//Calcul clé : fonction () ///////////////////////////////////////////////////////
void calcul_cle(const char phrase[], const char cryptee[], char deviner[]) {
    int len = strlen(phrase);
    int min_cle = 4; // \n de la fin de chaine de car
    int max_cle = len / 2;  // clé <  1/2 phrase

    bool trouve = false;     // flag pour clé trouvée
    int long_cle = max_cle;  // initialisation à max

    // tampon pour contenir la clé "brute" sur max_cle lettres
    char devine_tampon[len];  //taille
    for (int i = 0; i < len; i++) {
        devine_tampon[i] = ((cryptee[i] - phrase[i] + 26) % 26) + 'A';
    }
    devine_tampon[len] = '\0';  //index : commence à zéro

    // tester toutes les longueurs possibles de répétition
    for (int long_cherchee = max_cle*2 - 3; long_cherchee >=  min_cle && !trouve; long_cherchee--) 
    { 
        // vérifier si motif à 4 lettres existe
        if (
            devine_tampon[0] != devine_tampon[long_cherchee] ||
            devine_tampon[1] != devine_tampon[long_cherchee + 1] ||
            devine_tampon[2] != devine_tampon[long_cherchee + 2] ||
            devine_tampon[3] != devine_tampon[long_cherchee + 3]) 
        {
            continue; // pas de motif, passer à la prochaine longueur
        }
        //motif trouvé ! on a un entier de répétition de clé
        //tester toutes les répétitions possibles
        long_cle = long_cherchee; // initier à au moins toute la longueure
        
        for (int rep = long_cherchee / 4; rep > 1 && !trouve; rep--) // on divise par rep, donc eviter 0

        {   
            //if (rep == 1 ) cand = max_cle; 
            if (long_cherchee % rep != 0) continue; // pas multiple exact

            int cand = long_cherchee / rep; //pas diviser par 0
            int motif_ok = 1;

            // vérifier que CHAQUE répétition contient le même mot, si vrai mot = clé
            for (int j = 1; j < rep; j++) 
            { // j commence à 1
                for (int k = 0 ; k <= cand - 1; k++)
                    {
                        if (devine_tampon[j*k] != devine_tampon[(j+1)*k]) 
                        {motif_ok; break;}
                    } 
            }

            if (motif_ok) { // répétition correcte
                long_cle = cand;   // longueur exacte de la clé
                trouve = true;     // sortir de toutes les boucles
            }
        }
    }

    // copier exactement la clé devinée (long_cle lettres)
    
    for (int i = 0; i < long_cle; i++) {
        deviner[i] = devine_tampon[i];
    }
    deviner[long_cle] = '\0'; // fin de chaîne

    
    cout << "Clé devinée (☞⌐▀͡ ͜ʖ͡▀ )☞ : " << deviner << endl; //https://texteditor.com/text-faces/
}



//limite majeur ici, si le mot est symétrique : répétitions dedans (exemple CLECLE), on va reporter la plus longue clé possible
// si c'est un multiple dela longueur : donc ici plus la clé est courte est une répétition en soit, plus on a de chance de se tromper


/////////////////////////////////////////////////////////////////////////////////////
// Programme principal /////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

int main() {
    ///programme principal qui lit la phrase à chiffrer, la clé de chiffrement,
    /// envoie le résultat et devine à partir de la phrase et le chiffrement la clé
    //message de bienvenue
    cout << "*********************************************************" << endl;
    cout << "*                                                       *" << endl;
    cout << "*              Projet4: Cryptographie   .ABA            *" << endl;
    cout << "*                                                       *" << endl;
    cout << "*********************************************************" << endl;
    cout << endl;
    cout << "*********************************************************" << endl;
    cout << "*                                                       *" <<endl;
    cout << "*                     Bienvenue                         *" << endl;
    cout << "*   Ce programme vous permet de chiffrer une phrase     *" << endl;
    cout << "*   en MAJUSCULES en utilisant une clé de chiffrement.  *" << endl;
    cout << "*         Les conditions sont les suivantes :           *" << endl;
    cout << "* - Pas de caractères spéciaux, especes ni miniscules   *" << endl;
    cout << "* - La phrase doit contenir au moins 9 caractères       *" << endl;
    cout << "* - La clé doit contenir au moins 4 caractères et       *" << endl;
    cout << "*   ne pas dépasser la 1/2 la longueur de la phrase     *"<< endl;
    cout << "* - Vous avez 3 essais                                  *" <<endl;
    cout << "*                                                       *" <<endl;
    cout << "*********************************************************" << endl;
    cout << endl;
    cout << "Le programme enregistrera vers la fin les résultats dans un fichier." << endl;
    cout << endl;

    cout << "Entrez le chemin du fichier pour enregistrer les résultats : ";
    cout << endl;

    char chemin_fichier[256];
    cin >> chemin_fichier;
    int essai = 1;
    cout << endl;

    char text_depart[256]; // ou réécrire pour plus long 
    char la_clee[128]; // au moins moitié de la phrase
    char text_crypte[256];
    int condition = 0; // Conditions à respecter pour la phrase
    char cle_tampon[256]; // tampon pour la clé
    char devine_cle[128]; // clé à deviner 

    //lire la phrase à chiffrer//
    while (essai < 4 && condition == 0) {   
        cout << "Essai " << essai << " : " << endl;
        cout << "Entrez une phrase à chiffrer qui respecte les conditions citées: " << endl;
        cin >> text_depart;

        if (strlen(text_depart) < 9) {
            cout << "La phrase doit être au moins de 9 caractères." << endl;
            essai++;
            continue; // passer à l'essai suivant
        }

        condition = 1; // on suppose que la phrase est bonne
        for (int i = 0; i < strlen(text_depart); i++) {
            if (text_depart[i] < 'A' || text_depart[i] > 'Z') {
                cout << "La phrase doit être en MAJUSCULES." << endl;
                condition = 0; // phrase invalide
                break; // inutile de continuer
            }
        }

        if (!condition) {
            essai++;
        }
    } // sortie du while pour la phrase et vérification si on est à 4 essais pour sortir du programme

    if (essai == 4) {
        cout << "Vous avez dépassé le nombre d'essais autorisés." << endl;
        exit(-1);
    }
            
    //lire la clé de chiffrement//
    condition = 0; // réinitialiser la condition pour la clé
    essai = 1; // réinitialiser le nombre d'essais
    while (essai < 4 && condition == 0) {
        cout << "Essai pour la clé " << essai << " : " << endl;
        cout << "Entrez la clé de chiffrement qui respecte les conditions citées: " << endl;
        cin >> la_clee;
        if (strlen(la_clee) < 4 || strlen(la_clee) > strlen(text_depart) / 2) {
            cout << "La clé doit être au moins de 4 caractères et au max la moitié de la phrase à chiffrer." << endl;
            essai++;
            continue; // passer à l'essai suivant
        }
        condition = 1; // on suppose que la clé est bonne
        for (int i = 0; i < strlen(la_clee); i++) {
            if (la_clee[i] < 'A' || la_clee[i] > 'Z') {
                cout << "La clé doit être en MAJUSCULES." << endl;
                condition = 0; // clé invalide
                break; // inutile de continuer
            }
        }   
        if (!condition) {
            essai++;
        }
    } // sortie du while pour la clé et vérification si on est à 4 essais pour sortir du programme
    if (essai == 4) {
        cout << "Vous avez dépassé le nombre d'essais autorisés pour la clé." << endl;
        exit(-1); //sorti du programme
    }

    decalage(text_depart, la_clee, cle_tampon);
    cout << endl;
    cryptage(text_depart, cle_tampon, text_crypte);
    cout << endl;
    calcul_cle(text_depart, text_crypte, devine_cle);
    if (strlen(devine_cle) != strlen (la_clee))
    {
        cout << endl;
        cout << "Noooooon !! (┛◉Д◉)┛彡┻━┻ " << endl;
        cout << "La clé devinée est incorrecte " << endl;
    }


    // Sauvegarder les résultats dans un fichier //////////////////////////////////////////////////////////////
    char chemin_complet[256]; // variable pour stocker le fichier avec son chemin complet
    strcpy(chemin_complet, chemin_fichier);  //chemin
    strcat(chemin_complet, "/Sortie.txt"); // fichier avec chemin
    FILE *fichier = fopen(chemin_complet, "w+"); // écrase et réécrit le fichier
    if (fichier != NULL) {
    // En-tête
        fprintf(fichier, "Lettres: \t A B C D E F G H I  J  K  L  M  N  O  P  Q  R  S  T  U  V  W  X  Y  Z\n");
        fprintf(fichier, "Rang alphabet: \t 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26\n\n");
    
        // Clé et texte original
        fprintf(fichier, "Clé utilisée: \t %s\n", la_clee);
        fprintf(fichier,"Décalage clé:    ");
        for (int i = 0; i < strlen(la_clee); i++) {
            fprintf(fichier, "%d ", la_clee[i] - 'A');
        }   
        fprintf(fichier, "\nTexte départ: \t %s\n", text_depart);
        
        // Rangs initiaux
        fprintf(fichier, "Rangs initiaux:\t ");
        for (int i = 0; i < strlen(text_depart); i++) {
            fprintf(fichier, "%d ", text_depart[i] - 'A');
        }
        
        // Décalages
        fprintf(fichier, "\nDécalages:\t ");
        for (int i = 0; i < strlen(text_depart); i++) {
            fprintf(fichier, "%d ", cle_tampon[i] - 'A');
        }
        
        // Somme avant 
        fprintf(fichier, "\nSomme avant :\t ");
        for (int i = 0; i < strlen(text_depart); i++) {
            fprintf(fichier, "%d ", (text_depart[i] - 'A') + (cle_tampon[i] - 'A'));
        }
        
        // Rangs finaux
        fprintf(fichier, "\nRangs finaux:\t ");
        for (int i = 0; i < strlen(text_depart); i++) {
            fprintf(fichier, "%d ", (text_crypte[i] - 'A'));
        }
        
        // Résultats complets
        fprintf(fichier, "\n\nTexte départ:\n %s\n", text_depart);
        fprintf(fichier, "Texte crypté:\n %s\n", text_crypte);
        
        fclose(fichier); // fermer le ficher et afficher un msg : ceci veut dire que la boule d'écriture a bien fonctionné
        cout << "J'ai sauvegardé le fichier Sortie.txt dans " << chemin_fichier << endl;
        }
    else //chemin non conforme, le programme marche mais n'enregistre rien
        {
        cout << endl;
        cout << "Noooooon !! (┛◉Д◉)┛彡┻━┻ " << endl;
        cout << "Sortie.txt non enregistré à cause d'une erreur de chemin\nVérifiez le chemin (dir) donné.\nFaite pwd et copier/coller tell qu'il est." << endl;
        }


    cout << endl;    
    return 0;
}
