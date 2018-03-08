/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 18:44:40 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/07 20:38:11 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <unistd.h>

typedef struct	s_args
{
	int			argc;
	char		**argv;
}				t_args;

typedef struct	s_shell
{
	char		**paths;
	char		**envp;
	char		pwd[2048];
	int			ison:1;
}				t_shell;

typedef enum	e_shret
{
	SH_ADENIED, SH_NFOUND, SH_NEXIST, SH_OK, SH_NONE
}				t_shret;

char			*ft_getargs(char *cmd, t_args *args);
void			ft_delargs(t_args *args);

char			**ft_getpaths(char **envp);

t_shret			ft_getfullpath(char *fname,
								t_shell *shell,
								char *fullpath,
								size_t size);

char			*ft_strshret(t_shret shret);

void			ft_initshell(t_shell *shell, char **envp);

#endif
