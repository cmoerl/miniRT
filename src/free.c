/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:25:58 by mafurnic          #+#    #+#             */
/*   Updated: 2024/09/04 14:00:52 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"
#include <mlx.h>

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
	if (scene->img)
	{
		if (scene->img->img_ptr)
			mlx_destroy_image(scene->mlx_ptr, scene->img->img_ptr);
		free(scene->img);
	}
	if (scene->win_ptr)
		mlx_destroy_window(scene->mlx_ptr, scene->win_ptr);
	mlx_destroy_display(scene->mlx_ptr);
	if (scene->objects)
	{
		free_spheres(scene->objects->spheres);
		free_planes(scene->objects->planes);
		free_cylinders(scene->objects->cylinders);
		free(scene->objects);
	}
	if (scene->hooks)
		free(scene->hooks);
	if (scene->mlx_ptr)
		free(scene->mlx_ptr);
}
