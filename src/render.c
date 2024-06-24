/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:03:05 by csturm            #+#    #+#             */
/*   Updated: 2024/06/24 17:50:21 by csturm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

/*
- take a t_scene struct
- iterate over the screen pixels
- get the ray for each pixel
- trace the ray and get the color
- put the color on the screen
- repeat until all pixels are colored
- show the image 
*/

t_vector    get_ray(t_scene scene, int x, int y)
{
    t_vector ray;
    t_vector screen_point;

// normalising the pixel coordinates to the range [0, 1]
// remapping the pixel coordinates to the range [-1, 1]
    screen_point.x = (2 * (x + 0.5) / (double)scene.width - 1) * scene.aspect_ratio * scene.tan_fov;
    screen_point.y = (1 - 2 * (y + 0.5) / (double)scene.height) * scene.tan_fov;
    screen_point.z = -1;
    ray = normalize_vector(screen_point);
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