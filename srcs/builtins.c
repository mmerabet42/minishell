/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 19:29:29 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/19 22:13:53 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_io.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "ft_printf.h"

t_shell	*g_shell;

int	builtin_echo(int argc, char **argv)
{
//	t_opt	opt;
//	int		ret;

/*	++argv;
	ft_bzero(&opt, sizeof(t_opt));
	while ((ret = ft_getopt(&argv, "neE", &opt)) != OPT_END)
	{
		
	}

*/	int		i;
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
	return (0);
}

int	builtin_setenv(int argc, char **argv)
{
	int		i;
	char	*c;
	char	*nava[2];

	i = 0;
	while (++i < argc)
	{
		if (ft_bzero(nava, sizeof(char *) * 2) && (c = ft_strchr(argv[i], '=')))
		{
			*c = '\0';
			nava[1] = c + 1;
			nava[0] = argv[i];
		}
		else if (i + 1 < argc)
			ft_memcpy(nava, &argv[i++], sizeof(char *) * 2);
		ft_setenv(nava[0], nava[1], &g_shell->envp);
		if (ft_strequ(nava[0], "HOME"))
			g_shell->homepwd = ft_getenv("HOME", g_shell->envp);
		else if (ft_strequ(nava[0], "USER"))
			g_shell->user = ft_getenv("USER", g_shell->envp);
	}
	return (0);
}

int	builtin_unsetenv(int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		ft_unsetenv(argv[i], &g_shell->envp);
		if (ft_strequ(argv[i], "HOME"))
			g_shell->homepwd = NULL;
		else if (ft_strequ(argv[i], "USER"))
			g_shell->user = NULL;
	}
	return (0);
}

int	builtin_env(int argc, char **argv)
{
	char	**it;

	(void)argc;
	(void)argv;
	it = g_shell->envp;
	while (*it)
		ft_putendl(*it++);
	return (0);
}

int	builtin_exit(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	g_shell->running = 0;
	return (0);
}
