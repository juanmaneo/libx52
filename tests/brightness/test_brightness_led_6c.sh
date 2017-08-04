#!/bin/bash
# Test setting LED brightness to 0x006c

source $(dirname $0)/../common_infra.sh

expect_pattern $X52_LED_BRIGHTNESS_INDEX 0x006c

$X52CLI bri LED 0x006c

verify_output
