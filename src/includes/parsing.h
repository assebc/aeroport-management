#ifndef PARSING_H
#define PARSING_H

int is_valid_plane(void * a);
int is_valid_aeroport(void * a);
int is_valid_flight(void * v);
int is_valid_ticket(void * b);

int pessoas_abordo(int num_voo, node * tree);
float horas(int num_voo);
float distancia(int num_voo);

float cost(int abordo, float horas, float milhas);
float all_tickets_return(int num_voo);
char * profit(node ** tree);

#endif