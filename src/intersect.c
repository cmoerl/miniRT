/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:23:36 by csturm            #+#    #+#             */
/*   Updated: 2024/08/29 10:30:07 by csturm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"
#include <math.h>

// checking if a ray intersects with a sphere
// oc is the vector from the center of the sphere to the origin of the ray
// discriminant measures the intersection of the ray and the sphere
// if the discriminant is less than 0, 
// the ray does not intersect with the sphere
// t is the distance to the intersection point
// if t is greater than 0, the ray intersects with the sphere
// if t is less than 0, the ray intersects with the sphere behind the origin
// if t is equal to 0, the ray intersects with the sphere at the origin
float	intersect_sphere(t_sphere *sphere, t_ray ray)
{
	t_coefficients	coeff;
	t_vector		oc;
	float			discriminant;
	float			t;

	oc = (t_vector){ray.origin.x - sphere->center.x,
		ray.origin.y - sphere->center.y, ray.origin.z - sphere->center.z};
	coeff.a = dot_product(ray.direction, ray.direction);
	coeff.b = 2 * dot_product(oc, ray.direction);
	coeff.c = dot_product(oc, oc) - sphere->radius * sphere->radius;
	discriminant = coeff.b * coeff.b - 4 * coeff.a * coeff.c;
	if (discriminant < 0)
		return (INFINITY);
	t = (-coeff.b - sqrt(discriminant)) / (2 * coeff.a);
	if (t > 0)
		return (t);
	t = (-coeff.b + sqrt(discriminant)) / (2 * coeff.a);
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
float	intersect_plane(t_plane *plane, t_ray ray)
{
	float	t;
	float	denominator;

	denominator = dot_product(plane->axis, ray.direction);
	if (fabs(denominator) < 1e-6)
		return (INFINITY);
	t = dot_product((t_vector){plane->point.x - ray.origin.x,
			plane->point.y - ray.origin.y, plane->point.z - ray.origin.z},
			plane->axis) / denominator;
	if (t > 0)
		return (t);
	return (INFINITY);
}

// checking if a ray intersects with a cylinder
// oc is the vector from the center of the cylinder to the origin of the ray
// discriminant measures the intersection of the ray and the cylinder
// if the discriminant is less than 0,
// the ray does not intersect with the cylinder
// t1 and t2 are the distances to the intersection points
// if t1 is greater than 0, the ray intersects with the cylinder
// if t2 is greater than 0, the ray intersects with the cylinder
// if t1 is less than 0, the ray intersects with the cylinder behind the origin
// if t2 is less than 0, the ray intersects with the cylinder behind the origin
// if t1 is equal to 0, the ray intersects with the cylinder at the origin
// if t2 is equal to 0, the ray intersects with the cylinder at the origin
float	intersect_cylinder(t_cylinder *cylinder, t_ray ray)
{
	t_coefficients	coeff;
	t_vector		oc;
	float			t;

	t = INFINITY;
	calc_coefficients(ray, cylinder, &oc, &coeff);
	t = check_discriminant(coeff, ray, cylinder, oc);
	t = check_caps(cylinder, ray, t, -cylinder->height / 2);
	t = check_caps(cylinder, ray, t, cylinder->height / 2);
	return (t);
}
