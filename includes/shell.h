/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 18:44:40 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/19 18:03:33 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <unistd.h>
# include "ft_list.h"

# define DLM_ARG " \t"
# define DLM_INS ";>"
# define DLM_FARG "\"'"
# define DLM_ALL DLM_ARG DLM_INS DLM_FARG

typedef enum	e_shret
{
	SH_ADENIED, SH_NFOUND, SH_NEXIST, SH_OK, SH_NONE, SH_EFAIL, SH_ESUCCESS
}				t_shret;

typedef enum	e_artype
{
	AR_NONE, AR_QUOTE, AR_DQUOTE
}				t_artype;

typedef struct	s_args
{
	int			argc;
	char		**argv;
}				t_args;

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
}				t_shell;

typedef struct	s_opt
{
	int			n;
	char		**ptr;
}				t_opt;

typedef t_shret	(*builtin_func)(int argc, char **argv);

typedef struct	s_builtin
{
	char			*name;
	builtin_func	func;
}				t_builtin;

char			*ft_getargs(char *cmd, t_args *args);
void			ft_delargs(t_args *args);

char			*ft_getenv(char *name, char **envp);
void			ft_setenv(char *name, char *value, char ***envp);
void			ft_unsetenv(char *name, char ***envp);
int				ft_addenv(char *name, char *value, char ***envp);

t_shret			ft_access(char *filename, int tests);
t_shret			ft_chdir(char *dirname);
char			*ft_getcwd(char *pwd, size_t size);
void			ft_getcursor(int *x, int *y);
char			ft_getopt(char ***argv, const char *options, t_opt *opt);

void			ft_makeraw(int setb);
int				ft_readraw(char *line, size_t size);

char			**ft_getpaths(char **envp);

t_shret			ft_getfullpath(char *fname,
								char *fullpath,
								size_t size);

char			*ft_strshret(t_shret shret);

void			shell_begin(char *name, char **envp);
void			shell_end(void);

void			ft_addhistory(char *line);
char			*ft_gethistory(int i);

void			ft_exec(char *filename, char **argv, char **envp);
void			ft_exit(int code, const char *msg);
void			ft_exitf(int code, const char *msgf, ...);

t_shret			ft_isbuiltin(char *name, t_args *args);

t_shret			builtin_cd(int argc, char **argv);
t_shret			builtin_env(int argc, char **argv);
t_shret			builtin_echo(int argc, char **argv);
t_shret			builtin_exit(int argc, char **argv);
t_shret			builtin_setenv(int argc, char **argv);
t_shret			builtin_unsetenv(int argc, char **argv);

extern t_shell	*g_shell;

#endif
