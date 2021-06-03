#include <ArduinoHttpClient.h>   
#include <WiFiNINA.h>          
#include <Adafruit_MPU6050.h>   
#include <Adafruit_Sensor.h>    
#include <Wire.h>           


// here we are taking the reading of the flex sensors ( from ports : A1,A2,A3,..etc) and assigning them to to variables : finger_1, finger_2, ..etc.
#define Finger_1 analogRead(A1) // finger_1 representhe pinky finger
#define Finger_2 analogRead(A2) // ring finger 
#define Finger_3 analogRead(A3) // middle finger 
#define Finger_4 analogRead(A4) // index finger 
#define Finger_5 analogRead(A5) // thumb finger 


Adafruit_MPU6050 mpu;


/////// Wifi Settings ///////
char ssid[] = ""; // your ssid ( wifi name ) 
char pass[] = ""; // wifi password 

char serverAddress[] = "";  // put here your server address
int port = 8090;            // the port number 

WiFiClient wifi;
WebSocketClient client = WebSocketClient(wifi, serverAddress, port);
int status = WL_IDLE_STATUS;


//variables 
int f1 =0;
int f2 = 0;
int f3 = 0;
int f4 = 0;
int f5 =0;





void setup() {


Serial.begin(115200);

  // Trying to initialize the mpu!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");


// mpu settings : 

  // set accelerometer range to +-8G
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

  // set gyro range to +- 500 deg/s
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);

  // set filter bandwidth to 21 Hz
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

    // trying to connect to the network
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                   // print the network name (SSID);

    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);
  }

  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}











void loop() {

 
  Serial.println("starting WebSocket client");
  client.begin();


  while (client.connected()) {

  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  
    
f1 = map(Finger_1, 0, 1023, 0, 255);
f2= map(Finger_2, 0, 1023, 0, 255);
f3= map(Finger_3, 0, 1023, 0, 255);
f4 = map(Finger_4, 0, 1023, 0, 255);
f5 = map(Finger_5, 0, 1023, 0, 255);


//here we declaring a string value cause we will send the data to the server as a string, the first character of the string will be "9"
// "9" is an arbitrary character, the purpose of it so we can know the begining of our string data that will be sent to the server. 

String thisString = String(9);;    

// here we are concatenating the sensors values to the string we created above..
thisString.concat(f1); 
thisString.concat(f2); 
thisString.concat(f3);
thisString.concat(f4);
thisString.concat(f5);


// ========= for demonstration puroposes =======
//Serial.println("Flex Sensors data and gyroscope data ( to know position of the hand ) :");
//Serial.print("Finger1 : ");
//Serial.println(f1);
//Serial.print("Finger2 : ");
//Serial.println(f2);
//Serial.print("Finger3 : ");
//Serial.println(f3);
//Serial.print("Finger4 : ");
//Serial.println(f4);
//Serial.print("Finger5 : ");
//Serial.println(f5);
//
//// mpu angels data 
//Serial.print("Angle X : ");
//Serial.print(a.acceleration.x);
//Serial.print(" Angle Y : ");
//Serial.print(a.acceleration.y);
//Serial.print(" Angle Z : ");
//Serial.println(a.acceleration.z);
//
//Serial.print("Position : ");

//==========================================



// here we going check the postion of the hand and attach ( to the string data above that contains sensors data ) an arbitrary character or number to represent that position
// the purposes of the numbers we attaching to the string is to represent the position of the hand , you can replace the numbers with any characters or numbers you want  

// if the hand in a position SIMILAR to the "a" letter in sign language , then concatenate "1" to the string 
if ( (  (int)(a.acceleration.x) <= -6 &&  (int)(a.acceleration.x) >= -9 ) &&
    ( (int)(a.acceleration.y) <= 3 && (int)(a.acceleration.y) >= -3 ) ) {
    thisString.concat(1);
    Serial.println(1);  // for demonstration purposes
}
// if the hand in a position SIMILAR to the "h" letter in sign language , then concatenate "2" to the string 
else if ( ( (int) (a.acceleration.x) <= 5 &&  (int)(a.acceleration.x) >= -1 )  &&
         ( (int)(a.acceleration.y) <= -7 && (int)(a.acceleration.y) >= -9 ) )  {
  thisString.concat(2);
  Serial.println(2); // for demonstration purposes
}
// if the hand in a position SIMILAR to the "Q" letter in sign language , then concatenate "3" to the string 
else if ( ( (int)(a.acceleration.x) <= 10 &&  (int)(a.acceleration.x) >= 7 )  &&
         ( (int)(a.acceleration.y) <= 3 && (int)(a.acceleration.y) >= -3 ) ) {
  thisString.concat(3);
  Serial.println(3); // for demonstration purposes
}
// if the hand were MOVING from up to down SIMILAR to the "work" word in sign language , then concatenate "4" to the string 
else if ( (  (int)a.acceleration.x >= 0 && (int)a.acceleration.x <= 2  ) && 
       ( (int)a.acceleration.y > -1 && (int)a.acceleration.y < 2 ) &&
     (  (int)a.acceleration.z > 10 || (int)a.acceleration.z < 8 ) ) {
         thisString.concat(4);
         Serial.println(4);
     }
// otherwise concatenate "5" to the string 
else {
 thisString.concat(5);
 Serial.println(5);
}

// ========= for demonstrating puroposes =======

 Serial.print("The data will be sent to the server as :");
 Serial.println(thisString);
//=================================================


// here we are sending the final data to the server 
client.print(thisString);

    
    client.endMessage();

// ending of sending data ..




    // check if a message is available to be received
    int messageSize = client.parseMessage();

    if (messageSize > 0) {
      Serial.println("Received a message:");
      Serial.println(client.readString());
    }

    // wait
    delay(300);
  }

  Serial.println("disconnected");
}
