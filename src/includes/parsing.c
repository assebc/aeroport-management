#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "modules/avioes.h"
#include "modules/aeroporto.h"
#include "modules/voo.h"
#include "modules/ticket.h"

#include "btree.h"
#include "parser.h"

#define LINE_BUFFER 1024

#define PLANE "data/avioes.csv"
#define AERO "data/aeroportos.csv"
#define FLIGHT "data/voos.csv"
#define TICKET "data/tickets.csv"

int is_valid_plane(void * a){
	//AVIOES as = (AVIOES) a;
	return 1;
}

int is_valid_aeroport(void * a){
	//AEROPORTO as = (AEROPORTO) a;
	return 1;
}

int is_valid_flight(void * v){
	//VOOS vs = (VOOS) v;
	return 1;
}

int is_valid_ticket(void * b){
	//BILHETES bs = (BILHETES) b;
	return 1;
}

btree * btree_organizer(){

	btree ** a = malloc(sizeof(btree*));
	FILE * v = fopen(FLIGHT, "r");
	char line[LINE_BUFFER];

	while(fgets(line,LINE_BUFFER,v)!=NULL){
		VOOS v = create_voo();
		set_voo(v,line);
		insertID(a,get_num_voo(v));
		delete_voo(v);
	}

	return *a;
}

int pessoas_abordo(int num_voo, btree * tree){

	struct btree * tmp = tree;

	int value = id_wanted2(tmp, num_voo);

	return value;
}

float horas(int num_voo){

	FILE * v = fopen(FLIGHT, "r");
	char line[LINE_BUFFER];
	float sec, horas;

	while(fgets(line,LINE_BUFFER,v)!=NULL){
		VOOS v = create_voo();
		set_voo(v,line);
		if(get_num_voo(v) == num_voo){
			sec = date_compare(get_data_partida(v),get_data_chegada(v));
			delete_voo(v);
			break;
		}
		else delete_voo(v);
	}
	fclose(v);

	horas = sec / 3600;

	return horas;
}

float distancia(int num_voo){

	FILE * t = fopen(TICKET, "r");
	char line[LINE_BUFFER];
	float distancia;

	while(fgets(line,LINE_BUFFER,t)!=NULL){
		BILHETES b = create_ticket();
		set_ticket(b,line);
		if(get_num_voo(get_voo_ticket(b)) == num_voo){
			distancia = get_distancia(b);
			delete_ticket(b);
			break;
		}
		else delete_ticket(b);
	}
	fclose(t);

	return distancia;
}

float cost(int abordo, float horas, float milhas){

	float sum_costs, tripulacao, preco_galao = 2.0709;

	tripulacao = 400 * horas * abordo;
	tripulacao += 5000;

	milhas *= preco_galao;

	sum_costs = tripulacao + milhas;

	return sum_costs;
}

float all_tickets_return(int num_voo){

	FILE * t = fopen(TICKET, "r");
	float tickets = 0;
	char line[LINE_BUFFER];

	while(fgets(line,LINE_BUFFER,t)!=NULL){
		BILHETES b = create_ticket();
		set_ticket(b,line);
		if(get_num_voo(get_voo_ticket(b))==num_voo){
			tickets += get_preco(b);
			delete_ticket(b);
		} else delete_ticket(b);

	}

	fclose(t);
	
	return tickets;
}

btree * profit(){

	btree * tmp = btree_organizer();
	int N = conta_nodos(tmp);
	int * list = create_list(N);
	list = preorder(tmp, list);
	char * list_profit[N];

	for(int j = 0;j<N;j++){
		list_profit[j] = NULL;
	}

	char * lucro = "lucro";
	char * equilibrio = "equilibrio";
	char * prejuizo = "prejuizo";

	int num_voo;
	for(int i = 0;i<N;i++){
		num_voo = list[i];
		if(all_tickets_return(num_voo) > cost(pessoas_abordo(num_voo, tmp), horas(num_voo), distancia(num_voo) ) ) list_profit[i] = lucro;
		else if(all_tickets_return(num_voo) == cost(pessoas_abordo(num_voo, tmp), horas(num_voo), distancia(num_voo) ) ) list_profit[i] = equilibrio;
		else list_profit[i] = prejuizo;
	}

	profit_insert(tmp,list_profit);

	return tmp;
}



/*

	funcionalidade 1 -> v-
	funcionalidade 2 -> v
	funcionalidade 3 -> v
	funcionalidade 4 -> x
	funcionalidade 5 -> x


*/
