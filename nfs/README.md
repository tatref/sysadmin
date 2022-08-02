# Find NFS ports, proto, nfsvers

```console
# rpcinfo  -p $IP
   program vers proto   port  service
    100000    2   udp    111  portmapper
    100000    2   tcp    111  portmapper
    100000    3   udp    111  portmapper
    100000    3   tcp    111  portmapper
    100000    4   udp    111  portmapper
    100000    4   tcp    111  portmapper
    100003    3   udp   2049  nfs
    100003    3   tcp   2049  nfs
    100005    1   udp    635  mountd
    100005    2   udp    635  mountd
    100005    3   udp    635  mountd
    100005    1   tcp    635  mountd
```
