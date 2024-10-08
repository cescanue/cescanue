/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 20:32:28 by cescanue          #+#    #+#             */
/*   Updated: 2023/06/29 09:35:08 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	exec(char *cmd, char **argv, char **envp)
{
	pid_t	pid;
	char	**tenvp;
	char	**path;
	char	*tmp;
	char	*tmp1;
	char	*path_cmd;
	int		fd, fdinfile, fdout;
	//int		p[2];
	char	txt[100] = "/usr/bin/wc -l";
	char	**argvwc;
	
	(void) fdinfile;
	(void) argv;
	tenvp = envp;
	while (ft_strncmp(*tenvp, "PATH=", 5) != 0)
		tenvp++;
	tmp = ft_calloc(ft_strlen(*tenvp), sizeof(char));
	tmp1 = *tenvp;
	ft_strlcpy(tmp, &tmp1[5], ft_strlen(*tenvp));
	path = ft_split(tmp, ':');
	while (*path)
	{
		path_cmd = ft_calloc(ft_strlen(*path) + ft_strlen(cmd) + 10, sizeof(char));
		ft_strlcpy(path_cmd, *path, ft_strlen(*path) + 5);
		ft_strlcat(path_cmd, "/", ft_strlen(path_cmd) + 5);
		ft_strlcat(path_cmd, cmd, ft_strlen(path_cmd) + ft_strlen(cmd) + 5);
		fd = open(path_cmd, O_RDONLY);
		if (fd >= 0)
		{
			close(fd);
			break;
		}
		free(path_cmd);
		close(fd);
		path++;
	}
	if (!*path)
		return 0;
	pid = fork();
	printf("pid:%d\n", pid);
	//pipe (p);
	if (pid == 0)
	{
		fdinfile = open("./infile", O_RDONLY);
		fdout = open("./outfile", O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
		dup2(fdinfile, 0);
		dup2(fdout, 1);
		argvwc = ft_split(txt, ' ');
		execve("/usr/bin/wc", argvwc, envp);
	}
	else
	{

	}
	return (pid);
}
