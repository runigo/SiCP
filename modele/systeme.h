/*
Copyright mars 2018, Stephan Runigo
runigo@free.fr
SiCP 1.4.4 simulateur de chaîne de pendules
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

#ifndef _SYSTEME_
#define _SYSTEME_

#include "chaine.h"
#include "moteurs.h"

typedef struct SystemeT systemeT;
	struct SystemeT
		{
		chaineT * premier;	//	Premier pendule couplé

		moteursT moteur;		//	Josephson, horloge
							//	Générateur de signal

		int nombre;			//	Nombre de pendule
		int equation;		//	Pendule=1, Harmonique=2, Corde=3, Dioptre=4

		float dephasage;	//	déphasage entre les limites
		int libreFixe;		//	0 : périodiques 1 : libres, 2 : fixes, 
							//		3 libre-fixe, 4 fixe-libre

		float masse;		//	Masse d'un pendule
		float longueur;		//	Longueur d'un pendule

		float couplage;		//	Mémoire pour conditions limites
		float dissipation;	//	Mémoire si alpha = 0.0

		float gravitation;	//	Accélération de la pesanteur

		};

// Création de la chaîne de pendule
int systemeCreation(systemeT * systeme);

// Suppression de la chaîne de pendule
void systemeSuppression(systemeT * systeme);

// Évolution temporelle du systemeT, "duree" cycle d'évolution
void systemeEvolution(systemeT * systeme, int duree);

// Réinitialisation des positions
void systemeInitialisePosition(systemeT * systeme);
#endif

////////////////////////////////////////////////////////////
