/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:25:53 by csturm            #+#    #+#             */
/*   Updated: 2024/08/20 11:04:06 by csturm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

// check whether the ray intersects with an object
// iterating over each object
// calculating the intersection point
// if the intersection point is closer than the previous intersection point, update the intersection point
// return the closest object
// if no object is hit, return NULL / INFINITY / NONE
t_hit   find_closest_object(t_scene scene, t_ray ray)
{
    t_hit hit;
    float t;
    t_sphere *sphere;
    t_plane *plane;
    t_cylinder *cylinder;
    int i;

    i = -1;
    hit.t = INFINITY;
    hit.object = NULL;
    hit.type = NONE;
    hit.index = -1;
    sphere = scene.objects->spheres;
    while (sphere != NULL)
    {
        i++;
        t = intersect_sphere(sphere, ray);
        if (t > 0 && t < hit.t)
        {
            hit.t = t;
            hit.object = sphere;
            hit.type = SPHERE;
            hit.index = i;
        }
        sphere = sphere->next;
    }
    i = -1;
    plane = scene.objects->planes;
    while (plane != NULL)
    {
        i++;
        t = intersect_plane(plane, ray);
        if (t > 0 && t < hit.t)
        {
            hit.t = t;
            hit.object = plane;
            hit.type = PLANE;
            hit.index = i;
        }
        plane = plane->next;
    }
    i = -1;
    cylinder = scene.objects->cylinders;
    while (cylinder != NULL)
    {
        i++;
        t = intersect_cylinder(cylinder, ray);
        if (t > 0 && t < hit.t)
        {
            hit.t = t;
            hit.object = cylinder;
            hit.type = CYLINDER;
            hit.index = i;
        }
        cylinder = cylinder->next;
    }
    return (hit);
}

// for each pixel that is part of an object:
// calculate from which direction the light is coming
// calculate how far the light is from the object by casting multiple shadow rays
// check if an object is blocking the light
// if an object is blocking the light, the pixel is in shadow
// if no object is blocking the light, calculate the color of the pixel
// dot is the angle between the normal and the light direction
// attenuation is the distance between the light and the object
// the color of the pixel is the object color multiplied by the light intensity and the dot divided by the attenuation
// the color of the pixel is capped at 255
t_color calc_shade(t_scene scene, t_vector ip, t_vector normal, t_color object_color, t_hit object_hit)
{
    t_color color;
    t_vector light_dir;
    t_ray shadow_ray;
    t_hit hit;
    float light_distance;
    float dot;
    float attenuation;
    t_vector jitter;

    color.r = scene.amblight.intensity * scene.amblight.color.r * object_color.r;
    color.g = scene.amblight.intensity * scene.amblight.color.g * object_color.g;
    color.b = scene.amblight.intensity * scene.amblight.color.b * object_color.b;
    jitter.x = ((float)rand() / (float)RAND_MAX - 0.5) * 0.1;
    jitter.y = ((float)rand() / (float)RAND_MAX - 0.5) * 0.1;
    jitter.z = ((float)rand() / (float)RAND_MAX - 0.5) * 0.1;
    light_dir.x = scene.light.position.x - (ip.x + jitter.x);
    light_dir.y = scene.light.position.y - (ip.y + jitter.y);
    light_dir.z = scene.light.position.z - (ip.z + jitter.z);
    light_distance = sqrt(light_dir.x * light_dir.x + light_dir.y * light_dir.y + light_dir.z * light_dir.z);
    light_dir = normalise_vector(light_dir);
    shadow_ray.origin = ip;
    shadow_ray.direction = light_dir;
    hit = find_closest_object(scene, shadow_ray);
    if (hit.t < light_distance && (hit.type != object_hit.type || hit.index != object_hit.index))
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

// for each ray:
// check if the ray intersects with any object
// if the ray intersects with an object, calculate the color of the pixel
// if the ray does not intersect with any object, the pixel is black
// check if the pixel is in shadow
t_color trace_ray(t_scene scene, t_ray ray)
{
    t_color color;
    t_hit   hit;
    t_vector ip;
    t_vector normal;
    t_color object_color;
    

    color = (t_color){0, 0, 0};
    object_color = (t_color){0, 0, 0};
    hit = find_closest_object(scene, ray);
    if (hit.t == INFINITY)
        return (color = (t_color){0, 0, 0});
    ip = get_intersection_point(ray, hit.t);
    normal = get_normal(ip, hit);
    if (hit.type == SPHERE)
        object_color = ((t_sphere*)hit.object)->color;
    else if (hit.type == PLANE)
        object_color = ((t_plane*)hit.object)->color;
    else if (hit.type == CYLINDER)
        object_color = ((t_cylinder*)hit.object)->color;
    color = calc_shade(scene, ip, normal, object_color, hit);
    return (color);
}

// for each pixel:
// calculate the aspect ratio
// calculate the tan of the fov
// calculate the direction of the ray
// ray origin is the camera center
t_ray    get_ray(t_scene scene, int x, int y)
{
    t_ray ray;
    t_vector ray_dir;
    float aspect_ratio;
    float tan_fov;
    t_vector orientation;

    aspect_ratio = scene.width / (float)scene.height;
    tan_fov = tan((scene.camera.fov * PI / 180) / 2.0);
    ray_dir.x = (2 * (x + 0.5) / (double)scene.width - 1) * aspect_ratio * tan_fov;
    ray_dir.y = (1 - 2 * (y + 0.5) / (double)scene.height) * tan_fov;
    ray_dir.z = -1;
    ray_dir = normalise_vector(ray_dir);
    orientation = normalise_vector(scene.camera.orientation);
    ray_dir = rotate_vector(ray_dir, orientation);
    ray.origin.x = scene.camera.center.x;
    ray.origin.y = scene.camera.center.y;
    ray.origin.z = scene.camera.center.z;
    ray.origin = scene.camera.center;
    ray.direction = ray_dir;
    return (ray);
}