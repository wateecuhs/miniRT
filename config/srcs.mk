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
