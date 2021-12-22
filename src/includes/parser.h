/**
 * @file parser.h
 * @brief Header quer inicializa as funções do ficheiro parser.c
 */
#ifndef PARSER_H
#define PARER_H

void sh (char *str);
void remove_possible_new_line(char *line);
char* remove_spaces(char *s);

#endif