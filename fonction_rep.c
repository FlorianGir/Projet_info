#include <stdio.h>

#include <stdlib.h>
#include <string.h>

#include <math.h>
#include <ctype.h>

#include "fonction_rep.h"

#include "Fonction_liste.h"





L_INST ajout_queue_inst(L_INST l_inst, MOT mot, LEXEME lex, int nb_op, int ligne, int decalage, L_LEX operande) {

	L_INST p = NULL;

	p = calloc(1, sizeof(*p));

	p->mot = mot;
	p->lex = lex;

	p->nb_op = nb_op;

	p->ligne = ligne;

	p->decalage = decalage;

	p->operande = operande;

	if (l_inst == NULL) return p;	//! Si liste NULL, on a que ce bloc en memoire

	else {				//! Sinon, on parcour la liste pour arriver jusqu'au pointeur de fin 

		L_INST q = l_inst;

		while (q->suiv != NULL) {

			q = q->suiv;

		}

		q->suiv = p;		//! On rattache le bloc cree en fin de liste

		return l_inst;

	}

}





L_DATA ajout_queue_data(L_DATA l_data, char mot[20], LEXEME lex, int nb_op, int ligne, int decalage, L_LEX operande) {

	L_DATA p = NULL;

	p = calloc(1, sizeof(*p));

	strcpy(p->mot, mot);
	p->lex = lex;

	p->nb_op = nb_op;

	p->ligne = ligne;

	p->decalage = decalage;

	p->operande = operande;

	if (l_data == NULL) return p;	//! Si liste NULL, on a que ce bloc en memoire

	else {				//! Sinon, on parcour la liste pour arriver jusqu'au pointeur de fin 

		L_DATA q = l_data;

		while (q->suiv != NULL) {

			q = q->suiv;

		}

		q->suiv = p;		//! On rattache le bloc cree en fin de liste

		return l_data;

	}

}



L_BSS ajout_queue_bss(L_BSS l_bss, char mot[20], LEXEME lex, int nb_op, int ligne, int decalage, L_LEX operande) {

	L_BSS p = NULL;

	p = calloc(1, sizeof(*p));

	strcpy(p->mot, mot);
	p->lex = lex;

	p->nb_op = nb_op;

	p->ligne = ligne;

	p->decalage = decalage;

	p->operande = operande;

	if (l_bss == NULL) return p;	//! Si liste NULL, on a que ce bloc en memoire

	else {				//! Sinon, on parcour la liste pour arriver jusqu'au pointeur de fin 

		L_BSS q = l_bss;

		while (q->suiv != NULL) {

			q = q->suiv;

		}

		q->suiv = p;		//! On rattache le bloc cree en fin de liste

		return l_bss;

	}

}





L_SYMB ajout_queue_symb(L_SYMB l_symb, MOT mot, int ligne, char section[20], int decalage) {

	L_SYMB p;

	p = calloc(1, sizeof(*p));

	p->mot = mot;

	p->ligne = ligne;

	strcpy(p->section, section);

	p->decalage = decalage;

	if (l_symb == NULL) return NULL;	//! Si liste NULL, on a que ce bloc en memoire

	else {				//! Sinon, on parcours la liste pour arriver jusqu'au pointeur de fin 

		L_SYMB q = l_symb;

		while (q->suiv != NULL) {

			q = q->suiv;

		}

		q->suiv = p;		//! On rattache le bloc cree en fin de liste

		return l_symb;

	}

}







void recup_mot(MOT mot, char tab[]){		//! Recupere un mot et fait une chaine de caractere avec, placee dans tab



	MOT q = mot;

	int a = 0;

	if ( q == NULL) {

		tab[0] = '\0';

	}

	else {		

		while((q != NULL) && (a < 99)){

			tab[a] = q->c;

			q = q->suiv;

			a++;

		}

		tab[a]='\0';

	}

	return;

}

	







