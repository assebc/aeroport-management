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

struct tup{

	float preco;
	int num_voo;
	float tempo;

};

typedef struct tup *TUPLE;

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

TUPLE * preco_direto(char * partida, char * chegada){

	TUPLE * res = malloc(sizeof(TUPLE));
	FILE * t = fopen(TICKET, "r");
	char line[LINE_BUFFER]; char * aux = NULL;
	int i = 0;

	while(fgets(line,LINE_BUFFER,t)!=NULL){
		BILHETES b = create_ticket();
		set_ticket(b,line);
		aux = get_voo_ticket(b);

		VOOS vs = create_voo();
		set_ticket(vs,aux);

		if( (strcmp(get_aeroport_partida(vs), partida) == 0) && (strcmp(get_aeroport_chegada(vs), chegada) == 0) ){
			res[i]->preco = get_preco(b);
			res[i]->num_voo = get_num_voo(vs);
			res[i]->tempo = date_compare(get_data_partida(vs),get_data_chegada(vs)) / 3600;
			i++;
			delete_voo(vs);
			delete_ticket(b);
			break;
		}
		delete_voo(vs);
		delete_ticket(b);
	}
	fclose(t);

	return res;
}

int count_direct_flights(TUPLE * t){

	int num = 0;

	while(t){
		num++;
	}

	return num;
}

int cheap_direct(TUPLE * t, int N){

	int min = 100000; // preço absurdo
	for(int i=0;i<N;i++){
		if(min>t[i]->preco) min = t[i]->preco;
	}

	return min;
}

int *** get_voos(char * aero_p, char * aero_c){

	int limit_time = 72;
	// arrays com arrays dos voos
	// ficha 4 alg
	
}

int *** get_voos_2(int *** voos){

	int i = 0, j = 0;
	int *** voos_2 = malloc(sizeof (char*)* sizeof(char*) * 200);

	while(voos){

		if(get_len(*voos[i]) == 2){
			while(*voos_2[j]){
				**voos_2[0] = **voos[0];
				**voos_2[1] = **voos[1];
				j++;
				break;
			}
		}

		i++;
	}

	return voos_2;
}

char ** cheapest_2(int *** escala){

	char ** escalas = NULL;
	float aux_price = 1000000, aux_1, aux_2, atm_price;

	while(escala){

		aux_1 = get_preco_num_voo(**escala[0]);
		aux_2 = get_preco_num_voo(**escala[1]);
		atm_price = aux_1 + aux_2;
		if(atm_price<aux_price){
			char * voo_1 = get_voo_num_voo(**escala[0]);
			char * voo_2 = get_voo_num_voo(**escala[1]);
			strcpy(escalas[0],voo_1);
			strcpy(escalas[1],voo_2);
			aux_1 = 0; aux_2 = 0, atm_price = 0;
		}
		
	}

	return escalas;
}

float precos_2(char * f1, char * f2){

	int preco = 0;
	VOOS v = create_voo();
	VOOS vs = create_voo();
	set_voo(v,f1);
	set_voo(vs,f2);
	preco += get_preco_num_voo(get_num_voo(v));
	preco += get_preco_num_voo(get_num_voo(vs));
	delete_voo(v);
	delete_voo(vs);

	return preco;
}

int *** get_voos_3(int *** voos){

	int i = 0, j = 0;
	int *** voos_3 =  malloc(sizeof (char*)* sizeof(char*) * 300);

	while(voos){

		if(get_len(*voos[i]) == 3){
			while(*voos_3[j]){
				*voos_3[0] = *voos[0];
				*voos_3[1] = *voos[1];
				*voos_3[2] = *voos[2];
				j++;
				break;
			}
		}

		i++;
	}

	return voos_3;

}
char ** cheapest_3(int *** escala){

	char ** escalas = NULL;
	int aux_price = 1000000, aux_1, aux_2, aux_3, atm_price;

	while(escala){

		aux_1 = get_preco_num_voo(**escala[0]);
		aux_2 = get_preco_num_voo(**escala[1]);
		aux_3 = get_preco_num_voo(**escala[2]);
		atm_price = aux_1 + aux_2 + aux_3;
		if(atm_price<aux_price){
			char * voo_1 = get_voo_num_voo(**escala[0]);
			char * voo_2 = get_voo_num_voo(**escala[1]);
			char * voo_3 = get_voo_num_voo(**escala[2]);
			strcpy(escalas[0],voo_1);
			strcpy(escalas[1],voo_2);
			strcpy(escalas[2],voo_3);
			aux_1 = 0; aux_2 = 0; aux_3 = 0; atm_price = 0;
		}
		
	}

	return escalas;
}

float precos_3(char * f1, char * f2, char * f3){

	int preco = 0;
	VOOS v = create_voo();
	VOOS vs = create_voo();
	VOOS vss = create_voo();
	set_voo(v,f1);
	set_voo(vs,f2);
	set_voo(vss,f3);
	preco += get_preco_num_voo(get_num_voo(v));
	preco += get_preco_num_voo(get_num_voo(vs));
	preco += get_preco_num_voo(get_num_voo(vss));
	delete_voo(v);
	delete_voo(vs);
	delete_voo(vss);

	return preco;
}

