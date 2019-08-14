#include <SoftwareSerial.h>
#define slope 7

int LED2 = 11;
int LED1 = 10;
int LED3 = 9;
SoftwareSerial BTSerial(2,3); //(TX,RX)

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(slope, INPUT);

  BTSerial.begin(9600);

  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  
}

char l[1];
int x=3;

void loop() {
    int m,n,i;
    int a = analogRead(A5); 
    int sum = 0; 
    int ave = 0;
    
    for(i =0; i<100; i++) 
    {
      sum = sum + a; 
      delay(100);
    }
    ave = sum/100;  
    Serial.print("기준치 : ");
    Serial.println(ave);


  int sumA[30]={0};
  int sumB[30]={0};
  int aveA=0;
  
   l[0]='3';
   
  for(n=0;n<29;n++){
     int c = analogRead(A5);
    sumA[n] =  c;
    delay(100);
    }

 while(1){
 
   for(m=0;m<30;m++){

    if(0<m<29)
    {    sumA[m-1] = analogRead(A5);}

    else if(m=0)
    {sumA[29]=analogRead(A5);}

    delay(100);
    for(int z=0;z<30;z++){

     sumB[m] = sumB[m]+ sumA[z];
    }
     
 aveA = sumB[m]/30;
   
  Serial.print("진동 : ");
  Serial.println(aveA);
  Serial.print("기울기 : ");
  Serial.println(digitalRead(slope));
   
  
  if(aveA>=10*ave && aveA<65*ave ){ 
    x=1;
  }else if(aveA>=65*aveA || digitalRead(slope)==HIGH){
    x=2;
  }else{
    x=3;
  }
  
  switch(x){
  case 1:
  l[0]='1';
  BTSerial.write(l[0]);
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  break;

  case 2:
  l[0]='2';
  BTSerial.write(l[0]);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED1, LOW);
  digitalWrite(LED3, LOW);
  break;

  case 3:
  l[0]='3';
  BTSerial.write(l[0]);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  break;
}
sumB[m]={0};
BTSerial.write(l[0]);

 }
 }
}
