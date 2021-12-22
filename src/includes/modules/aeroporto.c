#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../parser.h"

struct aeroport {
	char *id;
	char *login;	
	char *type;
	char *created_at;
	char *followers;
	char *follower_list;
	char *following;
	char *following_list;
	char *public_gists;
	char *public_repos;
};

