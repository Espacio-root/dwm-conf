#!/bin/bash
kitty --listen-on=unix:@"$(date +%s%N)" -o allow_remote_control=yes
