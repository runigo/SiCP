/*
Copyright septembre 2017, Stephan Runigo
runigo@free.fr
SiCP 1.3.7  simulateur de chaîne de pendules
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

#include "graphe.h"

int grapheCreation(grapheT * graphe, int nombre)
	{
		//		Création du graphe

	pointsT *iter;
	(*graphe).premier=NULL;
	(*graphe).premier=pointCreationGraphe(nombre);

	if((*graphe).premier!=NULL)
		{
		fprintf(stderr, "Graphe créé\n");
		}
	else
		{
		fprintf(stderr, "Echec de pointCreationGraphe\n");
		}

	iter=(*graphe).premier;
	do
		{
		iter->xm=LARGEUR/2;
		iter->ym=HAUTEUR/2;
		}
	while(iter!=(*graphe).premier);

	return 0;
	}

void grapheSuppression(grapheT * graphe)
	{
	pointSupprime(&(*graphe).premier);
	printf("Graphe supprimé\n");
	}

void grapheChangeSupport(grapheT * graphe)
	{
	if((*graphe).support==1)
		{(*graphe).support=0;
		printf("Support transparent\n");}
	else
		{(*graphe).support=1;
		printf("Support apparent\n");}
	}

//////////////////////////////////////////////////////////////////
