/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 19:29:29 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/15 22:01:48 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_io.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "ft_printf.h"

t_shell	*g_shell;

t_shret	builtin_echo(int argc, char **argv)
{
	int		i;
	int		n;
	char	*l;

	i = 0;
	n = 0;
	if (argc > 1 && !ft_strcmp(argv[1], "-n") && ++i)
		n = 1;
	while (i++ < argc)
	{
		ft_putstr((l = ft_strdupk(argv[i])));
		free(l);
		if (i + 1 < argc)
			ft_putchar(' ');
	}
	if (!n)
		ft_putchar('\n');
	return (SH_ESUCCESS);
}

t_shret	builtin_setenv(int argc, char **argv)
{
	int		i;
	char	*c;
	char	*value;

	i = 1;
	while (i < argc)
	{
		if ((c = ft_strchr(argv[i], '=')))
		{
			*c = '\0';
			value = c + 1;
			ft_setenv(argv[i], value, &g_shell->envp);
		}
		else if (i + 1 < argc)
		{
			ft_setenv(argv[i], argv[i + 1], &g_shell->envp);
			++i;
		}
		++i;
	}
	if (ft_strcmp(argv[1], "HOME"))
		g_shell->homepwd = ft_getenv("HOME", g_shell->envp);
	else if (ft_strcmp(argv[1], "USER"))
		g_shell->user = ft_getenv("USER", g_shell->envp);
	return (SH_ESUCCESS);
}

t_shret	builtin_unsetenv(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
		ft_unsetenv(argv[i++], &g_shell->envp);
	return (SH_ESUCCESS);
}

t_shret	builtin_env(int argc, char **argv)
{
	char	**it;

	(void)argc;
	(void)argv;
	it = g_shell->envp;
	while (*it)
		ft_putendl(*it++);
	return (SH_ESUCCESS);
}

t_shret	builtin_exit(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	g_shell->running = 0;
	return (SH_ESUCCESS);
}
