/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getlinecmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 20:27:14 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/29 16:59:18 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "ft_printf.h"

extern t_shell	*g_shell;

static char	*ctilde(int pos, char *homepwd, char **cmd)
{
	char	*str;
	char	*cstr;

	if (!(str = (pos == -1 ? ft_strdupl(*cmd) : ft_strndupl(*cmd, pos))))
		return (NULL);
	if (str[0] == '~' && str[1] != '~' && homepwd)
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

static char	*goenv(char *tld)
{
	int		di;
	char	*dptr;

	if ((di = ft_strchr_pos(tld, '$')) != -1)
	{
		tld[di] = '\0';
		if ((dptr = ft_getenv(&tld[di + 1], g_shell->envp)))
			tld = ft_strjoin_clr(tld, dptr, 0);
		else
			tld = ft_strjoin_clr(tld, NULL, 0);
	}
	return (tld);
}

static char	*checkarg(char **cmd)
{
	static char	*str;
	char		*tld;

	if (ft_strchr(DLM_FARG, **cmd))
	{
		tld = ft_strbetweenl(*cmd, **cmd, **cmd);
		if (*(*cmd += ft_strlen(tld) + 1) != '\0')
			++(*cmd);
		str = ft_strjoin_clr(str, tld, 2);
	}
	else
	{
		tld = ctilde(ft_strpbrkl_pos(*cmd, DLM_ALL), g_shell->homepwd, cmd);
		str = ft_strjoin_clr(str, goenv(tld), 2);
	}
	if (!ft_strchr(DLM_ALLT, **cmd))
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
	while (*cmd && ft_strchr(DLM_ARG, *cmd))
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
	int	i;

	if (!args)
		return ;
	i = 0;
	if (args->argv)
		while (i < args->argc)
			free(args->argv[i++]);
	free(args->argv);
	ft_bzero(args, sizeof(t_args));
}
