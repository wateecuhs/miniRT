NAME				=	miniRT

include config/srcs.mk
SRC_PATH			=	srcs/
DIR_BUILD			=	.build/
OBJS				=	$(patsubst %.c, $(DIR_BUILD)%.o, $(SRCS))
OBJS_TEST			=	$(patsubst %.c, $(DIR_BUILD)%.o, $(TEST))
DEPS				=	$(patsubst %.c, $(DIR_BUILD)%.d, $(SRCS))
DEPS_FLAGS			=	-MMD -MP
BASE_CFLAGS			=	-g3 -Wall -Wextra #-Werror
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
debug:
			$(MAKE) -j FLAGS="$(DEBUG_CLFAGS)"

.PHONY:	re
re:		fclean
			$(MAKE) all

-include $(DEPS)
$(DIR_BUILD)%.o : $(SRC_PATH)%.c
			@mkdir -p $(shell dirname $@)
			$(CC) $(FLAGS) $(DEPS_FLAGS) $(INCLUDES) -c $< -o $@
