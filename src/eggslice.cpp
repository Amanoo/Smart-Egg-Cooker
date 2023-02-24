//#include <Arduino.h>
#include "eggslice.h"
//<App !Start!>
// FILE: [eggslice.ino]
// Created by GUIslice Builder version: [0.17.b18]
//
// GUIslice Builder Generated File
//
// For the latest guides, updates and support view:
// https://github.com/ImpulseAdventure/GUIslice
//
//<App !End!>
//using namespace esphome;

// ------------------------------------------------
// Headers to include
// ------------------------------------------------
#include "eggslice_GSLC.h"
#include <Preferences.h>
#include "WiFi.h"

// ------------------------------------------------
// Program Globals
// ------------------------------------------------

// some multithreading
TaskHandle_t WiFiSearchTask;
bool wifirunning = false;

//GPIO
#define heater 13
#define backlight 26
#define buzzer 0

//Preferences myPrefs;

//WiFi
uint8_t wifisignal = 0;
char* ssid;
char* pass;

//timer
bool timer_running = false;
int timer_seconds = 0;
int64_t seconds_passed = 0;


//bit of anti-spam
uint32_t lastMillis;

Switch *state_ {nullptr};
Sensor *secs_ {nullptr};
Select *hardness_ {nullptr};
Select *size_ {nullptr};


// Save some element references for direct access
//<Save_References !Start!>
gslc_tsGui                      m_gui;
gslc_tsDriver                   m_drv;
gslc_tsFont                     m_asFont[MAX_FONT];
gslc_tsPage                     m_asPage[MAX_PAGE];

//<GUI_Extra_Elements !Start!>
gslc_tsElem                     m_asPage1Elem[MAX_ELEM_PG_MAIN_RAM];
gslc_tsElemRef                  m_asPage1ElemRef[MAX_ELEM_PG_MAIN];
gslc_tsElem                     m_asPage2Elem[MAX_ELEM_PG_WIFI_RAM];
gslc_tsElemRef                  m_asPage2ElemRef[MAX_ELEM_PG_WIFI];
gslc_tsElem                     m_asPage3Elem[MAX_ELEM_PG_PASSWD_RAM];
gslc_tsElemRef                  m_asPage3ElemRef[MAX_ELEM_PG_PASSWD];
gslc_tsElem                     m_asKeypadAlphaElem[1];
gslc_tsElemRef                  m_asKeypadAlphaElemRef[1];
gslc_tsXKeyPad                  m_sKeyPadAlpha;
gslc_tsXListbox                 m_sListbox2;
// - Note that XLISTBOX_BUF_OH_R is extra required per item
char                            m_acListboxBuf2[94 + XLISTBOX_BUF_OH_R];
gslc_tsXSlider                  m_sListScroll2;

gslc_tsElemRef* eggImg_hard = NULL;
gslc_tsElemRef* eggImg_med = NULL;
gslc_tsElemRef* eggImg_soft = NULL;
gslc_tsElemRef* eggSizeLabel = NULL;
gslc_tsElemRef* m_pListSlider2 = NULL;
gslc_tsElemRef* passwordInput = NULL;
gslc_tsElemRef* startLabel = NULL;
gslc_tsElemRef* timerLabel = NULL;
gslc_tsElemRef* wifiImg_100 = NULL;
gslc_tsElemRef* wifiImg_33 = NULL;
gslc_tsElemRef* wifiImg_66 = NULL;
gslc_tsElemRef* wifiImg_off = NULL;
gslc_tsElemRef* wifiListBox = NULL;
gslc_tsElemRef* wifiNameLabel = NULL;
gslc_tsElemRef* m_pElemKeyPadAlpha = NULL;
//<Save_References !End!>

