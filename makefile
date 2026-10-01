all: random random2
random: random.c
	gcc -o random random.c
random2:
	gcc -o random2 random2.c
clean:
	rm -rf random2 random