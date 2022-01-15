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

void print_f5(char * ap, char * ac, int opt, int N, int matriz[N][N]){

	char ** flight = get_choices(ap, ac, opt, N, matriz);

	btree * tree = btree_organizer();
 
	int ocu_lugares, lugares, num_voos, num_1, num_2, num_3, num_4; int * num_flights = malloc(sizeof(int)*4);
	float  t_espera, t_voo, t_total, costs;
	char * flights = NULL; char ** horarios = malloc(sizeof(char*)*8); 
	char * aviao = NULL; char * aviao2 = NULL; char * aviao3 = NULL; char * aviao4 = NULL;

	switch(opt){

		case 0: // output para voo mais barato

			num_voos = get_len_pointer(flight);

			if (num_voos != 1) print_f5(ap,ac,num_voos,N,matriz);
			else print_f5(ap,ac,num_voos,N,matriz);

			break;

		case 1: // output para voo mais rápido

			for(int a = 0;a<2;a++){
				strcpy(flights,flight[a]);

				VOOS vs = create_voo();
				set_voo(vs, flights);

				num_flights[0] = get_num_voo(vs);
				num_flights[1] = 0;
				num_flights[2] = 0;
				num_flights[3] = 0;

				ocu_lugares = id_wanted2(tree,num_flights[0]);
				horarios[0] = get_data_partida(vs);
				horarios[1] = get_data_chegada(vs);
				horarios[2] = "";
				horarios[3] = "";
				horarios[4] = "";
				horarios[5] = "";
				horarios[6] = "";
				horarios[7] = "";

				AVIOES as = create_aviao();
				aviao = get_aviao_voo(vs);
				set_aviao(as, aviao);
				lugares = get_num_lugares(as);
				delete_aviao(as);

				delete_voo(vs);
			}

			t_espera = 0;
			t_voo = horas(num_flights[0]);
			t_total = t_espera + t_voo;

			costs = cost(ocu_lugares, t_voo, distancia(num_flights[0]));

			break;

		case 2:	// output para viagem com 2 escalas

			num_1 = directly_connected_num(flight[0],flight[1]);
			num_2 = directly_connected_num(flight[1],flight[2]);

			num_flights[0] = num_1;
			num_flights[1] = num_2;
			num_flights[2] = 0;
			num_flights[3] = 0;

			ocu_lugares = id_wanted2(tree,num_1) + id_wanted2(tree,num_2);
			horarios[0] = get_data_partida_num(num_1);
			horarios[1] = get_data_chegada_num(num_1);
			horarios[2] = get_data_partida_num(num_2);
			horarios[3] = get_data_chegada_num(num_2);
			horarios[4] = "";
			horarios[5] = "";
			horarios[6] = "";
			horarios[7] = "";

			AVIOES as1 = create_aviao();
			AVIOES as2 = create_aviao();
			aviao = get_aviao_nvoo(num_1);
			aviao2 = get_aviao_nvoo(num_2);
			set_aviao(as1, aviao);
			set_aviao(as2, aviao2);
			lugares = get_num_lugares(as1) + get_num_lugares(as2);
			delete_aviao(as1);
			delete_aviao(as2);

			t_espera = date_compare(horarios[1],horarios[2]);
			t_voo = horas(num_1) + horas(num_2);
			t_total = t_espera + t_voo;

			costs = cost(ocu_lugares, t_voo, distancia(num_1) + distancia(num_2));

			break;

		case 3: // output para viagem com 3 escalas

			num_1 = directly_connected_num(flight[0],flight[1]);
			num_2 = directly_connected_num(flight[1],flight[2]);
			num_3 = directly_connected_num(flight[2],flight[3]);

			num_flights[0] = num_1;
			num_flights[1] = num_2;
			num_flights[2] = num_3;
			num_flights[3] = 0;

			ocu_lugares = id_wanted2(tree,num_1) + id_wanted2(tree,num_2) + id_wanted2(tree,num_3);
			horarios[0] = get_data_partida_num(num_1);
			horarios[1] = get_data_chegada_num(num_1);
			horarios[2] = get_data_partida_num(num_2);
			horarios[3] = get_data_chegada_num(num_2);
			horarios[4] = get_data_partida_num(num_3);
			horarios[5] = get_data_chegada_num(num_3);
			horarios[6] = "";
			horarios[7] = "";

			
			as1 = create_aviao();
			as2 = create_aviao();
			AVIOES as3 = create_aviao();
			aviao = get_aviao_nvoo(num_1);
			aviao2 = get_aviao_nvoo(num_2);
			aviao3 = get_aviao_nvoo(num_3);
			set_aviao(as1, aviao);
			set_aviao(as2, aviao2);
			set_aviao(as3, aviao3);
			lugares = get_num_lugares(as1) + get_num_lugares(as2) + get_num_lugares(as3);
			delete_aviao(as1);
			delete_aviao(as2);
			delete_aviao(as3);

			t_espera = date_compare(horarios[1],horarios[2]) + date_compare(horarios[3],horarios[4]);
			t_voo = horas(num_1) + horas(num_2) + horas(num_3);
			t_total = t_espera + t_voo;

			costs = cost(ocu_lugares, t_voo, distancia(num_1) + distancia(num_2) + distancia(num_3));

			break;

		case 4: // output para viagem com 4 escalas

			num_1 = directly_connected_num(flight[0],flight[1]);
			num_2 = directly_connected_num(flight[1],flight[2]);
			num_3 = directly_connected_num(flight[2],flight[3]);
			num_4 = directly_connected_num(flight[3],flight[4]);

			num_flights[0] = num_1;
			num_flights[1] = num_2;
			num_flights[2] = num_3;
			num_flights[3] = num_4;

			ocu_lugares = id_wanted2(tree,num_1) + id_wanted2(tree,num_2) + id_wanted2(tree,num_3) + id_wanted2(tree,num_4);
			horarios[0] = get_data_partida_num(num_1);
			horarios[1] = get_data_chegada_num(num_1);
			horarios[2] = get_data_partida_num(num_2);
			horarios[3] = get_data_chegada_num(num_2);
			horarios[4] = get_data_partida_num(num_3);
			horarios[5] = get_data_chegada_num(num_3);
			horarios[6] = get_data_partida_num(num_4);
			horarios[7] = get_data_chegada_num(num_4);

			as1 = create_aviao();
			as2 = create_aviao();
			as3 = create_aviao();
			AVIOES as4 = create_aviao();
			aviao = get_aviao_nvoo(num_1);
			aviao2 = get_aviao_nvoo(num_2);
			aviao3 = get_aviao_nvoo(num_3);
			aviao4 = get_aviao_nvoo(num_4);
			set_aviao(as1, aviao);
			set_aviao(as2, aviao2);
			set_aviao(as3, aviao3);
			set_aviao(as4, aviao4);
			lugares = get_num_lugares(as1) + get_num_lugares(as2) + get_num_lugares(as3) + get_num_lugares(as4);
			delete_aviao(as1);
			delete_aviao(as2);
			delete_aviao(as3);
			delete_aviao(as4);

			t_espera = date_compare(horarios[1],horarios[2]) + date_compare(horarios[3],horarios[4])  + date_compare(horarios[5],horarios[6]);
			t_voo = horas(num_1) + horas(num_2) + horas(num_3) + horas(num_4);
			t_total = t_espera + t_voo;

			costs = cost(ocu_lugares, t_voo, distancia(num_1) + distancia(num_2) + distancia(num_3) + distancia(num_4));

			break;

	}
	if(t_total>72) printf("impossivel com tantas escalas");
	else{
		printf("numero lugares ocupados (total) / numero lugares do(s) voo(s) (total) => %d/%d\n", ocu_lugares, lugares);
		printf("tempo de espera entre voo(s) (total) => %.2f h\n", t_espera);
		printf("tempo total do(s) voo(s) => %.2f h\n", t_voo);
		printf("tempo total entre partida e chegada => %.2f h\n", t_total);
		printf("voo(s) a apanhar => %s\n", flights);
		printf("numero do(s) voo(s) a apanhar => %d %d %d %d\n", num_flights[0], num_flights[1], num_flights[2], num_flights[3]);
		printf("horarios do(s) voo(s) => partida: %s chegada: %s partida: %s chegada: %s partida: %s chegada: %s partida: %s chegada: %s\n", horarios[0], horarios[1], horarios[2], horarios[3] ,horarios[4], horarios[5], horarios[6], horarios[7]);
		printf("custo total de todas as viagens para a(s) franquia(s) => %.2f €\n", costs);
	}
}

