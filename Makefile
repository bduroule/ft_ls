# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: beduroul <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/03/29 18:42:45 by beduroul     #+#   ##    ##    #+#        #
#    Updated: 2019/03/29 18:42:47 by beduroul    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #


NAME = ft_ls

#Color
BLUE 	= \033[2K\r\033[36m
GREEN 	= \e[92m
WITHE 	= \033[37m
YELLOW	= \033[33m
END 	= \033[0m

#Dir
OBJ_PATH = ./obj/
SRC_PATH = ./srcs/
INC_PATH = ./include/

#file
SRC_NAME = 	main.c 			\
			parsing.c		\
			display.c		\
			ls_permission.c	\
			list_sort.c		\
			list.c			\
			browse.c		\
			display_ls_l.c	\
			ls_l_str.c		\
			ls_color.c		\
			option.c		\
			sort_param.c

# ft library
FT        = ./libft/
FT_LIB    = $(addprefix $(FT),libft.a)
FT_INC    = -I ./libft
FT_LNK    = -L ./libft -l ft
REQUIRED  = include/ft_ls.h include/struct.h libft/libft.a
#add
SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ	= $(addprefix $(OBJ_PATH), $(SRC_NAME:.c=.o))

#compil
CC = gcc
CFLAGS =  -Wextra -Wall -Werror $(INC_HDR)

all: make_libft $(NAME)

make_libft:
	@make -C libft/

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(REQUIRED)
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(FT_INC) -I $(INC_PATH)  -o $@ -c $<
	@printf "$(BLUE)>>Compiling $(WITHE) $< $(END)"

$(NAME): $(OBJ)
	@$(MAKE) -C libft
	@$(CC) $(CFLAGS) $(OBJ) $(FT_LNK) -o $(NAME)
	@printf "$(YELLOW)$(NAME)$(END)		$(GREEN)[compiled]$(END)\n"

clean:
	@rm -rf $(OBJ_PATH)
	@cd libft && $(MAKE) clean

fclean: clean
	@rm -f $(NAME)
	@cd libft && $(MAKE) fclean

re: fclean all
