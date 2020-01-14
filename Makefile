YELLOW = \033[1;33m
CYAN = \033[1;36m
RED = \033[1;31m
GREEN = \033[1;32m
EOC = \033[1;0m

NAME = ft_select

CC = gcc

FLAGS = -Wall -Wextra -Werror

SELECT = main init_free write_args draw_state ncanonic print_selected\
		 signals tools events search_engine termcaps launch_select\
		 cursor exit\
		 delete_me\

SRC = $(addprefix srcs/, $(addsuffix .c, $(SELECT)))

OBJ = $(addprefix srcs/, $(addsuffix .o, $(SELECT)))

all : $(NAME)

$(NAME) : $(OBJ)
		@make -C ./libft
		@$(CC) -o $(NAME) $(OBJ) -ltermcap -L ./libft -lft
		@echo "$(GREEN)"
		@echo "    __ _              _           _    "
		@echo "   / _| |            | |         | |   "
		@echo "  | |_| |_   ___  ___| | ___  ___| |_  "
		@echo "  |  _| __| / __|/ _ \ |/ _ \/ __| __| "
		@echo "  | | | |_  \__ \  __/ |  __/ (__| |_  "
		@echo "  |_|  \__| |___/\___|_|\___|\___|\__| "
		@echo "        ______                         "
		@echo "       |______|  $(EOC)     by: $(CYAN)obelouch$(EOC) "
		@echo "$(YELLOW)                              "
		@echo "   Selecting is much easier and funny! "
		@echo "$(EOC)                                 "
		@echo "                                       "

$(OBJ) : srcs/%.o : srcs/%.c
		@$(CC) -c $< $(FLAGS) -o $@ -I ./libft/includes -I ./includes/

clean :
		@/bin/rm -f $(OBJ)
		@make -C ./libft clean
		@echo "$(YELLOW)Clean the Workspace$(EOC)"

fclean : clean
		@/bin/rm -f $(NAME)
		@make -C ./libft fclean
		@echo "$(RED)Totaly Cleaned ft_select$(EOC)"

re : fclean all
