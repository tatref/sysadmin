    ps aux | awk '$8 ~ /^D/ {print $11}'
