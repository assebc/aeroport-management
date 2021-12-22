#ifndef PARSING_H
#define PARSING_H

int is_valid_plane(AVIOES a);
int is_valid_aeroport(AEROPORTO a);
int is_valid_flight(VOOS v);
int is_valid_ticket(BILHETES b);

int cost();
int all_tickets_return();
char * profit();

#endif