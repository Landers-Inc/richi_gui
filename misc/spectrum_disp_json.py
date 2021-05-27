import numpy as np
import matplotlib.pyplot as plt
import json
import struct
import binascii

f = open('SpectrumData2.json',)

data = json.load(f)

asdf = data[2]["data"][0]["spectrum"]
totalLength = len(asdf)
spectrumLength = int((totalLength-2)/16)
spectrum = []

for i in range(spectrumLength):
    valueHex = bytes.fromhex(asdf[(2+16*i):(2+16*(i+1))])
    valueDouble = struct.unpack("<d",valueHex)
    spectrum.append(valueDouble)

plt.plot(spectrum)
plt.show()
