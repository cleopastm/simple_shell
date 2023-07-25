#include "shell.h"

/**
 * my_getline - function to create a getline
 *
 * Return: 0
 */

char *my_getline(void)
{
	char *line;
	static char buffer[BUFFER_SIZE];
	static int pos;
	static int len;
	int i;

	if (pos >= len)
	{
		len = read(STDIN_FILENO, buffer, sizeof(buffer));
		if (len <= 0)
			return (NULL);
		pos = 0;
	}

	line = malloc(sizeof(char) * (len - pos + 1));
	if (line == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	i = 0;
	while (pos < len && buffer[pos] != '\n')
	{
		line[i++] = buffer[pos++];
	}
	line[i] = '\0';
	if (pos < len && buffer[pos] == '\n')
		pos++;
	return (line);
}
