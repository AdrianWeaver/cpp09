NAME = PmergeMe

CXX = c++

CXXFLAGS	= -Wall -Wextra -Werror -std=c++98 -g3
CPPFLAGS	= -MMD

SRCS		=	main.cpp\
				PmergeMe.cpp


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
		./$(NAME) 3 5 9 7 4
		./$(NAME) `shuf -i 1-100000 -n 3000 | tr "\n" " "`
		./$(NAME) "-1" "2"
		./$(NAME) `jot -r 3000 1 100000 | tr '\n' ' '`

vtest:	$(NAME)
		valgrind --leak-check=full ./$(NAME)

-include $(DEPS)

.PHONY: all clean fclean re test vtest
