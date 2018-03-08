/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 19:29:29 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/08 20:04:30 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_io.h"

t_shret	builtin_echo(int argc, char **argv, t_shell *shell)
{
	int	i;

	(void)shell;
	i = 1;
	while (i < argc)
		ft_putendl(argv[i++]);
	return (SH_ESUCCESS);
}

t_shret	builtin_cd(int argc, char **argv, t_shell *shell)
{
	int	i;

	(void)shell;
	i = 1;
	while (i < argc)
		ft_putendl(argv[i++]);
	return (SH_ESUCCESS);
}

t_shret	builtin_setenv(int argc, char **argv, t_shell *shell)
{
	int	i;

	(void)shell;
	i = 1;
	while (i < argc)
		ft_putendl(argv[i++]);
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
	int	i;

	(void)shell;
	i = 1;
	while (i < argc)
		ft_putendl(argv[i++]);
	return (SH_ESUCCESS);
}
