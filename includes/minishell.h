/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 18:44:40 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/07 20:38:11 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

typedef struct	s_cmdf
{
	int			argc;
	char		**argv;
	char		*cmd;
}				t_cmdf;

char			*ft_getcmdf(char *cmd, t_cmdf *cmdf);
void			ft_cmdfdel(t_cmdf *cmdf);

#endif
