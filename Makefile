socketpair:socketpair.c
	gcc -o $@ $^
.PHONY:clean
clean:
	rm -r socketpair

