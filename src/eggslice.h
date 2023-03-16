#include "esphome.h"

using namespace esphome;
using namespace api;
using namespace sensor;
using namespace switch_;
using namespace select;
using namespace number;

void InitGUIslice_gen();
bool CbBtnCommon(void *, void *, int, int, int);
bool CbCheckbox(void *, void *, int, bool);
bool CbDrawScanner(void *, void *, int);
bool CbKeypad(void *, void *, int, void *);
bool CbListbox(void *, void *, int);
bool CbSlidePos(void *, void *, int);
bool CbSpinner(void *, void *, int, void *);
bool CbTickScanner(void *, void *);
void update_wifi();
void update_egg();
void update_size();
void update_timer();
void update_planner();
void findWiFi(void *);
void timerOn();
void timerOff();
void plannerOn();
void plannerOff();
void set_planner_hours(float x);
void set_planner_mins(float x);
void set_timer_offset(float x);
void set_hardness_offset(float x);
void set_size_offset(float x);
class EggCooker : public Component, public CustomAPIDevice {
  public:
    EggCooker(Sensor *secs, Switch *timerstate, Select* size, Select* hardness, Switch *planOnOff, Number* planninghours, Number* planningminutes,Number* timeroffset, Number* hardnessoffset, Number* sizeoffset);
    void setup() override;
    void loop() override;

  private:

};
