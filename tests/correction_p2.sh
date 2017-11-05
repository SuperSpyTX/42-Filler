#!/bin/sh
rm -f wins; for i in $(seq 5); do rm -f debug_2; ./filler_vm -q -p2 "../filler -v" -p1 $1 -f $2; cat filler.trace | grep "won" >> wins; done; cat wins
