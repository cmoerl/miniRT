/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:25:53 by csturm            #+#    #+#             */
/*   Updated: 2024/07/29 12:28:31 by csturm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

t_hit   find_closest_object(t_scene scene, t_ray ray)
{
    t_hit hit;
    float t;
    t_sphere *sphere;
    t_plane *plane;
    t_cylinder *cylinder;

    hit.t = INFINITY;
    hit.object = NULL;
    hit.type = NONE;
    sphere = scene.objects->spheres;
    while (sphere != NULL)
    {
        t = intersect_sphere(sphere, ray);
        if (t > 0 && t < hit.t)
        {
            hit.t = t;
            hit.object = sphere;
            hit.type = SPHERE;
        }
        sphere = sphere->next;
    }
    plane = scene.objects->planes;
    while (plane != NULL)
    {
        t = intersect_plane(plane, ray);
        if (t > 0 && t < hit.t)
        {
            hit.t = t;
            hit.object = plane;
            hit.type = PLANE;
        }
        plane = plane->next;
    }
    cylinder = scene.objects->cylinders;
    while (cylinder != NULL)
    {
        t = intersect_cylinder(cylinder, ray);
        if (t > 0 && t < hit.t)
        {
            hit.t = t;
            hit.object = cylinder;
            hit.type = CYLINDER;
        }
        cylinder = cylinder->next;
    }
    return (hit);
}

// shadow_ray is the vector from the intersection point to the light source
// check if the shadow ray intersects with any object
// if the shadow ray intersects with an object, the pixel is in shadow
// if the pixel is not in shadow, calculate the color of the pixel
t_color calc_shade(t_scene scene, t_vector ip, t_vector normal, t_color object_color)
{
    t_color color;
    t_vector light_dir;
    t_ray shadow_ray;
    t_hit hit;
    float light_distance;
    float dot;
    float attenuation;

    color = (t_color){0, 0, 0};
    light_dir.x = scene.light.position.x - ip.x;
    light_dir.y = scene.light.position.y - ip.y;
    light_dir.z = scene.light.position.z - ip.z;
    light_distance = sqrt(light_dir.x * light_dir.x + light_dir.y * light_dir.y + light_dir.z * light_dir.z);
    light_dir = normalise_vector(light_dir);
    shadow_ray.direction = light_dir;
    shadow_ray.origin = ip;
    hit = find_closest_object(scene, shadow_ray);
    if (hit.t < light_distance)
        return (color);
    dot = dot_product(normal, light_dir);
    printf("dot: %f\n", dot);
    if (dot < 0)
        dot = 0;
    attenuation = 1.0 / (1.0 + 0.1 * light_distance);
    color.r += object_color.r * scene.light.intensity * dot / attenuation;
    color.g += object_color.g * scene.light.intensity * dot / attenuation;
    color.b += object_color.b * scene.light.intensity * dot / attenuation;
    color.r = fmin(color.r, 255);
    color.g = fmin(color.g, 255);
    color.b = fmin(color.b, 255);
    return (color);
}

// check if the ray intersects with the object
// t is the distance from the ray origin to the intersection point
// if t is less than the closest_t, update the closest_t and the closest_object
// if closest_t is still INFINITY, no object was hit
// get the intersection point and the normal of the closest object
// calculate the color of the pixel
// return the color of the pixel
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
    color = calc_shade(scene, ip, normal, object_color);
    return (color);
}

// normalising the pixel coordinates to the range [0, 1]
// remapping the pixel coordinates to the range [-1, 1]
// transform the ray direction based on the camera's orientation
// translate the ray origin based on the camera's position
// normalise the ray direction
t_ray    get_ray(t_scene scene, int x, int y)
{
    t_ray ray;
    t_vector ray_dir;
    float aspect_ratio;
    float tan_fov;

    aspect_ratio = scene.width / (float)scene.height;
    tan_fov = tan((scene.camera.fov * PI / 180) / 2.0);
    ray_dir.x = (2 * (x + 0.5) / (double)scene.width - 1) * aspect_ratio * tan_fov;
    ray_dir.y = (1 - 2 * (y + 0.5) / (double)scene.height) * tan_fov;
    ray_dir.z = -1;
    ray_dir = normalise_vector(ray_dir);
    ray_dir = rotate_vector(ray_dir, scene.camera.orientation);
    ray.origin.x = scene.camera.center.x;
    ray.origin.y = scene.camera.center.y;
    ray.origin.z = scene.camera.center.z;
    ray.direction = ray_dir;
    return (ray);
}
