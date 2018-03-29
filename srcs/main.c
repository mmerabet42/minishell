/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 18:40:09 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/29 17:00:05 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_io.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "shell.h"
#include "ft_types.h"
#include <unistd.h>

t_shell	*g_shell;

static void	ft_readline(char *line)
{
	char	fullpath[1024];
	t_args	args;
	t_shret	shret;
	int		pos;

	ft_bzero(&args, sizeof(t_args));
	while ((line = ft_getargs(line, &args)) && g_shell->running)
	{
		if (((pos = ft_strpbrkstr(line, DLM_INSL))
					|| ft_strchr(DLM_INS, *line)))
			line += (pos ? pos : 1);
		if (args.argc >= 1
				&& ft_isbuiltin(args.argv[0], &args) == SH_NFOUND)
		{
			shret = ft_getfullpath(args.argv[0], fullpath, 1024);
			if (shret != SH_OK)
				ft_printf("%s: %s: %s\n", g_shell->name, ft_strshret(shret),
					args.argv[0]);
			else if (ft_exec(fullpath, args.argv, g_shell->envp) == -1)
				ft_printf("%s: exec format error: %s\n",
						g_shell->name, args.argv[0]);
		}
		ft_delargs(&args);
	}
}

static void	printprompt(void)
{
	int	x;

	ft_getcursor(&x, NULL);
	if (x > 1)
		ft_printf("%#{lgrey}%{bold/;0;0;0}%%%{0}\n");
	ft_printf("%{0}%S %{lred}%s %{lcyan}%s%{0} %{bold}%S%{0} ", L"㋜",
		g_shell->user, g_shell->pwd, L"∴");
}

int			main(int argc, char **argv, char **envp)
{
	char	line[8192];
	int		c;

	shell_begin("minishell", argc, argv, envp);
	ft_bzero(line, 8192);
	c = 0;
	while (g_shell->running)
	{
		printprompt();
		if ((c = ft_readraw(ft_strclr(line), 8192)))
		{
			if (c != 3 && (c != 4 || (c == 4 && ft_strcpy(ft_bzero(line,
									ft_strlen(line)), "exit"))))
				ft_readline(line);
			if (c != 3 && c != 4)
				addhistory(line);
		}
	}
	ft_makeraw(0);
	return (shell_end());
}
