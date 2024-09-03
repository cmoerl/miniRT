/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafurnic <mafurnic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 23:38:31 by marianfurni       #+#    #+#             */
/*   Updated: 2024/09/03 12:10:21 by mafurnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"


// Helper function to parse a float with validation
float	parse_float_with_checks(char **line, int *i, t_scene *scene)
{
    int		start;
    float	value;
    int		sign_count = 0;
    int		dot_count = 0;

    start = *i;
    while ((*line)[*i] && (ft_isdigit((*line)[*i])
        || (*line)[*i] == '.' || (*line)[*i] == '-' || (*line)[*i] == '+'))
    {
        if ((*line)[*i] == '-' || (*line)[*i] == '+')
        {
            if (sign_count > 0)
                error("Multiple signs in number", scene, *line);
            sign_count++;
        }
        if ((*line)[*i] == '.')
        {
            if (dot_count > 0)
                error("Multiple dots in number", scene, *line);
            dot_count++;
        }
        (*i)++;
    }
    if (start == *i)
        error("Error: Invalid character in camera definition", scene, *line);
    value = ft_atof(&(*line)[start]);
    if ((*line)[*i] == ',')
        (*i)++;
    skip_whitespacess(line, i);
    return (value);
}
// Helper function to validate the line for multiple consecutive signs or dots
void	validate_line_format(char *line, t_scene *scene)
{
    scene->flags.dot_count = 0;
    scene->flags.sign_count = 0;
    scene->flags.comma_count = 0;

    int i = 0;
    while (line[i])
    {
        if (line[i] == '.')
            scene->flags.dot_count++;
        else if (line[i] == '+' || line[i] == '-')
            scene->flags.sign_count++;
        else if (line[i] == ',')
            scene->flags.comma_count++;

        if ((line[i] == '+' || line[i] == '-' || line[i] == '.' || line[i] == ',') &&
            (line[i] == line[i + 1]))
        {
            error("Multiple consecutive signs or dots in line", scene, line);
        }
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

	vec.x = parse_float_with_checks(line, i, scene);
	vec.y = parse_float_with_checks(line, i, scene);
	vec.z = parse_float_with_checks(line, i, scene);
	return (vec);
}

// Helper function to validate FOV
void	validate_fov(float fov, t_scene *scene, char *line)
{
	if (fov < 0.0 || fov > 180.0)
		error("Camera FOV out of range [0.0, 180.0]", scene, line);
}

// Helper function to validate the end of line
void	validate_end_of_line(char *line, int i, t_scene *scene)
{
	while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
		i++;
	if (line[i] != '\0')
		error("Invalid character in camera definition", scene, line);
}

// Function to parse the camera
void	parse_camera(char *line, t_camera *camera, t_scene *scene)
{
	int	i;

	i = 0;
	skip_whitespacess(&line, &i);
	validate_identifier(line[i], 'C');
	i++;
	validate_line_format(line, scene);
	skip_whitespacess(&line, &i);
	camera->center = parse_vector(&line, &i, scene);
	camera->orientation = parse_vector(&line, &i, scene);
	if (camera->orientation.x == 0
		&& camera->orientation.y == 0 && camera->orientation.z == 0)
		error("Camera orientation cannot be zero", scene, line);
	// camera->orientation = normalise_vector(camera->orientation);
	camera->fov = parse_float_with_checks(&line, &i, scene);
	validate_fov(camera->fov, scene, line);
	validate_end_of_line(line, i, scene);
}
