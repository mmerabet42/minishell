/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getlinecmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 20:27:14 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/07 20:50:46 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_str.h"
#include "ft_mem.h"

char	*ft_getcmdf(char *cmd, t_cmdf *cmdf)
{
	char	*str;

	if (!cmd || !cmdf)
		return (NULL);
	while (*cmd == ' ')
		++cmd;
	cmdf->cmd = cmd;
	cmdf->argv = NULL;
	cmdf->argc = 0;
	while (*cmd && *cmd != ';')
	{
		if (*cmd == '"')
			str = ft_strbetween(cmd, '"', '"');
		else if (*cmd == '\'')
			str = ft_strbetween(cmd, '\'', '\'');
		else if (!(str = ft_strbefore(cmd, ' ')))
			str = ft_strdup(cmd);
		ft_printf("L: '%s'\n", str);
		cmdf->argv = ft_memjoin_clr(cmdf->argv, sizeof(char *) * cmdf->argc, &str, sizeof(char *));
		cmd += ft_strlen(str) + (*cmd == '"' || *cmd == '\'' ? 2 : 1);
		free(str);
		++cmdf->argc;
	}
	return (cmd);
}

void	ft_cmdfdel(t_cmdf *cmdf)
{
	char	**ptr;

	if (!cmdf)
		return ;
	ptr = cmdf->argv;
	while (*ptr)
		free(*ptr++);
	free(cmdf->argv);
	cmdf->argv = NULL;
	cmdf->cmd = NULL;
}
