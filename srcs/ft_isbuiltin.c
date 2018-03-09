/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isbuiltin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 19:09:06 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/08 20:22:08 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"

static t_builtin	g_builtins[] = {
	{"cd", builtin_cd}, {"echo", builtin_echo}, {"setenv", builtin_setenv},
	{"unsetenv", builtin_unsetenv}, {"env", builtin_env}
};
static size_t		g_builtins_size = sizeof(g_builtins) / sizeof(t_builtin);

t_shret	ft_isbuiltin(char *filename, t_args *args, t_shell *shell)
{
	size_t	i;

	i = 0;
	while (i < g_builtins_size)
	{
		if (!ft_strcmp(filename, g_builtins[i].name))
			return (g_builtins[i].func(args->argc - 1, args->argv, shell));
		++i;
	}
	return (SH_NFOUND);
}
