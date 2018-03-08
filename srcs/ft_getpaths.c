/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpaths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 19:09:27 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/08 19:09:30 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_mem.h"
#include <unistd.h>

char	**ft_getpaths(char **envp)
{
	while (*envp)
	{
		if (ft_strmatch(*envp, "PATH=*"))
			return (ft_strsplit(ft_strchr(*envp, '=') + 1, ':'));
		++envp;
	}
	return (NULL);
}

static t_shret	testaccess(char *filename)
{
	if (!access(filename, F_OK))
	{
		if (!access(filename, X_OK))
			return (SH_OK);
		return (SH_ADENIED);
	}
	return (SH_NFOUND);
}

t_shret	ft_getfullpath(char *fname, t_shell *shell, char *fullpath, size_t size)
{
	t_shret	shret;
	char	**it;
	
	if (fname[0] == '.' && fname[1] == '/' && ft_memset(fullpath, '\0', size))
	{
		ft_strcat(ft_strcatc(ft_strcat(fullpath, shell->pwd), '/'), fname);
		if ((shret = testaccess(fullpath)) == SH_NFOUND)
			return (SH_NEXIST);
		return (shret);
	}
	shret = SH_NFOUND;
	it = shell->paths;
	while (*it)
	{
		ft_bzero(fullpath, size);
		ft_strcat(ft_strcatc(ft_strcat(fullpath, *it), '/'), fname);
		if (!access(fullpath, F_OK))
		{
			if (!access(fullpath, X_OK))
				return (SH_OK);
			shret = SH_ADENIED;
		}
		++it;
	}
	return (shret);
}

char	*ft_strshret(t_shret shret)
{
	if (shret == SH_OK)
		return ("success");
	else if (shret == SH_ADENIED)
		return ("permission denied");
	else if (shret == SH_NFOUND)
		return ("command not found");
	else if (shret == SH_NEXIST)
		return ("no such file or directory");
	return ("none");
}
