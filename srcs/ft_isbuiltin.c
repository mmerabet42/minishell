/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isbuiltin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 19:09:06 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/15 21:21:38 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_mem.h"

static t_builtin	g_builtins[] = {
	{"cd", builtin_cd}, {"echo", builtin_echo}, {"setenv", builtin_setenv},
	{"unsetenv", builtin_unsetenv}, {"env", builtin_env}, {"exit", builtin_exit}
};

static size_t		g_builtins_size = sizeof(g_builtins) / sizeof(t_builtin);

t_shell	*g_shell;

t_shret	ft_isbuiltin(char *filename, t_args *args)
{
	size_t	i;
	char	**argvp;

	i = 0;
	while (i < g_builtins_size)
	{
		if (!ft_strcmp(filename, g_builtins[i].name))
		{
			argvp = ft_memdup(args->argv, sizeof(char *) * (args->argc + 1));
			g_builtins[i].func(args->argc, argvp);
			free(argvp);
			return (SH_ESUCCESS);
		}
		++i;
	}
	return (SH_NFOUND);
}
