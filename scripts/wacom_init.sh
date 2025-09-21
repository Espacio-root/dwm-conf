#!/bin/bash

# Config file to store current monitor
CONFIG_FILE=~/.config/dwm/wacom_monitor

xsetwacom \
--set 'Wacom One by Wacom S Pen stylus' Button 2 'pan' && \
xsetwacom \
--set 'Wacom One by Wacom S Pen stylus' PanScrollThreshold 100 && \
# xsetwacom \
# --set 'Wacom One by Wacom S Pen stylus' Rotate half && \
xsetwacom \
--set 'Wacom One by Wacom S Pen stylus' Mode absolute

# Map to HEAD-1 initially and store in config
xsetwacom --set 'Wacom One by Wacom S Pen stylus' MapToOutput HEAD-1
echo "HEAD-1" > "$CONFIG_FILE"
