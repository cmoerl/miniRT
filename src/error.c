/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 08:36:52 by marianfurni       #+#    #+#             */
/*   Updated: 2024/08/28 09:31:23 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	error(char *message, t_scene *scene)
{
	if (message != NULL)
	{
		write(1, "Error: ", 7);
		write(1, message, ft_strlen(message));
		write(1, "\n", 1);
	}
	printf("before free_scene\n");
	if (scene != NULL)
	{
		printf("scene is not NULL\n");
		free_scene(scene);
	}
	get_next_line(0, 1);
	exit(1);
}
