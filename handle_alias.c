#include "shell.h"

	
void handle_alias(char *cmd)
{
	Alias alias_list[MAX_ALIASES];
	int num_aliases = 0;
	int i;
	char *name;
	char *value;
	int alias_index;

	if (cmd == NULL)
	{
		for (i = 0; i < num_aliases; i++) {
		printf("%s='%s'\n", alias_list[i].name, alias_list[i].value);
        }
    } else {
        
        char *token = strtok(cmd, " ");
        while (token != NULL) {
        
            char *equal_sign = strchr(token, '=');
            if (equal_sign != NULL) {
          
                *equal_sign = '\0'; 
                name = token;
                value = equal_sign + 1;
               
                alias_index = -1;
                for (i = 0; i < num_aliases; i++) {
                    if (strcmp(alias_list[i].name, name) == 0) {
                        alias_index = i;
                        break;
                    }
                }
               
                if (alias_index != -1) {
               
                    strncpy(alias_list[alias_index].value, value, MAX_ALIAS_LENGTH - 1);
                    alias_list[alias_index].value[MAX_ALIAS_LENGTH - 1] = '\0';
                } else {
               
                    if (num_aliases < MAX_ALIASES) {
                        strncpy(alias_list[num_aliases].name, name, MAX_ALIAS_LENGTH - 1);
                        alias_list[num_aliases].name[MAX_ALIAS_LENGTH - 1] = '\0';
                        strncpy(alias_list[num_aliases].value, value, MAX_ALIAS_LENGTH - 1);
                        alias_list[num_aliases].value[MAX_ALIAS_LENGTH - 1] = '\0';
                        num_aliases++;
                    } else {
                        printf("Maximum number of aliases reached\n");
                    }
                }
            } else {
                     int alias_found = 0;
                for ( i = 0; i < num_aliases; i++) {
                    if (strcmp(alias_list[i].name, token) == 0) {
                        printf("%s='%s'\n", alias_list[i].name, alias_list[i].value);
                        alias_found = 1;
                        break;
                    }
                }
                if (!alias_found) {
                    printf("Alias not found: %s\n", token);
                }
            }
            token = strtok(NULL, " ");
        }
    }
}
