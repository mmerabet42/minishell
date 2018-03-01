/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 18:40:09 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/01 20:54:39 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_io.h"
#include "ft_str.h"
#include <unistd.h>

int main(int argc, char **argv)
{
	ft_printf("ll: '%s'\n", argv[1]);
	return (0);
	char	currpwd[2048];
	char	*line;

	(void)argc;
	(void)argv;
	line = NULL;
	getcwd(currpwd, 2048);
	while (ft_strcmp(line, "exit"))
	{
		ft_printf("%{lgreen}%s%{0} > ", currpwd);
		get_next_line(1, &line);
/*		while ((line = ft_formatcmd(line, &cmdf)))
		{
			ft_printf("
		}*/
	}
	return (0);
}
