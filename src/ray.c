/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csturm <csturm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:25:53 by csturm            #+#    #+#             */
/*   Updated: 2024/09/05 12:14:10 by csturm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

// for each ray:
// check if the ray intersects with any object
// if the ray does not intersect with any object, the pixel is black
// if the ray intersects with an object, calculate the color of the pixel
// check if the pixel is in shadow
t_color	trace_ray(t_scene scene, t_ray ray)
{
	t_shade	shade;
	t_color	color;
	t_hit	hit;

	if (scene.camera.fov == 0)
		return ((t_color){0, 0, 0});
	color = (t_color){0, 0, 0};
	shade.object_color = (t_color){0, 0, 0};
	hit = find_closest_object(scene, ray);
	if (hit.t == INFINITY)
		return (color = (t_color){0, 0, 0});
	shade.ip = get_intersection_point(ray, hit.t);
	shade.normal = get_normal(shade.ip, hit);
	if (hit.type == SPHERE)
		shade.object_color = ((t_sphere *)hit.object)->color;
	else if (hit.type == PLANE)
		shade.object_color = ((t_plane *)hit.object)->color;
	else if (hit.type == CYLINDER)
		shade.object_color = ((t_cylinder *)hit.object)->color;
	color = calc_shade(scene, shade, hit);
	return (color);
}

// normalise the pixel coordinates
// scale the pixel coordinates to the aspect ratio
// combine the scaled coordinates with the orientation of the camera
// normalise the direction of the ray
t_vector	calc_ray_dir(int x, int y, t_cam_params params)
{
	t_vector	ray_dir;

	ray_dir.x = (2 * (x + 0.5) / (double)WIDTH - 1)
		* params.aspect_ratio * params.tan_fov;
	ray_dir.y = (1 - 2 * (y + 0.5) / (double)HEIGHT) * params.tan_fov;
	ray_dir.z = -1;
	ray_dir = vector_add(vector_add(vector_scale
				(params.orient.right, ray_dir.x),
				vector_scale(params.orient.up, ray_dir.y)),
			vector_scale(params.orient.forward, ray_dir.z));
	ray_dir = normalise_vector(ray_dir);
	return (ray_dir);
}

// for each pixel:
// calculate the aspect ratio
// calculate the tan of the fov
// calculate the orientation of the camera
// adjust world_up if the camera is looking straight up or down
// calculate the direction of the ray
// ray origin is the camera center
t_ray	get_ray(t_scene scene, int x, int y)
{
	t_orientation	orient;
	t_cam_params	params;
	t_ray			ray;

	params.aspect_ratio = WIDTH / (float)HEIGHT;
	if (scene.camera.fov == 180)
		params.tan_fov = 750;
	else
		params.tan_fov = tan((scene.camera.fov * PI / 180) / 2.0);
	orient.world_up = (t_vector){0, 1, 0};
	orient.forward = vector_scale(scene.camera.orientation, -1);
	if (fabs(scene.camera.orientation.y) > 0.9999)
		orient.world_up = (t_vector){1, 0, 0};
	orient.right = normalise_vector
		(cross_product(orient.world_up, orient.forward));
	orient.up = cross_product(orient.forward, orient.right);
	params.orient = orient;
	ray.origin = scene.camera.center;
	ray.direction = calc_ray_dir(x, y, params);
	return (ray);
}
