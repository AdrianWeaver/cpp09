NAME = btc

CXX = c++

CXXFLAGS	= -Wall -Wextra -Werror -std=c++98 -g3
CPPFLAGS	= -MMD

SRCS		=	main.cpp


OBJS = $(SRCS:.cpp=.o)
DEPS = $(OBJS:.o=.d)


all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(@)

clean:
	rm -f $(OBJS)
	rm -f $(DEPS)

fclean: clean
	rm -f $(NAME)

re: fclean
	make all

test:	$(NAME)
		./$(NAME) tofind

vtest:	$(NAME)
		valgrind --leak-check=full ./$(NAME)

-include $(DEPS)

.PHONY: all clean fclean re test vtest
