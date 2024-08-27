/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:41:24 by marianfurni       #+#    #+#             */
/*   Updated: 2024/08/27 10:25:10 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

static char	*g_backup = NULL;

void	free_get_next_line_backup(void)
{
	if (g_backup)
	{
		free(g_backup);
		g_backup = NULL;
	}
}

static char	*read_line(int fd, char *buf, char *g_backup)
{
	int		read_line;
	char	*temp;

	read_line = 1;
	while (read_line != '\0')
	{
		read_line = read(fd, buf, BUFFER_SIZE);
		if (read_line == -1)
		{
			free(g_backup);
			return (NULL);
		}
		else if (read_line == 0)
			break ;
		buf[read_line] = '\0';
		if (!g_backup)
			g_backup = ft_strdup("");
		temp = g_backup;
		g_backup = ft_strjoin(temp, buf);
		free(temp);
		temp = NULL;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (g_backup);
}

static char	*extract_line(char *content)
{
	size_t	count;
	char	*g_backup;

	if (!content || *content == '\0')
		return (NULL);
	count = 0;
	while (content[count] != '\n' && content[count] != '\0')
		count++;
	if (content[count] == '\0')
		return (NULL);
	g_backup = ft_substr(content, count + 1, ft_strlen(content) - count - 1);
	if (!g_backup)
		return (NULL);
	if (*g_backup == '\0')
	{
		free(g_backup);
		g_backup = NULL;
	}
	content[count + 1] = '\0';
	return (g_backup);
}

char	*get_next_line(int fd)
{
	char	*line;
	char	*buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	line = read_line(fd, buf, g_backup);
	if (!line)
	{
		free(buf);
		free_get_next_line_backup();
		return (NULL);
	}
	free(buf);
	g_backup = extract_line(line);
	return (line);
}
