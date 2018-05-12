const int analogInPin = A0;
const int indicatorInPin = 5;
const int tumbler = 4;
const int d6 = 6;
int b;
int indicator_viz;
int indicator_bar;
const int warning_led = 7;
const int success_led = 8;
  float p1=10;
  float p2=321;
  float p3=178;
int sensorValue = 0; // переменная для хранения значения датчика
int sensorQuickValue = 0;
int quick_or_accurate;
long nagrev=60000;
long izmer=90000;
long time;
byte stat;

void setup()
{

Serial.begin(9600);
//pinMode(ledPin, OUTPUT);
pinMode(warning_led, OUTPUT);
pinMode(success_led, OUTPUT);
pinMode(tumbler,INPUT_PULLUP);
time=millis();
stat=1; //nagrev

}
void loop()
{ // 71 - у того чувака
quick_or_accurate = digitalRead(tumbler);

if (!quick_or_accurate) {

analogWrite(6, 255);
sensorQuickValue = analogRead(analogInPin); 

b=round(p1*exp((sensorQuickValue-p2)/p3));

indicator_viz = b;
//indicator_bar = sensorQuickValue;

  if (indicator_viz > 20) 
    digitalWrite(warning_led, HIGH);
      else
    digitalWrite(warning_led, LOW);

  if (indicator_viz > 150) indicator_viz = 150;
  analogWrite (indicatorInPin, indicator_viz);

  //if (indicator_bar > 150) indicator_bar = 150;
  //analogWrite (indicatorInPin, indicator_bar);
  
 if (indicator_viz <= 5) 
      digitalWrite(success_led, HIGH);
      else  
      digitalWrite(success_led, LOW);

Serial.print("QUICK_PPM = ");
Serial.println(b);

Serial.print("QUICK_POP = ");
Serial.println(sensorQuickValue);

delay (1000);

}



if ((millis()-time) >= nagrev and stat == 1 and quick_or_accurate == 1) {

stat=2; // izmerenije
Serial.println("1.4 volts");
analogWrite (6, 71);
time=millis();

}  


if ((millis()-time) >= izmer and stat==2 and quick_or_accurate == 1) {
stat=1; // nagrev
Serial.println("5 volts");
analogWrite (6, 0);
delay(10);
sensorValue = analogRead(analogInPin); 

b=round(p1*exp((sensorValue-p2)/p3));
indicator_viz = b;

  if (indicator_viz > 20) 
    digitalWrite(warning_led, HIGH);
      else
    digitalWrite(warning_led, LOW);

  if (indicator_viz > 150) indicator_viz = 150;
  analogWrite (indicatorInPin, indicator_viz);

 if (indicator_viz <= 5) 
      digitalWrite(success_led, HIGH);
      else  
      digitalWrite(success_led, LOW);

Serial.print("ACCURATE_PPM = ");
Serial.println(b);

Serial.print("ACCURATE_POP = ");
Serial.println(sensorValue);


analogWrite(6, 255);
time=millis();
}

}
