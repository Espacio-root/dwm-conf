#!/bin/bash

# Config file to track current monitor
MONITOR_FILE=~/.config/dwm/wacom_monitor

# Read current monitor (default: HEAD-1 if not set)
CURRENT_MONITOR=$(cat "$MONITOR_FILE" 2>/dev/null || echo "HEAD-1")

# Switch to the other monitor
if [[ "$CURRENT_MONITOR" == "HEAD-0" ]]; then
    OTHER_MONITOR="HEAD-1"
else
    OTHER_MONITOR="HEAD-0"
fi

# Get current mouse position (X,Y)
eval $(xdotool getmouselocation --shell)

# Calculate new position:
# - If moving from HEAD-0 (left) → HEAD-1 (right), add 1920 to X
# - If moving from HEAD-1 (right) → HEAD-0 (left), subtract 1920 from X
if [[ "$CURRENT_MONITOR" == "HEAD-0" ]]; then
    NEW_X=$((X + 1920))
    NEW_Y=$Y
else
    NEW_X=$((X - 1920))
    NEW_Y=$Y
fi

# Map the tablet to the new monitor
xsetwacom --set 'Wacom One by Wacom S Pen stylus' MapToOutput "$OTHER_MONITOR"

# Save the new monitor setting
echo "$OTHER_MONITOR" > "$MONITOR_FILE"

# Move the cursor to the mirrored position
xdotool mousemove "$NEW_X" "$NEW_Y"
