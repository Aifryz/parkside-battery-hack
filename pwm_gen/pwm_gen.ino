// OC1A, PB1, pin9
volatile uint16_t counter;
const uint8_t pattern[5] = {0x00, 0x88, 0x33, 0x44, 0x77};
void setup() {
  // put your setup code here, to run once:
  //pinMode (9, INPUT) ;
  //digitalWrite (9, LOW) ;
  digitalWrite (9, HIGH) ;
   pinMode (9, OUTPUT) ;  
  Serial.begin(9600);
  
  Serial.println("Hello!!!dfdfgdgj");
Serial.println(String(TCCR0A, HEX).c_str());
  Serial.println(String(TCCR0B, HEX).c_str());

  Serial.println(String(TCCR1A, HEX).c_str());
  Serial.println(String(TCCR1B, HEX).c_str());

 Serial.println(String(TCCR2A, HEX).c_str());
  Serial.println(String(TCCR2B, HEX).c_str()); 
Serial.println(F_CPU);
delay(585);
delay(12);
TCCR1A = 0;
TCCR1B = (1<<CS11) | (1<<WGM12);
uint16_t time = 1999;
OCR1AH = time>>8;
OCR1AL = time&0xFF;
TIMSK1 |= (1<<OCIE1A);
Serial.println("start");
sei();

}
volatile int cnt;
ISR(TIMER1_COMPA_vect){  //change the 0 to 1 for timer1 and 2 for timer2
   //interrupt commands here
   cnt += 1;
   if(counter <40)
   {
     uint32_t idx = counter/8;
     uint32_t sub = counter%8;     
     uint8_t val = pattern[idx];
     uint8_t bval = val&(1<<(7-sub));
     digitalWrite(9, bval);
   }

   counter+= 1;

   if(counter >= 40+205-2)
   {
     counter = 0;
   }
   
}
void loop() {
  // put your main code here, to run repeatedly:
  delay(1);
  Serial.println(cnt);
}
