CC =	clang++

FLAG =	-g -Wall -Wextra -Werror -std=c++98 -I ./headers

NAME =	health_records

SDIR =	src

SRCS =	$(addprefix $(SDIR)/, \
			main.cpp \
			HealthProfile.class.cpp \
		)

FDIR =	frame

TEMP =	$(SRCS:.cpp=.o)

OBJS =	$(subst $(SDIR),$(FDIR),$(TEMP))

all: 	$(NAME)

echo:
		@echo $(OBJS)
		@echo $(SRCS)

frame:
		@mkdir $(FDIR)
		@echo "$(FDIR): has been created"

$(NAME): $(OBJS)
		@$(CC) $(FLAG) $^ -o $@
		@echo "$(NAME): has been created"

$(FDIR)/%.o: $(SDIR)/%.cpp | frame
		@$(CC) $(FLAG) -c $< -o $@

clean:
		@rm -f $(OBJS)
		@rm -rf $(FDIR)
		@echo "$(FDIR) & $(OBJS): have been cleaned"

fclean:	clean
		@/bin/rm -f $(NAME)
		@echo "$(NAME): have been cleaned"

re: fclean all

.PHONY: all clean fclean re
