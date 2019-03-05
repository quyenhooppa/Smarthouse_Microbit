const int PushButton = 7;
const int LedOut = 9;
const int PIR = 8;
const int pinSpeaker = 10;
int detect = 1;
bool ButtonStatus = 0;
bool LedStatus = 0;//determine the status of led


void setup() 
{
  Serial.begin(9600);
  Serial.println("Microbit is ready!\n");
  pinMode(PushButton, INPUT);
  pinMode(pinSpeaker, OUTPUT);
  pinMode(LedOut, OUTPUT);
}


//----------turn on buzzer when dectectin motion----------
void playTone(long duration, int freq)
{
  duration *= 1000;
  int count = duration;
  int period = (1.0 / freq) * 1000;
  long elapsed_time = 0;
  while (elapsed_time < duration)
  {
    Serial.println(count/1000);
    digitalWrite(pinSpeaker,HIGH);
    delay(period / 2);
    digitalWrite(pinSpeaker, LOW);
    delay(period / 2);
    count = count - period;
    elapsed_time += (period);
  }
    Serial.println(count/1000);  
}



void loop()
{  
 //-----------when button is pressed-----------
  if (digitalRead(PushButton)) 
  {
    //button was not pressed before pressing 
    if (ButtonStatus == 0) 
    {
      LedStatus = !LedStatus;
      ButtonStatus = 1;
      Serial.print("Button pressed: ");
      Serial.println(LedStatus);
    }
    digitalWrite(LedOut, LedStatus);
    delay(200);
  }
  else ButtonStatus = 0;//button is not pressed

  
//---------------detect people by PIR---------------
  if (!digitalRead(PIR))
  {
    if (detect == 1)
    {
      detect = 0;
      Serial.println("No motion!");
    }
    delay(100);   
  }
  else
  {
    if (detect == 0) 
    {
      detect = 1; 
      Serial.println("Detect motion!"); 
      playTone(5, 1);//5s delay with 1s frequency
    }
  }
}
