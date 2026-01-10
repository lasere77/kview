CC=cc
CFLAGS=-Wall -Wextra -Werror -I includes/
SRCS_DIR=srcs/
NAME=kview
SOURCES=$(SRCS_DIR)kview.c		

OBJ_DIR = .build/
OBJS = $(SOURCES:$(SRCS_DIR)%.c=$(OBJ_DIR)%.o)

INCLUDES = -I includes/ -I libft/includes/
LIBS = libft/libft.a

DEPS = $(SOURCES:$(SRCS_DIR)%.c=$(OBJ_DIR)%.d)

CFLAGS = -MP -MMD -Wall -Werror -Wextra -g $(INCLUDES)

all: $(NAME)

$(NAME): make_dir $(OBJS)
	$(MAKE) --no-print-directory -C libft/
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

make_dir:
	@mkdir -p .build/

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c
	$(CC) $(CFLAGS) $< -c -o $@

fclean: clean
	$(MAKE) clean --no-print-directory -C libft/
	rm -rf $(NAME)

clean:
	$(MAKE) fclean --no-print-directory -C libft/
	rm -rf $(OBJ_DIR)

re: fclean all

.PHONY: re clean fclean all make_dir

-include $(DEPS)