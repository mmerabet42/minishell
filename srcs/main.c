/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 18:40:09 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/08 21:58:32 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_io.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "shell.h"
#include <unistd.h>
#include <sys/wait.h>
#include <locale.h>

static void ft_readline(char *line, t_shell *shell)
{
	char	fullpath[1024];
	t_args	args;
	t_shret	shret;
	
	ft_bzero(&args, sizeof(t_args));
	while ((line = ft_getargs(line, &args, shell)))
	{
		if (args.argc > 1 && !ft_strcmp(args.argv[0], "exit"))
			shell->ison = 0;
		else
		{
			if (ft_isbuiltin(args.argv[0], &args, shell) == SH_NFOUND)
			{
				shret = ft_getfullpath(args.argv[0], shell, fullpath, 1024);
				if (shret != SH_OK)
					ft_printf("%s: %s: %s\n", shell->name, ft_strshret(shret),
						args.argv[0]);
				else
					ft_exec(fullpath, args.argv, shell->envp);
			}
		}
		ft_delargs(&args);
	}
}

int main(int argc, char **argv, char **envp)
{
	char	*line;
	t_shell	shell;
	char	*promptf;

	ft_initshell("minishell", &shell, envp);
	if (argc > 1)
	{
		promptf = ft_strrepstr_clr(ft_strdup(argv[1]), "@user", "%2$s");
		promptf = ft_strrepstr_clr(promptf, "@pwd", "%3$s");
		promptf = ft_strrepstr_clr(promptf, "@sign-jap", "%1$S");
		promptf = ft_strrepstr_clr(promptf, "@sign-3dot", "%4$S");
	}
	else
		promptf = "%S %{lred}%s %{cyan}%s%{0} %{bold}%S%{0} ";
	setlocale(LC_ALL, "");
	while (shell.ison)
	{
		ft_printf(promptf, L"㋜", shell.user, shell.pwd, L"∴");
		if (get_next_line(1, &line) == -1)
			exit(EXIT_FAILURE);
		ft_readline(line, &shell);
		free(line);
	}
	return (0);
}
