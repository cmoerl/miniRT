/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:55:06 by csturm            #+#    #+#             */
/*   Updated: 2024/09/05 12:11:16 by csturm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

// if the intersection point is closer than the previous intersection point,
// update the intersection point
void	check_intersect(t_hit *hit, float t, t_intersect_info info)
{
	if (t > 0 && t < hit->t)
	{
		hit->t = t;
		hit->object = info.object;
		hit->type = info.type;
		hit->index = info.index;
	}
}

// calculating the intersection point of the ray and a sphere
void	find_closest_sphere(t_hit *hit, t_sphere *sphere, t_ray ray, int i)
{
	t_intersect_info	info;

	if (sphere == NULL)
		return ;
	info.object = sphere;
	info.type = SPHERE;
	info.index = i;
	check_intersect(hit, intersect_sphere(sphere, ray), info);
	find_closest_sphere(hit, sphere->next, ray, i + 1);
}

// calculating the intersection point of the ray and a plane
void	find_closest_plane(t_hit *hit, t_plane *plane, t_ray ray, int i)
{
	t_intersect_info	info;

	if (plane == NULL)
		return ;
	info.object = plane;
	info.type = PLANE;
	info.index = i;
	check_intersect(hit, intersect_plane(plane, ray), info);
	find_closest_plane(hit, plane->next, ray, i + 1);
}

// calculating the intersection point of the ray and a cylinder
void	find_closest_cylinder(t_hit *hit, t_cylinder *cylinder,
			t_ray ray, int i)
{
	t_intersect_info	info;

	if (cylinder == NULL)
		return ;
	info.object = cylinder;
	info.type = CYLINDER;
	info.index = i;
	check_intersect(hit, intersect_cylinder(cylinder, ray), info);
	find_closest_cylinder(hit, cylinder->next, ray, i + 1);
}

// check whether the ray intersects with an object
// iterating over each object
// return the closest object
// if no object is hit, return NULL / INFINITY / NONE
t_hit	find_closest_object(t_scene scene, t_ray ray)
{
	t_hit	hit;

	hit.t = INFINITY;
	hit.object = NULL;
	hit.type = NONE;
	hit.index = -1;
	find_closest_sphere(&hit, scene.objects->spheres, ray, 0);
	find_closest_plane(&hit, scene.objects->planes, ray, 0);
	find_closest_cylinder(&hit, scene.objects->cylinders, ray, 0);
	return (hit);
}
