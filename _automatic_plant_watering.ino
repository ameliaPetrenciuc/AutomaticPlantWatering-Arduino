#include <LiquidCrystal_I2C.h>
const int sensorpin = A0;//umiditate
const int ANALOG_INPUT = A2; // temp
const int sensorpower = 8;//
const int LED1 = 2;//ROSU
const int LED2 = 3;
const int LED3 = 4;//VERDE
const int pumppin = 9;
int sensorMoisture = 0;
int state = 0;
const int delayTime = 100; 

int wet = 480;
int dry = 751;
                   
int  temp_output ;                                                      
int  revised_temp;                                                      
float temp_C ;  
double Temp ;

int puls = 0; 
int pas = 150; 
LiquidCrystal_I2C lcd(0x27, 16, 2); 

void setup(){
  Serial.begin(9600); 
  lcd.init();          
  lcd.backlight();    
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(sensorpower,OUTPUT);
  pinMode(pumppin,OUTPUT);
  pinMode ( ANALOG_INPUT, INPUT )  ;  
}

void loop() {
  if(Serial.available()>0){
      state=Serial.read();
  }

  temp_output = analogRead ( ANALOG_INPUT ) ;         
  revised_temp= map ( temp_output, 0, 1023, 1023, 0 ) ;
  temp_C    = Thermistor ( revised_temp ) ;

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(float(temp_C/3.08));
  lcd.print(" C");

  lcd.setCursor(0, 1); 
  lcd.print("Umid: ");
  lcd.print(sensorMoisture);
  lcd.print("    "); 
  delay(2000);

  if(state =='0' || (state=='1' && sensorMoisture<wet)){
    analogWrite(pumppin, 0); 
    puls = 0;
    pas = 22;
    Serial.print(float(temp_C/3.08));
    Serial.print("|");
    Serial.print("Pompa:OFF");
    Serial.print("|");

  if (temp_C>55.4 && temp_C<64.4){
    Serial.print("Temperatura ideala pentru crizantema");
    Serial.print("|");
  }else{
    Serial.print("Temperatura prea ridicata pentru crizantema");
    Serial.print("|");
  }
    delay(200);
    state=0;
  }
  else if(state == '1' && sensorMoisture>wet){

    analogWrite(pumppin, updatePWM(puls, pas)); 
      //delay(200);
      Serial.print(float(temp_C/3.08));
      Serial.print("|");
      Serial.print("Pompa:ON");
      Serial.print("|");
    if (temp_C>55.4 && temp_C<64.4){
      Serial.print("Temperatura ideala pentru crizantema");
      Serial.print("|");
    } else {
      Serial.print("Temperatura prea ridicata pentru crizantema");
      Serial.print("|");
    }
    delay(200);
    state=0;
  }
  delay(500);

  digitalWrite(sensorpower,HIGH);
  delay(10);
  sensorMoisture = analogRead(sensorpin);
  digitalWrite(sensorpower,LOW);
  
  //Serial.println(sensor);
  if(sensorMoisture<wet){
    analogWrite(pumppin, 0);
    puls = 0;
    pas = 22;
    //delay(200);
    digitalWrite(LED1,LOW);
    digitalWrite(LED2,LOW);
    digitalWrite(LED3,HIGH);//verde 
  }
  else if(sensorMoisture<dry && sensorMoisture>wet){
    if(state=='1'){
        analogWrite(pumppin, updatePWM(puls, pas));
    }
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, LOW);
  }
  else if(sensorMoisture>dry){
    if(state=='1'){
       analogWrite(pumppin, updatePWM(puls, pas)); 
    }
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
  } 
}

double Thermistor ( int RawADC )
{
  Temp = log (2*((10240000/RawADC)-10000));
  Temp =( 1 / ( 0.001129148 + ( 0.000234125 * Temp ) + ( 0.0000000876741 * Temp * Temp * Temp ) )) ;
  Temp = Temp - 273.15 ;           
  return Temp;
}

int updatePWM(int &puls, int &pas) {
  puls += pas; // Modifică factorul de umplere PWM
  if (puls <= 0 || puls >= 255) {
    pas = -pas; // Inversează direcția modificării la limitele intervalului
  }
  return puls;
}
