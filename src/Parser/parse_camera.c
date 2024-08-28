/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 23:38:31 by marianfurni       #+#    #+#             */
/*   Updated: 2024/08/28 09:35:51 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

// Helper function to validate identifier
void	validate_identifier(char actual, char expected, t_scene *scene)
{
	if (actual != expected)
		error("Invalid identifier", scene);
}

// Helper function to parse a vector
t_vector	parse_vector(char **line, int *i, t_scene *scene)
{
	t_vector	vec;

	vec.x = parse_float_with_check(line, i, scene);
	vec.y = parse_float_with_check(line, i, scene);
	vec.z = parse_float_with_check(line, i, scene);
	return (vec);
}

// Helper function to validate FOV
void	validate_fov(float fov, t_scene *scene)
{
	if (fov < 0.0 || fov > 180.0)
		error("Camera FOV out of range [0.0, 180.0]", scene);
}

// Helper function to validate the end of line
void	validate_end_of_line(char *line, int i, t_scene *scene)
{
	while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
		i++;
	if (line[i] != '\0')
		error("Invalid character in camera definition", scene);
}

// Function to parse the camera
void	parse_camera(char *line, t_camera *camera, t_scene *scene)
{
	int	i;

	i = 0;
	skip_whitespacess(&line, &i);
	validate_identifier(line[i], 'C', scene);
	i++;
	skip_whitespacess(&line, &i);
	camera->center = parse_vector(&line, &i, scene);
	camera->orientation = parse_vector(&line, &i, scene);
	camera->fov = parse_float_with_check(&line, &i, scene);
	validate_fov(camera->fov, scene);
	validate_end_of_line(line, i, scene);
	print_camera(camera);
}
