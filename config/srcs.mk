SRCS			=	miniRT.c $(SRCS_PARSING) $(SRCS_LIB) $(SRCS_GNL) $(SRCS_WINDOW) $(SRCS_TMP)

SRCS_PARSING	=	parsing/parsing.c \
					parsing/scene_identifiers.c \
					parsing/objects_identifiers.c \
					parsing/parsing_tools.c

SRCS_WINDOW		=	window_handlers/set_hooks.c

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
					lib/lst.c

SRCS_GNL		=	get_next_line/get_next_line_utils.c \
					get_next_line/get_next_line.c

SRCS_TMP		=	lib/print_scene.c