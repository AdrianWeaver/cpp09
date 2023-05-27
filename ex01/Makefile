NAME = RPN

CXX = c++

CXXFLAGS	= -Wall -Wextra -Werror -std=c++98 -g3
CPPFLAGS	= -MMD

SRCS		=	main.cpp\
				RPN.cpp


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
		./$(NAME) "8 9 * 9 - 9 - 9 - 4 - 1 +"
		./$(NAME) "7 7 * 7 -"
		./$(NAME) "1 2 * 2 / 2 * 2 4 - +"
		./$(NAME) "(1 + 1)"

vtest:	$(NAME)
		valgrind --leak-check=full ./$(NAME)

-include $(DEPS)

.PHONY: all clean fclean re test vtest
