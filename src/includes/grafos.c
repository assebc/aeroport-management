#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

#include "modules/avioes.h"
#include "modules/aeroporto.h"
#include "modules/voo.h"
#include "modules/ticket.h"

#define LINE_BUFFER 1024

#define PLANE "data/avioes.csv"
#define AERO "data/aeroportos.csv"
#define FLIGHT "data/voos.csv"
#define TICKET "data/tickets.csv"

// strongly connected components

int aeroportos(){

	int acum = 0;

	FILE * a = fopen(AERO, "r");
	char line[LINE_BUFFER];

	while(fgets(line,LINE_BUFFER,a)!=NULL){
		acum++;
	}


	return acum;
}

char ** list_aeroport(int N){

	char ** aeroportos = malloc(sizeof(char*)*N);
	FILE * a = fopen(AERO, "r");
	char line[LINE_BUFFER];
	int i = 0;

	while(fgets(line,LINE_BUFFER,a)!=NULL){

		AEROPORTO a = create_aeroporto();
		set_aeroporto(a,line);
		aeroportos[i] = get_nome(a);
		i++;
		delete_aeroporto(a);

	}

	fclose(a);

	return aeroportos;
}

int get_indice_aeroport(char * aeroporto, char * aeroportos[]){

	int indice = 0;

	while(strcmp(aeroporto,aeroportos[indice])!=0) indice++;

	return indice;
}

void voos_matriz(int N, int matriz[N][N]){

	FILE * v = fopen(FLIGHT, "r");
	char line[LINE_BUFFER];
	char * partida = NULL; char * chegada = NULL;
	char ** aero = list_aeroport(N);
	int p, c;

	while(fgets(line,LINE_BUFFER,v)!=NULL){
		
		VOOS v = create_voo();
		set_voo(v,line);
		partida = get_aeroport_partida(v);
		p = get_indice_aeroport(partida,aero);
		chegada = get_aeroport_chegada(v);
		c = get_indice_aeroport(chegada,aero);
		matriz[p][c] = 1;
		delete_voo(v);

	}

	fclose(v);

}

int directly_connected(char * partida, char * chegada){

	int r = 0;
	int N = aeroportos();
	char ** aero = list_aeroport(N);
	int matriz[N][N];

	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			matriz[i][j] = 0;
		}
	}
	
	voos_matriz(N, matriz);

	int p = get_indice_aeroport(partida, aero);
	int c = get_indice_aeroport(chegada, aero);

	if(matriz[p][c] == 1) r = 1;

	return r;
}

float tempo_total_direto(char * partida, char * chegada){

	float tempo = 0;

	FILE * v = fopen(FLIGHT, "r");
	char line[LINE_BUFFER];

	while(fgets(line,LINE_BUFFER,v)!=NULL){
		VOOS v = create_voo();
		set_voo(v,line);
		if((strcmp(get_aeroport_partida(v),partida)==0) && (strcmp(get_aeroport_chegada(v),chegada)==0)) {
			tempo = date_compare(get_data_partida(v),get_data_chegada(v));
			delete_voo(v);
			break;
		 } else delete_voo(v);

	}
	fclose(v);
	tempo = tempo / 3600;

	return tempo;
}

float preco_direto(char * partida, char * chegada){

	float preco = 0;

	FILE * t = fopen(TICKET, "r");
	char line[LINE_BUFFER];

	while(fgets(line,LINE_BUFFER,t)!=NULL){
		BILHETES b = create_ticket();
		set_ticket(b,line);
		if( (strcmp(get_aeroport_partida(get_voo_ticket(b)), partida) == 0) && (strcmp(get_aeroport_chegada(get_voo_ticket(b)), chegada) == 0) ){
			preco = get_preco(b);
			delete_ticket(b);
			break;
		 } else delete_ticket(b);

	}
	fclose(t);

	return preco;
}