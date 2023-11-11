#!/usr/bin/python
from Adafruit_MotorHAT import Adafruit_MotorHAT, Adafruit_DCMotor

import time
import atexit
import serial


###############################################################################################
### 아두이노 관련 설정

port = 'COM10'
baud = 9600
ser = serial.Serial(port, baud, timeout = 1)

### 모터 관련 설정

# create a default object, no changes to I2C address or frequency
mh = Adafruit_MotorHAT(addr=0x60)

# recommended for auto-disabling motors on shutdown!
def turnOffMotors():
    mh.getMotor(1).run(Adafruit_MotorHAT.RELEASE)
    mh.getMotor(2).run(Adafruit_MotorHAT.RELEASE)
    mh.getMotor(3).run(Adafruit_MotorHAT.RELEASE)
    mh.getMotor(4).run(Adafruit_MotorHAT.RELEASE)

atexit.register(turnOffMotors)

myMotor = mh.getMotor(1)

# set the speed to start, from 0 (off) to 255 (max speed)
myMotor.setSpeed(150)
myMotor.run(Adafruit_MotorHAT.FORWARD);
# turn on motor
myMotor.run(Adafruit_MotorHAT.RELEASE);
###############################################################################################


### 키 입력으로 조절
while True :
    key = input()

    ### 이동 관련 키 (W, S, A, D)

    # 앞으로 이동
    if key == 'W' :
        print("Forward!")
        myMotor.run(Adafruit_MotorHAT.FORWARD)

        for i in range(255):
            myMotor.setSpeed(i)
            time.sleep(0.01)

        for i in reversed(range(255)):
            myMotor.setSpeed(i)
            time.sleep(0.01)

    # 뒤로 이동
    elif key == 'S' : 
        print("Backward!")
        myMotor.run(Adafruit_MotorHAT.BACKWARD)

        for i in range(255):
            myMotor.setSpeed(i)
            time.sleep(0.01)

        for i in reversed(range(255)):
            myMotor.setSpeed(i)
            time.sleep(0.01)

    ### 아두이노 함수 실행 관련 키 (U, I, O, P)

    # 특정 위치에 도착 하였을 때 호출
    # 식판 배달 함수 (Delivery() 호출)
    # delivery::p129:리얼타임
    if key == 'U' :
        print('Delivery() 호출')
        ser.write("delivery")

        # 반환값 대기
        while True :
            # 아두이노에게 반환값을 받았으면
            received_data = ser.readline()
            # 환자가 식판을 챙겼으면
            if str(received_data) == '1' :
                print('환자 밥 먹음')
                print('다음으로 이동')
                break
            # 환자가 식판을 챙기지 않았으면
            if str(received_data) == '-1' :
                print('환자 밥 먹지않음')
                print('다음으로 이동')
                break


    # 식판 배식후 병실 대기할 때 호출
    # 대기 함수 (Stand() 호출) 
    if key == 'I' :
        print('Stand() 호출')
        ser.write("stand:")

        # 반환값 대기
        while True :
            # 아두이노에게 반환값을 받았으면
            if str(received_data) == '1' :
                    print('식판회수 완료')
                    print('다음으로 이동')
                    break
        

    # 최초 장소 복귀하였을 떄 호출
    # Sleep() 호출
    if key == 'O' :
        print('Sleep() 호출')
        ser.write("sleelp:")

        