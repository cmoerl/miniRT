/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:30:14 by csturm            #+#    #+#             */
/*   Updated: 2024/07/31 10:50:30 by csturm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

// changing the direction of a vector
t_vector    rotate_vector(t_vector v, t_vector orientation)
{
    t_vector rotated;
    t_vector axis;
    float c;
    float s;
    float angle;

    axis = cross_product(orientation, (t_vector){0, 0, 1});
    angle = acos(dot_product(orientation, (t_vector){0, 0, 1}));
    c = cos(angle);
    s = sin(angle);
    rotated.x = (c + (1 - c) * axis.x * axis.x) * v.x + ((1 - c) * axis.x * axis.y - axis.z * s) * v.y + ((1 - c) * axis.x * axis.z + axis.y * s) * v.z;
    rotated.y = ((1 - c) * axis.x * axis.y + axis.z * s) * v.x + (c + (1 - c) * axis.y * axis.y) * v.y + ((1 - c) * axis.y * axis.z - axis.x * s) * v.z;
    rotated.z = ((1 - c) * axis.x * axis.z - axis.y * s) * v.x + ((1 - c) * axis.y * axis.z + axis.x * s) * v.y + (c + (1 - c) * axis.z * axis.z) * v.z;
    return (rotated);
}

// setting the length of a vector to 1
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

// calculating the intersection point of a ray and an object
t_vector    get_intersection_point(t_ray ray, float t)
{
    t_vector ip;

    ip.x = ray.origin.x + t * ray.direction.x;
    ip.y = ray.origin.y + t * ray.direction.y;
    ip.z = ray.origin.z + t * ray.direction.z;
    return (ip);
}

// calculating the normal of an object at a given point
t_vector    get_normal(t_vector v, t_hit hit)
{
    t_vector normal;

    normal = (t_vector){0, 0, 0};    
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