int *** get_voos_4(int *** voos){

	int i = 0, j = 0;
	int *** voos_4 =  malloc(sizeof (char*)* sizeof(char*) * 400);

	while(voos){

		if(get_len(*voos[i]) == 4){
			while(*voos_4[j]){
				**voos_4[0] = **voos[0];
				**voos_4[1] = **voos[1];
				**voos_4[2] = **voos[2];
				**voos_4[3] = **voos[3];
				j++;
				break;
			}
		}

		i++;
	}

	return voos_4;
}
char ** cheapest_4(int *** escala){

	char ** escalas = NULL;
	int aux_price = 1000000, aux_1, aux_2, aux_3, aux_4, atm_price;

	while(escala){

		aux_1 = get_preco_num_voo(**escala[0]);
		aux_2 = get_preco_num_voo(**escala[1]);
		aux_3 = get_preco_num_voo(**escala[2]);
		aux_4 = get_preco_num_voo(**escala[3]);
		atm_price = aux_1 + aux_2 + aux_3 + aux_4;
		if(atm_price<aux_price){
			char * voo_1 = get_voo_num_voo(**escala[0]);
			char * voo_2 = get_voo_num_voo(**escala[1]);
			char * voo_3 = get_voo_num_voo(**escala[2]);
			char * voo_4 = get_voo_num_voo(**escala[3]);
			strcpy(escalas[0],voo_1);
			strcpy(escalas[1],voo_2);
			strcpy(escalas[2],voo_3);
			strcpy(escalas[3],voo_4);
			aux_1 = 0; aux_2 = 0; aux_3 = 0; aux_4 = 0; atm_price = 0;
		}
		
	}

	return escalas;
}

float precos_4(char * f1, char * f2, char * f3, char * f4){

	int preco = 0;
	VOOS v = create_voo();
	VOOS vs = create_voo();
	VOOS vss = create_voo();
	VOOS vsss = create_voo();
	set_voo(v,f1);
	set_voo(vs,f2);
	set_voo(vss,f3);
	set_voo(vsss,f4);
	preco += get_preco_num_voo(get_num_voo(v));
	preco += get_preco_num_voo(get_num_voo(vs));
	preco += get_preco_num_voo(get_num_voo(vss));
	preco += get_preco_num_voo(get_num_voo(vsss));
	delete_voo(v);
	delete_voo(vs);
	delete_voo(vss);
	delete_voo(vsss);

	return preco;
}

char ** get_choices(char * aero_p, char *  aero_c, int opt){

	FILE * v = fopen(FLIGHT, "r");
	char line[LINE_BUFFER]; char def_line[LINE_BUFFER]; char ** flight = malloc(sizeof(char*)*4);
	int *** escalas_2; int *** escalas_3; int *** escalas_4;
	TUPLE * tup = malloc(sizeof(TUPLE));
	int direct_cheap, i = 0, min = 72, atm_voo;
	float preco_def = 0, preco_min;

	tup = preco_direto(aero_p, aero_c);
	direct_cheap = cheap_direct(tup,count_direct_flights(tup));

	// menor voo
	while(tup){
		if(min>tup[i]->tempo){
			min = tup[i]->tempo;
			atm_voo = tup[i]->num_voo;
			i++;
		}
	}

	escalas_2 = get_voos_2(get_voos(aero_p,aero_c));
	char ** barato_2 = cheapest_2(escalas_2);
	float preco_2 = precos_2(barato_2[0],barato_2[1]);

	escalas_3 = get_voos_3(get_voos(aero_p,aero_c));
	char ** barato_3 = cheapest_3(escalas_3);
	float preco_3 = precos_3(barato_3[0],barato_3[1],barato_3[2]);

	escalas_4 = get_voos_4(get_voos(aero_p,aero_c));
	char ** barato_4 = cheapest_4(escalas_4);
	float preco_4 = precos_4(barato_4[0],barato_4[1],barato_4[2],barato_4[3]);

	while(fgets(line,LINE_BUFFER,v)!=NULL){
		VOOS vs = create_voo();
		set_voo(vs,line);

		VOOS vtmp = create_voo();
		
		switch(opt){

			case 0: // mais barato
				if(get_num_voo(vs) == direct_cheap) {  // por default o voo mais barato é o mais barato direto
					set_voo(vtmp,line);
					strcpy(def_line,line);
					preco_def = get_preco(vtmp);
					delete_voo(vtmp);
				}

				if(preco_def != 0) preco_min = mais_barato(preco_def, preco_2, preco_3, preco_4);

				if (preco_min == preco_def) *flight = def_line;
				else if (preco_min == preco_2) flight = barato_2;
				else if (preco_min == preco_3) flight = barato_3;
				else if (preco_min == preco_4) flight = barato_4;
				break;

			case 1: // mais rápido
				if(get_num_voo(vs)==atm_voo) *flight = line;
				break;

			case 2: // melhor com 2 escalas (o mais barato)
				flight = barato_2;
				break;

			case 3: // melhor com 3 escalas (o mais barato)
				flight = barato_3;
				break;

			case 4: // melhor com 4 escalas (o mais barato)
				flight = barato_4;
				break;

		}
		delete_voo(vs);
	}
	fclose(v);

	return flight;

}

