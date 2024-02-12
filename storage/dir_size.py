#!/usr/bin/python3

import sys
import os
import datetime
from pathlib import Path

try:
    roots = list(map(Path, sys.argv[1:]))
except:
    print('Usage:\n  ' + sys.argv[0] + ' <path>...')
    sys.exit(1)


units = 'M'
if units.lower() == 'b':
    units = 1
elif units.lower() == 'k':
    units = 1024
elif units.lower() == 'm':
    units = 1024 * 1024
elif units.lower() == 'g':
    units = 1024 * 1024 * 1024



infos = {}
for root in roots:
    org_mount = os.stat(root).st_dev
    root = Path(os.path.abspath(root))
    queue = [root]
    while len(queue) > 0:
        dir = queue.pop()
        with os.scandir(dir) as it:
            for entry in it:
                if entry.is_dir(follow_symlinks=False):
                    mount = entry.stat().st_dev
                    if mount != org_mount:
                        print('Skipping mount {}'.format(entry))
                        continue
                    queue.append(entry)
                if entry.is_file(follow_symlinks=False):
                    file = Path(os.path.join(dir, entry.name))
                    stat = os.stat(file)
                    size = stat.st_size
                    timestamp = datetime.datetime.fromtimestamp(stat.st_mtime)
                    date = timestamp.date()
                    node = infos.setdefault(date, {'size': 0, 'dirs': {}})
                    infos[date]['size'] += size
                    parts = file.parent.relative_to(root).parts
                    for part in parts:
                        _ = node['dirs'].setdefault(part, {'size': 0, 'dirs': {}})
                        node['dirs'][part]['size'] += size
                        node = node['dirs'][part]

if len(infos) == 0:
    print("No files found")
    sys.exit(0)

dates = sorted([date for date in infos.keys()])
print(dates[0], '>', dates[-1])

start_date = input('Enter first date? ')
start_date = datetime.datetime.strptime(start_date, '%Y-%m-%d')
end_date = input('Enter last date? ')
end_date = datetime.datetime.strptime(end_date, '%Y-%m-%d')
days = (end_date - start_date).days + 1

print('Deltas by date:')
for day in range(0, days):
    date = (start_date + datetime.timedelta(days=day)).date()
    print(date, end=': ')
    if not date in infos:
        print('0')
        continue
    size = int(infos[date]['size'] / units)
    print(size)

date = input('Select date? ')
date = datetime.datetime.strptime(date, '%Y-%m-%d').date()


node = infos[date]
currentpath = root

while True:
    print('')
    print(date, currentpath)
    for dir in node['dirs'].keys():
        size = int(node['dirs'][dir]['size'] / units)
        print('{:>10} {}'.format(size, dir))
    x = input('? ')
    if x == '':
        continue
    else:
        if not x in node['dirs'].keys():
            print('not found')
            print(node['dirs'].keys())
            continue
        node = node['dirs'][x]
        currentpath = currentpath / x
