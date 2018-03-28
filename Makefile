# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyork <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/09 13:08:18 by kyork             #+#    #+#              #
#    Updated: 2018/03/28 10:32:07 by kyork            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = abstract-vm

$(NAME): Build/Makefile
	make -C Build $(NAME)

all: $(NAME)

Build/Makefile: CMakeLists.txt
	mkdir -p Build
	cd Build && sh -c 'cmake ..'

clean:
	make -C Build clean

fclean:
	rm -rf Build

re: fclean all

format:
	clang-format -style=file -i src/*.cpp src/*.hpp

