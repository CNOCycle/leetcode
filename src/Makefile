# gtest setting
GOOGLE_TEST_ROOT = ../third-party-libs/gtest/
GOOGLE_TEST_INCLUDE = $(GOOGLE_TEST_ROOT)/include/
GOOGLE_TEST_LIBS    = $(GOOGLE_TEST_ROOT)/lib/

# set compiling info
ifeq ($(GDB), 1)
	BUILD_FLAGS := -g -O0
else
	BUILD_FLAGS := 
endif

ID :=

build: $(ID).cpp
	g++ --std=c++14 -I $(GOOGLE_TEST_INCLUDE) $(BUILD_FLAGS) $< gtest_main.cpp -L $(GOOGLE_TEST_LIBS) -l gtest -l pthread

run: build
	./a.out

clean:
	rm *.out

.PHONY: build run clean