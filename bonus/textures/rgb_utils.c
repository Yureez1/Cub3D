/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leaugust <leaugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 21:12:10 by leaugust          #+#    #+#             */
/*   Updated: 2025/07/16 16:09:52 by leaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

static int	convert_rgb(unsigned int r, unsigned int g, unsigned int b)
{
	if (r > 255 || g > 255 || b > 255)
		return (-1);
	return ((r << 16) | (g << 8) | b);
}

static void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

int	parse_rgb(const char *str, int *res)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	rgb = ft_split(str, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (free_split(rgb), printf("Error: Invalid RGB format\n"), 1);
	if (rgb[0][0] == '\0' || rgb[1][0] == '\0' || rgb[2][0] == '\0')
		return (free_split(rgb), printf("Error: Empty RGB value\n"), 1);
	if (has_leading_zero(rgb[0]) || has_leading_zero(rgb[1])
		|| has_leading_zero(rgb[2]))
		return (free_split(rgb), 1);
	if (!is_valid_number(rgb[0]) || !is_valid_number(rgb[1])
		|| !is_valid_number(rgb[2]))
		return (free_split(rgb), printf("Error: RGB values must be numbers\n"),
			1);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (free_split(rgb), printf("Error: RGB value out of range\n"), 1);
	*res = convert_rgb(r, g, b);
	return (free_split(rgb), 0);
}

int	check_exist_textures(t_texpath *texpath)
{
	int	fd;

	fd = open(texpath->no, O_RDONLY);
	if (fd < 0)
		return (printf("Error : Cannot open NO texture file\n"), 1);
	close(fd);
	fd = open(texpath->so, O_RDONLY);
	if (fd < 0)
		return (printf("Error: Cannot open SO texture file\n"), 1);
	close(fd);
	fd = open(texpath->we, O_RDONLY);
	if (fd < 0)
		return (printf("Error: Cannot open WE texture file\n"), 1);
	close(fd);
	fd = open(texpath->ea, O_RDONLY);
	if (fd < 0)
		return (printf("Error: Cannot open EA texture file\n"), 1);
	close(fd);
	return (0);
}

int	check_xpm_file(const char *file_path)
{
	size_t		len;
	const char	*ext;

	len = ft_strlen(file_path);
	ext = file_path + len - 4;
	if (!file_path || ft_strlen(file_path) < 4)
		return (printf("Invalid file path"), 1);
	if (ft_strncmp(ext, ".xpm", 4) != 0 && ft_strncmp(ext, ".XPM", 4) != 0)
		return (1);
	return (0);
}
