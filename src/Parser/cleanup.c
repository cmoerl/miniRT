/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 20:10:29 by marianfurni       #+#    #+#             */
/*   Updated: 2024/08/25 12:43:41 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	free_planes(t_plane *plane)
{
	t_plane	*tmp;

	while (plane)
	{
		tmp = plane;
		plane = plane->next;
		free(tmp);
	}
}

void	free_spheres(t_sphere *sphere)
{
	t_sphere	*tmp;

	while (sphere)
	{
		tmp = sphere;
		sphere = sphere->next;
		free(tmp);
	}
}

void	free_cylinders(t_cylinder *cylinder)
{
	t_cylinder	*tmp;

	while (cylinder)
	{
		tmp = cylinder;
		cylinder = cylinder->next;
		free(tmp);
	}
}

void	free_scene(t_scene *scene)
{
	if (scene->objects)
	{
		free_planes(scene->objects->planes);
		free_spheres(scene->objects->spheres);
		free_cylinders(scene->objects->cylinders);
		free(scene->objects);
	}
}
