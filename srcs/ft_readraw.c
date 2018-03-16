/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readraw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 18:44:03 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/15 21:15:49 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_io.h"
#include "ft_mem.h"
#include "ft_str.h"
#include "ft_types.h"
#include <termios.h>

static struct termios	g_origt;

void		ft_makeraw(int setb)
{
	static int		isset;
	struct termios	newt;

	if (setb && !isset)
	{
		isset = 1;
		tcgetattr(0, &g_origt);
		ft_memcpy(&newt, &g_origt, sizeof(struct termios));
	/*	newt.c_iflag &= ~(IMAXBEL | IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR
				| IGNCR | ICRNL | IXON);
		newt.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
		newt.c_oflag &= ~OPOST;
		newt.c_cflag &= ~(CSIZE | PARENB);
		newt.c_cflag &= ECHOE;
		newt.c_cflag |= CS8;
		newt.c_cc[VMIN] = 1;
		newt.c_cc[VTIME] = 0;*/
		newt.c_lflag &= ~(ICANON | ECHO | ISIG);
		newt.c_iflag &= ~(ICRNL);
		newt.c_cc[VMIN] = 1;
		newt.c_cc[VTIME] = 0;
		tcsetattr(0, TCSANOW, &newt);
	}
	else if (isset)
		tcsetattr((isset = 0), TCSANOW, &g_origt);
}

static void moveline(char *line, size_t *cursor, int direction)
{
	size_t	i;
	
	if (!direction && !*cursor)
		return ;
	i = (direction ? ft_strlen(line) : --(*cursor));
	while (((direction == 0 && line[i])
		|| (direction && i >= *cursor && i > 0)) && i < 2048)
	{
		line[i] = line[i + (direction ? -1 : 1)];
		i += (direction ? -1 : 1);
	}
	if (direction)
		ft_printf("%s\033[%dD", &line[*cursor + 1],
				ft_strlen(line) - *cursor - 1);
	else
		ft_printf("\033[1D%s \033[%dD", &line[*cursor],
				ft_strlen(line) - *cursor + 1);
}

static void	movehistory(char c, char *line, size_t *cursor)
{
	char	*str;

	if (*cursor > 0)
		ft_printf("\033[%dD\033[K", *cursor);
	if (g_shell->ihis == -1)
		g_shell->cline = ft_strdup(line);
	ft_strclr(line);
	if (c == 'A' && g_shell->ihis < (int)ft_lstsize(g_shell->history) - 1)
		++g_shell->ihis;
	else if (c == 'B' && g_shell->ihis > -1)
		--g_shell->ihis;
	ft_putstr(ft_strcpy(line, (str = ft_gethistory(g_shell->ihis))));
	if (str == g_shell->cline)
	{
		free(g_shell->cline);
		g_shell->cline = NULL;
	}
	*cursor = ft_strlen(line);
}

static void	movecursor(char *line, size_t *cursor)
{
	int	c;

	ft_getch();
	if ((c = ft_getch()) == 'D' && *cursor != 0)
		ft_printf("\033[1D", --(*cursor));
	else if (c == 'C' && *cursor < ft_strlen(line))
		ft_printf("\033[1C", ++(*cursor));
	else if ((c == 'A' || c == 'B') && g_shell->history)
		movehistory(c, line, cursor);
}

int			ft_readraw(char *line, size_t size)
{
	int		c;
	size_t	cursor;

	cursor = 0;
	ft_makeraw(1);
	while ((c = ft_getch()) && cursor < size)
	{
		if (c == 3 || c == 4 || c == 13)
			break ;
		else if (c == 127)
			moveline(line, &cursor, 0);
		else if (c == '\033')
			movecursor(line, &cursor);
		else
		{
			ft_putchar((char)c);
			if (line[cursor] != '\0')
				moveline(line, &cursor, 1);
			line[cursor++] = (char)c;
		}
	}
	ft_makeraw(0);
	ft_putchar('\n');
	return (c);
}
