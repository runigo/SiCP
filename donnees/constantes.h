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

#ifndef _CONSTANTES_
#define _CONSTANTES_

//#include "unistd.h"

#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include <assert.h>

//#define PI 3.14159265358979323846264338327950288419716939937510582
//#define PI 3.1415926535897932384626433832795
#define PI 3.14159265359
#define DEUXPI 6.28318530718

#define LARGEUR 999 // Largeur de la fenêtre 990
#define HAUTEUR 440 // Hauteur de la fenêtre

#define DUREE_MAX 999 // Nombre maximal d'incrémentation du système entre deux affichages.

#define DT_MIN 0.0000003 // Discrétisation minimal du temps
#define DT 0.0003
#define DT_MAX 0.003		//	discrétisation du temps
//#define DT_MIN 0.000000003	//	discrétisation du temps

#define NOMBRE_MIN 2 // Nombre minimal de pendules
#define NOMBRE_MAX 1099 // Nombre maximal de pendules

#define SOLITON_MAX 199 // Nombre maximal de soliton

#define COUPLAGE_MAX 99 // Couplage maximal / nombre de pendule
#define COUPLAGE_MIN 0.003

//#define GRAVITATION_MAX 666 // Gravitation maximal.
#define GRAVITATION_MAX 7777
#define GRAVITATION_MIN 0.00007

#define MASSE_MAX 7777
#define MASSE_MIN 0.7

#define DISSIPATION_MAX 333	//	Coeficient de frottement visqueux
#define DISSIPATION_MAX_DT 0.0999
#define DISSIPATION_MIN 0.0000003

#define FREQUENCE_MAX 9123
#define FREQUENCE_MIN 0.00007

#define AMPLITUDE_MAX 912
#define AMPLITUDE_MIN 0.00007

#define JOSEPHSON_MAX 912
#define JOSEPHSON_MIN 0.00007

#endif
