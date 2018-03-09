/*
Copyright mars 2018, Stephan Runigo
runigo@free.fr
SiCP 1.5  simulateur de chaîne de pendules
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

#include "options.h"

void optionsDt(optionsT * options, char *opt);
//void optionsEquation(optionsT * options, char *opt);
void optionsFond(optionsT * options, char *opt);
void optionsSupport(optionsT * options, char *opt);
void optionsNombre(optionsT * options, char *opt);
void optionsPause(optionsT * options, char *opt);
void optionsSoliton(optionsT * options, char *opt);
void optionsMode(optionsT * options, char *opt);
void optionsDuree(optionsT * options, char *opt);
void optionsAide();

int optionsTraitement(optionsT * options, int nb, char *opt[])
	{
	int i=0;
	//fprintf(stderr, "\nNombre d'options : %d\n", nb);
	// TODO int Moteur;	//	0:eteint, 1:sinus, 2:carre, 3:impulsion

	do
		{
		if(strcmp(opt[i], "fond")==0 && opt[i+1]!=NULL)
			optionsFond(options, opt[i+1]);  // Couleur du fond 
		if(strcmp(opt[i], "mode")==0 && opt[i+1]!=NULL)
			optionsMode(options, opt[i+1]);  // Mode -1 : Wait, 1 : Poll
		if(strcmp(opt[i], "pause")==0 && opt[i+1]!=NULL)
			optionsPause(options, opt[i+1]);	// temps de pause en ms
		if(strcmp(opt[i], "duree")==0 && opt[i+1]!=NULL)
			optionsDuree(options, opt[i+1]);	// Nombre d'évolution du système entre les affichages

		if(strcmp(opt[i], "support")==0 && opt[i+1]!=NULL)
			optionsSupport(options, opt[i+1]);	// Avec ou sans support

		//if(strcmp(opt[i], "equation")==0 && opt[i+1]!=NULL)
			//optionsEquation(options, opt[i+1]);	// choix de l'équation
		if(strcmp(opt[i], "dt")==0 && opt[i+1]!=NULL)
			optionsDt(options, opt[i+1]);	// discrétisation du temps

		if(strcmp(opt[i], "nombre")==0 && opt[i+1]!=NULL)
			optionsNombre(options, opt[i+1]);  // Nombre de pendules
		if(strcmp(opt[i], "soliton")==0 && opt[i+1]!=NULL)
			optionsSoliton(options, opt[i+1]);	// Nombre initial de solitons

		if(strcmp(opt[i], "aide")==0)
			optionsAide();	// Affiche l'aide.
		if(strcmp(opt[i], "help")==0)
			optionsAide();	// Affiche l'aide.

/*
		if(strcmp(opt[i], "th")==0 && opt[i+1]!=NULL)
			optionsThread(option, opt[i+1]);  // Deux threads
*/

  		i++;
  		}
		while(i<nb);
	return 0;
	}

    	// Nombre de pendules
void optionsNombre(optionsT * options, char *opt)
	{
	int nombre = atoi(opt);
	if(nombre>0 && nombre<NOMBRE_MAX)
		{
		(*options).nombre = nombre;
		printf("Option nombre valide, nombre = %d\n", (*options).nombre);
		}
	else
		{
		printf("Option nombre non valide, nombre = %d\n", (*options).nombre);
		printf("	option nombre : 0.0 < nombre < %d\n", NOMBRE_MAX);
		}
	return;
	}

		// déphasage entre les extrémitées
void optionsSoliton(optionsT * options, char *opt)
	{
	int soliton = atoi(opt);
	int solitonMax = (int)(0.1 + DEPHASAGE_MAX/DEUXPI);

	if(soliton > -solitonMax && soliton < solitonMax)
		{
		(*options).soliton = soliton;// * 2 * PI
		printf("Option soliton valide, soliton = %d\n", (*options).soliton);
		}
	else
		{
		printf("Option soliton non valide, soliton = %d\n", (*options).soliton);
		printf("	option soliton : %d < soliton < %d\n", -solitonMax, solitonMax);
		}
	return;
	}

    	// discrétisation du temps 
void optionsDt(optionsT * options, char *opt)
	{
	float dt = atof(opt);
	if(dt>DT_MIN && dt<DT_MAX)
		{
		(*options).dt = dt;
		printf("Option dt valide, dt = %f\n", (*options).dt);
		}
	else
		{
		printf("Option dt non valide, dt = %f\n", (*options).dt);
		printf("	option dt : %f < dt < %6.3f\n",DT_MIN , DT_MAX);
		}
	return;
	}

		// choix de l'équation
void optionsEquation(optionsT * options, char *opt)
	{
	int equation = atoi(opt);
	if(equation > 0 && equation <5)
		{
		(*options).equation = equation;
		printf("Option equation valide, equation = %d\n", (*options).equation);
		}
	else
		{
		printf("Option equation non valide, equation = %d\n", (*options).equation);
		printf("	option equation : 1 < equation < 5\n");
		}
	return;
	}


    	// Couleur du fond 
void optionsFond(optionsT * options, char *opt)
	{
	int fond = atoi(opt);
	if(fond>0 && fond<255)
		{
		(*options).fond = fond;
		printf("Option fond valide, fond = %d\n", (*options).fond);
		}
	else
		{
		printf("Option fond non valide, fond = %d\n", (*options).fond);
		printf("	option fond : 0 < fond < 255\n");
		}
	return;
	}

    	// Temps de pause en ms après affichage graphique
