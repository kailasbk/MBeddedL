import serial

port = input("Enter port:")

ser = serial.Serial(port)  # change based on computer used

while True:
    print(ser.readline().decode("ascii"), end='')
