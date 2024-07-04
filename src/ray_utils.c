/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:30:14 by csturm            #+#    #+#             */
/*   Updated: 2024/07/04 12:33:54 by csturm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

t_vector    rotate_vector(t_vector v, t_vector normal)
{
    t_vector rotated;

    rotated.x = v.x * (1 - normal.x * normal.x) + v.y * (-normal.z) + v.z * normal.y;
    rotated.y = v.x * normal.z + v.y * (1 - normal.y * normal.y) + v.z * (-normal.x);
    rotated.z = v.x * (-normal.y) + v.y * normal.x + v.z * (1 - normal.z * normal.z);
    return (rotated);
}
t_vector    normalise_vector(t_vector v)
{
    float length;
    t_vector normalised;

    length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z); // magnitude (length) of the vector
    normalised.x = v.x / length;
    normalised.y = v.y / length;
    normalised.z = v.z / length;
    return (normalised);
}

t_vector    get_intersection_point(t_ray ray, float t)
{
    t_vector ip;

    ip.x = ray.origin.x + t * ray.direction.x;
    ip.y = ray.origin.y + t * ray.direction.y;
    ip.z = ray.origin.z + t * ray.direction.z;
    return (ip);
}

t_vector    get_normal(t_vector v, t_hit hit)
{
    t_vector normal;
    
    if (hit.type == SPHERE)
    {
        normal.x = v.x - ((t_sphere*)hit.object)->center.x;
        normal.y = v.y - ((t_sphere*)hit.object)->center.y;
        normal.z = v.z - ((t_sphere*)hit.object)->center.z;
    }
    else if (hit.type == PLANE)
    {
        normal = ((t_plane*)hit.object)->axis;
    }
    else if (hit.type == CYLINDER)
    {
        normal.x = v.x - ((t_cylinder*)hit.object)->center.x;
        normal.y = v.y - ((t_cylinder*)hit.object)->center.y;
        normal.z = v.z - ((t_cylinder*)hit.object)->center.z;
    }
    normal = normalise_vector(normal);
    return (normal);
}
