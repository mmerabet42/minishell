/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 18:25:06 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/15 19:24:06 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"

t_shell	*g_shell;

void	ft_addhistory(char *line)
{
	t_list	*lst;

	g_shell->ihis = -1;
	free(g_shell->cline);
	g_shell->cline = NULL;
	if ((g_shell->history && !ft_strcmp(line, g_shell->history->content))
			|| !(lst = ft_lstnew(line, ft_strlen(line) + 1)))
		return ;
	if ((lst->next = ft_lstparent(g_shell->history)))
		lst->next->parent = lst;
	g_shell->history = lst;
}

char	*ft_gethistory(int i)
{
	t_list	*lst;

	if (i == -1 && g_shell->cline)
		return (g_shell->cline);
	else if ((lst = ft_lstatpos(g_shell->history, i)))
		return ((char *)lst->content);
	return ("");
}


