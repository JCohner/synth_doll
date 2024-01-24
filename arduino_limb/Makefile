
build:
	arduino-cli compile --output-dir bin --fqbn arduino:samd:nano_33_iot \
	--build-property "compiler.cpp.extra_flags=-std=c++14" .

deploy:
	# can parse `arduino-cli board list` with awk if needed 
	arduino-cli upload --input-file bin/arduino_limb.ino.bin --fqbn arduino:samd:nano_33_iot -p /dev/ttyACM0 --verbose