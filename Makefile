.PHONY: all engine testbed clean

all: engine testbed

engine:
	@mkdir -p bin
	$(MAKE) -C engine

testbed: engine
	@mkdir -p bin
	$(MAKE) -C testbed

clean:
	$(MAKE) -C engine clean
	$(MAKE) -C testbed clean
	rm -rf bin