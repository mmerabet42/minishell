/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getlinecmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 20:27:14 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/12 12:51:08 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "ft_printf.h"

static char	*ctilde(char *str, char *homepwd, char **cmd)
{
	char	*cstr;

	if (!str)
		return (NULL);
	if (str[0] == '~' && str[1] != '~')
	{
		if ((cstr = ft_strjoin(homepwd, str + 1)))
		{
			*cmd += ft_strlen(str);
			free(str);
			return (cstr);
		}
	}
	*cmd += ft_strlen(str);
	return (str);
}

static char	*checkarg(char **cmd, t_shell *shell)
{
	static char	*str;
	char		*tld;
	int			pos;

	if (**cmd == '"' || **cmd == '\'')
	{
		tld = ft_strbetween(*cmd, **cmd, **cmd);
		if (*(*cmd += ft_strlen(tld) + 1) != '\0')
			++(*cmd);
		str = ft_strjoin_clr(str, tld, 2);
	}
	else if ((pos = ft_strpbrk_pos(*cmd, " \t;\"'")) != -1 || 1)
	{
		tld = ctilde((pos != -1 ? ft_strndup(*cmd, pos) : ft_strdup(*cmd)),
			shell->homepwd, cmd);
		str = ft_strjoin_clr(str, tld, 2);
	}
	if (**cmd != ' ' && **cmd != '\t' && **cmd != ';' && **cmd != '\0')
		return (NULL);
	tld = str;
	str = NULL;
	return (tld);
}

char		*ft_getargs(char *cmd, t_args *args, t_shell *shell)
{
	char	*str;

	if (!cmd || !args || !*cmd)
		return (NULL);
	while (*cmd == ' ' || *cmd == '\t')
		++cmd;
	while (*cmd && *cmd != ';')
	{
		if ((str = checkarg(&cmd, shell)))
			args->argv = ft_memjoin_clr(args->argv,
					sizeof(char *) * args->argc++, &str, sizeof(char *));
		while (*cmd == ' ' || *cmd == '\t')
			++cmd;
	}
	str = NULL;
	args->argv = ft_memjoin_clr(args->argv, sizeof(char *) * args->argc++,
		&str, sizeof(char *));
	return (*cmd == ';' ? cmd + 1 : cmd);
}

void		ft_delargs(t_args *args)
{
	int		i;

	if (!args)
		return ;
	i = 0;
	while (i < args->argc)
		free(args->argv[i++]);
	free(args->argv);
	ft_bzero(args, sizeof(t_args));
}
