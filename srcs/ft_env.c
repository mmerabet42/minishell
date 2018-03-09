/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 12:59:20 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/09 17:34:43 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"

char	*ft_getenv(char *name, t_shell *shell)
{
	char	*ename;
	char	**it;

	if (!(ename = ft_strnew(ft_strlen(name) + 2)))
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

	if (!(ename = ft_strnew(ft_strlen(name) + 2)))
		return ;
	ft_strcat(ename, name);
	ft_strcat(ename, "=*");
	it = shell->envp;
	while (*it)
	{
		if (ft_strmatch(*it, ename))
		{
			free(*it);
			*it = ft_strrepstr_clr(ename, "*", value);
			return ;
		}
		++it;
	}
	free(ename);
}
