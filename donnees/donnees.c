/*
Copyright mars 2018, Stephan Runigo
runigo@free.fr
SiCP 1.6 simulateur de chaîne de pendules
Ce logiciel est un programme informatique servant à simuler l'équation
d'une chaîne de pendules et à en donner une représentation graphique.
Ce logiciel est régi par la licence CeCILL soumise au droit français et
respectant les principes de diffusion des logiciels libres. Vous pouvez
utiliser, modifier et/ou redistribuer ce programme sous les conditions
de la licence CeCILL telle que diffusée par le CEA, le CNRS et l'INRIA
sur le site "http://www.cecill.info".
En contrepartie de l'accessibilité au code source et des droits de copie,
de modification et de redistribution accordés par cette licence, il n'est
offert aux utilisateurs qu'une garantie limitée. Pour les mêmes raisons,
seule une responsabilité restreinte pèse sur l'auteur du programme, le
titulaire des droits patrimoniaux et les concédants successifs.
A cet égard  l'attention de l'utilisateur est attirée sur les risques
associés au chargement, à l'utilisation, à la modification et/ou au
développement et à la reproduction du logiciel par l'utilisateur étant
donné sa spécificité de logiciel libre, qui peut le rendre complexe à
manipuler et qui le réserve donc à des développeurs et des professionnels
avertis possédant des connaissances informatiques approfondies. Les
utilisateurs sont donc invités à charger et tester l'adéquation du
logiciel à leurs besoins dans des conditions permettant d'assurer la
sécurité de leurs systèmes et ou de leurs données et, plus généralement,
à l'utiliser et l'exploiter dans les mêmes conditions de sécurité.
Le fait que vous puissiez accéder à cet en-tête signifie que vous avez
pris connaissance de la licence CeCILL, et que vous en avez accepté les
termes.
*/

#include "donnees.h"

	//		Valeurs initiales des données physiques du simulateur,
	//						et création du système

	//		Valeur initiale et création du graphe

	//		Initialisation de la SDL


int donneesSysteme(systemeT * systeme, optionsT * options);
int donneesGraphe(grapheT * graphe, optionsT * options);

int donneesControleur(controleurT * control)
	{

	//(*control).duree = (*control).options.duree;	// 100 : temps réèl. Voir options.c
	//(*control).mode = 1;	// -1 : Wait, 1 : Poll
	(*control).sortie = 0;	// Sortie de SiCP si > 0
	(*control).appui = 0;	// Appuie sur la souris

		fprintf(stderr, " Initialisation du système\n");
	donneesSysteme(&(*control).systeme, &(*control).options);

		fprintf(stderr, " Création du système\n");
	systemeCreation(&(*control).systeme);
	changeFormeDissipation(&(*control).systeme, 2);
		fprintf(stderr, " Initialisation du graphe\n");
	donneesGraphe(&(*control).graphe, &(*control).options);

		fprintf(stderr, " Création du graphe\n");
	grapheCreation(&(*control).graphe, (*control).options.nombre);

		fprintf(stderr, " Initialisation de la projection\n");
		fprintf(stderr, "projectionInitialiseCouleurs\n");
	projectionInitialiseCouleurs(&(*control).projection, 222, 111, 222, 255);// r, v, b, fond
		fprintf(stderr, "projectionInitialiseLongueurs\n");
	projectionInitialiseLongueurs(&(*control).projection, HAUTEUR/3, LARGEUR*0.7, 0.9);// hauteur, largeur, perspective
		fprintf(stderr, "projectionInitialisePointDeVue\n");
	projectionInitialisePointDeVue(&(*control).projection, 3*LARGEUR, PI/2 - 0.27, PI/2 + 0.21);//r, psi, phi
	//projectionInitialisePointDeVue(&(*control).projection, 3*LARGEUR, 0.0, 0.0);//r, psi, phi

		fprintf(stderr, " Initialisation SDL\n");
	graphiqueInitialise((*control).options.fond);

	return 0;
	}

int donneesOptions(optionsT * options)
	{
		// Préréglage des valeurs optionnelles

	(*options).duree = 91;		// 100 : temps réèl.
	(*options).fond=240;		// couleur du fond de l'affichage
	(*options).support=1;		// Support de la chaîne
	(*options).nombre=233;		// nombre de pendule
	(*options).equation=1;		// 1 : pendule, 2 : linéarisation,
							//	 3 : corde, 4 : dioptre

	(*options).dt=0.0003;		// discrétisation du temps
							// 25 images par seconde, SDL_Delay(30);
							// dt*duree = 0.004
	(*options).pause=25;		// temps de pause SDL en ms

	(*options).soliton=4;
							
	return 0;
	}

int donneesSysteme(systemeT * systeme, optionsT * options)
	{

		// Initialisation du moteurs

	(*systeme).moteur.dt = (*options).dt;	// discrétisation du temps
	//(*systeme).moteur.horloge = 0.0;
	(*systeme).moteur.chrono = 0.0;

	(*systeme).moteur.courant=15.0;		// Mémoire courant Josephson si = 0
	(*systeme).moteur.josephson=-3*(*options).dt*(*options).dt;

	(*systeme).moteur.generateur = 0;	// éteint, sinus, carre, impulsion
	(*systeme).moteur.amplitude=0.3;		// Amplitude du générateur de signaux
	(*systeme).moteur.frequence=5.0;	// Ffréquence du générateur de signaux
	(*systeme).moteur.phi=0;


		// Caractéristique de la chaîne
	(*systeme).libreFixe = 0;	// 0 periodique, 1 libre, 2 fixe
	(*systeme).nombre = (*options).nombre;		// nombre de pendule
	(*systeme).equation = (*options).equation;	// 1 : pendule pesant
												// 2 : linéarisation
												// 3 : corde
												// 4 : dioptre

		// Paramètres physiques
	(*systeme).gravitation = 9.81;
	(*systeme).masse = 1.0;
	(*systeme).longueur = 9.81/4/PI/PI; // = 25 cm => période = 1 s
	(*systeme).dissipation = 0.3;
	(*systeme).couplage = 11.1 * (*systeme).nombre;
	(*systeme).dephasage = (*options).soliton * 2 * PI;




	if((*systeme).equation == 3 || (*systeme).equation == 4)
		{		 // donneeCorde;
		(*systeme).couplage = (*systeme).couplage * 10.0;
		(*systeme).gravitation = 0.0;
		(*systeme).libreFixe = 2;
		(*systeme).moteur.josephson=0.0;
		}

	return 0;
	}

int donneesGraphe(grapheT * graphe, optionsT * options)
	{
	(*graphe).rouge=20;
	(*graphe).bleu=150;
	(*graphe).vert=200;
	(*graphe).fond=(*options).fond;	//	Couleur du fond
	(*graphe).support=(*options).support;	//	Couleur du fond
	(*graphe).dessous = 0;	// Vue de dessous
	(*graphe).gauche = 0;		// Vue de gauche
	return 0;
	}

//////////////////////////////////////////////////////////////////////////
