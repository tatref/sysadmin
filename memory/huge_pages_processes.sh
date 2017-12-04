#!/bin/bash
#
# List processes using hugepages


pushd /proc

for i in */numa_maps
do
  if grep -q -s huge $i
  then
    cmdline=$(grep -q -s huge $i && cat ${i%%/numa_maps}/cmdline)
    pid=${i%%/numa_maps}

    echo $pid $cmdline
  fi
done | sort | uniq

popd
