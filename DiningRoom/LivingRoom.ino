unsigned long Time; 
unsigned long time1 = 0;
unsigned long time2 = 0;
unsigned long time3 = 0;

const int LedOut = 1;
const int PIR = 8;
const int pinSpeaker = 2;
const int AllowLed = 13; 
const int button = 0;

int detect = HIGH;
int speaker = LOW;

bool LedButtonStatus = false;
bool DetectingButtonStatus = false;

void setup()
{
  Serial.begin(9600);
  pinMode(button, INPUT);
  pinMode(PIR, INPUT);
  pinMode(AllowLed, OUTPUT);
  pinMode(pinSpeaker, OUTPUT);
  pinMode(LedOut, OUTPUT);
 // count = 0;
}


/*void setspeaker (int a, int b)
{
  count = a + 1;
  period = b;
}*/


//----------TURN ON BUZZER WHEN DECTECTING MOTION----------
void playTone()
{
  //int speaker = digitalRead(pinSpeaker);
  //if (time1 == 0) 
  //{
    //time1 = Time;
   // time2 = Time + 1;
    //Serial.println("HI");
  //}
//  if (count == 5 && time1 == 0)
 //   time2 = Time;
  /*if (Time - time2 > 5010)
  {
    //count == 0;
    digitalWrite(pinSpeaker, LOW);
    if (Time - time2 > 10010) 
    {
       time2 = Time; 
    }
  }
  else*/
  //if (count > 0)
  //{
    if (Time - time2 > 200)
    {
      speaker = !speaker;
      digitalWrite(pinSpeaker, speaker);
      if (speaker)
      {
        /*Serial.println(count - 1);
        count -= period;*/
        Serial.println("Detect motion!");
      }
      time2 = Time; 
    }
  //}
  //time1 = (count == 0) ? 0 : time1;
 // time2 = ((Time - time2) == 0) ? 0 : time2;
}


//---------CHANGE LED STATUS AND PIR DETECTION WHEN BUTTON PRESSED----------
int ChangeLedStatus(int button, int number)
{ 
  if (number == 1)
  {
    //count = 0;  
    detect = HIGH;
    int led = digitalRead(AllowLed);
    digitalWrite(pinSpeaker, LOW);
    //count = 0;
    if (led == 1) Serial.println("Disable detection!\n");
    else 
    {
      Serial.println("Enable detection!\n");
      time3 = Time;
    }
    digitalWrite(AllowLed, !led);
  }
  else 
  {
    int led = digitalRead(LedOut);
    if (led == 1) Serial.println("Turn off led!");
    else Serial.println("Turn on led!");
    digitalWrite(LedOut, !led);
  }  
  return !button;
}


//---------IDENTIFY WHICH BUTTON IS PRESSED-----------
void button_choose()
{
  int Time = millis();
  if (Time - time1 > 20)
  {
    int button_A0 = analogRead(button);
    if (button_A0 > 305 && button_A0 < 325)// PIR
    {
      if (DetectingButtonStatus == false)
      { 
        DetectingButtonStatus = ChangeLedStatus(DetectingButtonStatus, 1);
        DetectingButtonStatus = true;
        //Serial.println(button_A0);
      }
    }
    else if (button_A0 > 505 && button_A0 < 525)// LED
    {
      if (LedButtonStatus == false)
      {
        LedButtonStatus = ChangeLedStatus(LedButtonStatus, 2);  
        LedButtonStatus = true;
        //Serial.println(button_A0);
      }
    }
    else
    {
      if (DetectingButtonStatus == true)
      {
        DetectingButtonStatus  = false;
      }
      if (LedButtonStatus == true)
        LedButtonStatus = false;
    }
    time1 = Time;
  }
}


void loop()
{
  Time = millis();
  button_choose();
  //---------------detect people by PIR---------------
  if (digitalRead(AllowLed) == HIGH)
  {
    if (!digitalRead(PIR))
    {
      if (detect == HIGH)// && count == 0)
      {
        detect = LOW;
        //setspeaker(5, 1);
       // Serial.println(count);
        digitalWrite(pinSpeaker, LOW);
        Serial.println("Buzzer OFF!");
      }
    }
    else
    {
      if (Time - time3 > 2500)
      {
        if (detect == LOW)// && count == 6)
        {
          detect = HIGH;
      //  Serial.println(count);
          Serial.println("Buzzer ON!");
        //setspeaker(5, 1);
        }
        playTone();
      }
    }
  }
            
  //-----------when button for accessing is pressed-----------
  /*if (digitalRead(AccessingButton))
  { 
    //button was not pressed before pressing
    if (AccessingButtonStatus == LOW)
      AccessingButtonStatus = ChangeLedStatus(AccessingButtonStatus, 1);
   // digitalWrite(LedOut, LOW);
   }
   else AccessingButtonStatus = LOW;//button is not pressed


 // if (digitalRead(AllowSignal) == 0)
  //{
    //-----------when button for controlling led is pressed-----------
    if (digitalRead(LedButton))
    {
      //button was not pressed before pressing
      if (LedButtonStatus == LOW)
          LedButtonStatus = ChangeLedStatus(LedButtonStatus, 2);
    }
    else LedButtonStatus = LOW;//button is not pressed
 
  //}
  //else*/

    //if (count != 0 && detect == HIGH) playTone();
  
}
