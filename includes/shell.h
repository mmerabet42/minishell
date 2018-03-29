/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 18:44:40 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/29 17:00:06 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <unistd.h>
# include "ft_list.h"

# define DLM_ARG " \t"
# define DLM_FARG "\"'"
# define DLM_INS ";<>|&"
# define DLM_ALLT DLM_ARG DLM_INS
# define DLM_INSL "&&:||:<<:>>"
# define DLM_BINSL "&|<>"
# define DLM_ALL DLM_ARG DLM_INS DLM_FARG DLM_BINSL

typedef enum	e_shret
{
	SH_ADENIED, SH_NFOUND, SH_NEXIST, SH_OK, SH_NONE, SH_EFAIL, SH_ESUCCESS,
	SH_NOTDIR
}				t_shret;

typedef enum	e_optret
{
	OPT_END, OPT_UNKNOWN, OPT_ALAST, OPT_OK, OPT_MISSING, OPT_EMPTY, OPT_EQUAL
}				t_optret;

typedef struct	s_args
{
	int			argc;
	char		**argv;
}				t_args;

typedef int	(*t_builtin_func)(int, char **);

typedef struct	s_builtin
{
	char			*name;
	t_builtin_func	func;
}				t_builtin;

typedef struct	s_shell
{
	char		*name;
	char		pwd[2048];
	char		*homepwd;
	char		*user;
	char		**paths;
	char		**envp;
	int			running:1;
	t_list		*history;
	int			ihis;
	char		*cline;
	t_builtin	*builtins;
	pid_t		curpid;
	int			exitcode;
}				t_shell;

typedef struct	s_opt
{
	char		c;
	char		*clong;
	int			n;
	char		**ptr;
	char		*cur;
	int			seq;
}				t_opt;

char			*ft_getargs(char *cmd, t_args *args);
void			ft_delargs(t_args *args);

char			*ft_getenv(char *name, char **envp);
int				ft_setenv(char *name, char *value, char ***envp);
int				ft_unsetenv(char *name, char ***envp);
int				ft_putenv(char *name, char *value, char ***envp);

t_shret			ft_access(char *filename, int tests);
t_shret			ft_chdir(char *dirname);
char			*ft_getcwd(char *pwd, size_t size);
void			ft_getcursor(int *x, int *y);
int				ft_getopt(char ***argv, const char *options, t_opt *opt);

void			ft_makeraw(int setb);
int				ft_readraw(char *line, size_t size);

char			**ft_getpaths(char **envp);
void			resetpath(void);

t_shret			ft_getfullpath(char *fname,
								char *fullpath,
								size_t size);

char			*ft_strshret(t_shret shret);

void			shell_begin(char *name, int argc, char **argv, char **envp);
int				shell_end(void);

void			addhistory(char *line);
char			*gethistory(int i);
void			clearhistory(void);

int				ft_exec(char *filename, char **argv, char **envp);
void			ft_exit(int code, const char *msg);
void			ft_exitf(int code, const char *msgf, ...);

t_shret			ft_isbuiltin(char *name, t_args *args);
int				isbuiltin(char *name);
int				execbuiltin(char *name, t_args *args);

int				builtin_cd(int argc, char **argv);
int				builtin_env(int argc, char **argv);
int				builtin_echo(int argc, char **argv);
int				builtin_exit(int argc, char **argv);
int				builtin_setenv(int argc, char **argv);
int				builtin_unsetenv(int argc, char **argv);
int				builtin_printenv(int argc, char **argv);
int				builtin_history(int argc, char **argv);

extern int		g_dontfree;
extern t_shell	*g_shell;

#endif
