#include "esphome.h"

using namespace esphome;
using namespace api;
using namespace sensor;
using namespace switch_;

//int DebugOut(char);
void InitGUIslice_gen();
bool CbBtnCommon(void *, void *, int, int, int);
bool CbCheckbox(void *, void *, int, bool);
bool CbDrawScanner(void *, void *, int);
bool CbKeypad(void *, void *, int, void *);
bool CbListbox(void *, void *, int);
bool CbSlidePos(void *, void *, int);
bool CbSpinner(void *, void *, int, void *);
bool CbTickScanner(void *, void *);
void InitGUIslice_gen();
//int DebugOut(char);
bool CbBtnCommon(void *, void *, int, int, int);
bool CbKeypad(void *, void *, int, void *);
bool CbListbox(void *, void *, int);
bool CbSlidePos(void *, void *, int);
void update_wifi();
void update_egg();
void update_size();
void update_timer();
void findWiFi(void *);
void timerOn();
void timerOff();
class EggCooker : public Component, public CustomAPIDevice {
  public:
    EggCooker(Sensor *secs, Switch *state);
    void setup() override;
    void loop() override;
    //void timerOn();

  private:

    //void stopService();
};
