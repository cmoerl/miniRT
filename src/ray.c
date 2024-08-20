/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:25:53 by csturm            #+#    #+#             */
/*   Updated: 2024/08/20 12:19:02 by csturm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

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
    ray.origin = scene.camera.center;
    ray.direction = ray_dir;
    return (ray);
}
