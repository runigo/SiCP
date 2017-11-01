/*
Copyright novembre 2017, Stephan Runigo
runigo@free.fr
SiCP 1.4 simulateur de chaîne de pendules
Ce logiciel est un programme informatique servant à simuler l'équation
d'une chaîne de pendules et à en donner une représentation graphique.
Ce logiciel est régi par la licence CeCILL soumise au droit français et
respectant les principes de diffusion des logiciels libres. Vous pouvez
utiliser, modifier et/ou redistribuer ce programme sous les conditions
de la licence CeCILL telle que diffusée par le CEA, le CNRS et l'INRIA
sur le site "http://www.cecill.info".
En contrepartie de l'accessibilité au code source et des droits de copie,
de modification et de redistribution accordés par cette licence, il n'est
offert aux utilisateurs qu'une garantie limitée.  Pour les mêmes raisons,
seule une responsabilité restreinte pèse sur l'auteur du programme, le
titulaire des droits patrimoniaux et les concédants successifs.
A cet égard  l'attention de l'utilisateur est attirée sur les risques
associés au chargement,  à l'utilisation,  à la modification et/ou au
développement et à la reproduction du logiciel par l'utilisateur étant
donné sa spécificité de logiciel libre, qui peut le rendre complexe à
manipuler et qui le réserve donc à des développeurs et des professionnels
avertis possédant  des  connaissances  informatiques approfondies. Les
utilisateurs sont donc invités à charger  et  tester  l'adéquation du
logiciel à leurs besoins dans des conditions permettant d'assurer la
sécurité de leurs systèmes et ou de leurs données et, plus généralement,
à l'utiliser et l'exploiter dans les mêmes conditions de sécurité.
Le fait que vous puissiez accéder à cet en-tête signifie que vous avez
pris connaissance de la licence CeCILL, et que vous en avez accepté les
termes.
*/

#include "controleur.h"

int controleurProjection(controleurT * control);
int controleurEvolutionSysteme(controleurT * control);
int controleurConstructionGraphique(controleurT * control);
int controleurActionClavier(controleurT * control);

int controleurTraiteEvenement(controleurT * control);

int controleurClavier(controleurT * control);
int controleurSouris(controleurT * control);
void controleurBoutonSouris(controleurT * control, int appui);

void controleurChangeMode(controleurT * control);
void controleurChangeVitesse(controleurT * control, float facteur);


int controleurSimulationGraphique(controleurT * control)
	{

	//fprintf(stderr, "Entrée dans la boucle SDL\n");
	do	{
			//fprintf(stderr, "Projection du systeme sur la représentation graphique\n");
		controleurProjection(control);

			//fprintf(stderr, "Projection du systeme sur la représentation graphique\n");
		controleurEvolutionSysteme(control);

			//fprintf(stderr, "Mise à jourde la fenêtre graphique et pause\n");
		controleurConstructionGraphique(control);

			//fprintf(stderr, "Prise en compte des actions clavier\n");
		controleurActionClavier(control);

		}
	while((*control).evenement.type != SDL_QUIT);

	return 0;
	}

int controleurProjection(controleurT * control)
	{
	projectionSystemChaineDePendule(&(*control).systeme, &(*control).projection, &(*control).graphe);
	//projectionSystemPendule(&(*control).systeme, &(*control).graphe);
	return (*control).sortie;
	}

int controleurEvolutionSysteme(controleurT * control)
	{
		//fprintf(stderr, "Evolution temporelle du systeme\n");
	systemeEvolution(&(*control).systeme, (*control).duree);

	return 0;
	}

int controleurConstructionGraphique(controleurT * control)
	{
		//fprintf(stderr, "Dessin des graphes\n");
	if((*control).graphe.support==0)
		{graphiquePendule(&(*control).graphe);}
	else
		{graphiquePenduleSupport(&(*control).graphe);}

		//fprintf(stderr, "Mise à jour de l'affichage\n");
	graphiqueMiseAJour();

		// Pause
	SDL_Delay((*control).options.pause);

	return (*control).sortie;
	}

