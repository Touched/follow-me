develop: build run

build:
	python assemble.py

run:
	mgba test.gba

clean:
	rm test.gba
