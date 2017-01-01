#ifndef SAPIN_H_
# define SAPIN_H_

# define PARITY(x) ((x) % 2 == 0) ? 1 : 0

void my_putchar(char, int);
void my_putstr(char *, int);

int print_blank(int);
void print_stars_tronc(int, int, int);

int width_tronc(int);
int max_width(int);

void print_sapin(int, int);
void print_tronc(int);
void sapin(int);

#endif
