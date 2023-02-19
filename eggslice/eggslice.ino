#include "eggslice.h"
Sensor sens;
TextSensor text;
EggCooker eggcooker(&sens, &text);

void setup(){
  eggcooker.setup();
}

void loop(){
  eggcooker.loop();
}
