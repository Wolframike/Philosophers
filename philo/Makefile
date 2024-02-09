# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/02 02:21:44 by misargsy          #+#    #+#              #
#    Updated: 2024/02/07 16:37:42 by misargsy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS		= -Wall -Wextra -Werror

NAME		= philo
SRCS		=	philosophers.c \
				philo_lib_1.c \
				philo_lib_2.c \
				philo_feast.c \
				philo_parse.c \
				philo_utils.c \
				philo_init.c \
				philo_logs.c

OBJS		= $(SRCS:.c=.o)

GRAY		= \033[1;37m
CYAN		= \033[1;36m
MAGENTA		= \033[1;35m
BLUE		= \033[1;34m
YELLOW		= \033[1;33m
GREEN		= \033[1;32m
RED			= \033[1;31m
RESET		= \033[0m
MAX			= 50
CONVERSION	= %-$(MAX).$(MAX)s\r

all: $(NAME)

$(NAME): $(OBJS)
	@printf "$(YELLOW)Compiling $@... $(CONVERSION)$(RESET)"
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS)
	@printf "$(GREEN)⪼ $(NAME): compilation done ⪻$(CONVERSION)$(RESET)\n"

%.o: %.c
	@printf "$(YELLOW)Compiling $<... $(CONVERSION)$(RESET)"
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@$(RM) -r $(OBJSDIR)
	@$(RM) $(OBJS)
	@printf "$(RED)Removed $(NAME)'s object files$(RESET)\n"

fclean: clean
	@$(RM) $(NAME)
	@printf "$(RED)Removed $(NAME)$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re
