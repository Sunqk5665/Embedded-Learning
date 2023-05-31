CC=gcc
CFLAGS=-c -g
OBJS=help.o clear.o score.o main.o
a.out:$(OBJS)
	$(CC) $(OBJS) -o $@
$(OBJS):%.o:%.c
	$(CC) $(CFLAGS) $^ -o $@
.PHONY:clean
clean:
	rm *.o a.out
