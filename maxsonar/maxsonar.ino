/* This script is designed to take several readings from the maxbotix sonar and generate a mode/median.
Author: Jason Lessels & Matt Cook <matt@zebradog.com>
Date created: 2011/June/06
License: GPL (=>2)
This work has been compiled using many sources mainly posts/wiki posts from;
Allen, Bruce (2009/July/23) and Gentles, Bill (2010/Nov/12)
*/

//Set the pin to recieve the signal.
const int pwPin = 7;
//variables needed to store values
int arraysize = 11; //quantity of values to find the median (sample size). Needs to be an odd number
int baud = 9600;

//declare an array to store the samples. not necessary to zero the array values here, it just makes the code clearer
int rangevalue[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
long pulse;
int distance; 
int maxDistance = 255; //max value for single byte. 255" = 21.25'
void setup() {
  //Open up a serial connection
  Serial.begin(9600);
  //Wait for the serial connection
  delay(500);
}
//Main loop where the action takes place
void loop() {
  pinMode(pwPin, INPUT);
  for(int i = 0; i < arraysize; i++)
  {								    
    pulse = pulseIn(pwPin, HIGH);
    rangevalue[i] = pulse/147; //in inches
    delay(10);
  }
  isort(rangevalue,arraysize);
  byte d = mode(rangevalue,arraysize);
  if(d > maxDistance) d = maxDistance;
  Serial.write(d);
 // delay(250);
}

//Sorting function
// sort function (Author: Bill Gentles, Nov. 12, 2010)
void isort(int *a, int n){
// *a is an array pointer function
  for (int i = 1; i < n; ++i)
  {
    int j = a[i];
    int k;
    for (k = i - 1; (k >= 0) && (j < a[k]); k--)
    {
      a[k + 1] = a[k];
    }
    a[k + 1] = j;
  }
}

//Mode function, returning the mode or median.
int mode(int *x,int n){

  int i = 0;
  int count = 0;
  int maxCount = 0;
  int mode = 0;
  int bimodal;
  int prevCount = 0;
  while(i<(n-1)){
    prevCount=count;
    count=0;
    while(x[i]==x[i+1]){
      count++;
      i++;
    }
    if(count>prevCount&count>maxCount){
      mode=x[i];
      maxCount=count;
      bimodal=0;
    }
    if(count==0){
      i++;
    }
    if(count==maxCount){//If the dataset has 2 or more modes.
      bimodal=1;
    }
    if(mode==0||bimodal==1){//Return the median if there is no mode.
      mode=x[(n/2)];
    }
    return mode;
  }
}
