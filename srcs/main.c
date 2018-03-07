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
#include "minishell.h"
#include <unistd.h>

int main(int argc, char **argv)
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
*/	char	currpwd[2048];
	char	*line;
	t_cmdf	cmdf;
	int	i = 0;

	(void)argc;
	(void)argv;
	line = NULL;
	getcwd(currpwd, 2048);
	while (ft_strcmp(line, "exit"))
	{
		ft_printf("%{lgreen}%s%{0} > ", currpwd);
		get_next_line(1, &line);
		ft_getcmdf(line, &cmdf);
		ft_printf("%d\n", cmdf.argc);
		i = 0;
		while (i < cmdf.argc)
			ft_printf("\t'%s'\n", cmdf.argv[i++]);
	}
	return (0);
}
