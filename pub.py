# python pub.py filename.bin decimalOffset decimalByteValue
from sys import argv
fileToEdit = open(argv[1], 'r+b')
fileToEdit.seek(long(argv[2]))
fileToEdit.write(chr(int(argv[3])))
fileToEdit.close()
