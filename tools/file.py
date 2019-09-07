import serial

port = input("Enter port: ")

ser = serial.Serial(port)  # change port based on computer used
line = b''
filestring = b''

while line != b'<FILE>\n':  # wait until file data
    line = ser.readline()
    print(line)

while line != b'</FILE>\n':
    line = ser.readline()
    if line != b'</FILE>\n':
        filestring += line
    print("reading file: " + line.decode("ascii"), end='')

# write stream contents to the file
f = open("output.csv", "w")
f.write(filestring.decode("ascii"))
f.close()
