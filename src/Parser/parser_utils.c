/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 18:42:55 by marianfurni       #+#    #+#             */
/*   Updated: 2024/09/09 14:30:53 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

// check if the file exists and has the correct format
void	check_file(char *file)
{
	int		fd;
	char	*extension;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("Error accessing file");
		exit(EXIT_FAILURE);
	}
	close(fd);
	extension = ft_strrchr(file, '.');
	if (!extension || ft_strcmp(extension, ".rt") != 0)
	{
		printf("Error: Incorrect file format. Expected .rt\n");
		exit(EXIT_FAILURE);
	}
}

// initialize the scene struct
t_scene	init_scene(t_scene scene)
{
	scene.objects = NULL;
	scene.hooks = NULL;
	scene.img = NULL;
	scene.mlx_ptr = NULL;
	scene.win_ptr = NULL;
	scene.objects = malloc(sizeof(t_object));
	if (!scene.objects)
		error("Memory allocation failed", &scene, NULL);
	scene.objects->spheres = NULL;
	scene.objects->planes = NULL;
	scene.objects->cylinders = NULL;
	return (scene);
}

// if the ambient light is found, parse it
void	parse_ambient_line(char *line, t_scene *scene)
{
	if (scene->flags.ambient_found)
		error ("Multiple ambient lighting definitions found", scene, line);
	parse_ambient(line, &scene->amblight, scene);
	scene->flags.ambient_found = 1;
}

// if the camera is found, parse it
void	parse_camera_line(char *line, t_scene *scene)
{
	if (scene->flags.camera_found)
		error("Multiple camera definitions found", scene, line);
	parse_camera(line, &scene->camera, scene);
	scene->flags.camera_found = 1;
}

//if the object is found, parse it
void	parse_object_line(char *line, t_scene *scene)
{
	if (line[0] == 'p' && line[1] == 'l' && (line[2] == ' ' || line[2] == '\t'))
	{
		parse_plane(line, &scene->objects->planes, scene);
		scene->flags.objects_found = 1;
	}
	else if (line[0] == 'c' && line[1] == 'y'
		&& (line[2] == ' ' || line[2] == '\t'))
	{
		parse_cylinder(line, &scene->objects->cylinders, scene);
		scene->flags.objects_found = 1;
	}
	else if (line[0] == 's' && line[1] == 'p'
		&& (line[2] == ' ' || line[2] == '\t'))
	{
		parse_sphere(line, &scene->objects->spheres, scene);
		scene->flags.objects_found = 1;
	}
	else
	{
		scene->flags.invalid_line_found = 1;
	}
}
