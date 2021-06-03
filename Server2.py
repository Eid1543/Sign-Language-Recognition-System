import socket
import pyttsx3

s = socket.socket(socket.AF_INET , socket.SOCK_STREAM)
s.bind((socket.gethostname(),8090)) # local host ip and the port to listen on

s.listen(0)

# text to speech engine :
engine = pyttsx3.init()  
engine.setProperty('rate',150)  


# here we going to connect the client ( Arduino ) and receive the data
while True:
    clientsocket , address = s.accept() 
    print(f"Connection{address} has been established")
    while True:
        s = clientsocket.recv(1024) 

        content = s.decode("utf-8")


        # 9 is the arbitrary character that we assigned in the arduino so it can help us know the begining of our string data
        # after checking if this is the string data that we want, we need to slice our data so we can work with them
        # after slicing them we need to convert the data from string to numeric value and we need to assign them to variables
        # f1 ,f2 ,...,f5 all of them represent the values of the flex sensors bending and the "mpu" represent the hand position
        if content [0] == "9" :
          f1 = eval(content[1:4])
          f2 = eval(content[4:7])
          f3 = eval(content[7:10])
          f4 = eval(content[10:13])
          f5 = eval(content[13:16])
          mpu = eval(content[16:])

          # for demonstration purposes :

          # print("the data will be received from the arduino as : ", content)
          # print("after slicing the data and assigining them to variables : ")
          # print("finger1 " , f1 )
          # print("finger2 ", f2)
          # print("finger3 ", f3)
          # print("finger4 ", f4)
          # print("finger5 ", f5)
          # print("Position", mpu)



          # here we gonna use the data we took from the arduino and perform a simple algorithm to match our data with an expression
          # you can use any other algorithms you wish

          if ( f1 >= 145 and f1 <= 170 ) and \
             ( f2 >= 250 and f2 <= 255 ) and \
             (f3 >= 250 and f3 <= 255 ) and \
             ( f4 >= 165 and f4 <= 200 ) and \
             (f5 >= 160 and f5 <= 200 ) and \
             (mpu == 1 ):
                print("I love you")
                engine.say("i love you")
                engine.runAndWait()
          elif (f1 >= 130 and f1 <= 160) and \
               (f2 >= 250 and f2 <= 255) and \
               (f3 >= 250 and f3 <= 255) and \
               (f4 >= 250 and f4 <= 255) and \
               (f5 >= 160 and f5 <= 175) and \
               (mpu == 2):
                print("Telephone")
                engine.say("telephone")
                engine.runAndWait()
          elif (f1 >= 200 and f1 <= 220) and \
               (f2 >= 250 and f2 <= 255) and \
               (f3 >= 250 and f3 <= 255) and \
               (f4 >= 160 and f4 <= 170) and \
               (f5 >= 200 and f5 <= 240) and \
               (mpu == 2):
                print("You")
                engine.say("You")
                engine.runAndWait()
          elif (f1 >= 200 and f1 <= 220) and \
               (f2 >= 250 and f2 <= 255) and \
               (f3 >= 250 and f3 <= 255) and \
               (f4 >= 160 and f4 <= 170) and \
               (f5 >= 200 and f5 <= 240) and \
               (mpu == 1):
                print("One")
                engine.say("one")
                engine.runAndWait()
          elif ( f1 >= 180 and f1 <= 220 ) and \
             ( f2 >= 150 and f2 <= 190 ) and \
             (f3 >= 150 and f3 <= 200 ) and \
             ( f4 >= 150 and f4 <= 180 ) and \
             (f5 >= 200 and f5 <= 240 ) and \
             (mpu == 1 ):
                print("Water")
                engine.say("water")
                engine.runAndWait()
          elif (f1 >= 200 and f1 <= 220 ) and \
             ( f2 >= 250 and f2 <= 255 ) and \
             (f3 >= 160 and f3 <= 200) and \
             ( f4 >= 150 and f4 <= 190 ) and \
             (f5 >= 200 and f5 <= 230 ) and \
             (mpu == 1 ):
                print("Peace")
                engine.say("peace")
                engine.runAndWait()
          elif (f1 >= 130 and f1 <= 160) and \
               (f2 >= 250 and f2 <= 255) and \
               (f3 >= 250 and f3 <= 255) and \
               (f4 >= 250 and f4 <= 255) and \
               (f5 >= 160 and f5 <= 175) and \
               (mpu == 1):
                print("Wrong")
                engine.say("wrong")
                engine.runAndWait()
          elif (f1 >= 190 and f1 <= 230) and \
               (f2 >= 250 and f2 <= 255) and \
               (f3 >= 250 and f3 <= 255) and \
               (f4 >= 250 and f4 <= 255) and \
               (f5 >= 200 and f5 <= 240) and \
               (mpu == 4):
                print("Work")
                engine.say("Work")
                engine.runAndWait()
          else :
               print("")




    print("Closing connection")
    client.close()

