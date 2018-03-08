/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 18:40:09 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/07 20:50:47 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_io.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "shell.h"
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv, char **envp)
{
/*	char **ok = NULL;
	while (i < argc)
	{
		ok = ft_memjoin_clr(ok, sizeof(char *) * i, argv + i, sizeof(char *));
		++i;
	}

	i = 0;
	while (i < argc)
	{
		ft_printf("L: '%s'\n", ok[i++]);
	}

	return (0);
*/	char	fullpath[1024];
	char	*line, *pline;
	t_shell	shell;
	t_args	args;
	t_shret	shret;

	(void)argc;
	(void)argv;
	ft_initshell(&shell, envp);
	ft_bzero(&args, sizeof(t_args));
	while (shell.ison)
	{
		ft_printf("%{lgreen}%s%{0} > ", shell.pwd);
		get_next_line(1, &line);
		pline = line;
		while ((pline = ft_getargs(pline, &args)))
		{
			if (args.argc > 1 && !ft_strcmp(args.argv[0], "exit"))
				shell.ison = 0;
			else if (args.argc > 1)
			{
				shret = ft_getfullpath(args.argv[0], &shell, fullpath, 1024);
				if (shret != SH_OK)
					ft_printf("minishell: %s: %s\n", ft_strshret(shret), args.argv[0]);
				else
				{
					pid_t pid = fork();
					if (!pid)
						execve(fullpath, args.argv, envp);
					else
						wait(NULL);
				}
			}
			ft_delargs(&args);
		}
		free(line);
	}
	return (0);
}