int controleurActionClavier(controleurT * control)
	{
	int sortie = 0;
		//fprintf(stderr, "Traitement des évenements, mode %d\n", (*control).mode);
	if((*control).mode<0)
		{
				// Attente d'un évenement SDL
		if(SDL_WaitEvent(&(*control).evenement))
			{
			sortie += controleurTraiteEvenement(control);
			}
		}
	else
		{
			// Sans attente
		if( SDL_PollEvent(&(*control).evenement) )
			{
			sortie += controleurTraiteEvenement(control);
			}
		}


	if((*control).evenement.type == SDL_QUIT) sortie += 1;

	(*control).sortie += sortie;

	return (*control).sortie;
	}

int controleurTraiteEvenement(controleurT * control)
	{
	int sortie = 0;
	switch((*control).evenement.type)
		{
		case SDL_QUIT:
			sortie = 1;break;
		case SDL_MOUSEMOTION:
			sortie = controleurSouris(control);break;
		case SDL_MOUSEBUTTONDOWN:
			controleurBoutonSouris(control, 1);break;
		case SDL_MOUSEBUTTONUP:
			controleurBoutonSouris(control, 0);break;
	  case SDL_KEYDOWN:
	    sortie = controleurClavier(control);break;
		/*case SDL_KEYDOWN:
			if (((*control).evenement.key.keysym.mod & KMOD_LSHIFT) == KMOD_LSHIFT)
				{sortie = controleurClavierMaj(control);break;}
			else
				{
				if (((*control).evenement.key.keysym.mod & KMOD_RSHIFT) == KMOD_RSHIFT)
					{sortie = controleurClavierMaj(control);break;}
				else {sortie = controleurClavier(control);break;}
				}*/
		default:
			;
		}

	if(sortie != 0)
		{
		fprintf(stderr, "sortie <> 0\n");
		(*control).sortie = 1;
		}
	return sortie;
	}
/*
int controleurTraiteEvenement(controleurT * control)
	{
	int sortie = 0;

	switch((*control).evenement.type)
	  {
	  case SDL_QUIT:
	    sortie = 1;break;
	  case SDL_KEYDOWN:
	    sortie = controleurClavier(control);break;
	  }

	if(sortie != 0)
	  {
	  fprintf(stderr, "sortie <> 0\n");
    (*control).sortie = 1;
    }

	return sortie;
	}
*/
void controleurChangeMode(controleurT * control)
	{
	(*control).mode=-(*control).mode;

	return;
	}

void controleurChangeVitesse(controleurT * control, float facteur)
	{
	if( (*control).duree > 999 && facteur > 1 )
		{
		fprintf(stderr, "duree maximale atteinte");
		}
	else
		{
		if( (*control).duree > 11 )
			{
			(*control).duree = (*control).duree * facteur;
			}
		else
			{
			if( facteur > 1)
				{
				(*control).duree ++;
				}
			else
				{
				if( (*control).duree > 1 )
					{
					(*control).duree --;
					}
				else
					{
					fprintf(stderr, "duree minimale atteinte");
					}
				}
			}
		}
	fprintf(stderr, "duree = %d\n", (*control).duree);
	return;
	}

