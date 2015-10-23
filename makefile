develop: build insert run

build : $(wildcard **/*.s) $(wildcard **/*.c)
	./scripts/build

insert: $(wildcard build/*)
	./scripts/insert

run:
	mgba test.gba

clean:
	rm test.gba