// ------------------------------------------------
// Callback Methods
// ------------------------------------------------
// Common Button callback
bool CbBtnCommon(void* pvGui, void* pvElemRef, gslc_teTouch eTouch, int16_t nX, int16_t nY) {
  // Typecast the parameters to match the GUI and element types
  gslc_tsGui* pGui = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem* pElem = gslc_GetElemFromRef(pGui, pElemRef);

  if (eTouch == GSLC_TOUCH_UP_IN) {

    // From the element's ID we can determine which button was pressed.
    switch (pElem->nId) {
      //<Button Enums !Start!>
      case E_ELEM_WIFIOFF:
      case E_ELEM_WIFI33:
      case E_ELEM_WIFI66:
      case E_ELEM_WIFI100:
        if (!wifirunning) {                             //if we're not already looking for networks, start new network task
          gslc_ElemXListboxReset(&m_gui, wifiListBox);  //Empty WiFi list
          xTaskCreatePinnedToCore(                      //create a new thread
            findWiFi,                                   //run the command to find new WiFi networks
            "Find-WiFi",                                /* Name of the task */
            10000,                                      /* Stack size in words */
            NULL,                                       /* Task input parameter */
            1,                                          /* Priority of the task */
            &WiFiSearchTask,                            /* Task handle. */
            0);                                         /* Core where the task should run */
        }

        gslc_SetPageCur(&m_gui, E_PG_WIFI);  //open WiFi menu
        break;
      case E_ELEM_BIGGER:
        //increase egg size if timer is not running
        if (!timer_running){
          auto call = size_->make_call();
          call.select_next(false);
          call.perform();
        }
        break;
      case E_ELEM_SMALLER:
        //decrease egg size if timer is not running
        if (!timer_running){
          auto call = size_->make_call();
          call.select_previous(false);
          call.perform();
        }
        break;
      case E_ELEM_SOFTER:
        //decrease hardness if timer is not running
        if (!timer_running){
          auto call = hardness_->make_call();
          call.select_previous(false);
          call.perform();
        }
        break;
      case E_ELEM_HARDER:
        //increase hardness if timer is not running
        if (!timer_running){
          auto call = hardness_->make_call();
          call.select_next(false);
          call.perform();
        }
        break;
      case E_ELEM_STARTBTN:
        //start or stop the timer
        if (timer_running) {
          timerOff();
        } else {
          timerOn();
        }
        break;
      case E_ELEM_BTN10:  //go back to mainscreen
        gslc_SetPageCur(&m_gui, E_PG_MAIN);
        break;
      case E_ELEM_PASSINPUT:
        // Clicked on edit field, so show popup box and associate with this text field
        gslc_ElemXKeyPadInputAsk(&m_gui, m_pElemKeyPadAlpha, E_POP_KEYPAD_ALPHA, passwordInput);
        break;
      case E_ELEM_BTN11:
        gslc_SetPageCur(&m_gui, E_PG_WIFI);  //go back
        break;
      case E_ELEM_WIFIOKBTN:
        //Get WiFi credentials, save them, connect to them
        ssid = gslc_ElemGetTxtStr(&m_gui, wifiNameLabel);
        pass = gslc_ElemGetTxtStr(&m_gui, passwordInput);

        esphome::wifi::global_wifi_component->save_wifi_sta(std::string(ssid), std::string(pass));
        esphome::wifi::global_wifi_component->retry_connect();
        gslc_ElemSetTxtStr(&m_gui, passwordInput, "");  // empty password
        gslc_SetPageCur(&m_gui, E_PG_MAIN);             //go to main page
        break;
      //<Button Enums !End!>
      default:
        break;
    }
  }
  return true;
}
//<Checkbox Callback !Start!>
//<Checkbox Callback !End!>
// KeyPad Input Ready callback
bool CbKeypad(void* pvGui, void* pvElemRef, int16_t nState, void* pvData) {
  gslc_tsGui* pGui = (gslc_tsGui*)pvGui;
  gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem* pElem = gslc_GetElemFromRef(pGui, pElemRef);

  // From the pvData we can get the ID element that is ready.
  int16_t nTargetElemId = gslc_ElemXKeyPadDataTargetIdGet(pGui, pvData);
  if (nState == XKEYPAD_CB_STATE_DONE) {
    // User clicked on Enter to leave popup
    // - If we have a popup active, pass the return value directly to
    //   the corresponding value field
    switch (nTargetElemId) {
        //<Keypad Enums !Start!>

      case E_ELEM_PASSINPUT:
        gslc_ElemXKeyPadInputGet(pGui, passwordInput, pvData);
        gslc_PopupHide(&m_gui);
        break;
      //<Keypad Enums !End!>
      default:
        break;
    }
  } else if (nState == XKEYPAD_CB_STATE_CANCEL) {
    // User escaped from popup, so don't update values
    gslc_PopupHide(&m_gui);
  }
  return true;
}
//<Spinner Callback !Start!>
//<Spinner Callback !End!>
bool CbListbox(void* pvGui, void* pvElemRef, int16_t nSelId) {
  gslc_tsGui* pGui = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem* pElem = gslc_GetElemFromRef(pGui, pElemRef);
  char acTxt[MAX_STR + 1];

  if (pElemRef == NULL) {
    return false;
  }

  // From the element's ID we can determine which listbox was active.
  switch (pElem->nId) {
      //<Listbox Enums !Start!>

    case E_ELEM_WIFILISTBOX:  //Element on our WiFi list was pressed
      if (nSelId != XLISTBOX_SEL_NONE) {
        gslc_ElemXListboxGetItem(&m_gui, pElemRef, nSelId, acTxt, MAX_STR);  //get selected WiFi SSID
        //Serial.println(acTxt);
        gslc_ElemSetTxtStr(&m_gui, wifiNameLabel, acTxt);  //put WiFi SSID as the page title
        gslc_SetPageCur(&m_gui, E_PG_PASSWD);
      }
      break;
    //<Listbox Enums !End!>
    default:
      break;
  }
  return true;
}
//<Draw Callback !Start!>
//<Draw Callback !End!>