int controleurClavier(controleurT * control)
	{
	switch ((*control).evenement.key.keysym.sym)
		{
	// Sortie
		case SDLK_ESCAPE:
			(*control).sortie = 1;break;

	// Mode : attente d'un evenement / pas d'attente
		case SDLK_RETURN:
			controleurChangeMode(control);break;
		//case SDLK_BACKSPACE:
			//controleurChangeMode(control);break;

	// Vitesse de la simulation
		case SDLK_KP_PLUS:
			controleurChangeVitesse(control, 1.1);break;
		case SDLK_KP_MINUS:
			controleurChangeVitesse(control, 0.91);break;
		case SDLK_F9:
			controleurChangeVitesse(control, 0.32);break;
		case SDLK_F10:
			controleurChangeVitesse(control, 0.91);break;
		case SDLK_F11:
			controleurChangeVitesse(control, 1.1);break;
		case SDLK_F12:
			controleurChangeVitesse(control, 3.1);break;

	// Support
		case SDLK_F8:
			grapheChangeSupport(&(*control).graphe);break;

	// Conditions aux limites
		case SDLK_y:
			changeDephasage(&(*control).systeme, 2*PI);break;
		case SDLK_h:
			changeDephasage(&(*control).systeme, -2*PI);break;
		case SDLK_w:
			changeConditionsLimites(&(*control).systeme, 0); // periodiques
			break;
		case SDLK_x:
			changeConditionsLimites(&(*control).systeme, 1); // libres
			break;
		case SDLK_c:
			changeConditionsLimites(&(*control).systeme, 2); // fixes
			break;
		case SDLK_b:
			changeConditionsLimites(&(*control).systeme, 3); // libre fixe
			break;
		case SDLK_n:
			changeConditionsLimites(&(*control).systeme, 4); // fixe libre
			break;


	// Dissipation
		case SDLK_e:
			changeDissipation(&(*control).systeme, 0.77);break;
		case SDLK_d:
			changeDissipation(&(*control).systeme, 1.3);break;
		case SDLK_r:
			changeFormeDissipation(&(*control).systeme, 0);break;
		case SDLK_f:
			changeFormeDissipation(&(*control).systeme, 1);break;
		case SDLK_v:
			changeFormeDissipation(&(*control).systeme, 2);break;

	// Couplage
		case SDLK_a:
			changeCouplage(&(*control).systeme, 1.1);break;
		case SDLK_q:
			changeCouplage(&(*control).systeme, 0.91);break;

	// Masse
		case SDLK_z:
			changeMasse(&(*control).systeme, 1.7);break;
		case SDLK_s:
			changeMasse(&(*control).systeme, 0.6);break;

	// Gravitation
		case SDLK_t:
			changeGravitation(&(*control).systeme, 1.3);break;
		case SDLK_g:
			changeGravitation(&(*control).systeme, 0.77);break;

	// Moteur jonction Josephson
		case SDLK_UP:
			moteursChangeJosephson(&(*control).systeme.moteur,1.1);break;
		case SDLK_DOWN:
			moteursChangeJosephson(&(*control).systeme.moteur,0.91);break;
		case SDLK_LEFT:
			moteursChangeJosephson(&(*control).systeme.moteur,-1.0);break;
		case SDLK_RIGHT:
			moteursChangeJosephson(&(*control).systeme.moteur,0.0);break;

	// Moteur générateur de signaux
		case SDLK_p:
			moteursChangeFrequence(&(*control).systeme.moteur,1.1);break;
		case SDLK_m:
			moteursChangeFrequence(&(*control).systeme.moteur,0.91);break;
		case SDLK_u:
			moteursChangeAmplitude(&(*control).systeme.moteur,1.1);break;
		case SDLK_j:
			moteursChangeAmplitude(&(*control).systeme.moteur,0.91);break;
		case SDLK_o:
			moteursChangeGenerateur(&(*control).systeme.moteur, -1);break;
		case SDLK_i:
			moteursChangeGenerateur(&(*control).systeme.moteur, 3);break;
		case SDLK_l:
			moteursChangeGenerateur(&(*control).systeme.moteur, 2);break;


	// Choix de la simulation
/*
		case SDLK_F1: // Pendules
			(*control).systeme.equation = 1;break;
		case SDLK_F2: // Harmoniques
			(*control).systeme.equation = 2;break;
		case SDLK_F3: // Corde
			(*control).systeme.equation = 3;break;
		case SDLK_F4: // Corde asymétrique
			(*control).systeme.equation = 4;break;
*/
  // Afficher les observables

		case SDLK_F5:
			observablesAfficheEnergie(&(*control).systeme);
			break;
		case SDLK_F6:
			moteursAfficheHorloge(&(*control).systeme.moteur);
			break;
		case SDLK_F7:
			projectionAffichePointDeVue(&(*control).projection);
			break;

		default:
			;
		}
	return (*control).sortie;
	}

int controleurSouris(controleurT * control)
	{
	float x, y;
	if((*control).appui==1)
		{
		//fprintf(stderr, "controleurSouris xrel = %d\n", (*control).evenement.motion.xrel);
		x=-0.0031*(float)((*control).evenement.motion.xrel);
		y=0.0031*(float)((*control).evenement.motion.yrel);
		//fprintf(stderr, "controleurSouris yrel = %d\n", (*control).evenement.motion.yrel);
		//fprintf(stderr, "controleurSouris yrel = %d\n", (*control).evenement.motion.yrel);
		projectionChangePsi(&(*control).projection, x);
		projectionChangePhi(&(*control).projection, y);
		}
	return (*control).sortie;
	}

void controleurBoutonSouris(controleurT * control, int appui)
	{
	(*control).appui=appui;
	return;
	}
//////////////////////////////////////////////////////////////////////////////////////
