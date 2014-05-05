import processing.serial.*;

Serial myPort;
String port = "/dev/tty.usbmodem3a21";
int baud = 9600;
int threshold = 18; //distance in inches
int distance = -1;

void setup() 
{
  size( 500, 500 );
  frameRate( 60 );
  
  // List all the available serial ports:
  println(Serial.list());
  
  // Open the port you are using at the rate you want:
  myPort = new Serial(this, port, baud);
  
}

void draw ()
{
  if(myPort.available() > 0){
     distance = myPort.read();
     println(distance);
  }
  color bg = color(255,0,0);
  if( distance <= threshold) bg = color(0,255,0);
  background( bg );
}
