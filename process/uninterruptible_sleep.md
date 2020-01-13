# List processes in D (uninterruptible), Z (zombie), or R (running or runnable) state
* ww: unlimited output
* ax: list all processes (including processes without tty)

Threads details (H + lwp)
```
ps Haxwwo stat,lwp,pid,ppid,pcpu,etime,cputime,rss,nlwp,user,wchan:25,command | grep -e ^STAT -e ^D -e ^Z -e ^R
```

Only processes
```
ps axwwo stat,pid,ppid,pcpu,etime,cputime,rss,nlwp,user,wchan:25,command | grep -e ^STAT -e ^D -e ^Z -e ^R
```

# Simulate D processes
```
yum install nfs-utils rpcbind
mkdir /nfs_export
cat <<EOF > /etc/exports
/nfs_export *(ro)
EOF
exportfs -rva
showmount -e
mkdir client_mount
mount localhost:/nfs_export client_mount
mount 192.168.0.100:/nfs_export client/
```

```
iptables -I INPUT --protocol tcp --dport 2049 -j DROP
for x in $(seq 0 10); do ls client& done
```

Now check load average, ps output
