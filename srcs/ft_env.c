/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 12:59:20 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/10 20:02:30 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_mem.h"

static char	*ft_envitize(char *name, char *value)
{
	char	*res;

	if (!(res = ft_strnew(ft_strlen(name) + ft_strlen(value) + 1)))
		return (NULL);
	return (ft_strcat(ft_strcatc(ft_strcat(res, name), '='), value));
}

int		ft_putenv(char *name, char *value, t_shell *shell)
{
	size_t	len;

	if (!shell || !shell->envp || ft_getenv(name, shell))
		return (0);
	len = ft_tabsize(shell->envp);
	if (!(shell->envp[len] = ft_envitize(name, value)))
		return (0);
	name = NULL;
	if (!(shell->envp = (char **)ft_memjoin_clr(shell->envp,
					sizeof(char *) * (len + 1), &name, sizeof(char *))))
		return (0);
	return (1);
}

char	*ft_getenv(char *name, t_shell *shell)
{
	char	*ename;
	char	**it;

	if (!shell || !shell->envp || !(ename = ft_strnew(ft_strlen(name) + 2)))
		return (NULL);
	ft_strcat(ename, name);
	ft_strcat(ename, "=*");
	it = shell->envp;
	while (*it)
	{
		if (ft_strmatch(*it, ename))
		{
			free(ename);
			return (ft_strchr(*it, '=') + 1);
		}
		++it;
	}
	free(ename);
	return (NULL);
}

void	ft_setenv(char *name, char *value, t_shell *shell)
{
	char	*ename;
	char	**it;
	size_t	len;

	if (!shell || !shell->envp)
		return ;
	else if (!(ename = ft_getenv(name, shell)))
	{
		ft_putenv(name, value, shell);
		return ;
	}
	len = ft_strlen(name);
	ename -= len + 1;
	it = shell->envp;
	while (*it)
	{
		if (ename == *it)
		{
			free(*it);
			*it = ft_envitize(name, value);
			return ;
		}
		++it;
	}
}

void	ft_unsetenv(char *name, t_shell *shell)
{
	char	*ename;
	char	**envp;
	int		i;

	if (!shell || !shell->envp || !(ename = ft_getenv(name, shell)))
		return ;
	else if (!(envp = (char **)malloc(sizeof(char *)
					* (ft_tabsize(shell->envp) + 1))))
		return ;
	ename -= ft_strlen(name) + 1;
	i = 0;
	while (shell->envp[i])
	{
		if (ename == shell->envp[i])
		{
			free(shell->envp[i]);
			ename = NULL;
		}
		else
			envp[(ename ? i : i - 1)] = shell->envp[i];
		++i;
	}
	envp[i - 1] = NULL;
	free(shell->envp);
	shell->envp = envp;
}
