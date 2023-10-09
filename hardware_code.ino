const int pingPin1 = 6;
const int echoPin1 = 7;
const int pingPin2 = 8;
const int echoPin2 = 9;
const int pingPin3 = 10;
const int echoPin3 = 11;
const int pingPin4 = 12;
const int echoPin4 = 13;
const int GREENLIGHT1 = 2;
const int REDLIGHT1 = 3;
const int GREENLIGHT2 = 4;
const int REDLIGHT2 = 5;
const int MIN_DISTANCE = 5;


int duration1 = 0;
int cm1 = 0;
int duration2 = 0;
int cm2 = 0;
int duration3 = 0;
int cm3 = 0;
int duration4 = 0;
int cm4 = 0;
int trafficLevel1 = 0;
int trafficLevel2 = 0;
int averageTrafficTrial1[10];
int averageTrafficTrial2[10];
int turn = 1;
int trafficLevel1Predicted = 0;
int trafficLevel2Predicted = 0;


void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  pinMode(pingPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(pingPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(pingPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(pingPin4, OUTPUT);
  pinMode(echoPin4, INPUT);
  pinMode(GREENLIGHT1, OUTPUT);
  pinMode(REDLIGHT1, OUTPUT);
  pinMode(GREENLIGHT2, OUTPUT);
  pinMode(REDLIGHT2, OUTPUT);
}

void loop() {
  for(int i = 0; i<10; i++){  
    digitalWrite(pingPin1, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin1, HIGH);
    delayMicroseconds(5);
    digitalWrite(pingPin1, LOW);
    duration1 = pulseIn(echoPin1, HIGH);



    digitalWrite(pingPin2, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin2, HIGH);
    delayMicroseconds(5);
    digitalWrite(pingPin2, LOW);
    duration2 = pulseIn(echoPin2, HIGH);


    digitalWrite(pingPin3, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin3, HIGH);
    delayMicroseconds(5);
    digitalWrite(pingPin3, LOW);
    duration3 = pulseIn(echoPin3, HIGH);


    digitalWrite(pingPin4, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin4, HIGH);
    delayMicroseconds(5);
    digitalWrite(pingPin4, LOW);
    duration4 = pulseIn(echoPin4, HIGH);




    cm1 = microsecondsToCentimeters(duration1);  
    cm2 = microsecondsToCentimeters(duration2);

    cm3 = microsecondsToCentimeters(duration3);
    cm4 = microsecondsToCentimeters(duration4);




    
    if(cm2 <= MIN_DISTANCE && cm1 <= MIN_DISTANCE){
      trafficLevel1 = 2;
    }
    else if(cm1 <= MIN_DISTANCE && cm2 >= MIN_DISTANCE){
      trafficLevel1 = 1;
    }
    else{
      trafficLevel1 = 0;
    }



    if(cm4 <= MIN_DISTANCE && cm3 <= MIN_DISTANCE){
      trafficLevel2 = 2;
    }
    else if(cm3 <= MIN_DISTANCE && cm4 >= MIN_DISTANCE){
      trafficLevel2 = 1;
    }
    else{
      trafficLevel2 = 0;
    }

    averageTrafficTrial1[i] = trafficLevel1;
    averageTrafficTrial2[i] = trafficLevel2;

    delay(100);
  }



  int trafficLevelSum = 0;
  for(int i = 0; i < 10; i++){
    trafficLevelSum += averageTrafficTrial1[i];
  }


  //FINAL TRAFFIC LEVELS
  trafficLevel1 = ceil(trafficLevelSum/10);

  trafficLevelSum = 0;

  for(int i = 0; i < 10; i++){
    trafficLevelSum += averageTrafficTrial2[i];
  }
  trafficLevel2 = ceil(trafficLevelSum/10);





  //GETTING PREDICTED DATA
  Serial.println("13"); //1 and 3
  delay(50);
  trafficLevel1Predicted = Serial.parseInt();
  Serial.println("24"); //2 and 4
  delay(50);
  trafficLevel2Predicted = Serial.parseInt();




  if (turn == 1){
    
    while(analogRead(A0) >= 500){
      signal2Open(1);
      
    }
    while(analogRead(A1) >= 500){
      signal1Open(1);
      
    }
    switch(trafficLevel1Predicted){
      case 0:
      if(trafficLevel1 > 0){
        signal1Open(10);
      }
      else{
        signal1Open(5);
      }
        break;
      case 1:
      if(trafficLevel1 > 1){
        signal1Open(15);
      }
      else if(trafficLevel1 < 1){
        signal1Open(5);
      }
      else{
        signal1Open(10);
      }

      break;
      case 2:
      if(trafficLevel1 < 1){
        signal1Open(5);
      }
      else if(trafficLevel1 < 2){
        signal1Open(10);
      }
      else{
        signal1Open(15);
      }
        break;
    }
    turn = 2;
  }

  else if (turn == 2){
    while(analogRead(A0) >= 500){
      signal2Open(1);
    }
    while(analogRead(A1) >= 500){
      signal1Open(1);
      
    }

    
    switch(trafficLevel2Predicted){
      case 0:
      if(trafficLevel2 > 0){
        signal2Open(10);
      }
      else{
        signal2Open(5);
      }
        break;
      case 1:
      if(trafficLevel2 > 1){
        signal2Open(15);
      }
      else if(trafficLevel2 < 1){
        signal2Open(5);
      }
      else{
        signal2Open(10);
      }

      break;
      case 2:
      if(trafficLevel2 < 1){
        signal2Open(5);
      }
      else if(trafficLevel2 < 2){
        signal2Open(10);
      }
      else{

        signal2Open(15);
      }
        break;
    }
    turn = 1;
  }

  

}


void signal1Open(float duration){

  digitalWrite(REDLIGHT1, LOW);
  digitalWrite(GREENLIGHT1, HIGH);
  digitalWrite(REDLIGHT2, HIGH);
  digitalWrite(GREENLIGHT2, LOW);
  for(int i = 0; i < duration; i+= 0.01){
    delay(i*1000);
    while(analogRead(A0) >= 500){
      signal2Open(0.01);
      delay(50);
    }
    while(analogRead(A1) >= 500){
      signal1Open(0.01);
      delay(50);
      
    }
  }
 
   
}

void signal2Open(float duration){

  digitalWrite(REDLIGHT2, LOW);
  digitalWrite(GREENLIGHT2, HIGH);
  digitalWrite(REDLIGHT1, HIGH);
  digitalWrite(GREENLIGHT1, LOW);
  for(int i = 0; i < duration; i+=0.01){
    delay(i*1000);
    while(analogRead(A0) >= 500){
      signal2Open(0.01);
      delay(50);
    }
    while(analogRead(A1) >= 500){
      signal1Open(0.01);
      delay(50);
      
    }
  }
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

// void emergency(int lane){
//   while isEmergency{
      
//   }
// }

// bool isEmergency{
//   if(A0 >= 500 || A1 >= 500){
//     return true;
//   }
//   else{
//     return false;
//   }
// }
