/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:23:36 by csturm            #+#    #+#             */
/*   Updated: 2024/07/02 11:05:38 by csturm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

float   dot_product(t_vector a, t_vector b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

float   intersect_sphere(t_sphere *sphere, t_ray ray)
{
    t_vector oc;
    float a;
    float b;
    float c;
    float discriminant;
    float t;

    // oc is the vector from the ray origin to the sphere center
    // a, b, c are the coefficients of the quadratic equation
    // discriminant is the value under the square root
    // t is the distance from the ray origin to the intersection point
    oc = (t_vector){ray.origin.x - sphere->center.x, ray.origin.y - sphere->center.y, ray.origin.z - sphere->center.z};
    a = dot_product(ray.direction, ray.direction);
    b = 2 * dot_product(oc, ray.direction);
    c = dot_product(oc, oc) - sphere->radius * sphere->radius;
    discriminant = b * b - 4 * a * c;
    // if the discriminant is negative, there are no real roots
    if (discriminant < 0)
        return (-1);
    // calculate the distance to the intersection point (smaller root, closer to the camera)
    t = (-b - sqrt(discriminant)) / (2 * a);
    if (t > 0)
        return (t);
    // calculate the distance to the intersection point (larger root, further from the camera)
    t = (-b + sqrt(discriminant)) / (2 * a);
    if (t > 0)
        return (t);
    // if t is negative, the intersection point is behind the ray origin
    return (-1);
}

float   intersect_plane(t_plane *plane, t_ray ray)
{
    float t;
    float denominator;

    // calculate the denominator of the equation
    denominator = dot_product(plane->axis, ray.direction);
    // if the denominator is 0, the ray is parallel to the plane
    if (denominator == 0)
        return (-1);
    // calculate the distance to the intersection point
    t = dot_product((t_vector){plane->point.x - ray.origin.x, plane->point.y - ray.origin.y, plane->point.z - ray.origin.z}, plane->axis) / denominator;
    if (t > 0)
        return (t);
    return (-1);
}

float   intersect_cylinder(t_cylinder *cylinder, t_ray ray)
{
    t_vector oc;
    float a;
    float b;
    float c;
    float discriminant;
    float t;

    oc = (t_vector){ray.origin.x - cylinder->center.x, ray.origin.y - cylinder->center.y, ray.origin.z - cylinder->center.z};
    a = dot_product(ray.direction, ray.direction);
    b = 2 * dot_product(oc, ray.direction);
    c = oc.x * oc.x + oc.y * oc.y - cylinder->radius * cylinder->radius;
    discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return (-1);
    t = (-b - sqrt(discriminant)) / (2 * a);
    if (t > 0)
        return (t);
    t = (-b + sqrt(discriminant)) / (2 * a);
    if (t > 0)
        return (t);
    return (-1);
}
