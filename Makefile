all:
	gcc ./src/*.c -I include -o penalty

run:
	./penalty

clean:
	rm penalty