// Callback function for when a slider's position has been updated
bool CbSlidePos(void* pvGui, void* pvElemRef, int16_t nPos) {
  gslc_tsGui* pGui = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem* pElem = gslc_GetElemFromRef(pGui, pElemRef);
  int16_t nVal;
  gslc_tsElemRef* pElemRefTmp = NULL;

  // From the element's ID we can determine which slider was updated.
  switch (pElem->nId) {
      //<Slider Enums !Start!>

    case E_LISTSCROLL2:
      // Fetch the slider position
      nVal = gslc_ElemXSliderGetPos(pGui, m_pListSlider2);
      // Update the textbox scroll position
      pElemRefTmp = gslc_PageFindElemById(pGui, E_PG_WIFI, E_ELEM_WIFILISTBOX);
      gslc_ElemXListboxSetScrollPos(pGui, pElemRefTmp, nVal);
      break;
    //<Slider Enums !End!>
    default:
      break;
  }

  return true;
}

//<Tick Callback !Start!>
//<Tick Callback !End!>

// ------------------------------------------------
// Create graphic elements
// ------------------------------------------------

//Update GUI element that displays WiFi signal strength
void update_wifi() {
  if (gslc_GetPageCur(&m_gui) == E_PG_MAIN) {  //stop flickering if not focused on the correct page
    if (wifisignal == 0) {
      gslc_ElemSetVisible(&m_gui, wifiImg_off, true);
      gslc_ElemSetVisible(&m_gui, wifiImg_33, false);
      gslc_ElemSetVisible(&m_gui, wifiImg_66, false);
      gslc_ElemSetVisible(&m_gui, wifiImg_100, false);
    } else if (wifisignal == 1) {
      gslc_ElemSetVisible(&m_gui, wifiImg_off, false);
      gslc_ElemSetVisible(&m_gui, wifiImg_33, true);
      gslc_ElemSetVisible(&m_gui, wifiImg_66, false);
      gslc_ElemSetVisible(&m_gui, wifiImg_100, false);
    } else if (wifisignal == 2) {
      gslc_ElemSetVisible(&m_gui, wifiImg_off, false);
      gslc_ElemSetVisible(&m_gui, wifiImg_33, false);
      gslc_ElemSetVisible(&m_gui, wifiImg_66, true);
      gslc_ElemSetVisible(&m_gui, wifiImg_100, false);
    } else {
      gslc_ElemSetVisible(&m_gui, wifiImg_off, false);
      gslc_ElemSetVisible(&m_gui, wifiImg_33, false);
      gslc_ElemSetVisible(&m_gui, wifiImg_66, false);
      gslc_ElemSetVisible(&m_gui, wifiImg_100, true);
    }
  }
}

//Update GUI element that displays egg hardness
void update_egg() {
  if (hardness_->active_index() == 0) {
    gslc_ElemSetVisible(&m_gui, eggImg_soft, true);
    gslc_ElemSetVisible(&m_gui, eggImg_med, false);
    gslc_ElemSetVisible(&m_gui, eggImg_hard, false);
  } else if (hardness_->active_index() == 1) {
    gslc_ElemSetVisible(&m_gui, eggImg_soft, false);
    gslc_ElemSetVisible(&m_gui, eggImg_med, true);
    gslc_ElemSetVisible(&m_gui, eggImg_hard, false);
  } else {
    gslc_ElemSetVisible(&m_gui, eggImg_soft, false);
    gslc_ElemSetVisible(&m_gui, eggImg_med, false);
    gslc_ElemSetVisible(&m_gui, eggImg_hard, true);
  }
  update_timer();
}

