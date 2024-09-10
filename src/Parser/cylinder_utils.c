/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:34:34 by marianfurni       #+#    #+#             */
/*   Updated: 2024/09/10 15:30:26 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	validate_cylinder_identifier(char *line, int *i)
{
	skip_whitespace(line, i);
	if (line[*i] != 'c' || line[*i + 1] != 'y')
		error("Missing 'cy' identifier for cylinder", NULL, line);
	*i += 2;
}

float parse_float(char *line, int *i, char *error_message, t_scene *scene)
{
    int start;
    int dot_count = 0;

    start = *i;
    while (line[*i] && (ft_isdigit(line[*i]) || line[*i] == '.' || line[*i] == '-' || line[*i] == '+'))
    {
        if (line[*i] == '.')
            dot_count++;
        (*i)++;
    }
    if (start == *i || dot_count > 1)
        error(error_message, scene, line);
    return (ft_atof(&line[start]));
}

void	parse_center(char *line, int *i, t_cylinder *cylinder, t_scene *scene)
{
	cylinder->center.x = parse_float(line, i,
			"Invalid character in cylinder definition", scene);
	skip_whitespace(line, i);
	if (line[*i] == ',')
		(*i)++;
	skip_whitespace(line, i);
	cylinder->center.y = parse_float(line, i,
			"Invalid character in cylinder definition", scene);
	skip_whitespace(line, i);
	if (line[*i] == ',')
		(*i)++;
	skip_whitespace(line, i);
	cylinder->center.z = parse_float(line, i,
			"Invalid character in cylinder definition", scene);
}

void	parse_axis(char *line, int *i, t_cylinder *cylinder, t_scene *scene)
{
	cylinder->axis.x = parse_float(line, i,
			"Invalid character in cylinder definition", scene);
	skip_whitespace(line, i);
	if (line[*i] == ',')
		(*i)++;
	skip_whitespace(line, i);
	cylinder->axis.y = parse_float(line, i,
			"Invalid character in cylinder definition", scene);
	skip_whitespace(line, i);
	if (line[*i] == ',')
		(*i)++;
	skip_whitespace(line, i);
	cylinder->axis.z = parse_float(line, i,
			"Invalid character in cylinder definition", scene);
	if (cylinder->axis.x < -1 || cylinder->axis.x > 1
		|| cylinder->axis.y < -1 || cylinder->axis.y > 1
		|| cylinder->axis.z < -1 || cylinder->axis.z > 1)
		error("Cylinder axis values out of range [-1, 1]", scene, line);
	// cylinder->axis = normalise_vector(cylinder->axis);
}

void	add_cylinder_to_list(t_cylinder **cylinders, t_cylinder *new_cylinder)
{
	t_cylinder	*current;

	new_cylinder->next = NULL;
	if (*cylinders == NULL)
	{
		*cylinders = new_cylinder;
	}
	else
	{
		current = *cylinders;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new_cylinder;
	}
}
