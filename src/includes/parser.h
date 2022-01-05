#ifndef PARSER_H
#define PARSER_H

void sh (char *str);
void remove_possible_new_line(char *line);
char* remove_spaces(char *s);

int is_valid_date(char *s);
int is_valid_number(char *s);
int date_compare(char * date_1, char * date_2);
int date_compare_bool(char * date_1, char * date_2);

#endif