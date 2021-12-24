#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define __USE_XOPEN
#include <time.h>

#include "modules/avioes.h"
#include "modules/aeroporto.h"
#include "modules/voo.h"
#include "modules/ticket.h"

void sh (char *str){
	char *p = str;
	for (;*p; p++) *p = *(p+1);
}

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

int is_valid_date(char *s){
		int year, month, day, hour, minutes, seconds, matches;

	matches = sscanf(s,"%4d-%2d-%2d %2d:%2d:%2d", &year, &month, &day, &hour, &minutes, &seconds);
	if (matches == 6 && ((year == 2005 && month > 4) || (year == 2005 && month == 4 && day >=7) || year > 2005) && year <= 2021 && strlen(s) == 19)
	{
		if ((((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day <= 31) || ((month == 4 || month == 6 || month == 9 || month == 11) && day <= 30) || (month == 2 && ((((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) && day <= 29) || day <= 28))) && day > 0)
		{
			if (hour >= 0 && hour <= 23 && minutes >= 0 && minutes <= 59 && seconds >= 0 && seconds <= 59)
				return 1;
		}

	}
	return 0;
}

int is_valid_number(char *s){
	char *p = s;
	float x = atof(p);

	if (x<=0) return 0;
	else return 1;
}

// return em segundos
int date_compare(char* date_1, char* date_2) {

	struct tm dtb_1 = {0}, dtb_2 = {0};
	time_t dt_1, dt_2;

	strptime(date_1, "%Y-%m-%d %H:%M:%S", &dtb_1);
	strptime(date_2, "%Y-%m-%d %H:%M:%S", &dtb_2);

	dt_1 = mktime(&dtb_1);
	dt_2 = mktime(&dtb_2);

	int r = difftime(dt_1, dt_2);
	
	return r;	
}
