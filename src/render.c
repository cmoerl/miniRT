/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:03:05 by csturm            #+#    #+#             */
/*   Updated: 2024/06/25 17:11:21 by csturm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"
#include <math.h>

/*
- take a t_scene struct
- iterate over the screen pixels
- get the ray for each pixel
- trace the ray and get the color
- put the color on the screen
- repeat until all pixels are colored
- show the image 
*/

t_color trace_ray(t_scene scene, t_vector ray)
{
    t_color color;
    t_object closest_object;
    float closest_t;
    float t;
    int i;

    i = 0;
    closest_t = INFINITY;
    while (i < scene.objects_count)
    {
        // are we allowed to use a switch statement here?
        switch (scene.objects[i].type)
        {
            case SPHERE:
                t = intersect_sphere(scene.objects[i].sphere, ray);
                break;
            case PLANE:
                t = intersect_plane(scene.objects[i].plane, ray);
                break;
            case CYLINDER:
                t = intersect_cylinder(scene.objects[i].cylinder, ray);
                break;
        }
        if (t > 0 && t < closest_t)
        {
            closest_t = t;
            closest_object = scene.objects[i];
        }
        i++;
    }
    if (closest_t == INFINITY)
        return (color = (t_color){0, 0, 0});
    return (closest_object.color);
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

void    render_scene(t_scene scene)
{
    int x;
    int y;
    t_vector ray;
    t_color color;

    x = 0;
    y = 0;
    while (y < scene.height)
    {
        while (x < scene.width)
        {
            ray = get_ray(scene, x, y);
            color = trace_ray(scene, ray);
            put_pixel(x, y, color);
            x++;
        }
        y++;
    }
}