/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 16:27:55 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/25 21:20:39 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_mem.h"
#include "ft_str.h"
#include "ft_io.h"

int	builtin_env(int argc, char **argv)
{
	char	**it;

	(void)argv;
	(void)argc;
	it = g_shell->envp;
	while (*it)
		ft_putendl(*it++);
	return (0);
}

int	builtin_printenv(int argc, char **argv)
{
	char	*value;
	char	**it;

	if (argc > 1)
	{
		if (!(value = ft_getenv(argv[1], g_shell->envp)))
			return (1);
		ft_putendl(value);
	}
	else if ((it = g_shell->envp))
		while (*it)
			ft_putendl(*it++);
	return (0);
}
