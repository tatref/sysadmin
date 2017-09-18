# inodes count
```
find . -mount -type d -print0 | 
while IFS= read -r -d $'\0' f; do 
	echo "$(find "$f" -mount | wc -l) $f"
done | sort -n -k 1 | tail -20
```

# disk space
```
find . -mount -type d -print0 | 
while IFS= read -r -d $'\0' f; do 
	du -sx "$f"
done | sort -n -k 1 | tail -20
```
