#!/bin/bash

# Convert lst to object
python3 lst2obj.py gcd.lst.expect gcd.obj.expect

status=0
../caltech10as gcd.asm || status=1
diff gcd.lst gcd.lst.expect || status=1
cmp gcd.obj gcd.obj.expect || status=1
exit $status