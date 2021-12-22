#ifndef VOO_H
#define VOO_H

typedef struct voo *VOOS;

void * create_voo();
void delete_voo(void * v);

void set_num_voo(VOOS v, int x);
void set_data_partida(VOOS v, char * s);
void set_data_chegada(VOOS v, char * s);
void set_aeroport_partida(VOOS v, char * s);
void set_aeroport_chegada(VOOS v, char * s);
void set_aviao_voo(VOOS v, char * s);
void set_voo(void * v, char * line);

int get_num_voo(void * v);
char * get_data_partida(void * v);
char * get_data_chegada(void * v);
char * get_aeroport_partida(void * v);
char * get_aeroport_chegada(void * v);
char * get_aviao_voo(void * v);

void print_voo(void * v);
void copy_voo(void* dst, void* src);

#endif