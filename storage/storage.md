# Storage details
## General information

    # ls -l /dev/disk/by-path

## Block devices (disks/partitions/LVs/...)
### Size (bytes)

    # blockdev --getsize64 /dev/sda

### Block device / hardware device mapping
SCSI ID <-> /dev/sdX

    # ls -ld /sys/block/sd*/device

# Scan new attached disks

```
for x in /sys/class/scsi_host/host*/scan
do
  echo '- - -' > $x
done
```


```
dmesg | tail
ls -ltr /dev/sd*
```

# Rescan disk size

```
echo 1 > /sys/block/sdX/device/rescan
```

# Rescan partition (RHEL 7+)

```
partx --update /dev/sdX
```
