/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 18:40:09 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/15 22:01:52 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_io.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "shell.h"
#include "ft_types.h"
#include <unistd.h>
#include <locale.h>

t_shell *g_shell;

static void ft_readline(char *line)
{
	char	fullpath[1024];
	t_args	args;
	t_shret	shret;
	
	ft_bzero(&args, sizeof(t_args));
	while ((line = ft_getargs(line, &args)))
	{
		if (args.argc >= 1
				&& ft_isbuiltin(args.argv[0], &args) == SH_NFOUND)
		{
			shret = ft_getfullpath(args.argv[0], fullpath, 1024);
			if (shret != SH_OK)
				ft_printf("%s: %s: %s\n", g_shell->name, ft_strshret(shret),
					args.argv[0]);
			else
				ft_exec(fullpath, args.argv, g_shell->envp);
		}
		ft_delargs(&args);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	line[2048];
	int		c;
	int		x;

	(void)argc;
	(void)argv;
	shell_begin("minishell", envp);
	setlocale(LC_ALL, "");
	ft_bzero(line, 2048);
	while (g_shell->running)
	{
		ft_getcursor(&x, NULL);
		if (x > 1)
			ft_printf("%#{lgrey}%{bold/;0;0;0}%%%{0}\n");
		ft_printf("%S %{lred}%s %{lcyan}%s%{0} %{bold}%S%{0} ", L"㋜", g_shell->user, g_shell->pwd, L"∴");
		ft_strclr(line);
		if ((c = ft_readraw(line, 2048)) != 3 && c != 4 && line[0] != '\0')
		{
			ft_addhistory(line);
			ft_readline(line);
		}
		else if (c == 4)
			ft_readline("exit");
	}
	ft_makeraw(0);
	shell_end();
	return (0);
}
