develop: build run

build:
	python assemble.py

run:
	mgba -d test.gba

clean:
	rm test.gba
