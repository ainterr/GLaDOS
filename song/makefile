NAME = song

CC = gcc
DEBUG = -g -O0
CFLAGS = $(DEBUG)

$(NAME)_b64.txt: $(NAME)
	base64 < $(NAME) | xargs printf '"%s"\n' > $(NAME)_b64.txt

$(NAME): $(NAME).c
	$(CC) $(CFLAGS) $(NAME).c -o $(NAME)

clean:
	rm -f $(NAME) $(NAME)_b64.txt
