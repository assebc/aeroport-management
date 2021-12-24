#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define LINE_BUFFER 1024

#include "modules/avioes.h"
#include "modules/aeroporto.h"
#include "modules/voo.h"
#include "modules/ticket.h"

#define PLANE "data/avioes.csv"
#define AERO "data/aeroportos.csv"
#define FLIGHT "data/voos.csv"
#define TICKET "data/tickets.csv"

#include "btree.h"
#include "parser.h"

int is_valid_plane(void * a){
	AVIOES as = (AVIOES) a;
	return 1;
}

int is_valid_aeroport(void * a){
	AEROPORTO as = (AEROPORTO) a;
	return 1;
}

int is_valid_flight(void * v){
	VOOS vs = (VOOS) v;
	return 1;
}

int is_valid_ticket(void * b){
	BILHETES bs = (BILHETES) b;
	return 1;
}

/*

	node ** tree = malloc(sizeof(node*));
	
	FILE * t = fopen(TICKET, "r");
	//FILE * p = fopen(PLANE, "r");

	char line[LINE_BUFFER], line_2[LINE_BUFFER];
	int sum_costs, valid_line = 0, count_passageiro = 0;
	float time = 0;

	while (fgets(line, LINE_BUFFER, t) != NULL) {
		remove_possible_new_line(line);

		BILHETES b = create_ticket();
		set_ticket(b,line);
		valid_line = is_valid_ticket(b);

		if(valid_line){
			insert(tree, get_num_voo(get_voo_ticket(b)) );
		}
		delete_ticket(b);

		sum_costs += 5000;
*/

node * btree_organizer(){

	node * btree = malloc(sizeof(node*));
	node * tmp = btree;

	/*
	*/

	return btree;
}

int pessoas_abordo(int num_voo, node ** tree){

	node ** tmp = tree;

	searchfor(num_voo,tmp);

	return ((*tmp)->data2);
}

float horas(int num_voo){

	FILE * v = fopen(FLIGHT, "r");
	char line[LINE_BUFFER];
	float sec, horas;

	while(fgets(line,1024,v)!=NULL){
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

	while(fgets(line,1024,t)!=NULL){
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

	float tickets = 0;
	/*

	*/

	return tickets;

}

char * profit(node ** tree){

	node ** btree = tree;

	int num_voo;

	if(all_tickets_return(num_voo) > cost(pessoas_abordo(num_voo, btree), horas(num_voo), distancia(num_voo) ) ) return "lucro";
	if(all_tickets_return(num_voo) == cost(pessoas_abordo(num_voo, btree), horas(num_voo), distancia(num_voo) ) ) return "equilibrio";
	else return "prejuizo";
}