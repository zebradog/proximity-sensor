import processing.serial.*;
import controlP5.*;

Serial myPort;
ControlP5 cp5;
String port = "/dev/tty.usbmodem"; //string to search for port by
int baud = 9600;
int threshold = 32; //distance in inches
int maxDistance = 255; //max value for single byte. 255" = 21.25'

PFont f; 

void setup() 
{
  size( 500, 500 );
  frameRate( 60 );
  
  cp5 = new ControlP5(this);
  
  cp5.addSlider("threshold")
     .setPosition(10,height-30)
     .setSize(width-80,20)
     .setRange(0,maxDistance)
     .setValue(threshold)
     ;
  
  //find serial port based on search string
  String[] ports =  Serial.list();
  for(int i = 0; i < ports.length; i++){
        if(ports[i].indexOf(port) >= 0){
           port = ports[i];
           break; 
        };
  }
  
  // Open the port you are using at the rate you want:
  myPort = new Serial(this, port, baud);
  
  f = createFont("Helvetica",128,true); 
  textAlign(CENTER);
  textFont(f); 
}

void draw ()
{
  if(myPort.available() > 0){
     int distance = myPort.read();
     //println(distance);
     myPort.clear();
     color bg = color(128,64,64);
     if( distance <= threshold) bg = color(64,128,64);
     background( bg );
     text(""+distance+"\"",width/2+10,height/2+24);
  }
}
