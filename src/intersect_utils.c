/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:10:31 by csturm            #+#    #+#             */
/*   Updated: 2024/09/05 12:14:01 by csturm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

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

// calculate whether the ray intersects with the top or bottom of the cylinder
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

// calculate the top and bottom of the cylinder
float	check_caps(t_cylinder *cylinder, t_ray ray, float t, float scale)
{
	t_vector	center;
	t_vector	p;
	float		t_cap;

	center = get_center(cylinder, scale);
	t_cap = intersect_top_bottom(center, cylinder->axis, ray);
	if (t_cap != INFINITY)
	{
		p = ray_at(ray, t_cap);
		if (vector_length(vector_subtract(p, center)) <= cylinder->radius)
			t = fmin(t_cap, t);
	}
	return (t);
}

// calculate the discriminant of the quadratic equation
// a discriminant above 0 means the ray intersects with the cylinder
// an intersection point above 0 means the ray intersects with the cylinder
// it is checked twice to find the closest intersection point
// if both intersection points are less than 0, the ray does not intersect
float	check_discriminant(t_coefficients coeff, t_ray ray,
			t_cylinder *cylinder, t_vector oc)
{
	float	t1;
	float	t2;
	float	t;
	float	discriminant;

	discriminant = coeff.b * coeff.b - 4 * coeff.a * coeff.c;
	t1 = INFINITY;
	t2 = INFINITY;
	t = INFINITY;
	if (discriminant >= 0)
	{
		t1 = check_intersection((-coeff.b - sqrt(discriminant))
				/ (2 * coeff.a), ray, cylinder, oc);
		t2 = check_intersection((-coeff.b + sqrt(discriminant))
				/ (2 * coeff.a), ray, cylinder, oc);
		if (t1 != INFINITY && t2 != INFINITY)
			t = fmin(t1, t2);
		else if (t1 != INFINITY)
			t = t1;
		else if (t2 != INFINITY)
			t = t2;
	}
	return (t);
}
