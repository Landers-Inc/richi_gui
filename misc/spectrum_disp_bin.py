import numpy as np
import matplotlib.pyplot as plt
import json
import struct
import binascii

f = open('SpectrumData-spectrum.bin','rb')

spectrum = []

for i in range(2048):
    bytes = f.read(8)
    valueDouble = struct.unpack("<d",bytes)
    spectrum.append(valueDouble)

plt.plot(spectrum)
plt.show()