int symb_existe(MOT mot){		//! regarde si la directive existe et renvoie son nombre d'operande si oui et -1 sinon



	int let_fich, test;

	FILE* fich;

	MOT q;

	fich = fopen("dico.txt", "r");

	if (fich == NULL) perror("Erreur ouverture fichier");	//! Si erreur ouverture

	

	test = 1;

	while ((let_fich = fgetc(fich)) != EOF) {	//! Tant que pas a la fin du fichier

		test = 1;

		q = mot;

		if (let_fich == toupper(q->c)){		//! touuper(...) --> add équivalent a ADD

			while ( q->suiv != NULL){

				q = q->suiv;

				let_fich = fgetc(fich);

				if (let_fich == toupper(q->c)) test = test*1;

				else test = test*0;

			}

			if (test == 1) return fgetc(fich);

			else while (let_fich != '\n') let_fich = fgetc(fich);



		}

		else {

			while (let_fich != '\n') let_fich = fgetc(fich);

		}

	}

	return -1;

}












int verification_word_byte(MOT mot, LEXEME lex, ETAT A) {		 //!fonction qui verifie les conditions operande de word et byte, renvoie 0 si c'est bon et 1 si non

	int a;
	
	if ((lex == DECIMAL) || (lex = HEXA)){				//! Si nombre Hexa ou Deci
		a = valeur_deci(mot, lex);				//! Conversion de la valeur en entier
		
		if (A == DATA_WORD) {					//! Si on est dans la section .data
			if ((a < 2147483647) && (a > -2147483648)) return 0;		//! Condition de validite
			else return 1;
		
		}
		else if (A == DATA_BYTE) {				//! Si on est dans la section .byte
			if ((a < 127) && (a > -128)) return 0;		//! Condition de validite
			else return 1;
	
		}
	}

	else if (lex == DECIMAL_ZERO) return 0;	
	
}







//! Compte le nombre de caractère d'un mot asciiz en comptant les  guillemets, il suffit de retrancher 1 pour prendre en compte uniquement les caractères et le '\0' de fin

int nbre_cara(MOT mot) {

	

	int compteur = 0;

	MOT q = mot;

	while (q != NULL) {

		compteur++;

		q = q->suiv;

	}

	return compteur;

}

		

	

//! Convertit une chaine de caractere decimale ou sous forme hexa en valeur decimale

int valeur_deci(MOT mot, LEXEME lex) {

	char tab[100];

	int i = 0;

	int valeur = 0;

	int nbre_chiffre_hexa;

	char deci_int[2];

	MOT q = mot;

	

	if (lex == DECIMAL) {			//! lex == DECIMAL

		recup_mot(mot, tab);

		return atoi(tab);		//! On convertit simplement la chaine de caractere en decimal

	}



	else if (lex == HEXA) {			//! lex == HEXA

		

		recup_mot(mot,tab);

		

		while (tab[i+2] != '\0') {	//! Compteur de caractere intervenant dans le calcul de la valeur decimale (sans le 0x devant)

			i++;

		}



		nbre_chiffre_hexa = i;

		

		q = q->suiv;

		for (i = 0; i < nbre_chiffre_hexa; i++) {	//! Calcul de la valeur en fonction du caractere hexadecimal

			q = q->suiv;				//! q commence a pointer sur le caractère après le 0x

			

			if (isdigit(tab[i+2])) {		//! Si c'est un chiffre

				deci_int[0] = q->c;

				valeur += (atoi(deci_int))*pow(16, nbre_chiffre_hexa - i - 1);

			}



			//! Si c'est une lettre (entre a et f, minuscule ou majuscule)

			else if (tolower(tab[i+2]) == 'a') valeur += 10*pow(16, nbre_chiffre_hexa - i - 1);

			else if (tolower(tab[i+2]) == 'b') valeur += 11*pow(16, nbre_chiffre_hexa - i - 1);	

			else if (tolower(tab[i+2]) == 'c') valeur += 12*pow(16, nbre_chiffre_hexa - i - 1);

			else if (tolower(tab[i+2]) == 'd') valeur += 13*pow(16, nbre_chiffre_hexa - i - 1);

			else if (tolower(tab[i+2]) == 'e') valeur += 14*pow(16, nbre_chiffre_hexa - i - 1);

			else if (tolower(tab[i+2]) == 'f') valeur += 15*pow(16, nbre_chiffre_hexa - i - 1);

		}

		return valeur;

	}



	else return 0;		//! lex == DECIMAL_ZERO

}

	

