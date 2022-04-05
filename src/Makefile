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

# check memory leak
# ref: https://stackoverflow.com/questions/6261201/how-to-find-memory-leak-in-a-c-code-project/28398186#28398186
ifeq ($(MEM_CKER), 1)
	BUILD_FLAGS := -fsanitize=address -ggdb3
else
	BUILD_FLAGS :=
endif

ID :=

build: $(ID).cpp
	g++ --std=c++14 -I $(GOOGLE_TEST_INCLUDE) $(BUILD_FLAGS) $< gtest_main.cpp -L $(GOOGLE_TEST_LIBS) -l gtest -l pthread

run:
	echo " ===== test memory leak ===== " && \
	make build MEM_CKER=1 ID=${ID} && ./a.out && \
	echo " ===== test performance ===== " && \
	make build ID=${ID} && ./a.out

clean:
	rm *.out

.PHONY: build run clean