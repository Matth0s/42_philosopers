# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/08 10:23:00 by mmoreira          #+#    #+#              #
#    Updated: 2021/12/16 17:20:12 by mmoreira         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#--------------------------------------//---------------------------------------
SRC_DIR	=	./sources
SRC		=	philo.c \
			init_components.c \
			start_simulation.c \
			actions_loop.c \
			actions_die_print.c \
			destroy_components.c \
			utils.c

OBJ_DIR	=	./builds
OBJ		=	$(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

INCD_DIR=	./includes
INCD	=	philo.h
#--------------------------------------//---------------------------------------
vpath %.c $(SRC_DIR)
vpath %.h $(INCD_DIR)

NAME	=	philo

CFLAGS	=	-Wall -Wextra -Werror -g3 -fsanitize=address

FLAGS	=	-pthread

RM		=	rm -rf

CC		=	clang
#--------------------------------------//---------------------------------------
all:			$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) $(FLAGS) $(OBJ) -I $(INCD_DIR) -o $(NAME)
	@echo ""
	@echo "/ ************************************ \\"
	@echo "|             philo Criado             |"
	@echo "\\ ************************************ /"
	@echo ""

$(OBJ_DIR)/%.o:	%.c $(INCD)
	mkdir -p $(OBJ_DIR)
	$(CC) -c -o $@ $(CFLAGS) -I $(INCD_DIR) $<
#--------------------------------------//---------------------------------------
clean:
	$(RM) $(OBJ_DIR)
	@echo ""
	@echo "/ ************************************ \\"
	@echo "|        Arquivos .o Deletados         |"
	@echo "\\ ************************************ /"
	@echo ""

fclean:		clean
	$(RM) $(NAME)
	@echo ""
	@echo "/ ************************************ \\"
	@echo "|            philo Deletado            |"
	@echo "\\ ************************************ /"
	@echo ""
#--------------------------------------//---------------------------------------

re:			fclean all

git:
	@git add .
	@git status
	@git commit -m "$m"

.PHONY:		all clean fclean re git
