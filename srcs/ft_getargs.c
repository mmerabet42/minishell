/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getlinecmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 20:27:14 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/15 21:20:44 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "ft_printf.h"

t_shell	*g_shell;

static char	*ctilde(int pos, char *homepwd, char **cmd)
{
	char	*str;
	char	*cstr;

	if (!(str = (pos == -1 ? ft_strdupl(*cmd) : ft_strndupl(*cmd, pos))))
		return (NULL);
	if (str[0] == '~' && str[1] != '~')
	{
		if ((cstr = ft_strjoin(homepwd, str + 1)))
		{
			*cmd += (pos == -1 ? ft_strlen(*cmd) : (size_t)pos);
			free(str);
			return (cstr);
		}
	}
	*cmd += (pos == -1 ? ft_strlen(*cmd) : (size_t)pos);
	return (str);
}

static char	*checkarg(char **cmd)
{
	static char	*str;
	char		*tld;
	int			pos;

	if (ft_strchr(DLM_FARG, **cmd))
	{
		tld = ft_strbetweenl(*cmd, **cmd, **cmd);
		if (*(*cmd += ft_strlen(tld) + 1) != '\0')
			++(*cmd);
		str = ft_strjoin_clr(str, tld, 2);
	}
	else if ((pos = ft_strpbrkl_pos(*cmd, DLM_ALL)) != -1 || 1)
	{
		tld = ctilde(pos, g_shell->homepwd, cmd);
		str = ft_strjoin_clr(str, tld, 2);
	}
	if (!ft_strchr(DLM_ARG DLM_INS, **cmd))
		return (NULL);
	tld = str;
	str = NULL;
	return (tld);
}

char		*ft_getargs(char *cmd, t_args *args)
{
	char	*str;

	if (!cmd || !args || !*cmd)
		return (NULL);
	while (ft_strchr(DLM_ARG, *cmd))
		++cmd;
	while (*cmd && !ft_strchr(DLM_INS, *cmd))
	{
		if ((str = checkarg(&cmd)))
			args->argv = ft_memjoin_clr(args->argv,
					sizeof(char *) * args->argc++, &str, sizeof(char *));
		while (*cmd && ft_strchr(DLM_ARG, *cmd))
			++cmd;
	}
	str = NULL;
	args->argv = ft_memjoin_clr(args->argv, sizeof(char *) * args->argc,
		&str, sizeof(char *));
	return (cmd);
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
