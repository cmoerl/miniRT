/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:30:14 by csturm            #+#    #+#             */
/*   Updated: 2024/09/05 11:06:01 by csturm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

// setting the length of a vector to 1
// lenght = magnitude (length) of the vector
t_vector	normalise_vector(t_vector v)
{
	t_vector	normalised;
	float		length;

	length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	normalised.x = v.x / length;
	normalised.y = v.y / length;
	normalised.z = v.z / length;
	return (normalised);
}

// calculating the intersection point of a ray and an object
t_vector	get_intersection_point(t_ray ray, float t)
{
	t_vector	ip;

	ip.x = ray.origin.x + t * ray.direction.x;
	ip.y = ray.origin.y + t * ray.direction.y;
	ip.z = ray.origin.z + t * ray.direction.z;
	return (ip);
}

// calculating the normal of an object at a given point
t_vector	get_normal(t_vector v, t_hit hit)
{
	t_vector	normal;

	normal = (t_vector){0, 0, 0};
	if (hit.type == SPHERE)
	{
		normal.x = v.x - ((t_sphere *)hit.object)->center.x;
		normal.y = v.y - ((t_sphere *)hit.object)->center.y;
		normal.z = v.z - ((t_sphere *)hit.object)->center.z;
	}
	else if (hit.type == PLANE)
		normal = ((t_plane *)hit.object)->axis;
	else if (hit.type == CYLINDER)
	{
		normal.x = v.x - ((t_cylinder *)hit.object)->center.x;
		normal.y = v.y - ((t_cylinder *)hit.object)->center.y;
		normal.z = v.z - ((t_cylinder *)hit.object)->center.z;
	}
	normal = normalise_vector(normal);
	return (normal);
}
