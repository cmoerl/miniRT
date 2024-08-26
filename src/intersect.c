/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:23:36 by csturm            #+#    #+#             */
/*   Updated: 2024/08/26 10:59:56 by csturm           ###   ########.fr       */
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
	if (denominator == 0)
		return (INFINITY);
	t = dot_product((t_vector){plane->point.x - ray.origin.x,
			plane->point.y - ray.origin.y, plane->point.z - ray.origin.z},
			plane->axis) / denominator;
	if (t > 0)
		return (t);
	return (INFINITY);
}

void	calc_coefficients(t_ray ray, t_cylinder *cylinder,
			t_vector *oc, t_coefficients *coeff)
{
	t_vector	dot;

	oc->x = ray.origin.x - (cylinder->center.x
			- cylinder->axis.x * cylinder->height / 2);
	oc->y = ray.origin.y - (cylinder->center.y
			- cylinder->axis.y * cylinder->height / 2);
	oc->z = ray.origin.z - (cylinder->center.z
			- cylinder->axis.z * cylinder->height / 2);
	dot.x = dot_product(ray.direction, cylinder->axis);
	dot.y = dot_product(*oc, cylinder->axis);
	dot.z = dot_product(cylinder->axis, cylinder->axis);
	coeff->a = dot_product(ray.direction, ray.direction)
		- dot.x * dot.x / dot.z;
	coeff->b = 2 * (dot_product(*oc, ray.direction) - dot.x * dot.y / dot.z);
	coeff->c = dot_product(*oc, *oc) - dot.y * dot.y / dot.z - cylinder->radius
		* cylinder->radius;
}

// m is the distances to the intersection points along the axis of the cylinder
// if m is greater than 0 and less than the height of the cylinder,
// the ray intersects with the cylinder
float	check_intersection(float t, t_ray ray,
			t_cylinder *cylinder, t_vector oc)
{
	float	m;

	if (t > 0)
	{
		m = dot_product(ray.direction, cylinder->axis)
			* t + dot_product(oc, cylinder->axis);
		if (m >= 0 && m < cylinder->height)
			return (t);
	}
	return (INFINITY);
}

t_vector	vector_subtract(t_vector a, t_vector b)
{
	return ((t_vector){a.x - b.x, a.y - b.y, a.z - b.z});
}
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

float	intersect_top_bottom(t_vector point, t_vector normal, t_ray ray)
{
	t_vector	p0l0;
	float		t;
	float		denominator;

	denominator = dot_product(normal, ray.direction);
	if (fabs(denominator) > 1e-6)
	{
		p0l0 = vector_subtract(point, ray.origin);
		t = dot_product(p0l0, normal) / denominator;
		if (t > 0)
			return (t);
	}
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
	t_vector		top_center;
	t_vector		bottom_center;
	t_vector		p;
	float			discriminant;
	float			t1;
	float			t2;
	float			t;
	float			t_top;
	float			t_bottom;

	t = INFINITY;
	calc_coefficients(ray, cylinder, &oc, &coeff);
	discriminant = coeff.b * coeff.b - 4 * coeff.a * coeff.c;
	if (discriminant >= 0)
	{
		t1 = (-coeff.b - sqrt(discriminant)) / (2 * coeff.a);
		t2 = (-coeff.b + sqrt(discriminant)) / (2 * coeff.a);
		t1 = check_intersection(t1, ray, cylinder, oc);
		t2 = check_intersection(t2, ray, cylinder, oc);
		if (t1 != INFINITY && t2 != INFINITY)
			t = fmin(t1, t2);
		else if (t1 != INFINITY)
			t = t1;
		else if (t2 != INFINITY)
			t = t2;
	}
	cylinder->axis = normalise_vector(cylinder->axis);
	bottom_center = vector_add(cylinder->center,
			vector_scale(cylinder->axis, -cylinder->height / 2));
	t_bottom = intersect_top_bottom(bottom_center, cylinder->axis, ray);
	if (t_bottom != INFINITY)
	{
		p = ray_at(ray, t_bottom);
		if (vector_length(vector_subtract(p, bottom_center)) <= cylinder->radius)
			t = fmin(t_bottom, t);
	}
	top_center = vector_add(cylinder->center,
			vector_scale(cylinder->axis, cylinder->height / 2));
	t_top = intersect_top_bottom(top_center, cylinder->axis, ray);
	if (t_top != INFINITY)
	{
		p = ray_at(ray, t_top);
		if (vector_length(vector_subtract(p, top_center)) <= cylinder->radius)
			t = fmin(t_top, t);
	}
	return (t);
}
