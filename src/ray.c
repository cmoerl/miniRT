/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:25:53 by csturm            #+#    #+#             */
/*   Updated: 2024/06/28 14:56:41 by csturm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

t_color calc_shade(t_scene scene, t_vector ip, t_vector normal, t_object object)
{
    t_color color;
    t_vector light_dir;
    t_vector shadow_ray;
    float light_distance;
    float t;
    int i;
    int j;

    i = 0;
    color = (t_color){0, 0, 0};
    light_dir.x = scene.light.center.x - ip.x;
    light_dir.y = scene.light.center.y - ip.y;
    light_dir.z = scene.light.center.z - ip.z;
    light_distance = sqrt(light_dir.x * light_dir.x + light_dir.y * light_dir.y + light_dir.z * light_dir.z);
    // shadow_ray is the vector from the intersection point to the light source
    shadow_ray = (t_vector){light_dir.x / light_distance, light_dir.y / light_distance, light_dir.z / light_distance};
    t = INFINITY;
    // check if the shadow ray intersects with any object
    j = 0;
    while (j < scene.objects_count)
    {
        if (scene.objects[j].type == SPHERE)
            t = intersect_sphere(scene.objects[j].sphere, shadow_ray);
        else if (scene.objects[j].type == PLANE)
            t = intersect_plane(scene.objects[j].plane, shadow_ray);
        else if (scene.objects[j].type == CYLINDER)
            t = intersect_cylinder(scene.objects[j].cylinder, shadow_ray);
        // if the shadow ray intersects with an object, the pixel is in shadow
        if (t > 0 && t < light_distance)
            break;
        j++;
    }
    // if the pixel is not in shadow, calculate the color of the pixel
    if (t >= light_distance)
    {
        color.r += object.color.r * scene.light.intensity * dot_product(normal, light_dir) / (light_distance * light_distance);
        color.g += object.color.g * scene.light.intensity * dot_product(normal, light_dir) / (light_distance * light_distance);
        color.b += object.color.b * scene.light.intensity * dot_product(normal, light_dir) / (light_distance * light_distance);
    }
    return (color);
}

t_vector    normalise_vector(t_vector v)
{
    float length;
    t_vector normalised;

    length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z); // magnitude (length) of the vector
    normalised.x = v.x / length;
    normalised.y = v.y / length;
    normalised.z = v.z / length;
    return (normalised);
}

t_vector    get_intersection_point(t_vector ray, float t, t_object object)
{
    t_vector ip;

    ip.x = ray.x * t;
    ip.y = ray.y * t;
    ip.z = ray.z * t;
    return (ip);
}

t_vector    get_normal(t_vector v, t_object object)
{
    t_vector normal;
    
    if (object.type == SPHERE)
    {
        normal.x = v.x - object.sphere.center.x;
        normal.y = v.y - object.sphere.center.y;
        normal.z = v.z - object.sphere.center.z;
    }
    else if (object.type == PLANE)
    {
        normal = object.plane.normal;
    }
    else if (object.type == CYLINDER)
    {
        normal.x = v.x - object.cylinder.center.x;
        normal.y = v.y - object.cylinder.center.y;
        normal.z = v.z - object.cylinder.center.z;
    }
    normal = normalise_vector(normal);
    return (normal);
}

t_color trace_ray(t_scene scene, t_vector ray)
{
    t_color color;
    t_object closest_object;
    t_vector ip;
    t_vector normal;
    float closest_t;
    float t;
    int i;

    i = 0;
    closest_t = INFINITY;
    while (i < scene.objects_count)
    {
        // check if the ray intersects with the object
        // t is the distance from the ray origin to the intersection point
        if (scene.objects[i].type == SPHERE)
            t = intersect_sphere(scene.objects[i].sphere, ray);
        else if (scene.objects[i].type == PLANE)
            t = intersect_plane(scene.objects[i].plane, ray);
        else if (scene.objects[i].type == CYLINDER)
            t = intersect_cylinder(scene.objects[i].cylinder, ray);       
        // if t is less than the closest_t, update the closest_t and the closest_object
        if (t > 0 && t < closest_t)
        {
            closest_t = t;
            closest_object = scene.objects[i];
        }
        i++;
    }
    // if closest_t is still INFINITY, no object was hit
    if (closest_t == INFINITY)
        return (color = (t_color){0, 0, 0});
    // get the intersection point and the normal of the closest object
    ip = get_intersection_point(ray, closest_t, closest_object);
    normal = get_normal(ip, closest_object);
    // calculate the color of the pixel
    color = calc_shade(scene, ip, normal, closest_object);
    // return the color of the pixel
    return (color);
}

t_vector    get_ray(t_scene scene, int x, int y)
{
    t_vector ray;
    t_vector ray_dir;
    float aspect_ratio;
    float tan_fov;

    aspect_ratio = scene.width / (float)scene.height;
    tan_fov = tan(scene.camera.fov / 2.0);
// normalising the pixel coordinates to the range [0, 1]
// remapping the pixel coordinates to the range [-1, 1]
// calculating the ray direction
    ray_dir.x = (2 * (x + 0.5) / (double)scene.width - 1) * aspect_ratio * tan_fov;
    ray_dir.y = (1 - 2 * (y + 0.5) / (double)scene.height) * tan_fov;
    ray_dir.z = -1;
    ray = normalise_vector(ray_dir);
    return (ray);
}
