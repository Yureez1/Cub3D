/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbanchon <jbanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:12:16 by leaugust          #+#    #+#             */
/*   Updated: 2025/07/15 13:50:24 by jbanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

int	handle_ceiling(t_texpath *texpath, char *line)
{
	char	*trimmed;

	if (texpath->ceiling)
	{
		printf("Error: Duplicate C\n");
		return (1);
	}
	trimmed = ft_strtrim(line + 1, " \t\n");
	if (!trimmed)
	{
		printf("Error: Invalid ceiling color format\n");
		return (1);
	}
	if (parse_rgb(trimmed, &texpath->ceiling_rgb))
	{
		free(trimmed);
		return (1);
	}
	texpath->ceiling = trimmed;
	return (0);
}

int	handle_floor(t_texpath *texpath, char *line)
{
	char	*trimmed;

	if (texpath->floor)
	{
		printf("Error: Duplicate F\n");
		return (1);
	}
	trimmed = ft_strtrim(line + 1, " \t\n");
	if (!trimmed)
	{
		printf("Error: Invalid floor color format\n");
		return (1);
	}
	if (parse_rgb(trimmed, &texpath->floor_rgb))
	{
		free(trimmed);
		return (1);
	}
	texpath->floor = trimmed;
	return (0);
}

int	destroy_texpath(t_texpath *texpath)
{
	if (texpath == NULL)
		return (printf("Error : Texpath is NULL\n"), 1);
	if (texpath->no)
		free(texpath->no);
	if (texpath->so)
		free(texpath->so);
	if (texpath->we)
		free(texpath->we);
	if (texpath->ea)
		free(texpath->ea);
	if (texpath->floor)
		free(texpath->floor);
	if (texpath->ceiling)
		free(texpath->ceiling);
	return (0);
}

int	has_leading_zero(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	if (str[i] == '0' && str[i + 1] && str[i + 1] >= '0' && str[i + 1] <= '9')
		return (1);
	return (0);
}

int	is_valid_number(const char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
				i++;
			if (str[i] != '\0')
				return (0);
			break ;
		}
		i++;
	}
	return (1);
}
