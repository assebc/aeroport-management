#ifndef GRAFOS_H
#define GRAFOS_H

int aeroportos();
char ** list_aeroport(int N);
int get_indice_aeroport(char * aeroporto, char * aeroportos[]);
void voos_matriz(int N, int matriz[N][N]);
int directly_connected(char * partida, char * chegada);
float tempo_total_direto(char * partida, char * chegada);
float preco_direto(char * partida, char * chegada);

#endif