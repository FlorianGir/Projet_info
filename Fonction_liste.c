#include <stdio.h>
#include <stdlib.h>
#include "Fonction_liste.h"


L_LEX creer_liste_lex(void) {
	return NULL;
}

MOT creer_liste_mot(void) {
	return NULL;
}

L_LEX ajout_tete_lex(L_LEX l_lex, LEXEME lex, MOT l_mot) {
	L_LEX p = NULL;				// Création pointeur sur liste lexeme
	p = calloc(1, sizeof(*p));		// Allocation de mémoire
	p->lex = lex;				// On complète le bloc cree
	p->mot = l_mot;
	p->suiv = l_lex;			// Liaison du bloc avec les suivants
 	return p;				// On renvoie p pour ajouter le bloc en tete
}


L_LEX ajout_queue_lex(L_LEX l_lex, LEXEME lex, MOT l_mot) {
	L_LEX p = NULL;
	p = calloc(1, sizeof(*p));
	p->lex = lex;
	p->mot = l_mot;
	if (l_lex == NULL) return p;	// Si liste NULL, on a que ce bloc en memoire
	else {				// Sinon, on parcour la liste pour arriver jusqu'au pointeur de fin 
		L_LEX q = l_lex;
		while (q->suiv != NULL) {
			q = q->suiv;
		}
		q->suiv = p;		// On rattache le bloc cree en fin de liste
		return l_lex;
	}
}



MOT ajout_tete_mot(MOT l_mot, int c) {
	MOT p = NULL;				
	p = calloc(1, sizeof(*p));		
	p->c = c;				
	p->suiv = l_mot;			
 	return p;				
}


MOT ajout_queue_mot(MOT l_mot, int c) {
	MOT p = NULL;				
	p = calloc(1, sizeof(*p));		
	p->c = c;
	if (l_mot == NULL) return p;	
	else {				
		MOT q = l_mot;
		while (q->suiv != NULL) {
			q = q->suiv;
		}
		q->suiv = p;		
		return l_mot;
	}	
}


void affiche_lex(L_LEX p_lex) {

	if (p_lex->lex == DEBUT) printf("DEBUT \n");
	else if (p_lex->lex == COMMENT) printf("COMMENT \n");
	else if (p_lex->lex == NL) printf("NL \n");
	else if (p_lex->lex == SYMBOLE) printf("SYMBOLE \n");
	else if (p_lex->lex == DEUX_PTS) printf("DEUX_PTS \n");
	else if (p_lex->lex == DIRECTIVE) printf("DIRECTIVE \n");
	else if (p_lex->lex == VIRGULE) printf("VIRGULE \n");
	else if (p_lex->lex == DECIMAL) printf("DECIMAL \n");
	else if (p_lex->lex == DECIMAL_ZERO) printf("DECIMAL_ZERO \n");
	else if (p_lex->lex == HEXA) printf("HEXA \n");
	else if (p_lex->lex == AUTRE) printf("AUTRE \n");
	else if (p_lex->lex == REGISTRE) printf("REGISTRE \n");
	else if (p_lex->lex == GUIL) printf("GUIL \n");
	else if (p_lex->lex == PAR_O) printf("PAR_O \n");
	else if (p_lex->lex == PAR_F) printf("PAR_F \n");
	return;
}

void affiche_mot(L_LEX p_lex) {
	MOT q = p_lex->mot;
	while (q != NULL) {
		printf("%c", q->c);
		q = q->suiv;
		
	}
	printf("\n");
	return;
}


// TEST :

/*void main() {
	
	FILE* fichier;
	MOT mot = NULL, p;
	int c;
	
	fichier = fopen("miam_sujet.s", "r");
	if (fichier == NULL) perror("Erreur ouverture fichier");    
	printf("1 \n");
	c = fgetc(fichier);
	while ( (c = fgetc(fichier)) != EOF) {
		printf("%c \n", c);
		
		mot = ajout_queue_mot(mot, c);
		
	}
	printf("2 \n");
	p = mot;
	while (p != NULL) {
		printf("%c \n", p->c);
		p = p->suiv;
	}
	return;
}
*/
