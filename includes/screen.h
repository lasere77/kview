#ifndef SCREEN_H
# define SCREEN_H

# define ALF		4278190080
# define RED		16711680
# define GREEN	65280 
# define BLUE	255
# define WHITE	-1

# include <sys/mman.h>
# include <sys/ioctl.h>
# include <linux/fb.h>

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdint.h>

//get writable screen memory; uint32_t here for 32bit color
// A(alpha)	R(rouge) G(vers)  B(blue)
// 00000000 00000000 00000000 00000000
typedef struct	s_screen
{
	struct fb_var_screeninfo	var_info;			/*variable info device form ioctl*/
	uint32_t					*display;			/*shared memory mapped with the device*/
	size_t						screen_size;		/*sizeof mapped-memory*/
}								t_screen;

void	rectangle_display(const t_screen *screen, const uint32_t x, const uint32_t y, const uint32_t w, const uint32_t h, const uint32_t color);
void	get_device(t_screen *screen);

#endif