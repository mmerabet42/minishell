/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 18:03:23 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/15 21:41:48 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "ft_printf.h"
#include <unistd.h>

t_shret	ft_chdir(char *name)
{
	t_shret	acc;

	acc = SH_NFOUND;
	if (!name || (acc = ft_access(name, R_OK)) != SH_OK)
		return (acc);
	else
		chdir(name);
	return (SH_OK);
}

int	builtin_cd(int argc, char **argv)
{
	t_shret	acc;
	char	*name;

	if (argc == 1)
	{
		if ((acc = ft_chdir(g_shell->homepwd)) != SH_OK)
			return (ft_printf("%s: %s: %s\n", argv[0], ft_strshret(acc),
					g_shell->homepwd) ? 1 : 1);
	}
	else if (argc > 1)
	{
		if (!ft_strcmp((name = argv[1]), "-"))
			name = ft_getenv("OLDPWD", g_shell->envp);
		if ((acc = ft_chdir(name)) != SH_OK)
			return (ft_printf("%s: %s: %s\n", argv[0],
					ft_strshret(acc), name) ? 1 : 1);
		if (!ft_strcmp(argv[1], "-"))
			ft_printf("%s\n", name);
	}
	ft_setenv("OLDPWD", ft_getenv("PWD", g_shell->envp), &g_shell->envp);
	ft_setenv("PWD", ft_getcwd(g_shell->pwd, 2048), &g_shell->envp);
	return (0);
}
