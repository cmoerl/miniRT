/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 12:18:29 by csturm            #+#    #+#             */
/*   Updated: 2024/09/05 12:04:40 by csturm           ###   ########.fr       */
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

	light_dir.x = scene.light.position.x - (ip.x);
	light_dir.y = scene.light.position.y - (ip.y);
	light_dir.z = scene.light.position.z - (ip.z);
	return (light_dir);
}

// check if an object is blocking the light
// if an object is blocking the light, the pixel is in shadow
int	in_shadow(t_scene scene, t_vector ip, t_light_ray light, t_hit object_hit)
{
	t_vector	jitter;
	t_ray		shadow_ray;
	t_hit		hit;
	float		jitter_scale;
	int			i;

	jitter_scale = 0.01;
	i = 0;
	while (i < 16)
	{
		jitter.x = ((float)rand() / (float)RAND_MAX - 0.5) * jitter_scale;
		jitter.y = ((float)rand() / (float)RAND_MAX - 0.5) * jitter_scale;
		jitter.z = ((float)rand() / (float)RAND_MAX - 0.5) * jitter_scale;
		shadow_ray.origin.x = ip.x + jitter.x;
		shadow_ray.origin.y = ip.y + jitter.y;
		shadow_ray.origin.z = ip.z + jitter.z;
		shadow_ray.direction = light.direction;
		hit = find_closest_object(scene, shadow_ray);
		if (hit.t < light.distance && hit.t > 0
			&& (hit.type != object_hit.type || hit.index != object_hit.index))
			return (1);
		i++;
	}
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
// calculate the ambient color contribution
// calculate the direction and distance of the light
// check if the pixel is in shadow
// calculate the attenuation of the light
// calculate the diffuse color contribution
// cap the color at 255
t_color	calc_shade(t_scene scene, t_shade shade, t_hit object_hit)
{
	t_light_ray	light;
	t_color		color;
	float		dot;
	float		attenuation;

	color = calc_ambient(scene, shade.object_color);
	light.direction = calc_light_dir(scene, shade.ip);
	light.distance = vector_length(light.direction);
	light.direction = normalise_vector(light.direction);
	if (in_shadow(scene, shade.ip, light, object_hit))
		return (color);
	dot = dot_product(shade.normal, light.direction);
	if (dot < 0 && object_hit.type == PLANE)
		dot *= -1;
	else if (dot < 0)
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
