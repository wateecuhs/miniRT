SRCS			=	miniRT.c $(SRCS_PARSING) $(SRCS_LIB) $(SRCS_GNL) $(SRCS_WINDOW)

SRCS_PARSING	=	parsing/parsing.c \
					parsing/A_C_L_identifiers.c

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
					lib/ft_numbers.c

SRCS_GNL		=	get_next_line/get_next_line_utils.c \
					get_next_line/get_next_line.c