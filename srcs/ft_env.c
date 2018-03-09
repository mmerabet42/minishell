/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 12:59:20 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/09 13:25:08 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"

char	*ft_getenv(char *name, t_shell *shell)
{
	char	*it;

	it = shell->envp;
	while (*it)
	{
		if (ft_strmatch(name, 
		++it;
	}
}
