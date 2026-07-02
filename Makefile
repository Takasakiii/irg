setup:
	meson setup build

build:
	ninja -C build

run: build
	ninja -C build
	./build/irg

patch:
	patchelf --set-interpreter /lib64/ld-linux-x86-64.so.2 ./build/irg
