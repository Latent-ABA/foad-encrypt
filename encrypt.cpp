// Projet : chiffrement d'une phrase en MAJUSCULES (inspiration Vignère Cipher : https://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher ) 
// Fichier : encrypt.cpp
// Autrice : Amani Ben Abdeljaoued
// Date_1.0 : 13.08.2025
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//-Révision_1.2 : 18.08.2025 de la fonction calcul_cle()                                                                                           //
//-Révision_2.0 : 19.08.2025 de la fonction calcul_cle()											   //
//Révision_2.1 : 20.08.2025 de la fonction calcul_cle()	                                                                                           //
//																		   //
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
    cle_tampon[len_phrase] = '\0';
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
void calcul_cle(const char phrase[], const char cryptee[] ,char deviner[]) {
    int len = strlen(phrase);
    //ici devine tampon c'est la clé avec répétition !! donc on connais pas la clé finalement !
    int min_cle = 4; //  de la fin de chaine de car
    int max_cle = len / 2 - 1;  // clé <  1/2 phrase -1

    bool trouve = false;     // flag pour clé trouvée
    int long_cle = max_cle;  // initialisation à max
    //cette fonction dois fonctionner sans avoir une idée de la clé (même clé tampon)
    char devine_tampon[len+1];  //taille
    for (int i = 0; i < len; i++) {
        devine_tampon[i] = ((cryptee[i] - phrase[i] + 26) % 26) + 'A';
    }
    devine_tampon[len] = '\0';  //index : commence à zéro

     // devine tampon est clé tampon générée par la fonction decalage
    // tester toutes les longueurs possibles de répétition
	for (int long_cherchee = len-1; long_cherchee >=  min_cle && !trouve; long_cherchee--) 
	{ 	
	    for (int rep = long_cherchee / 4; rep > 1 && !trouve; rep--) 
	    {   
		if (long_cherchee % rep != 0) continue; // pas multiple exact

		int cand = long_cherchee / rep;
		int motif_ok = 1;

		for (int j = 1; j < rep; j++) 
		{
		    for (int k = 0 ; k < cand; k++) // vérifier que CHAQUE répétition à longueur candidate cand contient le même mot, si vrai mot = clé
		    {

		        if (devine_tampon[k] != devine_tampon[j*cand + k]) 
		        {
		            motif_ok = 0; break; // au moindre inégalité, on sort de la boucle de vérification ici: boucle imbriquée 1/2
		        }
		    }
		    if (!motif_ok) break;  // au moindre inégalité de lettre, on sort de la boucle de répétition aussi 2/2
		}
 
		if (motif_ok) { // seule candition pour retenir cand comme longueur et pas long_max, cette condition couvre aussi la longueue de 4 , minimal, car dans nos conditions initiales on fait en sorte d'avoir au moins deux
		    long_cle = cand;
		    trouve = true;
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



//limite majeur ici, si le mot est symétrique : répétitions dedans (exemple CLECLE) : sans info supplémentaire sur la taille de la clé, le programme donnera
//une clé avec le pattern correct mais symétrie non controlée (dépendra de la congueure de la phrase en plus du multiplicateur, on a celui de la symétrie) 



/////////////////////////////////////////////////////////////////////////////////////
// Programme principal /////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

int main() {
    ///programme principal qui lit la phrase à chiffrer, la clé de chiffrement,
    /// envoie le résultat et devine à partir de la phrase et le chiffrement la clé
    ///message de bienvenue
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
    cout << "* - La phrase doit contenir au moins 10 caractères      *" << endl;
    cout << "* - La clé doit contenir au moins 4 caractères et       *" << endl;
    cout << "*   ne pas dépasser la 1/2 la longueur de la phrase -1  *"<< endl;
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

        if (strlen(text_depart) <=9) {
            cout << "La phrase doit être au moins de 10 caractères." << endl;
            essai++;
            continue; // passer à l'essai suivant
        }

        condition = 1; // on suppose que la phrase est bonne
        for (int i = 0; i < strlen(text_depart); i++) {
            if (text_depart[i] < 'A' || text_depart[i] > 'Z') {
                cout << "La phrase doit être en MAJUSCULES." << endl;
                condition = 0; // phrase invalide
		essai++;
                break; // inutile de continuer
            }
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
        if (strlen(la_clee) < 4 || strlen(la_clee) > strlen(text_depart) / 2 -1 ) {
            cout << "La clé doit être au moins de 4 caractères et au max la moitié de la phrase à chiffrer." << endl;
            essai++;
            continue; // passer à l'essai suivant
        }
        condition = 1; // on suppose que la clé est bonne
        for (int i = 0; i < strlen(la_clee); i++) {
            if (la_clee[i] < 'A' || la_clee[i] > 'Z') {
                cout << "La clé doit être en MAJUSCULES." << endl;
                condition = 0; // clé invalide
		essai++;
                break; // inutile de continuer
            }
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
    if (strlen(devine_cle) != strlen (la_clee)) //comparaison de la longueur de la clé devinée et celle donnée pour savoir si on est bon
    { 
        cout << endl;
        cout << "Noooooon !! (┛◉Д◉)┛彡┻━┻ " << endl;
        cout << "La clé devinée est incorrecte " << endl;
    }


    // sauvegarder les résultats dans le fichier Sortie.txt /////////////////////////////////////////////////////
    char chemin_complet[256]; // variable pour stocker le fichier avec son chemin complet
    strcpy(chemin_complet, chemin_fichier);  //chemin
    strcat(chemin_complet, "/Sortie.txt"); // fichier avec chemin
    FILE *fichier = fopen(chemin_complet, "w+"); // écrase et réécrit le fichier ici le chemin doit être correcte
    if (fichier != NULL) {
    // lettres et correspondance en rang
        fprintf(fichier, "Lettres: \t A B C D E F G H I  J  K  L  M  N  O  P  Q  R  S  T  U  V  W  X  Y  Z\n");
        fprintf(fichier, "Rang alphabet: \t 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26\n\n");
    
        // Clé et texte original
        fprintf(fichier, "Clé utilisée: \t %s\n", la_clee);
        fprintf(fichier,"Décalage clé:    ");
        for (int i = 0; i < strlen(la_clee); i++) {
            fprintf(fichier, "%d ", la_clee[i] - 'A');
        }   
        fprintf(fichier, "\nTexte départ: \t %s\n", text_depart);
        
        // rangs de départ
        fprintf(fichier, "Rangs initiaux:\t ");
        for (int i = 0; i < strlen(text_depart); i++) {
            fprintf(fichier, "%d ", text_depart[i] - 'A');
        }
        
        // décalages
        fprintf(fichier, "\nDécalages:\t ");
        for (int i = 0; i < strlen(text_depart); i++) {
            fprintf(fichier, "%d ", cle_tampon[i] - 'A');
        }
        
        // somme avant 
        fprintf(fichier, "\nSomme avant :\t ");
        for (int i = 0; i < strlen(text_depart); i++) {
            fprintf(fichier, "%d ", (text_depart[i] - 'A') + (cle_tampon[i] - 'A'));
        }
        
        // rangs finaux
        fprintf(fichier, "\nRangs finaux:\t ");
        for (int i = 0; i < strlen(text_depart); i++) {
            fprintf(fichier, "%d ", (text_crypte[i] - 'A'));
        }
        
        // affichage text de départ et final
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
