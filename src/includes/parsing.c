#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "modules/avioes.h"
#include "modules/aeroporto.h"
#include "modules/voo.h"
#include "modules/ticket.h"


#define PLANE "data/avioes.csv"
#define AERO "data/aeroportos.csv"
#define FLIGHT "data/voos.csv"
#define TICKET "data/tickets.csv"

#include "hashtable.h"
#include "parser.h"

int is_valid_plane(AVIOES a){

	return 1;
}

int is_valid_aeroport(AEROPORTO a){

	return 1;
}

int is_valid_flight(VOOS v){

	return 1;
}

int is_valid_ticket(BILHETES b){

	return 1;
}

int cost(){

	ht *ht = ht_create(TABLE_SIZE);

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
			ht_insert(ht, get_num_voo(get_voo_ticket(b)), b);
			ht->data += 1;
		}
		delete_ticket(b);

		sum_costs += 5000;


	return sum_costs;
}

int all_tickets_return(){


}

char * profit(){

	if(all_tickets_return()>cost()) return "lucro";
	if(all_tickets_return()==cost()) return "equilibrio";
	else return "prejuizo";
}