//Update GUI element that displays egg size
void update_size() {
  //auto sizeString = size_->state;
  gslc_ElemSetTxtStr(&m_gui, eggSizeLabel, size_->state.c_str());
  update_timer();
}

//Update GUI element that displays timer
void update_timer() {
  if (!timer_running) timer_seconds = 360 + 40 * size_->active_index().value()+ 180 * hardness_->active_index().value();  //don't use inputs to change the timer if timer is running
  int minutes = timer_seconds / 60;
  int secs = timer_seconds % 60;
  char numstr[6];
  sprintf(numstr, " %02d:%02d  ", minutes, secs);
  gslc_ElemSetTxtStr(&m_gui, timerLabel, numstr);
  secs_->publish_state(timer_seconds);
}

//find WiFi networks and put them in the GUI
void findWiFi(void* parameter) {
  wifirunning = true;
  int n = WiFi.scanNetworks(false, false, false, 150);
  if (n > 0) {
    for (int i = 0; i < n; ++i) { //add networks to list
      gslc_ElemXListboxAddItem(&m_gui, wifiListBox, WiFi.SSID(i).c_str());
    }
  }
  wifirunning = false;
  vTaskDelete(WiFiSearchTask);
}

//constructor
EggCooker::EggCooker(Sensor* secs, Switch* state, Select* size, Select* hardness){
  state_=state;
  secs_=secs;
  size_=size;
  hardness_=hardness;
}

void EggCooker::setup() {

  // ------------------------------------------------
  // Initialize
  // ------------------------------------------------
  pinMode(backlight, OUTPUT);
  digitalWrite(backlight, HIGH);
  pinMode(heater, OUTPUT);
  digitalWrite(heater, LOW);
  pinMode(buzzer, OUTPUT);  // Set buzzer - pin 9 as an output

  // ------------------------------------------------
  // Create graphic elements
  // ------------------------------------------------
  InitGUIslice_gen();

  //update GUI elements related to timer, egg hardness, and egg size
  update_egg();
  update_wifi();
  update_size();
}

// -----------------------------------
// Main event loop
// -----------------------------------
void EggCooker::loop() {

  // ------------------------------------------------
  // Update GUI Elements
  // ------------------------------------------------
  int64_t curr_secs = esp_timer_get_time() / 1000000;  //get system time in seconds
  if (timer_running && curr_secs != seconds_passed) {  //check if a second has already passed, if yes and timer is running, then execute timer code
    if (timer_seconds > 0) {                           //as long as timer still has time left, decrease time.
      timer_seconds--;
      update_timer();
    } else {                      //if timer has run out, run alarm
      digitalWrite(heater, LOW);  //turn heater off
      if (seconds_passed % 2) {
        gslc_ElemSetVisible(&m_gui, timerLabel, true);  //timer visible
        ledcAttachPin(buzzer, 0);                       //buzzer channel 0
        ledcWriteNote(0, NOTE_F, 4);                    // channel 0 play note
      } else {
        gslc_ElemSetVisible(&m_gui, timerLabel, false);  //timer invisible
        ledcDetachPin(buzzer);
      }
    }
  }
  seconds_passed = curr_secs;

  //show current wifi connection
  if (!WiFi.isConnected()) {
    wifisignal = 0;
  } else {
    int strength = WiFi.RSSI();
    if (strength > -70) {
      wifisignal = 3;
    } else if (strength > -85) {
      wifisignal = 2;
    } else {
      wifisignal = 1;
    }
  }
  update_wifi();

  // ------------------------------------------------
  // Periodically call GUIslice update function
  // ------------------------------------------------
  gslc_Update(&m_gui);

}

void timerOn(){
  timer_running = true;
  digitalWrite(heater, HIGH);  //turn on heating
  gslc_ElemSetTxtStr(&m_gui, startLabel, "Stop");
  state_->publish_state(1);
}

void timerOff(){
  timer_running = false;
  digitalWrite(heater, LOW);  //turn heater off
  gslc_ElemSetTxtStr(&m_gui, startLabel, "Start");
  //Reset timer
  gslc_ElemSetVisible(&m_gui, timerLabel, true);  //timer visible
  ledcDetachPin(buzzer);
  update_timer();
  state_->publish_state(0);
}
