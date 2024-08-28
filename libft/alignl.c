/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alignl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:28:43 by mafurnic          #+#    #+#             */
/*   Updated: 2024/08/28 11:35:22 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


size_t	ft_strlengnl(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchrgnl(char *s, int c)
{
	int		i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return (&s[ft_strlengnl(s)]);
	while (s[i])
	{
		if (s[i] == (char) c)
			return (&s[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoingnl(char *s1, char *s2)
{
	char	*ns;
	int		i;
	int		j;

	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		if (s1 == NULL)
			return (NULL);
		s1[0] = '\0';
	}
	if (!s2)
		return (free(s1), NULL);
	ns = (char *)malloc(ft_strlengnl(s1) + ft_strlengnl(s2) + 1);
	if (!ns)
		return (free(s1), NULL);
	i = -1;
	j = 0;
	while (s1[++i])
		ns[i] = s1[i];
	while (s2[j])
		ns[i++] = s2[j++];
	ns[ft_strlengnl(s1) + ft_strlengnl(s2)] = '\0';
	return (free(s1), ns);
}

char	*read_line(int fd, char *ncall)
{
	int		b_read;
	char	*buf;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
	{
		free(ncall);
		return (NULL);
	}
	b_read = 1;
	while (!ft_strchrgnl(ncall, '\n') && b_read != 0)
	{
		b_read = read(fd, buf, BUFFER_SIZE);
		if (b_read == -1)
		{
			free(ncall);
			return (free(buf), NULL);
		}
		buf[b_read] = '\0';
		ncall = ft_strjoingnl(ncall, buf);
		if (ncall == NULL)
			return (free(buf), NULL);
	}
	return (free(buf), ncall);
}

char	*ft_get_line(char *ncall)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	if (!ncall[i])
		return (NULL);
	while (ncall[i] != '\0' && ncall[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	while (j < i)
	{
		line[j] = ncall[j];
		j++;
	}
	if (ncall[i] == '\n')
	{
		line[i] = ncall[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*last_read(char *ncall)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	while (ncall[i] && ncall[i] != '\n')
		i++;
	if (!ncall[i])
	{
		free(ncall);
		return (NULL);
	}
	temp = malloc(sizeof(char) * (ft_strlengnl(ncall) - i + 1));
	if (!temp)
		return (free(ncall), NULL);
	i++;
	while (ncall[i])
		temp[j++] = ncall[i++];
	temp[j] = '\0';
	free(ncall);
	return (temp);
}

char	*ali_get_next_line(int fd, int flag)
{
	static char	*ncall;
	char		*line;

	if (flag == 1)
		return (free(ncall), NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	ncall = read_line(fd, ncall);
	if (!ncall)
		return (NULL);
	line = ft_get_line(ncall);
	if (!line)
		return (free(ncall), NULL);
	ncall = last_read(ncall);
	return (line);
}

