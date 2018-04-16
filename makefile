# Copyright avril 2018, Stephan Runigo
# runigo@free.fr
# SiCP 1.7  simulateur de chaîne de pendules
# Ce logiciel est un programme informatique servant à simuler l'équation 
# d'une chaîne de pendules et à en donner une représentation graphique.
# Ce logiciel est régi par la licence CeCILL soumise au droit français et 
# respectant les principes de diffusion des logiciels libres. Vous pouvez 
# utiliser, modifier et/ou redistribuer ce programme sous les conditions 
# de la licence CeCILL telle que diffusée par le CEA, le CNRS et l'INRIA 
# sur le site "http://www.cecill.info".
# En contrepartie de l'accessibilité au code source et des droits de copie, 
# de modification et de redistribution accordés par cette licence, il n'est 
# offert aux utilisateurs qu'une garantie limitée.  Pour les mêmes raisons, 
# seule une responsabilité restreinte pèse sur l'auteur du programme, le 
# titulaire des droits patrimoniaux et les concédants successifs.
# A cet égard  l'attention de l'utilisateur est attirée sur les risques 
# associés au chargement,  à l'utilisation,  à la modification et/ou au 
# développement et à la reproduction du logiciel par l'utilisateur étant 
# donné sa spécificité de logiciel libre, qui peut le rendre complexe à 
# manipuler et qui le réserve donc à des développeurs et des professionnels 
# avertis possédant  des  connaissances  informatiques approfondies. Les 
# utilisateurs sont donc invités à charger  et  tester  l'adéquation du 
# logiciel à leurs besoins dans des conditions permettant d'assurer la 
# sécurité de leurs systèmes et ou de leurs données et, plus généralement, 
# à l'utiliser et l'exploiter dans les mêmes conditions de sécurité. 
# Le fait que vous puissiez accéder à cet en-tête signifie que vous avez 
# pris connaissance de la licence CeCILL, et que vous en avez accepté les 
# termes.

CC=gcc
EXEC=SiCP
CFLAGS= -Wall -Wextra -Werror --std=c99
#SDLFLAGS= `sdl-config --libs`
#LDFLAGS= -Wall -Wextra -Werror --std=c99 -lm -lpthread
LDFLAGS= -Wall -Wextra -Werror --std=c99 -lm

OBJDIR = ./obj

all : $(EXEC)

$(EXEC) : $(OBJDIR)/principale.o $(OBJDIR)/options.o $(OBJDIR)/donnees.o $(OBJDIR)/controleur.o $(OBJDIR)/projection.o $(OBJDIR)/horloge.o $(OBJDIR)/graphique.o $(OBJDIR)/observables.o $(OBJDIR)/graphe.o $(OBJDIR)/point.o $(OBJDIR)/vecteur.o $(OBJDIR)/change.o $(OBJDIR)/systeme.o $(OBJDIR)/moteurs.o $(OBJDIR)/chaine.o $(OBJDIR)/pendule.o
	$(CC) -g $(OBJDIR)/principale.o $(OBJDIR)/options.o $(OBJDIR)/donnees.o $(OBJDIR)/controleur.o $(OBJDIR)/projection.o $(OBJDIR)/horloge.o $(OBJDIR)/graphique.o $(OBJDIR)/observables.o $(OBJDIR)/graphe.o $(OBJDIR)/point.o $(OBJDIR)/vecteur.o $(OBJDIR)/change.o $(OBJDIR)/systeme.o $(OBJDIR)/moteurs.o $(OBJDIR)/chaine.o $(OBJDIR)/pendule.o `sdl-config --libs` $(LDFLAGS) -o $(EXEC)

$(OBJDIR)/principale.o : controleur/principale.c controleur/principale.h
	$(CC) -c -g controleur/principale.c $(CFLAGS) -o $@

$(OBJDIR)/options.o : controleur/options.c controleur/options.h
	$(CC) -c -g controleur/options.c $(CFLAGS) -o $@

$(OBJDIR)/donnees.o : donnees/donnees.c donnees/donnees.h
	$(CC) -c -g donnees/donnees.c $(CFLAGS) -o $@

$(OBJDIR)/controleur.o : controleur/controleur.c controleur/controleur.h
	$(CC) -c -g controleur/controleur.c $(CFLAGS) -o $@

$(OBJDIR)/projection.o : controleur/projection.c controleur/projection.h
	$(CC) -c -g controleur/projection.c $(CFLAGS) -o $@

$(OBJDIR)/horloge.o : graphique/horloge.c graphique/horloge.h
	$(CC) -c -g graphique/horloge.c $(CFLAGS) -o $@

$(OBJDIR)/graphique.o : graphique/graphique.c graphique/graphique.h
	$(CC) -c -g graphique/graphique.c $(CFLAGS) -o $@

$(OBJDIR)/graphe.o : graphique/graphe.c graphique/graphe.h
	$(CC) -c -g graphique/graphe.c $(CFLAGS) -o $@

$(OBJDIR)/point.o : graphique/point.c graphique/point.h
	$(CC) -c -g graphique/point.c $(CFLAGS) -o $@

$(OBJDIR)/vecteur.o : graphique/vecteur.c graphique/vecteur.h
	$(CC) -c -g graphique/vecteur.c $(CFLAGS) -o $@

$(OBJDIR)/observables.o : modele/observables.c modele/observables.h
	$(CC) -c -g modele/observables.c $(CFLAGS) -o $@

$(OBJDIR)/change.o : modele/change.c modele/change.h
	$(CC) -c -g modele/change.c $(CFLAGS) -o $@

$(OBJDIR)/systeme.o : modele/systeme.c modele/systeme.h
	$(CC) -c -g modele/systeme.c $(CFLAGS) -o $@

$(OBJDIR)/moteurs.o : modele/moteurs.c modele/moteurs.h
	$(CC) -c -g modele/moteurs.c $(CFLAGS) -o $@

$(OBJDIR)/chaine.o : modele/chaine.c modele/chaine.h
	$(CC) -c -g modele/chaine.c $(CFLAGS) -o $@

$(OBJDIR)/pendule.o : modele/pendule.c modele/pendule.h
	$(CC) -c -g modele/pendule.c $(CFLAGS) -o $@

clean :
	rm $(OBJDIR)/*.o

net : clean
	rm $(EXEC)

