/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getlinecmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 20:27:14 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/08 18:47:50 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "ft_printf.h"

static void impltype(t_args *args, char c)
{
	t_artype	type;

	if (c == '"')
		type = AR_DQUOTE;
	else if (c == '\'')
		type = AR_QUOTE;
	else
		type = AR_NONE;
	args->types = ft_memjoin_clr(args->types, sizeof(t_artype) * args->argc,
		&type, sizeof(t_artype));
}

static char	*ctilde(char *str, char *homepwd)
{
	char	*cstr;

	if (!str)
		return (NULL);
	if (str[0] == '~' && str[1] != '~')
	{
		if ((cstr = ft_strjoin(homepwd, str + 1)))
		{
			free(str);
			return (cstr);
		}
	}
	return (str);
}

char	*ft_getargs(char *cmd, t_args *args, t_shell *shell)
{
	char	*str;
	int		pos;

	if (!cmd || !args || !*cmd)
		return (NULL);
	while (*cmd == ' ' || *cmd == '\t')
		++cmd;
	while (*cmd && *cmd != ';')
	{
		if (*cmd == '"' || *cmd == '\'')
			str = ft_strbetween(cmd, *cmd, *cmd);
		else if ((pos = ft_strpbrk_pos(cmd, " \t;")) != -1 || 1)
			str = ctilde(pos != -1 ? ft_strndup(cmd, pos) : ft_strdup(cmd),
				shell->homepwd);
		impltype(args, *cmd);
		args->argv = ft_memjoin_clr(args->argv, sizeof(char *) * args->argc++,
			&str, sizeof(char *));
		cmd += ft_strlen(str) + (*cmd == '"' || *cmd == '\'' ? 2 : 0);
		while (*cmd == ' ' || *cmd == '\t')
			++cmd;
	}
	str = NULL;
	args->argv = ft_memjoin_clr(args->argv, sizeof(char *) * args->argc++,
		&str, sizeof(char *));
	return (*cmd == ';' ? cmd + 1 : cmd);
}

void	ft_delargs(t_args *args)
{
	int		i;

	if (!args)
		return ;
	i = 0;
	while (i < args->argc)
		free(args->argv[i++]);
	free(args->argv);
	free(args->types);
	args->types = NULL;
	args->argv = NULL;
	args->argc = 0;
}
