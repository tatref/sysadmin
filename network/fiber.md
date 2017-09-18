# Error counters
```
for host in /sys/class/fc_host/host*
do
  echo $host
  for counter in link_failure_count loss_of_signal_count loss_of_sync_count nos_count
  do
    echo -n "$counter "
    data=$(cat $host/statistics/$counter)
    printf "%d\n" $data
  done
done
```
