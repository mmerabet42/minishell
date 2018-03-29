/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpaths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 19:09:27 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/29 13:45:13 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "ft_printf.h"
#include <unistd.h>

t_shell	*g_shell;

char	**ft_getpaths(char **envp)
{
	char	*paths;

	if ((paths = ft_getenv("PATH", envp)))
		return (ft_strsplit(paths, ':'));
	return (NULL);
}

t_shret	ft_access(char *filename, int tests)
{
	if (!access(filename, F_OK))
	{
		if (!access(filename, tests))
			return (SH_OK);
		return (SH_ADENIED);
	}
	return (SH_NEXIST);
}

t_shret	ft_getfullpath(char *fname, char *fullpath, size_t size)
{
	t_shret	shret;
	char	**it;

	if (fname[0] == '.' || fname[0] == '/')
		return (ft_access(ft_strcat(ft_bzero(fullpath, size), fname), X_OK));
	else if (isbuiltin(fname))
		return (ft_strcat(fullpath, fname) ? SH_OK : SH_OK);
	shret = SH_NFOUND;
	if (!(it = g_shell->paths))
		return (shret);
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
	else if (shret == SH_NOTDIR)
		return ("not a directory");
	return ("none");
}
