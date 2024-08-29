/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 08:36:52 by marianfurni       #+#    #+#             */
/*   Updated: 2024/08/29 11:36:34 by csturm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	error(char *message, t_scene *scene, char *line)
{
	if (scene->fd != 0)
	{
		if (close(scene->fd) == -1)
		{
			perror("Error closing file descriptor");
		}
		scene->fd = 0;
	}
	if (line != NULL)
		free(line);
	if (message != NULL)
	{
		write(2, "Error: ", 7);
		write(2, message, ft_strlen(message));
		write(2, "\n", 1);
	}
	if (scene != NULL)
		free_scene(scene);
	get_next_line(0, 1);
	exit(1);
}
