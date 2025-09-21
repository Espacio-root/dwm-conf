#!/bin/bash

while true; do
    # Get system metrics
    cpu=$(top -bn1 | grep "Cpu(s)" | awk '{print $2}' | cut -d'%' -f1)
    ram=$(free -h | awk '/^Mem:/ {print $3}')
    vol=$(pamixer --get-volume)
    is_muted=$(pamixer --get-mute)
    brt=$(brightnessctl g | awk -v max="$(brightnessctl m)" '{printf "%d\n", ($1 / max) * 100}')
    bat=$(cat /sys/class/power_supply/BAT*/capacity)
    date=$(date '+%b %d')
    time=$(date '+%H:%M')
    
    # Handle mute status
    if [ "$is_muted" = "true" ]; then
        vol_status="[MUT]"
    else
        vol_status="${vol}%"
    fi
    
    # Build status string
    status="BAT  ^c#ffffff^${bat}%^d^      BRT  ^c#ffffff^${brt}%^d^      VOL  ^c#ffffff^${vol_status}^d^      RAM  ^c#ffffff^${ram}^d^      CPU  ^c#ffffff^${cpu}%^d^      ^c#ffffff^${time}^d^  ^c#ffffff^${date}^d^"

    # Report low battery
    if [ "$bat" -lt 5 ]; then
        notify-send -u critical "Battery Low" "Only ${bat}% remaining!"
    fi
    
    xsetroot -name "$status"
    sleep 2
done