int insert(int f1){

	int f1_1;
	printf("O que deseja inserir?\n");
	printf("Aviao : 1\n");
	printf("Aeroporto : 2\n");
	printf("Voo: 3\n");
	printf("Bilhete : 4\n");
	scanf("%d", &f1_1);
	return f1_1;

}

void insert_f1(int f1_1){

	switch(f1_1){

		case 1: // aviao

			break;

		case 2: // aeroporto

			break;

		case 3: // voo

			break;

		case 4: // bilhete

			break;

	}

}

int main(){

	int funcionalide, opt, f1 f1_1;
	int N = aeroportos();
	int matriz[N][N];
	char * ap = NULL; char * ac = NULL;

	for (int i = 0;i<N;i++){
		for(int j = 0;j<N;j++){
			matriz[i][j] = 0;
		}
	}
	
	printf("Que funcionalidade? 1 ou 5?\n");
	scanf("%d",&funcionalidade);
	putchar('\n');

	switch(funcionalidade){

		case 1 :
			printf("O que deseja fazer?\n");
			printf("Inserir : 1\n");
			printf("Remover : 2\n");
			printf("Alterar : 3\n");
			printf("Listar : 4\n");
			scanf("%d", &f1);
			putchar('\n');

			switch(f1){

				case 1 :
					f1_1 = insert(f1);
					insert_f1(f1_1);
					break;

				case 2 :

					break;

				case 3 :

					break;

				case 4 :

					break;
			}
			

			break;

		case 5 :
			printf("Partida : \n");
			scanf("%s", ap);
			printf("Destino : \n");
			scanf("%s", ac);
			putchar('\n');

			printf("Tipo de viagem : \n");
			printf("Voo mais barato : 0\n");
			printf("Voo mais rápido : 1\n");
			printf("2 escalas : 2\n");
			printf("3 escalas : 3\n");
			printf("4 escalas : 4\n");
			scanf("%d", &opt);
			putchar('\n');

			print_f5(ap, ac, opt, N, matriz);
			break;
	}
		

	return 0;
}