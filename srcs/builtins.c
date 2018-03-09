/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 19:29:29 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/09 17:41:06 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_io.h"
#include "ft_str.h"
#include "ft_mem.h"

t_shret	builtin_echo(int argc, char **argv, t_shell *shell)
{
	int	i;
	int	n;

	(void)shell;
	i = 1;
	n = 0;
	if (argc > 1 && !ft_strcmp(argv[1], "-n") && ++i)
		n = 1;
	while (i < argc)
	{
		ft_putstr(argv[i++]);
		if (i + 1 < argc)
			ft_putchar(' ');
	}
	if (!n)
		ft_putchar('\n');
	return (SH_ESUCCESS);
}

t_shret	builtin_setenv(int argc, char **argv, t_shell *shell)
{
	if (argc >= 3)
		ft_setenv(argv[1], argv[2], shell);
	shell->homepwd = ft_getenv("HOME", shell);
	return (SH_ESUCCESS);
}

t_shret	builtin_unsetenv(int argc, char **argv, t_shell *shell)
{
	int	i;

	(void)shell;
	i = 1;
	while (i < argc)
		ft_putendl(argv[i++]);
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