import sys

def get_filename():
    if len(sys.argv) < 2:
        print "Please specify a binary file!"
        exit(1)

    return sys.argv[1]

file_path = get_filename()

with open(file_path, "rb") as f:
    byte = f.read(0x10000) # read 0x10000
    f.close()

byte = byte[0x8000:0x8400] # cut to 0x400
with open(file_path, "wb") as f:
    f.write(byte)
    f.close()

