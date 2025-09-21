#!/bin/bash

~/dwm/scripts/dwm_status.sh &

setxkbmap \
-option caps:swapescape \
-option altwin:swap_lalt_lwin \
-option ctrl:swap_ralt_rctl \
-option custom_remap:swap_grave_backslash &

xset r rate 300 50 &

xinput set-prop \
"ELAN0300:00 04F3:3206 Touchpad" \
"libinput Tapping Enabled" 1 &
xinput set-prop \
"ELAN0300:00 04F3:3206 Touchpad" \
"libinput Accel Speed" 0.5 &

xrandr --output DP-1-0.2 --mode 1920x1080 &&
xrandr --output eDP-1 --mode 1920x1080 &&
xrandr --output DP-1-0.2 --same-as eDP-1 &
# xrandr --output eDP-1 --off --output DP-1-0.2 --auto --primary &

# xrandr \
# --output DP-1-0.2 \
# --same-as eDP-1 &

feh --bg-scale ~/pictures/wallpapers/M3-MacBook-Pro-Wallpaper-8K.png &

picom &

ulauncher --hide-window &

dunst &

flameshot &

# ~/dwm/scripts/toggle_keyboard.sh &

# Initialize Wacom tablet to primary display (DP-1)
~/dwm/scripts/wacom_init.sh &
