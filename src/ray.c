/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:25:53 by csturm            #+#    #+#             */
/*   Updated: 2024/07/02 11:50:19 by csturm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

t_hit   find_closest_object(t_scene scene, t_ray ray)
{
    t_hit hit;
    float t;
    int i;

    i = 0;
    hit.t = INFINITY;
    while (i < scene.objects_count)
    {
        if (scene.objects[i].type == SPHERE)
            t = intersect_sphere(scene.objects[i].sphere, ray);
        else if (scene.objects[i].type == PLANE)
            t = intersect_plane(scene.objects[i].plane, ray);
        else if (scene.objects[i].type == CYLINDER)
            t = intersect_cylinder(scene.objects[i].cylinder, ray);       
        if (t > 0 && t < hit.t)
        {
            hit.t = t;
            hit.object = scene.objects[i];
        }
        i++;
    }
    return (hit);
}

// shadow_ray is the vector from the intersection point to the light source
// check if the shadow ray intersects with any object
// if the shadow ray intersects with an object, the pixel is in shadow
// if the pixel is not in shadow, calculate the color of the pixel
t_color calc_shade(t_scene scene, t_vector ip, t_vector normal, t_object object)
{
    t_color color;
    t_color object_color;
    t_vector light_dir;
    t_ray shadow_ray;
    t_hit hit;
    float light_distance;

    color = (t_color){0, 0, 0};
    light_dir.x = scene.light.position.x - ip.x;
    light_dir.y = scene.light.position.y - ip.y;
    light_dir.z = scene.light.position.z - ip.z;
    light_distance = sqrt(light_dir.x * light_dir.x + light_dir.y * light_dir.y + light_dir.z * light_dir.z);
    shadow_ray.direction = (t_vector){light_dir.x / light_distance, light_dir.y / light_distance, light_dir.z / light_distance};
    shadow_ray.origin = ip;
    hit = find_closest_object(scene, shadow_ray);
    if (hit.t < light_distance)
        return (color);
    if (object.type == SPHERE)
        object_color = (t_color){object.sphere->color.r, object.sphere->color.g, object.sphere->color.b};
    else if (object.type == PLANE)
        object_color = (t_color){object.plane->color.r, object.plane->color.g, object.plane->color.b};
    else if (object.type == CYLINDER)
        object_color = (t_color){object.cylinder->color.r, object.cylinder->color.g, object.cylinder->color.b};
    color.r += object_color.r * scene.light.intensity * dot_product(normal, light_dir) / (light_distance * light_distance);
    color.g += object_color.g * scene.light.intensity * dot_product(normal, light_dir) / (light_distance * light_distance);
    color.b += object_color.b * scene.light.intensity * dot_product(normal, light_dir) / (light_distance * light_distance);
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

    hit = find_closest_object(scene, ray);
    if (hit.t == INFINITY)
        return (color = (t_color){0, 0, 0});
    ip = get_intersection_point(ray, hit.t, hit.object);
    normal = get_normal(ip, hit.object);
    color = calc_shade(scene, ip, normal, hit.object);
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
    tan_fov = tan(scene.camera.fov / 2.0);
    ray_dir.x = (2 * (x + 0.5) / (double)scene.width - 1) * aspect_ratio * tan_fov;
    ray_dir.y = (1 - 2 * (y + 0.5) / (double)scene.height) * tan_fov;
    ray_dir.z = -1;
    ray_dir = rotate_vector(ray_dir, scene.camera.orientation);
    ray.origin.x = scene.camera.center.x;
    ray.origin.y = scene.camera.center.y;
    ray.origin.z = scene.camera.center.z;
    ray.direction = normalise_vector(ray_dir);
    return (ray);
}
