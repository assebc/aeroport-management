/**
 * @file parser.c
 * @brief Ficheiro que contém as funções auxiliares usadas ao longo do projeto
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

/**
 * @brief Função sh
 *
 * Função que remove um caracter de uma string
 * 
 */
void sh (char *str){
	char *p = str;
	for (;*p; p++) *p = *(p+1);
}

/**
 * @brief Função is_valid_type
 *
 * Função que remove (/n ou /r/n) do final de uma string
 * 
 */
void remove_possible_new_line(char line[]) {
	int len = 0;
	char *s = line;
	while (*s != '\0') { len++; s++; }
	if (line[len-2] == '\r') { //WINDOWS
		sh(s-1);
		sh(s-2);
	} else if (line[len-1] == '\n') // UNIX
		sh(s-1);
}

/**
 * @brief Função remove_spaces
 *
 * Função que retira todos os espaços (' ') de uma dada string
 * 
 * @returns string sem espaços
 */
char* remove_spaces(char *s) {
	char *p = s;
	while (*p)
	{
		if (*p == ' ')
			sh(p);
		p++;
	}
	return s;
}