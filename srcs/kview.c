#include "screen.h"
#include "image.h"

#include <stddef.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>

/*do not touch the 8 MSB*/
static inline uint32_t	get_rgb_color(uint8_t *data, uint8_t color_max)
{
	(void)color_max;
	return ((data[0] << 16) | (data[1] << 8) | data[2]);
}

/*3*x with x the divise of the image*/
#define DATA_PER_PIXEL 3*1

static void	draw(t_screen *screen, t_image *image)
{
	size_t	current_line;
	size_t	current_column;
	uint8_t	data[DATA_PER_PIXEL];

	current_line = 0;
	while (current_line < image->height)
	{
		current_column = 0;
		while (current_column < image->width)
		{
			if (read(image->fd_image, data, DATA_PER_PIXEL) != DATA_PER_PIXEL)
				break ;
			rectangle_display(screen, current_column, current_line, 1, 1, get_rgb_color(data, image->max_color_value));
			current_column++;
		}
		current_line++;
	}
}

int	main(int argc, char *argv[])
{
	t_screen	screen;
	t_image		image;
	(void)argc;

	init_image_info(argv[1], &image);
	get_device(&screen);
	draw(&screen, &image);
	munmap(screen.display, screen.screen_size);
	return (0);
}
