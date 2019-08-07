#!/bin/sh
# TODO: Script parameters for passing in serial port, baud rate, timezone(?)

# Serial port discovery
# TODO: Add and test proper LINUX support, choose logic based on platform
# Going with first serial port returned that is NOT "Bluetooth-Incoming-Port"
# Mac: Using /dev/tty.* leads to high-cpu hanging with read/write. /dev/cu.* works as expected.
ports=($(find /dev -regex '/dev/cu\..*' 2>/dev/null | grep -v 'Bluetooth-Incoming-Port'))
if [[ ${#ports[@]} -eq 0 ]]; then
    # Bail if no serial port was defined
    echo "No serial port was found. Abort!"
    exit 1
else
    port=${ports[0]}
fi
echo "Serial port found: ${port}"

# Format: YYMMDDwHHMMSS
right_now=$(date +'%y%m%d%u%H%M%S')
echo "Current time: ${right_now}"

# Setup serial port for read/write communication
# TODO: use -F on Linux
stty -f ${port} speed 9600 cs8 -cstopb -parenb cread clocal

# Send to serial port
echo "Sending current time to ${port}"
echo "${right_now}" > ${port}

echo "Done."
