#include <LiquidCrystal_I2C.h>

#include <DHT.h>


const int PumpWater = 1;
const int button = 5;
const int Soil = 2;
const int delay_pump = 5000;


unsigned long Time = 0;
unsigned long time1 = 0;
unsigned long time2 = 0;
unsigned long time_but = 0;
unsigned long time_auto = 0;

int pump = LOW;
int Status = LOW;
bool Auto = true;

LiquidCrystal_I2C lcd(0x27,16,2);
DHT dht(8, DHT11);

void Button(int&, bool &);
void ReadTemp(float);

void setup() {
  lcd.begin();
  lcd.backlight();
  pinMode(PumpWater,OUTPUT);
  pinMode(button, INPUT);
  dht.begin();
  Serial.begin(9600); // open serial port, set the baud rate as 9600 bps
}

void loop() 
{
  Time = millis();
  int val;
  val = analogRead(Soil); //connect sensor to Analog 2
  
  float temp = (float)dht.readTemperature();
  ReadTemp(temp);

  if (Time - time_but > 100)
  {
    Button(Status, Auto);
    time_but = Time;  
  }
  
  if (Time - time2 > 500)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Temp:");
    lcd.print(temp);
    if (val > 900)
    {
      lcd.setCursor(11,0);
      lcd.print("- DRY");  
    }
    else if (val < 700)
    {
      lcd.setCursor(11,0);
      lcd.print("- WET");  
    }
    if (!pump)
    {
      lcd.setCursor(4,1);
      lcd.print("Pump ON");
    }
    else
    {
      lcd.setCursor(4,1);
      lcd.print("Pump OFF");
    }
    Serial.println(val);
    if (Auto == true)
    {
      if ( val > 900 && temp <= 30) 
      {  
        Serial.println("Dry");
        Serial.println("Pump ON");
        pump = LOW;
        digitalWrite(PumpWater, pump);
        //lcd.setCursor(11,0);
        //lcd.print("- DRY");
        //lcd.setCursor(2,1);
        //lcd.print("Pump ON");
      }
      else if (val < 700)
      {  
        Serial.println("Wet");
        Serial.println("Pump OFF");
        pump = HIGH;
        digitalWrite(PumpWater, pump);
        //lcd.setCursor(11,0);
        //lcd.print("- WET");
        //lcd.setCursor(2,1);
        //lcd.print("Pump OFF");
      }
    }
    time2 = Time;
  }
}


void ReadTemp(float _temp)
{
  if (Time - time1 > 2000)
  {
    Serial.print("Temperature: ");
    Serial.println(_temp);
    time1 = Time;
  }
}

void Button(int& _Status, bool& _Auto)
{
  if (!digitalRead(button))
  {
    if (_Status == LOW)
    {
      _Status = HIGH;
      Auto = false;
      time_auto = Time;
      if (pump == HIGH)
        pump = LOW;
      else
        pump = HIGH;
      digitalWrite(PumpWater, pump);
      /*if (pump) { 
        Serial.println("Pump OFF");
        lcd.setCursor(2,1);
        lcd.print("Pump OFF");
      }
       else { 
       Serial.println("Pump ON");
       lcd.setCursor(2,1);
       lcd.print("Pump ON");
       }*/
    }
  }
  else
  {
    if (_Status == HIGH)  
      _Status = LOW;
  }
  if (Auto == false)
  {
    if (Time - time_auto > delay_pump)
    {
      Auto = true;
    }
  }
}
