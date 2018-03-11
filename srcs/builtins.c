/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 19:29:29 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/10 19:59:11 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_io.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "ft_printf.h"

t_shret	builtin_echo(int argc, char **argv, t_shell *shell)
{
	int		i;
	int		n;

	(void)shell;
	i = 1;
	n = 0;
	if (argc > 1 && !ft_strcmp(argv[1], "-n") && ++i)
		n = 1;
	while (i < argc)
	{
		ft_putstr(argv[i]);
		if (i + 1 < argc)
			ft_putchar(' ');
		++i;
	}
	if (!n)
		ft_putchar('\n');
	return (SH_ESUCCESS);
}

t_shret	builtin_setenv(int argc, char **argv, t_shell *shell)
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
			ft_setenv(argv[i], value, shell);
		}
		else if (i + 1 < argc)
		{
			ft_setenv(argv[i], argv[i + 1], shell);
			++i;
		}
		++i;
	}
	if (ft_strcmp(argv[1], "HOME"))
		shell->homepwd = ft_getenv("HOME", shell);
	else if (ft_strcmp(argv[1], "USER"))
		shell->user = ft_getenv("USER", shell);
	return (SH_ESUCCESS);
}

t_shret	builtin_unsetenv(int argc, char **argv, t_shell *shell)
{
	int	i;

	i = 0;
	while (i < argc)
		ft_unsetenv(argv[++i], shell);
	return (SH_ESUCCESS);
}

t_shret	builtin_env(int argc, char **argv, t_shell *shell)
{
	char	**it;

	(void)argc;
	(void)argv;
	it = shell->envp;
	while (*it)
		ft_putendl(*it++);
	return (SH_ESUCCESS);
}

t_shret	builtin_exit(int argc, char **argv, t_shell *shell)
{
	(void)argc;
	(void)argv;
	shell->running = 0;
	return (SH_ESUCCESS);
}
