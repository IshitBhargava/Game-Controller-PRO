import serial
import pydirectinput

arduino = serial.Serial('COM5', 115200, timeout=.1)     #serial input from arduino. change COM port to wherever your arduino is connected

pydirectinput.PAUSE = 0
pydirectinput.FAILSAFE = False


keysDown = {}   #list of currently pressed keys
prevButtonState = 0

def keyDown(key):               #what to do if key pressed. takes value from handleJoyStickAsArrowKeys
    keysDown[key] = True        #adds key to KeysDown list
    pydirectinput.keyDown(key)  #runs pydirectinput using key from (argument)
    #print('Down: ', key)       #remove '#' from print to test data stream


def keyUp(key):                     #what to do if key released. takes value from handleJoyStickAsArrowKeys
    if key in keysDown:
        del (keysDown[key])         #remove key from KeysDown
        pydirectinput.keyUp(key)    #runs pydirectinput using key from (argument)
        #print('Up: ', key)         #remove '#' from print to test data stream


def handleJoyStickAsArrowKeys(x, y, z, potValue):      #note that the x and y directions are swapped due to the way I orient my thumbstick
    global prevButtonState
    if x == 0:          #0 is up on joystick
        keyDown('up')   #add up key to keyDown (argument)
        keyUp('down')   #add down key to keyUp (argument), as you can't press up and down together
    elif x == 2:        #2 is down on joystick
        keyDown('down')
        keyUp('up')
    else:               #1 is neutral on joystick
        keyUp('up')
        keyUp('down')

    if y == 2:          #2 is right on joystick
        keyDown('right')
        keyUp('left')
    elif y == 0:        #0 is left on joystick
        keyDown('left')
        keyUp('right')
    else:               #1 is neutral on joystick
        keyUp('left')
        keyUp('right')


    if z == 1 and prevButtonState == 0:    # Button pressed and previous state was released
        keyDown('f')    # Press the key
    elif z == 0 and prevButtonState == 1:  # Button released and previous state was pressed
        keyUp('f')      # Release the key

    prevButtonState = z  # Update the previous button state

    # Press the keyboard key corresponding to the potentiometer value
    if(potValue != 10):
        #do nothing
        #print("do nothing")
        key_press = str(potValue)
        keyDown(key_press)

        

while True:
    rawdata = arduino.readline()            #read serial data from arduino one line at a time
    data = str(rawdata.decode('utf-8'))     #decode the raw byte data into UTF-8
    if data.startswith("S"):                #make sure the read starts in the correct place
        dx = int(data[1])                   #X direction is second digit in data (data[0] is 'S')
        dy = int(data[3])                   #Y direction is fourth digit in data
        JSButton = int(data[5])             #JSButton is sixth digit in data
        potValue = int(data[7:])            # Potentiometer value starts from eighth digit in data
        #print(dx, dy, JSButton, potValue)  #remove '#' from print to test data stream
        handleJoyStickAsArrowKeys(dx, dy, JSButton, potValue)     #run body of code using dx, dy, JSButton, and potValue as inputs
