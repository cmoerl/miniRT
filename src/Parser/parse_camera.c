/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 23:38:31 by marianfurni       #+#    #+#             */
/*   Updated: 2024/09/10 12:33:10 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

// Helper function to validate the line for multiple consecutive signs or dots
void	validate_line_format(char *line, t_scene *scene)
{
	int	i;

	scene->flags.dot_count = 0;
	scene->flags.sign_count = 0;
	scene->flags.comma_count = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '.')
			scene->flags.dot_count++;
		else if (line[i] == '-')
			scene->flags.sign_count++;
		else if (line[i] == ',')
			scene->flags.comma_count++;
		if ((line[i] == '+' || line[i] == '-'
				|| line[i] == '.' || line[i] == ',')
			&& (line[i] == line[i + 1]))
			error("Multiple consecutive signs or dots in line", scene, line);
		if ((line[i] == '+' && line[i + 1] == '-')
			|| (line[i] == '-' && line[i + 1] == '+'))
			error("Invalid sign sequence in line", scene, line);
		i++;
	}
}

// Helper function to validate identifier
void	validate_identifier(char actual, char expected)
{
	if (actual != expected)
		error("Invalid identifier", NULL, NULL);
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
void	validate_fov(float fov, t_scene *scene, char *line)
{
	if (fov < 0.0 || fov > 180.0)
		error("Camera FOV out of range [0.0, 180.0]", scene, line);
}

// Function to parse the camera
void	parse_camera(char *line, t_camera *camera, t_scene *scene)
{
	int	i;

	i = 0;
	skip_whitespace(line, &i);
	validate_identifier(line[i], 'C');
	i++;
	if (line[i] != ' ')
		error("Missing space after 'C' identifier for camera", scene, line);
	validate_line_format(line, scene);
	skip_whitespace(line, &i);
	camera->center = parse_vector(&line, &i, scene);
	camera->orientation = parse_vector(&line, &i, scene);
	if (camera->orientation.x == 0
		&& camera->orientation.y == 0 && camera->orientation.z == 0)
		error("Camera orientation cannot be zero", scene, line);
	if (camera->orientation.x < -1 || camera->orientation.x > 1
		|| camera->orientation.y < -1 || camera->orientation.y > 1
		|| camera->orientation.z < -1 || camera->orientation.z > 1)
		error("Camera orientation out of range [-1.0, 1.0]", scene, line);
	camera->orientation = normalise_vector(camera->orientation);
	camera->fov = parse_float_with_check(&line, &i, scene);
	validate_fov(camera->fov, scene, line);
	validate_end_of_line(line, i, scene);
}
