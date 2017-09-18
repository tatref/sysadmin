# Storage details
## General information

    # ls -l /dev/disk/by-path

## Block devices
### Size (bytes)

    # blockdev --getsize64 /dev/sda

### Block device / hardware device mapping
SCSI ID <-> /dev/sdX

    # ls -ld /sys/block/sd*/device
