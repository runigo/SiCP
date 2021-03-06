/*
Copyright avril 2018, Stephan Runigo
runigo@free.fr
SiCP 1.7 simulateur de chaîne de pendules
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

#include "graphique.h"

/*
	VARIABLE GLOBALE
*/

SDL_Surface* affichage;

/*
	...............
*/

void graphiqueAffichePixel (int x, int y, Uint32 couleur);
void graphiquegraphiqueAffichePixelVerif(int x, int y, Uint32 couleur);
void graphiqueligneDroite(int X, int Y, int x, int y, Uint32 couleur);
void graphiqueTige(int X, int Y, int x, int y, Uint32 couleur);
void graphiqueMasse(int abs, int ord, Uint32 couleur);

void graphiqueTriangleGris(int X, int Y, int Ax, int Ay, int Bx, int By);

void graphiqueMobile(grapheT * graphe);

int graphiqueInitialise(int fond)
	{
		//fprintf(stderr, " Initialisation de la SDL, fond = %d\n", fond);

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
		{
		fprintf(stderr, "Erreur à l'initialisation de la SDL : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
		}
	else fprintf(stderr, "SDL initialisé\n");

	atexit(SDL_Quit);

	affichage = SDL_SetVideoMode(LARGEUR, HAUTEUR, 32, SDL_SWSURFACE);

	if (affichage == NULL)
		{
		fprintf(stderr, "Impossible d'activer le mode graphique : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
		}
	else
		{
		fprintf(stderr, "Mode graphique activé\n");
		}

	SDL_WM_SetCaption("Chaîne de pendules", NULL);

	Uint32 clrFond = SDL_MapRGB(affichage->format, fond, fond, fond);
	SDL_FillRect(affichage, NULL, clrFond);

	return 0;
	}

int graphiqueNettoyage(int couleurFond)
	{
	Uint32 couleurF=SDL_MapRGB(affichage->format,couleurFond,couleurFond,couleurFond);
	SDL_FillRect(affichage, NULL, couleurF);
	return 0;
	}

int graphiqueMiseAJour(void)
	{
	SDL_UpdateRect(affichage, 0, 0, 0, 0);
	return 0;
	}

void graphiqueAffichePixel(int x, int y, Uint32 couleur)
	{
	*((Uint32*)(affichage->pixels) + x + y * affichage->w) = couleur;
	return;
	}

void graphiqueAffichePixelVerif(int x, int y, Uint32 couleur)
	{
	if (x>=0 && x < affichage->w && y>=0 && y < affichage->h)
		graphiqueAffichePixel(x, y, couleur);
	else 
		if(x>=0 && x < affichage->w) graphiqueAffichePixel(x, 2, couleur);
	return;
	}

void graphiqueLigneDroite(int X, int Y, int x, int y, Uint32 couleur)
	{
	int i, abs, ord;
	int min, max;
	float a;

	max=X-x; min=Y-y;
	if(max<0) max=-max; if(min<0) min=-min;
	if(max<min) max=min;

	for(i=0;i<=max;i++)
		{
		a=i/(float)max;
		abs=(X+(int)(a*(x-X)));
		ord=(Y+(int)(a*(y-Y)));
		graphiqueAffichePixelVerif(abs, ord, couleur);
		}
	return;
	}

void graphiqueTige(int X, int Y, int x, int y, Uint32 couleur)
	{

	graphiqueLigneDroite(X, Y, x, y, couleur);
	graphiqueLigneDroite(X+1, Y, x+1, y, couleur);
	graphiqueLigneDroite(X, Y+1, x, y+1, couleur);

	return;
	}

void graphiqueLigneContraste(int Xp, int Yp, int Mx, int My)
	{
	Uint32 couleurC = SDL_MapRGB(affichage->format, 0, 0, 0);
	graphiqueLigneDroite(Xp, Yp, Mx, My, couleurC);
	return;
	}

void graphiqueTriangleGris(int X, int Y, int Ax, int Ay, int Bx, int By)
	{
	int x[3];
	int y[3];
	float a = 0.0;
	float b = 0.0;
	float c = 0.0;
	float d = 0.0;

	Uint32 couleurG = SDL_MapRGB(affichage->format, 127, 127, 127);

	if(Y>Ay && Y>By){x[2]=X;y[2]=Y;
		if(Ay>By)
			{x[0]=Bx; y[0]=By; x[1]=Ax; y[1]=Ay;}
		else
			{x[0]=Ax; y[0]=Ay; x[1]=Bx; y[1]=By;}
		}
	else
		{
		if(Y<Ay && Y<By){x[0]=X;y[0]=Y;
			if(By>Ay)
				{x[1]=Ax; y[1]=Ay; x[2]=Bx; y[2]=By;}
			else
				{x[1]=Bx; y[1]=By; x[2]=Ax; y[2]=Ay;}
			}
		else{x[1]=X;y[1]=Y;
			if(By>Ay)
				{x[0]=Ax; y[0]=Ay; x[2]=Bx; y[2]=By;}
			else
				{x[0]=Bx; y[0]=By; x[2]=Ax; y[2]=Ay;}
			}
		}

	int i;

	if(y[0]!=y[1])
		a=(float)(x[1]-x[0])/(y[1]-y[0]); b=x[0]-a*y[0];

	if(y[0]!=y[2])
		c=(float)(x[2]-x[0])/(y[2]-y[0]); d=x[0]-c*y[0];

	for(i=y[0];i<=y[1];i++)
		{graphiqueLigneDroite(a*i+b, i, c*i+d, i, couleurG);}

	if(y[1]!=y[2])
		a=(float)(x[2]-x[1])/(y[2]-y[1]); b=x[1]-a*y[1];

	for(i=y[1];i<=y[2];i++)
		{graphiqueLigneDroite(a*i+b, i, c*i+d, i, couleurG);}

	return;
	}

void graphiqueTriangle(int X, int Y, int Ax, int Ay, int Bx, int By)
	{
	Uint32 couleurC = SDL_MapRGB(affichage->format, 0, 0, 0);
	graphiqueTriangleGris(X, Y, Ax, Ay, Bx, By);
	graphiqueLigneDroite(X, Y, Ax, Ay, couleurC);
	graphiqueLigneDroite(X, Y, Bx, By, couleurC);
	graphiqueLigneDroite(Ax, Ay, Bx, By, couleurC);
	return;
	}

void graphiqueRectangle(int Ax, int Ay, int Bx, int By, int Cx, int Cy, int Dx, int Dy)
	{
	Uint32 couleurC = SDL_MapRGB(affichage->format, 0, 0, 0);

	graphiqueTriangleGris(Ax, Ay, Bx, By, Cx, Cy);
	graphiqueTriangleGris(Ax, Ay, Cx, Cy, Dx, Dy);

	graphiqueLigneDroite(Bx, By, Ax, Ay, couleurC);
	graphiqueLigneDroite(Dx, Dy, Ax, Ay, couleurC);
	graphiqueLigneDroite(Cx, Cy, Bx, By, couleurC);
	graphiqueLigneDroite(Cx, Cy, Dx, Dy, couleurC);
	return;
	}

void graphiqueMasse(int abs, int ord, Uint32 couleur)
	{
	int i=0;
	int j=0;

	for(i=-2;i<3;i++)
		{
	for(j=-2;j<3;j++)
			{
			graphiqueAffichePixelVerif(abs+i, ord+j, couleur);
			}
		}
	graphiqueAffichePixelVerif(abs+3, ord, couleur);
	graphiqueAffichePixelVerif(abs-3, ord, couleur);
	graphiqueAffichePixelVerif(abs, ord+3, couleur);
	graphiqueAffichePixelVerif(abs, ord-3, couleur);

	return;
	}

void graphiquePendule(grapheT * graphe)
	{
	int Mx, My, Nx, Ny;

		// Position des extrémités
	Mx = (*graphe).supporX[12]; My = (*graphe).supporY[12];
	Nx = (*graphe).supporX[13]; Ny = (*graphe).supporY[13];

		// Axe de la chaîne
	graphiqueLigneContraste(Nx, Ny, Mx, My);

		// Chaîne de pendule
	graphiqueMobile(graphe);

	return;
	}

void graphiquePenduleSupport(grapheT * graphe)
	{
//                                                J   I
//                                             L   K
//                                               M
//                                               
//                                                H   G
//                                             F   E
//               N


//             D   C
//         B   A

	int Ax, Ay, Bx, By;
	int Ex, Ey, Fx, Fy, Gx, Gy, Hx, Hy;
	int Ix, Iy, Jx, Jy, Kx, Ky, Lx, Ly;
	int Nx, Ny;

		//	Point du support
	Ax = (*graphe).supporX[0]; Ay = (*graphe).supporY[0];
	Bx = (*graphe).supporX[1]; By = (*graphe).supporY[1];

	Ex = (*graphe).supporX[4]; Ey = (*graphe).supporY[4];
	Fx = (*graphe).supporX[5]; Fy = (*graphe).supporY[5];
	Gx = (*graphe).supporX[6]; Gy = (*graphe).supporY[6];
	Hx = (*graphe).supporX[7]; Hy = (*graphe).supporY[7];
	Ix = (*graphe).supporX[8]; Iy = (*graphe).supporY[8];
	Jx = (*graphe).supporX[9]; Jy = (*graphe).supporY[9];
	Kx = (*graphe).supporX[10]; Ky = (*graphe).supporY[10];
	Lx = (*graphe).supporX[11]; Ly = (*graphe).supporY[11];

	Nx = (*graphe).supporX[13]; Ny = (*graphe).supporY[13];


		// Boitier moteur et montant avant
	if((*graphe).arriere <= 0) // Vue de devant
		{
			// Boitier moteur	
		if((*graphe).gauche <= 0) // Montant gauche
			{
			graphiqueRectangle(Ex, Ey, Gx, Gy, Ix, Iy, Kx, Ky);
			}
		else// Montant droit
			{
			graphiqueRectangle(Fx, Fy, Hx, Hy, Jx, Jy, Lx, Ly);
			}

			// Face avant
		graphiqueRectangle(Fx, Fy, Ex, Ey, Kx, Ky, Lx, Ly);

		if((*graphe).dessous <= 0) // Vue de dessus
			{
				// Chassis
			graphiqueRectangle(Ax, Ay, Bx, By, Fx, Fy, Ex, Ey);
				// Dessus moteur
			graphiqueRectangle(Kx, Ky, Ix, Iy, Jx, Jy, Lx, Ly);
			}
		}
	else // Vue de derriere
		{
		if((*graphe).dessous <= 0) // Vue de dessus
			{
				// Chassis
			graphiqueRectangle(Ax, Ay, Bx, By, Fx, Fy, Ex, Ey);
				// Palier avant
			graphiqueTriangle(Nx, Ny, Ax, Ay, Bx, By);
			}
		else // Vue de dessous
			{	// Chassis
			//graphiqueRectangle(Ax, Ay, Bx, By, Fx, Fy, Ex, Ey);
				// Palier avant
			graphiqueTriangle(Nx, Ny, Ax, Ay, Bx, By);
			}
		}

		// Chaine de pendule
	graphiquePendule(graphe);

		// Boitier moteur et montant avant	
	if((*graphe).arriere > 0) // Vue de derrière
		{
			// Boitier moteur	
		if((*graphe).gauche <= 0) // Montant gauche
			{
			graphiqueRectangle(Ex, Ey, Gx, Gy, Ix, Iy, Kx, Ky);
			}
		else// Montant droit
			{
			graphiqueRectangle(Fx, Fy, Hx, Hy, Jx, Jy, Lx, Ly);
			}
			// Face arrière
		graphiqueRectangle(Hx, Hy, Gx, Gy, Ix, Iy, Jx, Jy);

		if((*graphe).dessous > 0) // Vue de dessous
			{	// Chassis
			graphiqueRectangle(Ax, Ay, Bx, By, Hx, Hy, Gx, Gy);
			}
		else
			{	// Dessus moteur
			graphiqueRectangle(Kx, Ky, Ix, Iy, Jx, Jy, Lx, Ly);
			}
		}
	else // Vue de devant
		{
		if((*graphe).dessous <= 0) // Vue de dessus
			{	// Palier avant
			graphiqueTriangle(Nx, Ny, Ax, Ay, Bx, By);
			}
		else // Vue de dessous
			{
				// Palier avant
			graphiqueTriangle(Nx, Ny, Ax, Ay, Bx, By);
				// Chassis
			graphiqueRectangle(Ax, Ay, Bx, By, Hx, Hy, Gx, Gy);
			}
		}

	return;
	}

void graphiqueMobile(grapheT * graphe)
	{
	int graphAbs, graphOrd, fixAbs, fixOrd;
	int sortie=0;
	pointsT *iter=(*graphe).premier;

	if((*graphe).arriere != 0) // Vue de derrière, la chaîne est dessinée vers les précédents.
		{iter = iter->precedent;}
	else {(*graphe).arriere = 0;}

		// Couleur segments et points
	Uint32 couleurS=SDL_MapRGB(affichage->format, (*graphe).rouge, (*graphe).vert, (*graphe).bleu);
	Uint32 couleurP=SDL_MapRGB(affichage->format, (*graphe).vert, (*graphe).rouge, (*graphe).bleu);


	do
		{
		//	Dessin des segments
		fixAbs=iter->xa;
		fixOrd=iter->ya;
		graphAbs=iter->xm;
		graphOrd=iter->ym;
		graphiqueTige(fixAbs, fixOrd, graphAbs, graphOrd, couleurS);

		//	Dessin des masses
		graphAbs=iter->xm;
		graphOrd=iter->ym;
		graphiqueMasse(graphAbs, graphOrd, couleurP);

		if((*graphe).arriere == 0)
			{iter=iter->suivant;}
		else // Vue de derrière, la chaîne est dessinée vers les précédents.
			{iter=iter->precedent;}


		if((*graphe).arriere == 0)
			{if(iter==(*graphe).premier) sortie = 1;}
		else // Vue de derrière, la chaîne est dessinée vers les précédents.
			{if(iter==(*graphe).premier->precedent) sortie = 1;}
		}
	while(sortie==0);

	return;
	}

//////////////////////////////////////////////////////////////////////////////
