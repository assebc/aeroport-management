#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "includes/modules/avioes.h"
#include "includes/modules/aeroporto.h"
#include "includes/modules/voo.h"
#include "includes/modules/ticket.h"

#include "includes/btree.h"
#include "includes/grafos.h"
#include "includes/parser.h"
#include "includes/parsing.h"

void print_f5(char * ap, char * ac, int opt){

	char ** flight = get_choices(ap, ac, opt);

	btree * tree = btree_organizer();

	int ocu_lugares, lugares, num_voos; int * num_flights = malloc(sizeof(int)*4);
	float  t_espera, t_voo, t_total, costs;
	char * flights = NULL; char ** horarios = malloc(sizeof(char*)*4); char * aviao = NULL;

	switch(opt){

		case 0: // output para voo mais barato

			num_voos = get_len_pointer(flight);

			if (num_voos != 1) print_f5(ap,ac,num_voos);
			else{

				strcpy(flights,*flight);

				VOOS vs = create_voo();
				set_voo(vs, flights);

				num_flights[0] = get_num_voo(vs);
				num_flights[1] = 0;
				num_flights[2] = 0;
				num_flights[3] = 0;

				ocu_lugares = id_wanted2(tree,*num_flights);
				horarios[0] = get_data_partida(vs);
				horarios[1] = get_data_chegada(vs);
				horarios[2] = "";
				horarios[3] = "";

				AVIOES as = create_aviao();
				aviao = get_aviao_voo(vs);
				set_aviao(as, aviao);
				lugares = get_num_lugares(as);
				delete_aviao(as);

				delete_voo(vs);

				t_espera = 0;
				t_voo = horas(*num_flights);
				t_total = t_espera + t_voo;

				costs = cost(ocu_lugares, t_voo, distancia(*num_flights));

			}

			break;

		case 1: // output para voo mais rápido

			strcpy(flights,*flight);

			VOOS vs = create_voo();
			set_voo(vs, flights);

			num_flights[0] = get_num_voo(vs);
			num_flights[1] = 0;
			num_flights[2] = 0;
			num_flights[3] = 0;

			ocu_lugares = id_wanted2(tree,*num_flights);
			horarios[0] = get_data_partida(vs);
			horarios[1] = get_data_chegada(vs);
			horarios[2] = "";
			horarios[3] = "";

			AVIOES as = create_aviao();
			aviao = get_aviao_voo(vs);
			set_aviao(as, aviao);
			lugares = get_num_lugares(as);
			delete_aviao(as);

			delete_voo(vs);

			t_espera = 0;
			t_voo = horas(*num_flights);
			t_total = t_espera + t_voo;

			costs = cost(ocu_lugares, t_voo, distancia(*num_flights));

			break;

		case 2:	// output para viagem com 2 escalas

			break;

		case 3: // output para viagem com 3 escalas

			break;

		case 4: // output para viagem com 4 escalas

			break;

	}

	printf("numero lugares ocupados (total) / numero lugares do(s) voo(s) (total) => %d/%d\n", ocu_lugares, lugares);
	printf("tempo de espera entre voo(s) (total) => %.2f h\n", t_espera);
	printf("tempo total do(s) voo(s) => %.2f h\n", t_voo);
	printf("tempo total entre partida e chegada => %.2f h\n", t_total);
	printf("voo(s) a apanhar => %s\n", flights);
	printf("numero do(s) voo(s) a apanhar => %d %d %d %d\n", num_flights[0], num_flights[1], num_flights[2], num_flights[3]);
	printf("horarios do(s) voo(s) => %s %s %s %s\n", horarios[0], horarios[1], horarios[2], horarios[3]);
	printf("custo total de todas as viagens para a(s) franquia(s) => %.2f €\n", costs);
	
}



int main(){

	return 0;
}