#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../hashtable.h"
#include "../parser.h"

struct ticket {

	char * nome_passageiro;
	int nif;
	char * voo_ticket;
	char * lugar;
	float preco;
	float distancia;

};

typedef struct ticket *BILHETES;

void * create_ticket(){

	BILHETES b = malloc(sizeof *b);
	if(b == NULL) printf("Erro\n");
	return b;

}

void delete_ticket(void * b){

	BILHETES bs = (BILHETES) b;
	free(bs->nome_passageiro);
	bs->nif = 0;
	free(bs->voo_ticket);
	free(bs->lugar);
	bs->preco = 0;
	bs->distancia = 0;
	free(bs);

} 

void set_nome_passageiro(BILHETES b, char * s){
	strcpy(b->nome_passageiro,s);
}

void set_nif(BILHETES b, int x){
	b->nif = x;
}

void set_voo_ticket(BILHETES b, char * s){
	strcpy(b->voo_ticket,s);
}

void set_lugar(BILHETES b, char * s){
	strcpy(b->lugar,s);
}

void set_preco(BILHETES b, float x){
	b->preco = x;
}

void set_distancia(BILHETES b, float x){
	b->distancia = x;
}

void set_ticket(void * b, char * line){

	char * p = NULL, *temp_line = strdup(line), *os;
	BILHETES bs = (BILHETES) b;
	os = temp_line;
	int i = 0;

	while((p = strsep(&temp_line, ";")) != NULL){
		switch(i){
			case 0:
				set_nome_passageiro(bs,p);
				break;

			case 1:
				set_nif(bs,atoi(p));
				break;

			case 2:
				set_voo_ticket(bs,p);
				break;

			case 3:
				set_lugar(bs,p);
				break;

			case 4:
				set_preco(bs,atof(p));
				break;

			case 5:
				set_distancia(bs,atof(p));
				break;
		}
		i++;
	}
	free(os);
}

int is_valid_ticket(BILHETES b){
	// to do
	return 1;
}

char * get_nome_passageiro(void * b){
	BILHETES bs = (BILHETES) b;
	return bs->nome_passageiro;
}

int get_nif(void * b){
	BILHETES bs = (BILHETES) b;
	return bs->nif;
}

char * get_voo_ticket(void * b){
	BILHETES bs = (BILHETES) b;
	return bs->voo_ticket;
}

char * get_lugar(void * b){
	BILHETES bs = (BILHETES) b;
	return bs->lugar;
}

float  get_preco(void * b){
	BILHETES bs = (BILHETES) b;
	return bs->preco;
}

float get_distancia(void * b){
	BILHETES bs = (BILHETES) b;
	return bs->distancia;
}

void print_ticket(void * b){
	BILHETES bs = (BILHETES) b;
	printf("nome_passageiro:%s nif:%d voo_ticket:%s lugar:%s preco:%.2f distancia:%.2f\n", bs->nome_passageiro, bs->nif, bs->voo_ticket, bs->lugar, bs->preco, bs->distancia);
}

void copy_ticket(void* dst, void* src){
	BILHETES dstc = (BILHETES) dst;
	BILHETES srcc = (BILHETES) src;

	dstc->nome_passageiro = srcc->nome_passageiro;
	dstc->nif = srcc->nif;
	dstc->voo_ticket = srcc->voo_ticket;
	dstc->lugar = srcc->lugar;
	dstc->preco = srcc->preco;
	dstc->distancia = srcc->distancia;
}