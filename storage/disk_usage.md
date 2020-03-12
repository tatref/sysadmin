# inodes count
```
mountpoint=$(df -P . | tail -n -1 | awk '{print $6}')

find . -mount -type d -print0 | 
while IFS= read -r -d $'\0' f; do 
  this_mountpoint=$(df -P "$f" | tail -n -1 | awk '{print $6}')
  if [ "$this_mountpoint" == "$mountpoint" ]
  then
    echo "$(find "$f" -mount | wc -l) $f"
  fi
done | sort -n -k 1 | tail -20
```

# disk space
```
mountpoint=$(df -P . | tail -n -1 | awk '{print $6}')

find . -mount -type d -print0 | 
while IFS= read -r -d $'\0' f; do 
  this_mountpoint=$(df -P "$f" | tail -n -1 | awk '{print $6}')
  if [ "$this_mountpoint" == "$mountpoint" ]
  then
    du -sx "$f"
  fi
done | sort -n -k 1 | tail -20
```

# Recent changes per directory per month
```
# directories with recent changes
dirs=$(for x in $(find . -type f -mtime +30 -mtime -90)
do
  dirname "$x"
done | sort | uniq)


for dir in $dirs
do
  echo $dir
  {
  # 4 months
  days=(0 30 60 90 120)
  for day in ${days[@]}
  do
    # size of the changes in dir between day and day+30
    size=$(find "$dir" -type f -mmin +$((60*24*day)) -mmin -$((60*24*(day + 30) )) -print0 | xargs -0 ls -l | awk '{s+=$5} END {print s/1024/1024}')
    echo "$day -> $((day+30)): $size"
  done

  total=$(find "$dir" -type f -mmin -$(( 60*24* (${days[${#days[@]}-1]} + 30) )) -print0 | xargs -0 ls -l | awk '{s+=$5} END {print s/1024/1024}')
  echo "total -> ${days[${#days[@]}-1]}: $total"
  } | column -t

  echo
done
```
