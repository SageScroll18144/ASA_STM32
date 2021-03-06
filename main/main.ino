#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <Adafruit_BMP280.h>

#define ll long long int
#define S0 1000.0

Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);
Adafruit_BMP280 bmp; // I2C Interface

const int parachute = 13;//mudar valor de acordo com a placa

const int maxn = 110;
const int lim = 100;

double queue_weights[maxn];

sensors_event_t event;

uint8_t sys, gyro, accel, mag = 0;

double init_time = 0;

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
  init_time = millis();
  
  DDRD &= ~(1 << DDD2);//configura PD2 como entrada
  DDRD |=  (1 << DDD7);//configura PD7 como saída
  
  PORTD |= (1 << PORTD2);//habilita pull-up interno de PD2
  
  EICRA |= (1 << ISC01) | (1 << ISC00);//configura interrupção externa 0 como borda de subida
  EIMSK |= (1 << INT0);//habilita interrupção externa 0
  
  sei();

  while(!bmp.begin())Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}
void loop() {
  bno.getCalibration(&sys, &gyro, &accel, &mag);
  update_queue(bmp.readAltitude(S0));  
  
  bno.getEvent(&event);
  PORTD = PORTD7 & !((int)event.orientation.y);
}
