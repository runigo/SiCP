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
offert aux utilisateurs qu'une garantie limitée.  Pour les mêmes raisons,
seule une responsabilité restreinte pèse sur l'auteur du programme, le
titulaire des droits patrimoniaux et les concédants successifs.
A cet égard  l'attention de l'utilisateur est attirée sur les risques
associés au chargement, à l'utilisation, à la modification et/ou au
développement et à la reproduction du logiciel par l'utilisateur étant
donné sa spécificité de logiciel libre, qui peut le rendre complexe à
manipuler et qui le réserve donc à des développeurs et des professionnels
avertis possédant des connaissances informatiques approfondies. Les
utilisateurs sont donc invités à charger  et  tester  l'adéquation du
logiciel à leurs besoins dans des conditions permettant d'assurer la
sécurité de leurs systèmes et ou de leurs données et, plus généralement,
à l'utiliser et l'exploiter dans les mêmes conditions de sécurité.
Le fait que vous puissiez accéder à cet en-tête signifie que vous avez
pris connaissance de la licence CeCILL, et que vous en avez accepté les
termes.
*/

#include "systeme.h"

void changeLimite(systemeT * systeme);

/*--------------------------------------------------------------*/

void changeCouplage(systemeT * systeme, float facteur)
	{// Multiplie le couplage par facteur
	float maximum;
	chaineT *iter=(*systeme).premier;

	maximum = (*systeme).couplage * facteur / (*systeme).nombre;

	if(maximum < COUPLAGE_MAX)
		{
		(*systeme).couplage=(*systeme).couplage*facteur;
		do
			{
			penduleChangeCouplage(&(iter->pendule), facteur);
			iter=iter->suivant;
			}
		while(iter!=(*systeme).premier);
		}
	else
		{
		printf("Maximum du couplage = %6.3f\n", (*systeme).couplage);
		}

	printf("Couplage = %6.3f\n", (*systeme).couplage);

	return;
	}

void changeGravitation(systemeT * systeme, float facteur)
	{// Multiplie la gravitation par facteur
	chaineT *iter=(*systeme).premier;
	float gravitation;

	gravitation = (*systeme).gravitation * facteur;

	if(gravitation < GRAVITATION_MAX && gravitation > GRAVITATION_MIN)
		{
		(*systeme).gravitation = gravitation;
		do
			{
			penduleChangeGravitation(&(iter->pendule), facteur);
			iter=iter->suivant;
			}
		while(iter!=(*systeme).premier);
		}
	else
		{
		printf("Maximum de la gravité = %6.3f\n", (*systeme).gravitation);
		}

	printf("Gravitation = %6.3f\n", (*systeme).gravitation);

	return;
	}

void changeMasse(systemeT * systeme, float facteur)
	{// Multiplie la masse par facteur
	chaineT *iter=(*systeme).premier;
	float masse;

	masse = (*systeme).masse * facteur;

	if(masse < MASSE_MAX && masse > MASSE_MIN)
		{
		(*systeme).masse = masse;
		do
			{
			penduleChangeMasse(&(iter->pendule), facteur);
			iter=iter->suivant;
			}
		while(iter!=(*systeme).premier);
		}
	else
		{
		printf("Masse limite atteinte\n");
		}

	printf("Masse = %6.3f\n", (*systeme).masse);

	return;
	}

void changeDissipation(systemeT * systeme, float facteur)
	{// Multiplie la dissipation par facteur
	chaineT *iter;
	iter = (*systeme).premier;

	float dissipation = (*systeme).dissipation * facteur;
	float dissipationMaximale = DISSIPATION_MAX_DT/(*systeme).moteur.dt;

	if(dissipation < dissipationMaximale && dissipation > DISSIPATION_MIN)
		{
		if(facteur!=0.0)
			{
			(*systeme).dissipation = (*systeme).dissipation * facteur;
			}

		do
			{
			penduleChangeDissipation(&(iter->pendule), facteur);
			iter=iter->suivant;
			}
		while(iter!=(*systeme).premier);
		}
	else
		{
		printf("dissipation limite atteinte\n");
		}


	printf("Dissipation = %6.3f\n", (*systeme).dissipation);

	return;
	}

void changeFormeDissipation(systemeT * systeme, int forme)
	{// initialise une dissipation nulle(0), uniforme(1) ou extremite absorbante(2)
	chaineT *iter;
	iter=(*systeme).premier;
	float dissipation = 0.99;

	if ( forme == 0 )
		dissipation = 0.0;

	if (  forme == 1 )
		{
		if ( (*systeme).dissipation != 0.0 )
			{
			dissipation = (*systeme).dissipation;
			}
		else
			{
			(*systeme).dissipation = dissipation;
			}
		}

	do
		{
		if ( forme == 2 )
			{
			dissipation = iter->pendule.dissipation;
			}
		penduleInitialiseAlpha(&(iter->pendule), dissipation, (*systeme).moteur.dt);
		iter=iter->suivant;
		}
	while(iter!=(*systeme).premier);

	if ( forme == 2 )
		{
		printf("Dissipation premier= %6.3f\n", iter->pendule.dissipation);
		printf("Dissipation dernier= %6.3f\n", iter->precedent->pendule.dissipation);
		}
	else
		{ // Cas uniforme (forme=1)
		printf("Dissipation = %6.3f\n", dissipation);
		}

	return;
	}

void changeConditionsLimites(systemeT * systeme, int libreFixe)
	{
	(*systeme).libreFixe=libreFixe;
	printf("libreFixe = %d, ", (*systeme).libreFixe);

	switch(libreFixe)
		{
		case 0:
			printf(": conditions aux limites périodiques\n");
			break;
		case 1:
			printf(": extrémités libres\n");
			break;
		case 2:
			printf(": extrémités fixes\n");
			break;
		case 3:
			printf(": premier libre, dernier fixe\n");
			break;
		case 4:
			printf(": premier fixe, dernier libre\n");
			break;
		}

	changeLimite(systeme);

	return;
	}

void changeLimite(systemeT * systeme)
	{// Change le couplage du dernier pendule
	float couplage=0.0;
	if ((*systeme).libreFixe==0 || (*systeme).libreFixe==2)
		{
		couplage=(*systeme).couplage;
		}

	penduleInitialiseKapa(&(*systeme).premier->precedent->pendule, couplage, (*systeme).moteur.dt);

	printf("Couplage dernier = %6.3f\n", couplage);

	return;
	}

void changeDephasage(systemeT * systeme, float dephasage)
	{
	float nouveau = (*systeme).premier->pendule.dephasage + dephasage;

	if(nouveau>(-DEPHASAGE_MAX) && nouveau<DEPHASAGE_MAX)
		{
		penduleAjouteDephasage(&(*systeme).premier->pendule, dephasage);
		}
	else
		{
		printf("dissipation limite atteinte\n");
		}
	
	
	printf("Dephasage premier = %6.3f\n", (*systeme).premier->pendule.dephasage);

	return;
	}

//////////////////////////////////////////////////////////////////////////
