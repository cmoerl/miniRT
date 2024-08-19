/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marianfurnica <marianfurnica@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 08:41:08 by marianfurni       #+#    #+#             */
/*   Updated: 2024/08/19 13:58:03 by marianfurni      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	parse_intensity(char *line, int *i, float *intensity)
{
	int	start;

	start = *i;
	while (line[*i] && (ft_isdigit(line[*i])
			|| line[*i] == '.' || line[*i] == '-' || line[*i] == '+'))
		(*i)++;
	if (start == *i)
		error("Invalid character in ambient lighting definition", NULL);
	*intensity = ft_atof(&line[start]);
	if (*intensity < 0.0 || *intensity > 1.0)
		error("Ambient lighting intensity out of range [0.0, 1.0]", NULL);
}

void	parse_color_value(char *line, int *i,
			int *color_value, const char *color_name)
{
	int	start;

	start = *i;
	while (line[*i] && ft_isdigit(line[*i]))
		(*i)++;
	if (start == *i)
		error("Invalid character in ambient lighting definition", NULL);
	*color_value = ft_atoi(&line[start]);
	if (*color_value < 0 || *color_value > 255)
	{
		printf("Error: Ambient lighting %s value out of range [0, 255]\n",
			color_name);
		error(NULL, NULL);
	}
}

void	parse_ambient(char *line, t_amblight *ambient)
{
    int i;
    float intensity;
    int r, g, b;

    i = 0;
    skip_whitespace(line, &i);
    if (line[i] != 'A')
        error("Missing 'A' identifier for ambient lighting", NULL);
    i++;
    skip_whitespace(line, &i);
    parse_intensity(line, &i, &intensity);
    skip_whitespace(line, &i);
    parse_color_value(line, &i, &r, "red");
    while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == ','))
        i++;
    parse_color_value(line, &i, &g, "green");
    while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == ','))
        i++;
    parse_color_value(line, &i, &b, "blue");
    while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
        i++;
    if (line[i] != '\0')
        error("Invalid character in ambient lighting definition", NULL);
    ambient->intensity = intensity;
    ambient->color.r = r / 255.0;
    ambient->color.g = g / 255.0;
    ambient->color.b = b / 255.0;
    printf("Parsed Ambient Lighting:\n");
    printf("  Intensity: %f\n", intensity);
    printf("  Color: R=%d, G=%d, B=%d\n", r, g, b);
    printf("  Normalized Color: R=%f, G=%f, B=%f\n", ambient->color.r, ambient->color.g, ambient->color.b);
}