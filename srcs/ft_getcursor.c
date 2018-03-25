/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getcursor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 16:36:17 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/25 16:36:26 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_io.h"

void	ft_getcursor(int *x, int *y)
{
	int	c;
	int	nx;
	int	ny;

	if (!x && !y)
		return ;
	ft_putstr("\033[6n");
	nx = 0;
	ny = 0;
	ft_makeraw(1);
	if (ft_getch() && ft_getch())
	{
		while ((c = ft_getch()) != ';')
			ny = ny * 10 + (c - 48);
		while ((c = ft_getch()) != 'R')
			nx = nx * 10 + (c - 48);
	}
	ft_makeraw(0);
	if (x)
		*x = nx;
	if (y)
		*y = ny;
}
