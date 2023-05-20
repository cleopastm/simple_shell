#include "shell.h"
/**
 * my_getline - reads a line from the standard input
 *
 * Return: a pointer to the line read, or NULL if there is no more input
 */
char *my_getline(void)
{
        static char buf[1024];
        static int pos;
        int c;
        while ((c = getchar()) != EOF && c != '\n')
        {
                buf[pos++] = c;
                if (pos == 1023)
                {
                        buf[pos] = '\0';
                        pos = 0;
                        return buf;
                }
        }
        if (c == EOF && pos == 0)
                return NULL;
        buf[pos] = '\0';
        pos = 0;
        return buf;
}
