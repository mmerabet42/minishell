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

t_shret	builtin_cd(int argc, char **argv)
{
	t_shret	acc;
	char	*name;

	if (argc == 1)
	{
		if ((acc = ft_chdir(g_shell->homepwd)) != SH_OK)
		{
			ft_printf("%s: %s: %s\n", argv[0], ft_strshret(acc),
					g_shell->homepwd);
			return (SH_EFAIL);
		}
	}
	else if (argc > 1)
	{
		name = argv[1];
		if (!ft_strcmp(argv[1], "-"))
			name = ft_getenv("OLDPWD", g_shell->envp);
		if ((acc = ft_chdir(name)) != SH_OK)
		{
			ft_printf("%s: %s: %s\n", argv[0], ft_strshret(acc), argv[1]);
			return (SH_EFAIL);
		}
	}
	ft_setenv("OLDPWD", ft_getenv("PWD", g_shell->envp), &g_shell->envp);
	ft_setenv("PWD", ft_getcwd(g_shell->pwd, 2048), &g_shell->envp);
	return (SH_ESUCCESS);
}
