#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

#define BNO055_SAMPLERATE_DELAY_MS (100)

Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);

const int parachute = 13;//mudar valor de acordo com a placa

const int maxn = 110;
const int lim = 100;

double queue_weights[maxn];

sensors_event_t event;

ISR (INT0_vect){
  if(free_fall()) digitalWrite(parachute, !digitalRead(parachute));
  print_queue();
}
void setup() {
  Serial.begin(115200);
  Serial.println("Orientation Sensor Test"); Serial.println("");

  build_queue();
  pinMode(parachute, OUTPUT);
  
  while(!bno.begin()) Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
  
  DDRD &= ~(1 << DDD2);//configura PD2 como entrada
  DDRD |=  (1 << DDD7);//configura PD7 como saída
  
  PORTD |= (1 << PORTD2);//habilita pull-up interno de PD2
  
  EICRA |= (1 << ISC01) | (1 << ISC00);//configura interrupção externa 0 como borda de subida
  EIMSK |= (1 << INT0);//habilita interrupção externa 0
  
  sei();
}
void loop() {
  update_queue(event.orientation.y);  
  bno.getEvent(&event);

  PORTD = PORTD7 & !((int)event.orientation.z);
}
