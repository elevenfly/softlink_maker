softlink_maker: softlink_maker.o
	gcc -o softlink_maker softlink_maker.o

	if [ ! -d ../../local/softlink_maker ]; then \
		mkdir ../../local/softlink_maker; \
		mkdir ../../local/softlink_maker/bin; \
	fi

	mv softlink_maker ../../local/softlink_maker/bin
	rm -f *.o

softlink_maker.o: softlink_maker.c
	gcc -c -o softlink_maker.o softlink_maker.c
