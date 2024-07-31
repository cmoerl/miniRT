/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:23:36 by csturm            #+#    #+#             */
/*   Updated: 2024/07/31 11:27:34 by csturm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"
#include <math.h>

// calculating the dot product of two vectors
float   dot_product(t_vector a, t_vector b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

// calculating the cross product of two vectors
t_vector   cross_product(t_vector a, t_vector b)
{
    return ((t_vector){a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x});
}

// checking if a ray intersects with a sphere
// oc is the vector from the center of the sphere to the origin of the ray
// discriminant measures the intersection of the ray and the sphere
// if the discriminant is less than 0, the ray does not intersect with the sphere
// t is the distance to the intersection point
// if t is greater than 0, the ray intersects with the sphere
// if t is less than 0, the ray intersects with the sphere behind the origin
// if t is equal to 0, the ray intersects with the sphere at the origin
float   intersect_sphere(t_sphere *sphere, t_ray ray)
{
    t_vector oc;
    float a;
    float b;
    float c;
    float discriminant;
    float t;

    oc = (t_vector){ray.origin.x - sphere->center.x, ray.origin.y - sphere->center.y, ray.origin.z - sphere->center.z};
    a = dot_product(ray.direction, ray.direction);
    b = 2 * dot_product(oc, ray.direction);
    c = dot_product(oc, oc) - sphere->radius * sphere->radius;
    discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return (INFINITY);
    t = (-b - sqrt(discriminant)) / (2 * a);
    if (t > 0)
        return (t);
    t = (-b + sqrt(discriminant)) / (2 * a);
    if (t > 0)
        return (t);
    return (INFINITY);
}

// checking if a ray intersects with a plane
// denominator measures the angle between the plane and the ray
// if the denominator is 0, the ray is parallel to the plane
// t is the distance to the intersection point
// if t is greater than 0, the ray intersects with the plane
// if t is less than 0, the ray intersects with the plane behind the origin
// if t is equal to 0, the ray intersects with the plane at the origin
float   intersect_plane(t_plane *plane, t_ray ray)
{
    float t;
    float denominator;

    denominator = dot_product(plane->axis, ray.direction);
    if (denominator == 0)
        return (INFINITY);
    t = dot_product((t_vector){plane->point.x - ray.origin.x, plane->point.y - ray.origin.y, plane->point.z - ray.origin.z}, plane->axis) / denominator;
    if (t > 0)
        return (t);
    return (INFINITY);
}

// checking if a ray intersects with a cylinder
// oc is the vector from the center of the cylinder to the origin of the ray
// discriminant measures the intersection of the ray and the cylinder
// if the discriminant is less than 0, the ray does not intersect with the cylinder
// t1 and t2 are the distances to the intersection points
// if t1 is greater than 0, the ray intersects with the cylinder
// if t2 is greater than 0, the ray intersects with the cylinder
// if t1 is less than 0, the ray intersects with the cylinder behind the origin
// if t2 is less than 0, the ray intersects with the cylinder behind the origin
// if t1 is equal to 0, the ray intersects with the cylinder at the origin
// if t2 is equal to 0, the ray intersects with the cylinder at the origin
// m1 and m2 are the distances to the intersection points along the axis of the cylinder
// if m1 is greater than 0 and less than the height of the cylinder, the ray intersects with the cylinder
// if m2 is greater than 0 and less than the height of the cylinder, the ray intersects with the cylinder
float   intersect_cylinder(t_cylinder *cylinder, t_ray ray)
{
    t_vector oc;
    t_vector dot;
    float a;
    float b;
    float c;
    float discriminant;
    float t1;
    float t2;
    t_vector ip;
    float m1;
    float m2;

    oc = (t_vector){ray.origin.x - cylinder->center.x, ray.origin.y - cylinder->center.y, ray.origin.z - cylinder->center.z};
    dot = (t_vector){dot_product(ray.direction, cylinder->axis), dot_product(oc, cylinder->axis), dot_product(cylinder->axis, cylinder->axis)};
    a = dot_product(ray.direction, ray.direction) - dot.x * dot.x / dot.z;
    b = 2 * (dot_product(oc, ray.direction) - dot.x * dot.y / dot.z);
    c = dot_product(oc, oc) - dot.y * dot.y / dot.z - cylinder->radius * cylinder->radius;
    discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return (INFINITY);
    t1 = (-b - sqrt(discriminant)) / (2 * a);
    if (t1 > 0)
    {
        ip = (t_vector){ray.origin.x + t1 * ray.direction.x, ray.origin.y + t1 * ray.direction.y, ray.origin.z + t1 * ray.direction.z};
        m1 = dot_product(ray.direction, cylinder->axis) * t1 + dot_product(oc, cylinder->axis);
        if (m1 >= 0 && m1 < cylinder->height)
            return (t1);
    }
    t2 = (-b + sqrt(discriminant)) / (2 * a);
    if (t2 > 0)
    {
        ip = (t_vector){ray.origin.x + t2 * ray.direction.x, ray.origin.y + t2 * ray.direction.y, ray.origin.z + t2 * ray.direction.z};
        m2 = dot_product(ray.direction, cylinder->axis) * t2 + dot_product(oc, cylinder->axis);
        if (m2 >= 0 && m2 < cylinder->height)
            return (t2);
    }
    return (INFINITY);
}
