"""
Simple script to convert a listing file to an object file.
"""

import re
import sys

if len(sys.argv) != 3:
    print('Usage:', sys.argv[0], '<listing file> <object file>')
    print('Converts a listing file to an object file.')
    exit(1)

with open(sys.argv[1]) as lst, open(sys.argv[2], 'wb') as obj:
    for line in lst:
        match = re.match("^[0-9A-F]{4}    ([0-9A-F]{4}).*", line)
        if match is not None:
            code = int(match.group(1), 16)
            obj.write(code.to_bytes(2, byteorder='little'))
