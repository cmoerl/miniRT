/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 08:36:52 by marianfurni       #+#    #+#             */
/*   Updated: 2024/08/27 10:41:22 by mafurnic         ###   ########.fr       */
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
	if (scene != NULL)
	{
		free_scene(scene);
	}
	free_get_next_line_backup();
	exit(1);
}
