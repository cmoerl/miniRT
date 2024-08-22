/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 12:18:29 by csturm            #+#    #+#             */
/*   Updated: 2024/08/22 12:16:30 by csturm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

// calculate the ambient light
t_color	calc_ambient(t_scene scene, t_color object_color)
{
	t_color	color;

	color.r = scene.amblight.intensity
		* (scene.amblight.color.r / 255.0) * object_color.r;
	color.g = scene.amblight.intensity
		* (scene.amblight.color.g / 255.0) * object_color.g;
	color.b = scene.amblight.intensity
		* (scene.amblight.color.b / 255.0) * object_color.b;
	return (color);
}

// calculate from which direction the light is coming
t_vector	calc_light_dir(t_scene scene, t_vector ip)
{
	t_vector	light_dir;
	t_vector	jitter;

	jitter.x = ((float)rand() / (float)RAND_MAX - 0.5) * 0.1;
	jitter.y = ((float)rand() / (float)RAND_MAX - 0.5) * 0.1;
	jitter.z = ((float)rand() / (float)RAND_MAX - 0.5) * 0.1;
	light_dir.x = scene.light.position.x - (ip.x + jitter.x);
	light_dir.y = scene.light.position.y - (ip.y + jitter.y);
	light_dir.z = scene.light.position.z - (ip.z + jitter.z);
	return (light_dir);
}

// check if an object is blocking the light
// if an object is blocking the light, the pixel is in shadow
int	in_shadow(t_scene scene, t_vector ip, t_light_ray light, t_hit object_hit)
{
	t_ray	shadow_ray;
	t_hit	hit;

	shadow_ray.origin = ip;
	shadow_ray.direction = light.direction;
	hit = find_closest_object(scene, shadow_ray);
	if (hit.t < light.distance
		&& (hit.type != object_hit.type || hit.index != object_hit.index))
		return (1);
	return (0);
}

// the color of the pixel is capped at 255
t_color	cap_color(t_color color)
{
	color.r = fmin(color.r, 255);
	color.g = fmin(color.g, 255);
	color.b = fmin(color.b, 255);
	return (color);
}

// for each pixel that is part of an object:
// calculate how far the light is from the object
// by casting multiple shadow rays
// if no object is blocking the light, calculate the color of the pixel
// dot is the angle between the normal and the light direction
// attenuation is the distance between the light and the object
// the color of the pixel is the object color
// multiplied by the light intensity and the dot divided by the attenuation
t_color	calc_shade(t_scene scene, t_shade shade, t_hit object_hit)
{
	t_light_ray	light;
	t_color		color;
	float		dot;
	float		attenuation;

	color = calc_ambient(scene, shade.object_color);
	light.direction = calc_light_dir(scene, shade.ip);
	light.distance = sqrt(light.direction.x * light.direction.x
			+ light.direction.y * light.direction.y
			+ light.direction.z * light.direction.z);
	light.direction = normalise_vector(light.direction);
	if (in_shadow(scene, shade.ip, light, object_hit))
		return (color);
	dot = dot_product(shade.normal, light.direction);
	if (dot < 0)
		dot = 0;
	attenuation = 1.0 / (1.0 + 0.1 * light.distance);
	color.r += DIFFUSE * shade.object_color.r
		* scene.light.intensity * dot / attenuation;
	color.g += DIFFUSE * shade.object_color.g
		* scene.light.intensity * dot / attenuation;
	color.b += DIFFUSE * shade.object_color.b
		* scene.light.intensity * dot / attenuation;
	color = cap_color(color);
	return (color);
}
