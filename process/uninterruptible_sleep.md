# To list processes in the uninterruptible sleep state
    
    ps aux | awk '$8 ~ /^D/ {print $2" "$11}'

# To simulate stuck processes
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

Now check load average, ps output...
