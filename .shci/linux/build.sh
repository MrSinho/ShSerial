function BUILD {
	mkdir linux
	cd linux
	cmake .. -DSH_SERIAL_BUILD_LOGGER=ON
	cmake --build .
}

BUILD > .shci/linux/build-output.txt
