#ifndef PARSING_H
#define PARSING_H

int is_valid_plane(void * a);
int is_valid_aeroport(void * a);
int is_valid_flight(void * v);
int is_valid_ticket(void * b);

int cost();
int all_tickets_return();
char * profit();

#endif