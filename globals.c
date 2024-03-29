/*
   CITS2002 Project 2 2017
   Names:             Alexander Rafferty, Dhaval Vaghjiani
   Student numbers:   21712241, 22258431
   Date:              03/11/17
*/

#include "myshell.h"

//  THREE INTERNAL VARIABLES (SEE myshell.h FOR EXPLANATION)
char	*HOME, *PATH, *CDPATH;

char	*argv0		= NULL;		// the program's name
bool	interactive	= false;

// ------------------------------------------------------------------------

void check_allocation0(void *p, char *file, const char *func, int line)
{
    if(p == NULL) {
	fprintf(stderr, "%s, %s() line %i: unable to allocate memory\n",
			file, func, line);
	exit(2);
    }
}

static void print_redirection(SHELLCMD *t)
{
    if(t->infile != NULL)
	printf("< %s ", t->infile);
    if(t->outfile != NULL) {
	if(t->append == false)
	    printf(">");
	else
	    printf(">>");
	printf(" %s ", t->outfile);
    }
}

void print_shellcmd0(SHELLCMD *t)
{
    if(t == NULL) {
	printf("<nullcmd> ");
	return;
    }

    switch (t->type) {
    case CMD_COMMAND :
	for(int a=0 ; a<t->argc ; a++)
	    printf("%s ", t->argv[a]);
	print_redirection(t);
	break;

    case CMD_SEMICOLON :
	print_shellcmd0(t->left); printf("; "); print_shellcmd0(t->right);
	break;

    case CMD_AND :
	print_shellcmd0(t->left); printf("&& "); print_shellcmd0(t->right);
	break;

    case CMD_OR :
	print_shellcmd0(t->left); printf("|| "); print_shellcmd0(t->right);
	break;

    case CMD_SUBSHELL :
	printf("( "); print_shellcmd0(t->left); printf(") ");
	print_redirection(t);
	break;

    case CMD_PIPE :
	print_shellcmd0(t->left); printf("| "); print_shellcmd0(t->right);
	break;

    case CMD_BACKGROUND :
	print_shellcmd0(t->left); printf("& "); print_shellcmd0(t->right);
	break;

    default :
	fprintf(stderr, "%s: invalid CMDTYPE in print_shellcmd0()\n", argv0);
	exit(EXIT_FAILURE);
	break;
    }
}

char *search_paths(char **path, char *suffix)
{
    static char full_path[4096];
    // If path points to NULL, no more paths to try
    if (*path == NULL) return NULL;
    char *fp = full_path;
    // Copy path variable into buffer
    strcpy(fp, *path);
    // Advance to the end of the current path prefix
    fp = strchr(full_path, ':');
    if (fp == NULL) {
        fp = full_path + strlen(full_path);
    }
    // Append a forward slash
    *fp++ = '/';
    // Append the filename
    strcpy(fp, suffix);
    // Advance the path pointer to the next prefix
    *path = strchr(*path, ':');
    if (*path != NULL) (*path)++;
    return full_path;
}
