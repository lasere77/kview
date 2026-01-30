#include "image.h"

#include "libft.h"
#include "get_next_line.h"
#include "ft_printf.h"

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>

#define WHITE_SPACE "\t\n\v\f\r \0"

#include <stdio.h>

static char	*get_next_data(const int fd, char *charset)
{
	char	*result;

	result = get_next_line(fd, charset);
	while (result[0] && (result[0] == '#' || !result[1]))
	{
		free(result);
		result = get_next_line(fd, WHITE_SPACE);
	}
	return (result);
}

static void	get_max_color_image(t_image *image)
{
	char *data;

	data = get_next_data(image->fd_image, WHITE_SPACE);
	image->max_color_value = ft_atoi(data);
	free(data);
	printf("color max: {%d}\n", image->max_color_value);
}

static void	get_image_size(t_image *image)
{
	char	*data;

	data = get_next_data(image->fd_image, WHITE_SPACE);
	image->width = ft_atoi(data);
	free(data);
	data = get_next_data(image->fd_image, WHITE_SPACE);
	image->height = ft_atoi(data);
	free(data);
	printf("w: {%d}, h: {%d}\n", image->width, image->height);
}

static uint8_t	check_magic_number(int fd)
{
	uint8_t	result;
	char	*str;

	str = get_next_line(fd, WHITE_SPACE);
	result = ft_strncmp(str, "P6", 2);
	free(str);
	return (result);
}

void	init_image_info(char *file_path, t_image *image)
{
	image->fd_image = 0;
	if (file_path)
		image->fd_image = open(file_path, O_RDONLY);
	if (image->fd_image == -1)
	{
		ft_printfd(2, "cannot open: %s\n", file_path);
		exit(1);
	}
	if (check_magic_number(image->fd_image))
	{
		write(2, "This file is not supported by kview\n", 36);
		exit(1);
	}
	write(1, "valid format image.\n", 20);
	get_image_size(image);
	get_max_color_image(image);
}
