#!/bin/bash
#
# Pure iptables port knocking with 1 knock
# Usage: sudo ./port_knocking.sh 22 12345
#
# From client:
# nc -zv -w 1 host 12345
# ssh host -p 22
#

set -eu


# both ports should be random
FINAL_PORT=$1
KNOCK_PORT=$2

blacklist_duration=600
door_open_duration=30



# default
iptables -A INPUT -m state --state related,established -j ACCEPT

iptables -A INPUT -p tcp -m recent --name BLACKLIST --rcheck --seconds $blacklist_duration -j DROP

iptables -A INPUT -p tcp --dport $FINAL_PORT -m recent --name KNOCK_$KNOCK_PORT --rcheck --seconds $door_open_duration -j ACCEPT
iptables -A INPUT -p tcp --dport $KNOCK_PORT -m recent --name KNOCK_$KNOCK_PORT --set -j DROP



# if the packet wasn't accepted until there, blacklist the sender
iptables -A INPUT -p tcp --dport $FINAL_PORT -m recent --set --name BLACKLIST -j DROP

iptables -A INPUT -j ACCEPT
