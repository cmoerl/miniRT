/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 12:18:29 by csturm            #+#    #+#             */
/*   Updated: 2024/08/20 12:20:36 by csturm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

// calculate the ambient light
t_color calc_ambient(t_scene scene, t_color object_color)
{
    t_color color;

    color.r = scene.amblight.intensity * scene.amblight.color.r * object_color.r;
    color.g = scene.amblight.intensity * scene.amblight.color.g * object_color.g;
    color.b = scene.amblight.intensity * scene.amblight.color.b * object_color.b;
    return (color);
}

// calculate from which direction the light is coming
t_vector    calc_light_dir(t_scene scene, t_vector ip)
{
    t_vector light_dir;
    t_vector jitter;

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
int in_shadow(t_scene scene, t_vector ip, t_vector light_dir, float light_distance, t_hit object_hit)
{
    t_ray shadow_ray;
    t_hit hit;

    shadow_ray.origin = ip;
    shadow_ray.direction = light_dir;
    hit = find_closest_object(scene, shadow_ray);
    if (hit.t < light_distance && (hit.type != object_hit.type || hit.index != object_hit.index))
        return (1);
    return (0);
}

// for each pixel that is part of an object:
// calculate how far the light is from the object by casting multiple shadow rays
// if no object is blocking the light, calculate the color of the pixel
// dot is the angle between the normal and the light direction
// attenuation is the distance between the light and the object
// the color of the pixel is the object color multiplied by the light intensity and the dot divided by the attenuation
// the color of the pixel is capped at 255
t_color calc_shade(t_scene scene, t_vector ip, t_vector normal, t_color object_color, t_hit object_hit)
{
    t_color color;
    t_vector light_dir;
    float light_distance;
    float dot;
    float attenuation;

    color = calc_ambient(scene, object_color);
    light_dir = calc_light_dir(scene, ip);
    light_distance = sqrt(light_dir.x * light_dir.x + light_dir.y * light_dir.y + light_dir.z * light_dir.z);
    light_dir = normalise_vector(light_dir);
    if (in_shadow(scene, ip, light_dir, light_distance, object_hit))
        return (color);
    dot = dot_product(normal, light_dir);
    if (dot < 0)
        dot = 0;
    attenuation = 1.0 / (1.0 + 0.1 * light_distance);
    color.r += DIFFUSE * object_color.r * scene.light.intensity * dot / attenuation;
    color.g += DIFFUSE * object_color.g * scene.light.intensity * dot / attenuation;
    color.b += DIFFUSE * object_color.b * scene.light.intensity * dot / attenuation;
    color.r = fmin(color.r, 255);
    color.g = fmin(color.g, 255);
    color.b = fmin(color.b, 255);
    return (color);
}
