/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 18:25:06 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/14 18:29:55 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"

t_shell	*g_shell;

void	ft_addhistory(char *line)
{
	if (g_shell->history)
	{
		g_shell->history = ft_lstparent(g_shell->history);
		if (!ft_strcmp(g_shell->history->content, line))
			return ;
	}
	ft_lstpushfront(&g_shell->history, ft_lstcreate(line, ft_strlen(line)));
}

char	*ft_gethistory(void)
{
	if (g_shell->history)
		return ((char *)g_shell->history->content);
	return (NULL);
}


