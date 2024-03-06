NAME				=	miniRT

SRCS			=	miniRT.c $(SRCS_PARSING) $(SRCS_LIB) $(SRCS_GNL) $(SRCS_WINDOW) $(SRCS_RENDER) $(SRCS_INTERSECTIONS)

SRCS_PARSING	=	parsing/parsing.c \
					parsing/scene_identifiers.c \
					parsing/objects_identifiers.c \
					parsing/parsing_tools.c

SRCS_WINDOW		=	window_handlers/set_hooks.c \
					window_handlers/init.c \
					window_handlers/render_image.c

SRCS_RENDER		=	render/draw_pixel.c \
					render/render_pixel.c \
					render/calc_ray.c \
					render/light_calculations.c \
					render/light_calculations2.c
				
SRCS_INTERSECTIONS =	intersections/cylinder_intersection.c \
					intersections/plane_intersection.c \
					intersections/sphere_intersection.c 

SRCS_LIB		=	lib/ft_strcmp.c \
					lib/ft_strchr.c \
					lib/ft_strlen.c \
					lib/ft_strdup.c \
					lib/errors.c \
					lib/init_structs.c \
					lib/is_digit.c \
					lib/is_float.c \
					lib/frees.c \
					lib/ft_substr.c \
					lib/ft_split.c \
					lib/ft_numbers.c \
					lib/lst.c \
					lib/vectors_operations2.c \
					lib/vectors_operations.c \
					lib/colors.c \
					lib/vectors_operations3.c

SRCS_GNL		=	get_next_line/get_next_line_utils.c \
					get_next_line/get_next_line.c

SRC_PATH			=	srcs/
DIR_BUILD			=	.build/
OBJS				=	$(patsubst %.c, $(DIR_BUILD)%.o, $(SRCS))
OBJS_TEST			=	$(patsubst %.c, $(DIR_BUILD)%.o, $(TEST))
DEPS				=	$(patsubst %.c, $(DIR_BUILD)%.d, $(SRCS))
DEPS_FLAGS			=	-MMD -MP
BASE_CFLAGS			=	-g3 -Wall -Wextra -Werror
BASE_DEBUG_CFLAGS	=	-g3
DEBUG_CLFAGS		=	$(BASE_DEBUG_CFLAGS) -fsanitize=address
FLAGS				=	$(BASE_CFLAGS)
RM					=	rm -rf

MINILIBX_PATH		=	minilibx/
MINILIBX_INCLUDES	=	$(MINILIBX_PATH)
MINILIBX_L			=	-L $(MINILIBX_PATH) -l mlx
MINILIBX_A			=	$(MINILIBX_PATH)libmlx.a
MAKE_MINILIBX		=	$(MAKE) -C $(MINILIBX_PATH)

DIR_INCS =\
	includes/			\
	$(MINILIBX_INCLUDES)
INCLUDES =\
	$(addprefix -I , $(DIR_INCS))

LIBS = \
	-lm	\
	$(MINILIBX_L)	\
	-lXext	\
	-lX11

DEPENDENCIES =\
	$(MINILIBX_A)

.PHONY:		all
all:
			$(MAKE_MINILIBX)
			$(MAKE) $(NAME)

test:	$(OBJS_TEST)
	$(CC) $(FLAGS) $(INCLUDES) $(OBJS_TEST) $(LIBS) -o $(NAME)	

$(NAME):	$(OBJS)
	$(CC) $(FLAGS) $(INCLUDES) $(OBJS) $(LIBS) -o $(NAME)

.PHONY:	clean
clean:
			$(MAKE_MINILIBX) clean
			$(RM) $(DIR_BUILD)

.PHONY:	fclean
fclean:	clean
			$(RM) $(NAME)

.PHONY:	debug
debug:	fclean
			$(MAKE) -j FLAGS="$(DEBUG_CLFAGS)"

.PHONY:	re
re:		fclean
			$(MAKE) all

-include $(DEPS)
$(DIR_BUILD)%.o : $(SRC_PATH)%.c
			@mkdir -p $(shell dirname $@)
			$(CC) $(FLAGS) $(DEPS_FLAGS) $(INCLUDES) -c $< -o $@
