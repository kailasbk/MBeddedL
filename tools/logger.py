from flask import Flask
import serial

ser = serial.Serial("COM3")

while True:
    print(ser.readline().decode("ascii"), end='')
