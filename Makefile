.PHONY: all
all: test build-client

.PHONY: cmake-debug
cmake-build:
	cmake -B build

build/CMakeCache.txt: cmake-build

.PHONY: build-server build-client
build-server build-client: build-%: build/CMakeCache.txt
	cmake --build build --target $*

.PHONY: build-test
build-test: build-test%: build-server
	cmake --build build --target TestCore

.PHONY: start-server start-client
start-server start-client: start-%: build-%
	cd build && ./$*

.PHONY: test
test: test%: build-test
	cd build && ((test -t 1 && GTEST_COLOR=1 PYTEST_ADDOPTS="--color=yes" ctest -V) || ctest -V)
