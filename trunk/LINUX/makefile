OUT=pacman3d

all:
	make -C source/; mkdir build; mv source/$(OUT) build/; cp -r data build/

clean:
	make -C source/ clean; rm -rf build/;
