#!/bin/bash

pkill -f picom
pkill -f dunst
pkill -f flameshot
pkill -f ulauncher
pkill -f dwm_status.sh

~/dwm/scripts/autostart.sh
