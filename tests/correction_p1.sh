#!/bin/sh
rm -f wins; for i in $(seq 5); do rm -f debug_1; ./filler_vm -q -p1 "../filler -v" -p2 $1 -f $2; cat filler.trace | grep "won" >> wins; done; cat wins
