/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 19:29:29 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/25 21:02:58 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_io.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "ft_printf.h"

t_shell	*g_shell;

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
		else if (ft_strequ(nava[0], "PATH"))
			resetpath();
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
		else if (ft_strequ(argv[i], "PATH"))
			resetpath();
	}
	return (0);
}

int	builtin_exit(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	g_shell->running = 0;
	return (0);
}
