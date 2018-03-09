/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 18:44:40 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/09 17:47:01 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <unistd.h>

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
	t_artype	*types;
}				t_args;

typedef struct	s_shell
{
	char		*name;
	char		*pwd;
	char		*homepwd;
	char		*user;
	char		**paths;
	char		**envp;
	int			ison:1;
}				t_shell;

typedef t_shret	(*builtin_func)(int argc, char **argv, t_shell *shell);

typedef struct	s_builtin
{
	char			*name;
	builtin_func	func;
}				t_builtin;

char			*ft_getargs(char *cmd, t_args *args, t_shell *shell);
void			ft_delargs(t_args *args);

char			*ft_getenv(char *name, t_shell *shell);
void			ft_setenv(char *name, char *value, t_shell *shell);

t_shret			ft_access(char *filename, int tests);
t_shret			ft_chdir(char *dirname, t_shell *shell);

char			**ft_getpaths(char **envp);

t_shret			ft_getfullpath(char *fname,
								t_shell *shell,
								char *fullpath,
								size_t size);

char			*ft_strshret(t_shret shret);

void			ft_initshell(char *name, t_shell *shell, char **envp);
void			ft_delshell(t_shell *shell);

void			ft_exec(char *filename, char **argv, char **envp);

t_shret			ft_isbuiltin(char *name, t_args *args, t_shell *shell);

t_shret			builtin_cd(int argc, char **argv, t_shell *shell);
t_shret			builtin_echo(int argc, char **argv, t_shell *shell);
t_shret			builtin_setenv(int argc, char **argv, t_shell *shell);
t_shret			builtin_unsetenv(int argc, char **argv, t_shell *shell);
t_shret			builtin_env(int argc, char **argv, t_shell *shell);

#endif