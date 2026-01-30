#include "screen.h"
#include "image.h"

#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>

int	main(int argc, char *argv[])
{
	t_screen	screen;
	t_image		image;
	(void)argc;

	init_image_info(argv[1], &image);
	get_device(&screen);
	// rectangle_display(&screen, 100, 100, 100, 100, -1);
	munmap(screen.display, screen.screen_size);
	return (0);
}
