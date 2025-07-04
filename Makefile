# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/10 07:22:39 by tchartie          #+#    #+#              #
#    Updated: 2025/06/27 18:50:37 by tchartie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#============ NAME ============#

NAME			= 	ft_shmup

#========= COMPILATOR =========#

CC 				= 	c++

#=========== FLAGS ============#

INC				= 	inc/
CFLAGS 			= 	-I$(INC) -Wall -Werror -Wextra -std=c++98 -g
LDFLAGS			= 	-lncursesw

MAKEFLAGS		=	--no-print-directory

#=========== COLOR ============#

BASE_COLOR 		=	\033[0;39m
GRAY 			=	\033[0;90m
RED 			=	\033[0;91m
GREEN 			=	\033[0;92m
YELLOW 			=	\033[0;93m
BLUE 			=	\033[0;94m
MAGENTA			=	\033[0;95m
CYAN 			=	\033[0;96m
WHITE			=	\033[0;97m

#========== SOURCES ===========#

SRC_DIR 		= 	src/
SRC_NAME 		=	main.cpp \
					utils.cpp \
					display.cpp \
					Game.cpp \
					Scoreboard.cpp \
					Entity.cpp \
					Player.cpp \
					Projectile.cpp \
					Wall.cpp

OBJ_DIR 		=	obj/
OBJ_NAME		=	$(SRC_NAME:.cpp=.o)
OBJ				=	$(patsubst %, $(OBJ_DIR)%, $(OBJ_NAME))

all:		$(NAME)

$(NAME):	$(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)
	@echo "$(GREEN)ft_shmup successfully compiled! $(BASE_COLOR)"

$(OBJ_DIR)%.o:$(SRC_DIR)%.cpp
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling: $< $(BASE_COLOR)"
	@$(CC) $(CFLAGS) $< -c -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(BLUE)ft_shmup objects files cleanned! $(BASE_COLOR)"

fclean:		clean
	@rm -f $(NAME)
	@echo "$(CYAN)ft_shmup executable file cleanned! $(BASE_COLOR)"


re: 		fclean all

.PHONY :	all clean fclean re