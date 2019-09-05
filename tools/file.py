import serial

port = input("Enter port:")

ser = serial.Serial(port)  # change port based on computer used
line = ""
filestring = ""

while line != "<FILE>\n":  # wait until file data
    line = ser.readline()

while line != "</FILE>\n":
    line = ser.readline()
    filestring += line
    print(ser.decode("ascii"), end='')

# write stream contents to the file
f = open("output.csv", "w")
f.write(filestring)
f.close()
