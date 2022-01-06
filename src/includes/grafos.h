#ifndef GRAFOS_H
#define GRAFOS_H

typedef struct tup *TUPLE;

int aeroportos();
char ** list_aeroport(int N);
int get_indice_aeroport(char * aeroporto, char * aeroportos[]);
void voos_matriz(int N, int matriz[N][N]);
int directly_connected(char * partida, char * chegada);
float tempo_total_direto(char * partida, char * chegada);
TUPLE * preco_direto(char * partida, char * chegada);
int count_direct_flights(TUPLE * t);
int cheap_direct(TUPLE * t, int N);

int *** get_voos(char * aero_p, char * aero_c);
int *** get_voos_2(int *** voos);
char ** cheapest_2(int *** escala);
float precos_2(char ** line);
int *** get_voos_3(int *** voos);
char ** cheapest_3(int *** escala);
float precos_3(char ** line);
int *** get_voos_4(int *** voos);
char ** cheapest_4(int *** escala);
float precos_4(char ** line);

char ** get_choices(char * aero_p, char * aero_c, int opt);

#endif