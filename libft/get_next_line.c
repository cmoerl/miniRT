/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:41:24 by marianfurni       #+#    #+#             */
/*   Updated: 2024/08/26 11:11:35 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

static char *backup = NULL;

void free_get_next_line_backup(void)
{
    if (backup)
    {
        free(backup);
        backup = NULL;
    }
}

static char *extract_line(char *str)
{
    char *line;
    int i;

    i = 0;
    while (str[i] && str[i] != '\n')
        i++;
    line = ft_substr(str, 0, i);
    return (line);
}

static char *read_line(int fd, char *buf, char *backup)
{
    int read_line;
    char *temp;

    read_line = 1;
    while (read_line != '\0')
    {
        read_line = read(fd, buf, BUFFER_SIZE);
        if (read_line == -1)
        {
            free_get_next_line_backup();
            return (NULL);
        }
        else if (read_line == 0)
            break;
        buf[read_line] = '\0';
        if (!backup)
            backup = ft_strdup("");
        temp = backup;
        backup = ft_strjoin(temp, buf);
        free(temp);
        temp = NULL;
    }
    return (backup);
}

char *get_next_line(int fd)
{
    char *buf;
    char *line;
    char *temp;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
    if (!buf)
        return (NULL);
    backup = read_line(fd, buf, backup);
    free(buf);
    if (!backup)
        return (NULL);
    line = extract_line(backup);
    temp = backup;
    backup = ft_strdup(backup + ft_strlen(line) + (backup[ft_strlen(line)] == '\n'));
    free(temp);
    return (line);
}