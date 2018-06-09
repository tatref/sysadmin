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
