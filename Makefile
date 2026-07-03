setup:
	meson setup build

build:
	ninja -C build

run: build
	ninja -C build
	./build/irg

patch:
	rm ./build/patched-irg
	cp ./build/irg ./build/patched-irg
	patchelf --set-interpreter /lib64/ld-linux-x86-64.so.2 ./build/patched-irg