void optionsPause(optionsT * options, char *opt)
	{
	int pause = atof(opt);
	if(pause>5 || pause<555)
		{
		(*options).pause = pause;
		printf("Option pause valide, pause = %d\n", (*options).pause);
		}
	else
		{
		printf("Option pause non valide, pause = %d\n", (*options).pause);
		printf("	option pause : 5 < pause < 555\n");
		}
	return;
	}

	// Avec ou sans support
void optionsSupport(optionsT * options, char *opt)
	{
	int support = atoi(opt);
	if(support==1 || support==0)
		{
		(*options).support = support;
		printf("Option support valide, support = %d\n", (*options).support);
		}
	else
		{
		printf("Option mode non valide, support = %d\n", (*options).support);
		printf("	option support = 1 ou 0 : avec ou sans support\n");
		}
	return;
	}

		// Mode  -1 : Wait, 1 : Poll
void optionsMode(optionsT * options, char *opt)
	{
	int mode = atoi(opt);
	if(mode==1 || mode==-1)
		{
		(*options).mode = mode;
		printf("Option mode valide, mode = %d\n", (*options).mode);
		}
	else
		{
		printf("Option mode non valide, mode = %d\n", (*options).mode);
		printf("	option mode : mode = + ou - 1\n");
		}
	return;
	}

void optionsDuree(optionsT * options, char *opt)
	{    	// Nombre d'évolution du système entre les affichages
	int duree = atoi(opt);
	if ( duree > 0 && duree < DUREE_MAX)
		{
		(*options).duree = duree;
		printf("Option duree valide, duree = %d\n", (*options).duree);
		}
	else
		{
		printf("Option duree non valide, duree = %d\n", (*options).duree);
		printf("	option duree : 0 < duree < %d\n", DUREE_MAX);
		}
	return;
	}

    	// Un processus ou deux threads
void optionsThread(optionsT * options, char *opt)
	{
	int thread = atoi(opt);
	if(thread==1 || thread==0)
		{
		(*options).thread = thread;
		printf("Option thread valide, thread = %d\n", (*options).thread);
		}
	else
		{
		printf("Option thread non valide, thread = %d\n", (*options).thread);
		printf("	option thread : thread = 0 ou 1\n");
		}
	return;
	}

void optionsAide(void)
	{
	printf("\nAIDE DE SiCP\n");

	printf("\n	OPTIONS DE LA LIGNE DE COMMANDE ()\n\n");

  // Couleur du fond 
	printf("fond	0 < fond < 255	:	couleur du fond de l'affichage\n");
	printf("support	1 ou 0 		: 	avec ou sans dessin du support\n");
	printf("pause	5 < pause < 555	:	pause entre les affichages en ms\n");
	printf("mode	mode = -1 ou 1	:	Avec ou sans attente (entrée)\n");  // Mode -1 : Wait, 1 : Poll
	printf("duree	1 < duree < %d	:	nombre d'évolution du système entre les affichages (F9, F10, F11, F12)\n", DUREE_MAX);
	printf("dt	%f < dt < %6.3f	discrétisation du temps\n", DT_MIN, DT_MAX);
	printf("nombre	%d < nombre < %d	Nombre de pendule \n", NOMBRE_MIN, NOMBRE_MAX);
	int soliton = (int)(0.1 + DEPHASAGE_MAX/DEUXPI);
	printf("soliton	%d < soliton < %d	Nombre de soliton initial (y, h) \n", -soliton, soliton);

	//printf("equation	-1 < equation < 5	Équation simulée, \n");
	//printf("		0 : pendule, 1 : harmonique \n");
	//printf("		2 : corde, 3 : dioptre. \n");
	//printf("	F9, F10, F11, F12. \n\n");

	printf("\n	COMMANDE DU CLAVIER\n\n");

	printf("	a, q : augmenter, diminuer le couplage\n");
	printf("	z, s : augmenter, diminuer la gravitation\n\n");

	printf("	e, d : diminuer, augmenter la dissipation\n");
	printf("	r, f : retire, forme la dissipation\n");
	printf("	v : forme l'extrémité absorbante\n\n");

	printf("	t, g : augmenter, diminuer la masse\n");
	printf("	y, h : ajoute, enlève un déphasage de 2pi\n\n");

	printf("	w : conditions aux limites périodique\n");
	printf("	x : extrémités libres\n");
	printf("	c : extrémités fixe\n");
	printf("	b, n : fixe une extrémité, libère l'autre\n\n");

	printf("	flêche droite : allume, éteint le courant Josephson\n");
	printf("	flêches haut, bas : augmente diminue l'intensité\n");
	printf("	flêche gauche : change le sens du courant\n\n");

	printf("	u, j : augmenter, diminuer l'amplitude du générateur\n");
	printf("	i : démarre une impulsion\n");
	printf("	o : démarre, éteint le générateur\n");
	printf("	l : démarre le signal carrée\n");
	printf("	p, m : augmenter, diminuer la fréquence\n\n");

	printf("	F5, F6, F7 : affiche les observables\n\n");

	printf("	Entrée : change le mode temporel\n\n");

	printf("	+, - : augmente, diminue la vitesse de la simulation\n");
	printf("	F9, F10, F11, F12 : diminue, augmente la vitesse de la simulation\n\n");

	printf("Lorsque le bouton de la souris est maintenu, les mouvements de celle-ci\n");
	printf("permettent la rotation du point de vue de l'observateur.\n\n");

	fprintf(stderr, "\nSortie de SiGP\n");
	exit(EXIT_FAILURE);
	return;
	}


////////////////////////////////////////////////////////////////////////////
