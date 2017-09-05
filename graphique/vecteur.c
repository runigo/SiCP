/*
Copyright juillet 2017, Stephan Runigo
runigo@free.fr
SiCP 1.3  simulateur de chaîne de pendules
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

/*

	L'initialisation d'un vecteur cartésien ne calcule pas les coordonées
	polaires. L'initialisation d'un vecteur polaire calcule et initialise 
	les coordonées cartésienne.

*/

#include "vecteur.h"

void vecteurCartesien(vecteurT * v, float x, float y, float z)
	{
	(*v).x=x;
	(*v).y=y;
	(*v).z=z;
	(*v).r=0.0;
	(*v).psi=0.0;
	(*v).phi=0.0;
	//(*v).r=sqrt(x*x+y*y+z*z);
	//(*v).psi=acos(x/(*v).r);
	//(*v).phi=acos(z/(*v).r);
	return;
	}

void vecteurInitialisePolaire(vecteurT * v, float r, float psi, float phi)
	{
		//fprintf(stderr, "vecteurInitialisePolaire, r, psi, phi\n");
	(*v).r=r;
	(*v).psi=psi;
	(*v).phi=phi;
		//fprintf(stderr, "vecteurInitialisePolaire, x, y, z\n");
	(*v).x=r*cos(psi)*sin(phi);
	(*v).y=r*sin(psi)*sin(phi);
	(*v).z=r*cos(phi);
	return;
	}

float vecteurScalaireCartesien(vecteurT * v1, vecteurT * v2)
	{
	return ((*v1).x*(*v2).x + (*v1).y*(*v2).y + (*v1).z*(*v2).z);
	}

void vecteurSommeCartesien(vecteurT * v1, vecteurT * v2, vecteurT * v3)
	{
	(*v3).x=(*v1).x+(*v2).x;
	(*v3).y=(*v1).y+(*v2).y;
	(*v3).z=(*v1).z+(*v2).z;
	return;
	}

void vecteurDifferenceCartesien(vecteurT * v1, vecteurT * v2, vecteurT * v3)
	{
	(*v3).x=(*v1).x-(*v2).x;
	(*v3).y=(*v1).y-(*v2).y;
	(*v3).z=(*v1).z-(*v2).z;
	return;
	}

int vecteurInitialiseVecteurPhi(vecteurT * pointDeVue, vecteurT * vecteurPhi, float hauteur)
	{
	(*vecteurPhi).x=-hauteur*cos((*pointDeVue).psi)*cos((*pointDeVue).phi);
	(*vecteurPhi).y=-hauteur*sin((*pointDeVue).psi)*cos((*pointDeVue).phi);
	(*vecteurPhi).z=hauteur*sin((*pointDeVue).phi);
	return 0;
	}

int vecteurInitialiseVecteurPsi(vecteurT * pointDeVue, vecteurT * vecteurPsi, float largeur)
	{
	(*vecteurPsi).x=-largeur*sin((*pointDeVue).psi);
	(*vecteurPsi).y=largeur*cos((*pointDeVue).psi);
	(*vecteurPsi).z=0;
	return 0;
	}

//////////////////////////////////////////////////////////////////////
