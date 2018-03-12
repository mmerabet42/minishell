/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 18:40:09 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/12 13:51:45 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_io.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "shell.h"
#include "ft_types.h"
#include <unistd.h>
#include <locale.h>

static void ft_readline(char *line, t_shell *shell)
{
	char	fullpath[1024];
	t_args	args;
	t_shret	shret;
	
	ft_bzero(&args, sizeof(t_args));
	while ((line = ft_getargs(line, &args, shell)))
	{
		if (args.argc >= 1
				&& ft_isbuiltin(args.argv[0], &args, shell) == SH_NFOUND)
		{
			shret = ft_getfullpath(args.argv[0], shell, fullpath, 1024);
			if (shret != SH_OK)
				ft_printf("%s: %s: %s\n", shell->name, ft_strshret(shret),
					args.argv[0]);
			else
				ft_exec(fullpath, args.argv, shell->envp, &shell->pid);
		}
		ft_delargs(&args);
	}
}

#include <termios.h>

struct termios	origt;

void	setraw(void)
{
	struct termios	newt;

	tcgetattr(0, &origt);
	ft_memcpy(&newt, &origt, sizeof(struct termios));
	cfmakeraw(&newt);
	tcsetattr(0, TCSANOW, &newt);
}

void	unsetraw(void)
{
	tcsetattr(0, TCSANOW, &origt);
}

int getch(void)
{
	int				r;
	unsigned char	c;
	if ((r = read(0, &c, sizeof(unsigned char))) < 0)
		return (r);
	return (c);
}

int main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	line[2048];
	char	*promptf;
	int		c;

	ft_initshell("minishell", &shell, envp);
	if (argc > 1)
	{
		promptf = ft_strrepstr_clr(ft_strdup(argv[1]), "@user", "%2$s");
		promptf = ft_strrepstr_clr(promptf, "@pwd", "%3$s");
		promptf = ft_strrepstr_clr(promptf, "@sign-jap", "%1$S");
		promptf = ft_strrepstr_clr(promptf, "@sign-3dot", "%4$S");
	}
	else
		promptf = ft_strdup("%S %{lred}%s %{lcyan}%s%{0} %{bold}%S%{0} ");
	setlocale(LC_ALL, "");
	setraw();
	while (shell.running)
	{
		ft_putchar('\r');
		ft_printf(promptf, L"㋜", shell.user, shell.pwd, L"∴");
		ft_bzero(line, 2048);
		while ((c = getch()) >= 0)
		{
			if (c == 3 || c == 13)
			{
				ft_putstr("\r\n");
				break ;
			}
			else if (c == '\033')
			{
				
			}
			else if (ft_isprint(c))
			{
				ft_strcatc(line, (char)c);
				ft_putchar((char)c);
			}
		/*	if (c == '\033')
			{
				getch();
				ft_printf("%c ", (c = getch()));
				if (c == 'A')
					ft_printf("UP\n");
				else if (c == 'B')
					ft_printf("DOWN\n");
				else if (c == 'C')
					ft_printf("RIGHT\n");
				else if (c == 'D')
					ft_printf("LEFT\n");
			}
			else
				ft_printf("Normal\n");*/
		}
	//	if (get_next_line(1, &line) == -1)
	//		exit(EXIT_FAILURE);
		ft_printf("%{0}");
		ft_readline(line, &shell);
	//	free(line);
	}
	unsetraw();
	ft_delshell(&shell);
	free(promptf);
	return (0);
}
