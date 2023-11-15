#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>


#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USEgetcharline 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: pointer
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *	struct passinfo - contains pseudo-arguements to pass into a function
 *@arg: a str generated containing arguements
 *@argv: an array of strings generated
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: command flag
 *@func: function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* hsh.c */
int hsh(info_t *, char **);
int finbult(info_t *);
void fincmd(info_t *);
void forcmd(info_t *);

/* path.c */
int testcmd(info_t *, char *);
char *doubchar(char *, int, int);
char *finpath(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* errors.c */
int putefed(char c, int fd);
int _eputchar(char);
int putesfed(char *str, int fd);
void _eputs(char *);



/* str_fun.c */
int stringcomp(char *, char *);
char *begwith(const char *, const char *);
char *stringconc(char *, char *);
int _strlen(char *);



/* str_fun2.c */
void _puts(char *);
int _putchar(char);
char *stringcp(char *, char *);
char *stringdoub(const char *);


/* str_fun3.c */
char *stringcon(char *, char *, int);
char *stringcop(char *, char *, int);
char *stringchar(char *, char);



/* str_fun4.c */
char **strintowor(char *, char *);
char **strintowor2(char *, char);

/* mem_fun */
char *memoset(char *, char, unsigned int);
void frfree(char **);
void *therealo(void *, unsigned int, unsigned int);

/* mem_fun2.c */
int befree(void **);

/* more_fun.c */
int animat(info_t *);
int _atoi(char *);
int isdel(char, char *);
int _isalpha(int);


/* more_fun2.c */
int errortoint(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convint(long int, int, int);
void rmcomm(char *);

/* bult_em.c */
int myqui(info_t *);
int myloca(info_t *);
int mysupp(info_t *);

/* bult_em2.c */
int myhisto(info_t *);
int myali(info_t *);

/* line.c module */
ssize_t getinline(info_t *);
int getcharline(info_t *, char **, size_t *);
void sigintHandler(int);

/* details.c module */
void cleardetai(info_t *);
void setdetai(info_t *, char **);
void releasedetai(info_t *, int);

/* envi.c module */
char *gettheenvi(info_t *, const char *);
int myeenvi(info_t *);
int setmyeenvi(info_t *);
int unsetmyeenvi(info_t *);
int mosteenvilist(info_t *);

/* envi2.c module */
char **gettheenvir(info_t *);
int unsetmyeenvir(info_t *, char *);
int setmyeenvir(info_t *, char *, char *);

/* fiof.c */
char *deshistofil(info_t *info);
int sethistofil(info_t *info);
int getthehisto(info_t *info);
int makethehisto(info_t *info, char *buf, int linecount);
int arrangethehiso(info_t *info);

/* li_str.c module */
list_t *addthenode(list_t **, const char *, int);
list_t *addthenodeend(list_t **, const char *, int);
size_t displistofstr(const list_t *);
int delthenodeatind(list_t **, unsigned int);
void releasethelist(list_t **);

/* li_str2.c module */
size_t listsize(const list_t *);
char **thelisttostr(list_t *);
size_t despthelist(const list_t *);
list_t *thenodstar(list_t *, char *, char);
ssize_t thenodeloc(list_t *, list_t *);

/* buff.c */
int testchain(info_t *, char *, size_t *);
void testthechain(info_t *, char *, size_t *, size_t, size_t);
int reptheali(info_t *);
int repthevar(info_t *);
int repthestr(char **, char *);

#endif
