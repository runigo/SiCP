/*
Copyright novembre 2017, Stephan Runigo
runigo@free.fr
SiCP 1.4.1 simulateur de chaîne de pendules
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

void graphiqueAffichePixel (int x, int y, Uint32 couleur);
void graphiquegraphiqueAffichePixelVerif(int x, int y, Uint32 couleur);
void graphiqueligneDroite(int X, int Y, int x, int y, Uint32 couleur);
void graphiqueTige(int X, int Y, int x, int y, Uint32 couleur);
void graphiqueMasse(int abs, int ord, Uint32 couleur);

void graphiqueTriangleGris(int X, int Y, int Ax, int Ay, int Bx, int By);

void graphiqueMobile(grapheT * graphe);

SDL_Surface* affichage;

int graphiqueInitialise(int fond)
	{
		//fprintf(stderr, " Initialisation de la SDL, fond = %d\n", fond);

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
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
	//graphiqueDisque(Mx, My, 2, couleurC);
	return;
	}

void graphiqueTriangleGris(int X, int Y, int Ax, int Ay, int Bx, int By)
	{
	int x[3];
	int y[3];
	float a, b, c, d;

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
		//{graphiqueTige(a*i+b, i, c*i+d, i, couleurG);}
		{graphiqueLigneDroite(a*i+b, i, c*i+d, i, couleurG);}
	//graphiqueLigneDroite(a*i+b+1, i+1, c*i+d+1, i+1, couleurG);

	if(y[1]!=y[2])
		a=(float)(x[2]-x[1])/(y[2]-y[1]); b=x[1]-a*y[1];

	for(i=y[1];i<=y[2];i++)
		//{graphiqueTige(a*i+b, i, c*i+d, i, couleurG);}
		{graphiqueLigneDroite(a*i+b, i, c*i+d, i, couleurG);}
	//graphiqueLigneDroite(a*i+b+1, i+1, c*i+d+1, i+1, couleurG);

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

	//Uint32 couleurG = SDL_MapRGB(affichage->format, 127, 127, 127);
	//graphiqueLigneDroite(Bx, By, Dx, Dy, couleurG);
	//graphiqueLigneDroite(Cx, Cy, Ax, Ay, couleurG);

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
		//fprintf(stderr, " Initialisation du graphe\n");
		// Couleur fond
	Uint32 couleurF=SDL_MapRGB(affichage->format,(*graphe).fond,(*graphe).fond,(*graphe).fond);

	Mx = (*graphe).supporX[12]; My = (*graphe).supporY[12];
	Nx = (*graphe).supporX[13]; Ny = (*graphe).supporY[13];

	  //	Suppression de l'ancien graphe

	SDL_FillRect(affichage, NULL, couleurF);

		// Chaine de pendule
	graphiqueLigneContraste(Nx, Ny, Mx, My);
	graphiqueMobile(graphe);

	return;
	}

void graphiquePenduleSupport(grapheT * graphe)
	{
		//fprintf(stderr, " Initialisation du graphe\n");
		// Couleur fond
	Uint32 couleurF=SDL_MapRGB(affichage->format,(*graphe).fond,(*graphe).fond,(*graphe).fond);

//                                                J   I
//                                             L   K
//                                               M
//                                               
//                                                H   G
//                                             F   E
//               N


//             D   C
//         B   A

	//int i, x, y, X, Y;, Xp, Yp;
	int Ax, Ay, Bx, By;//, Cx, Cy, Dx, Dy;
	int Ex, Ey, Fx, Fy, Gx, Gy, Hx, Hy;
	int Ix, Iy, Jx, Jy, Kx, Ky, Lx, Ly;
	int Mx, My, Nx, Ny;

	  //	Suppression de l'ancien graphe

	SDL_FillRect(affichage, NULL, couleurF);

		//	Point du support
	//Xp = (*chaine).abscisFix[0]; Yp = (*chaine).ordonnFix[0];
	Ax = (*graphe).supporX[0]; Ay = (*graphe).supporY[0];
	Bx = (*graphe).supporX[1]; By = (*graphe).supporY[1];
	//Cx = (*graphe).supporX[2]; Cy = (*graphe).supporY[2];
	//Dx = (*graphe).supporX[3]; Dy = (*graphe).supporY[3];
	Ex = (*graphe).supporX[4]; Ey = (*graphe).supporY[4];
	Fx = (*graphe).supporX[5]; Fy = (*graphe).supporY[5];
	Gx = (*graphe).supporX[6]; Gy = (*graphe).supporY[6];
	Hx = (*graphe).supporX[7]; Hy = (*graphe).supporY[7];
	Ix = (*graphe).supporX[8]; Iy = (*graphe).supporY[8];
	Jx = (*graphe).supporX[9]; Jy = (*graphe).supporY[9];
	Kx = (*graphe).supporX[10]; Ky = (*graphe).supporY[10];
	Lx = (*graphe).supporX[11]; Ly = (*graphe).supporY[11];
	Mx = (*graphe).supporX[12]; My = (*graphe).supporY[12];
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
	graphiqueLigneContraste(Nx, Ny, Mx, My);
	graphiqueMobile(graphe);


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
	pointsT *iter=(*graphe).premier;

		// Couleur segments et points
	Uint32 couleurS=SDL_MapRGB(affichage->format, (*graphe).rouge, (*graphe).vert, (*graphe).bleu);
	Uint32 couleurP=SDL_MapRGB(affichage->format, (*graphe).vert, (*graphe).rouge, (*graphe).bleu);

	int graphAbs, graphOrd, fixAbs, fixOrd;

	do	//	Dessin des points arrières
		{
		if(iter->position < 0)
			{
			graphAbs=iter->xm;
			graphOrd=iter->ym;

			graphiqueMasse(graphAbs, graphOrd, couleurP);
			}

		iter=iter->suivant;
		}
	while(iter!=(*graphe).premier);

	do	//	Dessin des segments
		{
		fixAbs=iter->xa;
		fixOrd=iter->ya;

		graphAbs=iter->xm;
		graphOrd=iter->ym;

		graphiqueTige(fixAbs, fixOrd, graphAbs, graphOrd, couleurS);

		iter=iter->suivant;
		}
	while(iter!=(*graphe).premier);

	do	//	Dessin des points avants
		{
		if(iter->position > 1)
			{
			graphAbs=iter->xm;
			graphOrd=iter->ym;

			graphiqueMasse(graphAbs, graphOrd, couleurP);
			}

		iter=iter->suivant;
		}
	while(iter!=(*graphe).premier);

	return;
	}

//////////////////////////////////////////////////////////////////////////////
/*
void graphiqueTige(int X, int Y, int x, int y, Uint32 couleur)
	{
	int i, abs, ord;
	int p=50;
	float a;
	for(i=0;i<p;i++)
		{
		a=i/(float)p;
		abs=(X+(int)(a*(x-X)));
		ord=(Y+(int)(a*(y-Y)));
		graphiqueAffichePixelVerif(abs, ord, couleur);
		graphiqueAffichePixelVerif(abs+1, ord, couleur);
		graphiqueAffichePixelVerif(abs-1, ord, couleur);
		graphiqueAffichePixelVerif(abs, ord+1, couleur);
		graphiqueAffichePixelVerif(abs, ord-1, couleur);
		}
	return;
	}
*/
