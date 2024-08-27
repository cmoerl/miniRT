/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:25:58 by mafurnic          #+#    #+#             */
/*   Updated: 2024/08/27 16:51:43 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	free_spheres(t_sphere *spheres)
{
	t_sphere	*temp;

	while (spheres)
	{
		temp = spheres;
		spheres = spheres->next;
		free(temp);
	}
}

void	free_planes(t_plane *planes)
{
	t_plane	*temp;

	while (planes)
	{
		temp = planes;
		planes = planes->next;
		free(temp);
	}
}

void	free_cylinders(t_cylinder *cylinders)
{
	t_cylinder	*temp;

	while (cylinders)
	{
		temp = cylinders;
		cylinders = cylinders->next;
		free(temp);
	}
}

void	free_scene(t_scene *scene)
{
	if (scene->objects)
	{
		free_spheres(scene->objects->spheres);
		free_planes(scene->objects->planes);
		free_cylinders(scene->objects->cylinders);
		free(scene->objects);
	}
	get_next_line(0, 1);
}
