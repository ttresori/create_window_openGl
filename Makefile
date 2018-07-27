NAME = create_window

SRCDIR = src
SRC = create_window.c

OBJDIR = obj
OBJ = $(SRC:.c=.o)

LIBDIR = libft
LIB = ft

SDL= -lSDL -lGL -lGLU -lSDL_ttf

CFLAGS = -Wall -Wextra

all: $(LIBDIR)/lib$(LIB).a $(OBJDIR) $(NAME)

$(LIBDIR)/lib$(LIB).a:
	@tput setaf 90 ; echo [COMPILE]
	@make -C $(LIBDIR)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(NAME): $(addprefix $(OBJDIR)/, $(OBJ))
	@$(CC) $(CFLAGS) $(addprefix $(OBJDIR)/, $(OBJ)) -o $(NAME) -L $(LIBDIR) -l $(LIB) $(SDL)
	@tput setaf 90 ; echo [DONE]

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@tput setaf 25 ; echo $<

clean:
	@tput setaf 70 ; echo [CLEAN --] [$(OBJDIR)] [$(LIBDIR)]
	@rm -rf $(OBJDIR)
	@make clean -C $(LIBDIR)

fclean: clean
	@tput setaf 70 ; echo [FCLEAN --] [$(NAME)] [$(LIBDIR)]
	@rm -rf $(NAME)
	@make fclean -C $(LIBDIR)

tmpc:
	@tput setaf 90 ; echo [Delete temporary file]
	@rm -rf *~
	@rm -rf src/*~

re: fclean all

.PHONY: re fclean clean all
