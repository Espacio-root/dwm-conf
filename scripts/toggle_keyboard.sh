#!/bin/bash

# Get device IDs dynamically
LAPTOP_KEYBOARD_ID=$(xinput list | grep -i "AT Translated Set 2 keyboard" | grep -oP 'id=\K\d+')
WIRELESS_KEYBOARD_ID=$(xinput list | grep -i "Compx 2.4G Wireless Receiver Keyboard" | grep -oP 'id=\K\d+')

if [ -z "$LAPTOP_KEYBOARD_ID" ]; then
    echo "Error: Could not find laptop keyboard."
    exit 1
fi

# Check conditions
# DP_CONNECTED=$(xrandr | grep -q "DP-1-0.2 connected" && echo "yes" || echo "no")
DP_CONNECTED="yes"
WIRELESS_CONNECTED=$(xinput list | grep -q "Compx 2.4G Wireless Receiver Keyboard" && echo "yes" || echo "no")

if [ "$DP_CONNECTED" = "yes" ] && [ "$WIRELESS_CONNECTED" = "yes" ]; then
    echo "External display + wireless keyboard detected → Disabling laptop keyboard (ID $LAPTOP_KEYBOARD_ID)"
    xinput disable "$LAPTOP_KEYBOARD_ID"
else
    echo "Conditions not met → Keeping laptop keyboard enabled (ID $LAPTOP_KEYBOARD_ID)"
    xinput enable "$LAPTOP_KEYBOARD_ID"
fi

