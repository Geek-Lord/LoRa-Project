import serial
import time
import webbrowser

print("Getting coordinates. Please wait....")
ard = serial.Serial('COM3', 9600, timeout=10)
msg = ard.readline() 
coord = msg.decode('ascii').split("*")
print('''Current Location:
    Latitude = %s
    Longitude = %s
    Opening location on google maps...''' %(coord[1],coord[2]))
time.sleep(2)
webbrowser.open('https://www.google.com/maps/search/?api=1&query=%s,%s'%(coord[1],coord[2]))
