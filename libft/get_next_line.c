/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:41:24 by marianfurni       #+#    #+#             */
/*   Updated: 2024/08/28 08:23:17 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

static char	*read_line(int fd, char *buf, char *backup)
{
	int		read_line;
	char	*temp;

	read_line = 1;
	while (read_line != '\0')
	{
		read_line = read(fd, buf, BUFFER_SIZE);
		if (read_line == -1)
			return (0);
		else if (read_line == 0)
			break ;
		buf[read_line] = '\0';
		if (!backup)
			backup = ft_strdup("");
		temp = backup;
		backup = ft_strjoin(temp, buf);
		free(temp);
		temp = NULL;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (backup);
}

static char	*extract_line(char *content)
{
	size_t	count;
	char	*backup;

	if (!content || *content == '\0')
		return (NULL);
	count = 0;
	while (content[count] != '\n' && content[count] != '\0')
		count++;
	if (content[count] == '\0')
		return (NULL);
	backup = ft_substr(content, count + 1, ft_strlen(content) - count - 1);
	if (!backup)
		return (NULL);
	if (*backup == '\0')
	{
		free(backup);
		backup = NULL;
	}
	content[count + 1] = '\0';
	return (backup);
}

char	*get_next_line(int fd, int flag)
{
	char		*line;
	char		*buf;
	static char	*backup;

	if (flag == 1)
	{
		free(backup);
		backup = NULL;
		return (NULL);
	}
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	line = read_line(fd, buf, backup);
	if (!line)
	{
		free(buf);
		return (NULL);
	}
	free(buf);
	backup = extract_line(line);
	return (line);
}
