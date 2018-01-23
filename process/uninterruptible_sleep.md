To list processes in the uninterruptible sleep state
    
    ps aux | awk '$8 ~ /^D/ {print $2" "$11}'
