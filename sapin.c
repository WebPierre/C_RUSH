/*********************************************************************
Nom ......... : sapin.c
Role ........ : Dessine un sapin suivant la valeur entrée en paramètre
Auteur ...... : Pierre
Version ..... : V1.0.0 du 14/10/2016
Licence ..... : MIT

Compilation :
gcc -Wall -o sapin sapin.c
Pour exécuter, tapez : ./sapin
*********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sapin.h"
#include "color.h"

void my_putchar(char c, int type) {
  write(type, &c, 1);
}

void my_putstr(char *str, int type) {
  int letter;

  letter = 0;

  while (str[letter] != '\0') {
    my_putchar(str[letter], type);
    letter++;
  }
}

/*********************************************************
Role : Affiche les espaces permettant le décalage du sapin
*********************************************************/
int print_blank(int condition) {
  int	i;

  i = 0;

  while (i < condition) {
    my_putchar(' ', 1);
    i++;
  }
  return (i);
}

/**********************************************
Role : Affiche le tronc (|) et le feuillage (*)
**********************************************/
void print_stars_tronc(int i, int condition, int id) {
  if (id == 0) {
    while (i < condition) {
      COLOR_BROWN;
	    my_putchar('|', 1);
	    i++;
	  }
  } else {
    while (i < condition) {
	    COLOR_GREEN;
	    my_putchar('*', 1);
	    i++;
	  }
  }
  COLOR_RESET;
  my_putchar('\n', 1);
}

/*****************************************************
Role : calcul la largeur du tronc
  - Si size est pair, la largeur du tronc est size + 1
  - Si size est impair, la largeur du tronc est size
*****************************************************/
int width_tronc(int size) {
  if (PARITY(size) == 1) {
    return (size + 1);
  } else {
    return (size);
  }
}

/************************************************************
Role : calcul le nombre d'* de la dernière ligne du feuillage
  - 4 + stop - 1 : nombre de lignes du bloc
  - stop / 2 + 1 : nombre d'* rajouté par bloc
  - * 2          : les deux côtés du tronc
************************************************************/
int max_width(int id) {
  int	lastLine;

  lastLine = 0;

  if (id == 1) {
    lastLine = 7;
  } else {
    lastLine = ((4 + id - 1) - (id / 2 + 1)) * 2 + max_width(id - 1);
  }
  return (lastLine);
}

/****************************************************************************
Role : affiche le feuillage
  - starsMiddleSapin : nombre d'* à la moitié de la taille max du sapin
  - firstStar        : position de la première * de la première ligne du bloc
  - starsLine        : nombre d'* dans une ligne du bloc
      - max_width(size_bloc) : largeur max du bloc
      - (linesBloc - 1) : espace max avant le sapin
      - * 2 : les deux espaces, de part et d'autre du sapin
  - starsFirstLine   : nombre d'* de la première ligne du bloc
****************************************************************************/
void print_sapin(int sizeBloc, int sizeSapin) {
  int	i;
  int	j;
  int	linesBloc;
  int	starsMiddleSapin;
  int	firstStar;
  int	starsLine;
  int	starsFirstLine;

  i = 0;
  j = 0;
  linesBloc = 4 + sizeBloc - 1;
  starsMiddleSapin = 0;
  firstStar = 0;
  starsLine = max_width(sizeBloc) - ((linesBloc - 1) * 2);
  starsFirstLine = starsLine;

  if (sizeBloc > 1) {
    print_sapin(sizeBloc - 1, sizeSapin);
  }
  while (i < linesBloc) {
    starsMiddleSapin = (max_width(sizeSapin)) / 2;
    firstStar = starsMiddleSapin - (starsFirstLine / 2);

    j =  print_blank(firstStar - i);
    print_stars_tronc(j, j + starsLine, 1);
    starsLine += 2;
    i++;
  }
}

/**************************************************
Role : affiche le tronc
  - left  : côté gauche du tronc
      - center + 1 : position du milieu du tronc
      - width / 2  : décalage de la moitié du tronc
  - right : limite droite du tronc
**************************************************/
void print_tronc(int height) {
  int	i;
  int center;
  int	width;
  int	left;
  int	right;

  i = 0;
  center = (max_width(height)) / 2;
  width = width_tronc(height);
  left = center + 1 - (width / 2);
  right = left + width;

  while (i < height) {
    print_stars_tronc(print_blank(left - 1), right - 1, 0);
    i++;
  }
}

void sapin(int size) {
  if (size > 0) {
    print_sapin(size, size);
    print_tronc(size);
  } else {
    my_putstr("The argument must be a positive integer.\n", 2);
  }
}

int main(int argc, char **argv) {
  if (argv[1] != '\0') {
    sapin(atoi(argv[1]));
  } else {
    my_putstr("Sapin takes its size as it first argument.\n", 2);
  }
  return (0);
}
