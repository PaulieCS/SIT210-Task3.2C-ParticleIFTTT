// This #include statement was automatically added by the Particle IDE.
#include <BH1750.h>

int count = 0;

int hour = Time.hour();

bool alert = false;


BH1750 sensor(0x23, Wire);

void setup()
{
  sensor.begin();

  sensor.set_sensor_mode(BH1750::forced_mode_high_res2);

  Serial.begin();
  
  Time.zone(+10);
  
}

void loop()
{
  int hour = Time.hour();
  if (hour = 0)
  {
      count = 0;
  }
  
  sensor.make_forced_measurement();
  
  float lux = sensor.get_light_level();
  
  if (lux > 29999)
  {
      count++;
  }
  
  if (count > 119 && alert == false)
  {
      Particle.publish("sunlight_limit_reached", PRIVATE);
      alert = true;
  }
  
  delay(60000);
}
