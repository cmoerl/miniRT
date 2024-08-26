/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:28:50 by csturm            #+#    #+#             */
/*   Updated: 2024/08/26 11:30:02 by csturm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

t_vector	vector_add(t_vector a, t_vector b)
{
	return ((t_vector){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_vector	vector_scale(t_vector a, float b)
{
	return ((t_vector){a.x * b, a.y * b, a.z * b});
}

t_vector	ray_at(t_ray ray, float t)
{
	return (vector_add(ray.origin, vector_scale(ray.direction, t)));
}

float	vector_length(t_vector a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

t_vector	get_center(t_cylinder *cylinder, float scale)
{
	return (vector_add(cylinder->center, vector_scale(cylinder->axis, scale)));
}
