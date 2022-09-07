#ifndef SHELL_H
#define SHELL_H

/* ------------Headers and macro def------------------- */

/* other utility header for basic functions and macros */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * header - The header below is used for the following
 *			function and system call
 *
 * chdir()
 * fork()
 * execve()
 * pid_t()
 */
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <errno.h>
#include <dirent.h>

/* ANSI C signal handling */
#include <signal.h>

/* header file for waitpid and associated macros */
#include <sys/wait.h>

/* ============================================== */


/* -------define the type of command----------- */

#define TERM_CMD 1
#define PATH_CMD 2
#define INTERNAL_CMD 3
#define INVALID_CMD -1

/* ============================================ */


/* ------------define delimeter---------------- */

#define DELIM " \t\r\n\a"
#define AND_DELIM "&&"
#define OR_DELIM "||"

/* ============================================ */

/* ---------define logical command type--------- */

#define LOGIC_AND 1
#define LOGIC_OR 2
#define NOT_FOUND 0

/* ============================================ */

/* --------token size and line read size-------- */

#define RL_BUFSIZE 1024
#define TOK_BUFSIZE 64

/* ============================================= */



/* ------------declare global variable------------- */

extern char **environ;

/* ================================================ */



/* -----------------------struct-------------------- */

/**
 * struct shell_data - Global data structure
 * @shell_name: the name of the shell at compile time
 * @old_pwd: old path visited
 * @cmd_counter: counts the number of cmds executed
 * @err_status: track error status for diff fxns
 * @aliases: holds the aliases we have currently
 */
typedef struct shell_data
{
	char **aliases;
	char *shell_name;
	char *old_pwd;
	int cmd_counter;
	int err_status;
} shell_t;


/**
 * struct mapFunc - maps a command to a function
 * @command_name: name of command
 * @func: the function that executes the command
 */
typedef struct mapFunc
{
	char *command_name;
	void (*func)(char **command, shell_t *);
} function_map;


/* ================================================== */


/* -------------------shell main-------------------- */

int main(int, char **);
shell_t *shell_init(shell_t *);

/* ================================================= */


/* -----------shell utility functions------------ */

void ctrl_C_func(int);
char *shell_readline(void);
void shell_launch(char **, int, shell_t *);
void (*get_func(char *))(char **, shell_t *);

/* =============================================== */


/* -------------shell process funtions-------------- */

void shell_loop(shell_t *);
void non_interractive(shell_t *);
int check_cmd_type(char *);
void shell_execute(char **, int, shell_t *);
char *_strcpy(char *, char *);

/* ================================================= */


/* ----------------helper functions------------------ */

int _printf(char *, int);
void remove_comment(char *);
int _putchar(char);
int _atoi(char *);
char *_itoa(int);

/* ================================================= */


/* ---------------String functions-------------------*/

char *_strcat(char *dst, char *src);
int _strcmp(char *, char *);
int _strlen(char *);
char *_strdup(char *s);
char *_strndup(char *s, int n);

/* ================================================== */


/* ------------------builtin funct------------------- */

void env(char **, shell_t *);
void quit(char **, shell_t *);
void ch_dir(char **, shell_t *);
void display_help(char **, shell_t *);

/* ===================================================== */

/* ------------------builtin funct 2-------------------- */

void aliasFunc(char **, shell_t *);
void handle_setenv(char **, shell_t *);
void handle_unsetenv(char **, shell_t *);
void set_alias(char *, shell_t *);
char *alias_error(char **, shell_t *);

/* ===================================================== */

/* ---------------Handle error messages----------------- */

void print_error(char **, shell_t *);

char *exit_error(char **, shell_t *);
char *chdir_error(char **, shell_t *);
char *env_error(char **, shell_t *);
char *invalid_cmd_error(char **, shell_t *);
/* ===================================================== */

/* -----------function to handle tokenization----------- */
char **tokenize(char *, const char *);
int is_delimeter(const char *delimeters, char c);
int startsWith(char *s, char *ndl);
int endsWith(char *s, char *ndl);

/* ==================================================== */


/* ---------------Memory management---------------------*/

void free_tokenized(char **tokens);
void *_realloc(void *, unsigned int, unsigned int);

/* ==================================================== */


/* ---------------Environmemt Functions---------------- */

char *_getenv(char *);
int _setenv(char *, char *);
int _unsetenv(char *);
char *check_path(char *);
void replace_vars(char **, shell_t *);

/* ==================================================== */

/* -----------shell logical functions help-------------- */

char **logic_token(char *);
void execute_logic(char *, shell_t *);
void logic_token_help(char *, shell_t *);

/* ===================================================== */

#endif /* SHELL_H */
