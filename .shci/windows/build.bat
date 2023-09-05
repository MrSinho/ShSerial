> .shci/windows/build-output.txt (
    mkdir windows
	cd windows
	cmake .. -DSH_SERIAL_BUILD_LOGGER=ON
	cmake --build .
)
