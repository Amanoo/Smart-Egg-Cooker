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

// ------------------------------------------------
// Headers to include
// ------------------------------------------------
#include "eggslice_GSLC.h"
#include <Preferences.h>

// ------------------------------------------------
// Program Globals
// ------------------------------------------------
//GPIO
#define heater 13
#define backlight 26
#define buzzer 0

Preferences preferences;

//WiFi
uint8_t wifisignal = 0;

//egg properties
uint8_t hardness = 1;
uint8_t size = 0;
char * sizeStrings[4] = {"S ", "M ", "L ", "XL"};

//timer
bool timer_running=false;
int timer_seconds = 0;
int64_t seconds_passed = 0;


// Save some element references for direct access
//<Save_References !Start!>
gslc_tsElemRef* eggImg_hard       = NULL;
gslc_tsElemRef* eggImg_med        = NULL;
gslc_tsElemRef* eggImg_soft       = NULL;
gslc_tsElemRef* eggSizeLabel      = NULL;
gslc_tsElemRef* m_pListSlider2    = NULL;
gslc_tsElemRef* passwordInput     = NULL;
gslc_tsElemRef* startLabel        = NULL;
gslc_tsElemRef* timerLabel        = NULL;
gslc_tsElemRef* wifiImg_100       = NULL;
gslc_tsElemRef* wifiImg_33        = NULL;
gslc_tsElemRef* wifiImg_66        = NULL;
gslc_tsElemRef* wifiImg_off       = NULL;
gslc_tsElemRef* wifiListBox       = NULL;
gslc_tsElemRef* wifiNameLabel     = NULL;
gslc_tsElemRef* m_pElemKeyPadAlpha = NULL;
//<Save_References !End!>

// Define debug message function
static int16_t DebugOut(char ch) {
  if (ch == (char)'\n') Serial.println("");
  else Serial.write(ch);
  return 0;
}

// ------------------------------------------------
// Callback Methods
// ------------------------------------------------
// Common Button callback
bool CbBtnCommon(void* pvGui, void *pvElemRef, gslc_teTouch eTouch, int16_t nX, int16_t nY)
{
  // Typecast the parameters to match the GUI and element types
  gslc_tsGui*     pGui     = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem*    pElem    = gslc_GetElemFromRef(pGui, pElemRef);

  if ( eTouch == GSLC_TOUCH_UP_IN ) {
    // From the element's ID we can determine which button was pressed.
    switch (pElem->nId) {
      //<Button Enums !Start!>
      case E_ELEM_WIFIOFF:
      case E_ELEM_WIFI33:
      case E_ELEM_WIFI66:
      case E_ELEM_WIFI100:
        gslc_SetPageCur(&m_gui, E_PG_WIFI); //open WiFi menu
        break;
      case E_ELEM_BIGGER:
        //increase egg size if timer is not running
        if (!timer_running && size < 3)size++;
        update_size();
        break;
      case E_ELEM_SMALLER:
        //decrease egg size if timer is not running
        if (!timer_running && size > 0)size--;
        update_size();
        break;
      case E_ELEM_SOFTER:
        //decrease hardness if timer is not running
        if (!timer_running && hardness > 0)hardness--;
        update_egg();
        break;
      case E_ELEM_HARDER:
        //increase hardness if timer is not running
        if (!timer_running && hardness < 2)hardness++;
        update_egg();
        break;
      case E_ELEM_STARTBTN:
        //start or stop the timer
        timer_running = !timer_running;
        if (timer_running) {
          digitalWrite(heater, HIGH); //turn on heating
          gslc_ElemSetTxtStr(&m_gui, startLabel, "Stop");
        } else {
            digitalWrite(heater, LOW); //turn heater off
            gslc_ElemSetTxtStr(&m_gui, startLabel, "Start");

          //Reset timer
          gslc_ElemSetVisible(&m_gui, timerLabel, true); //timer visible
          ledcDetachPin(buzzer);
          update_timer();
        }
        break;
      case E_ELEM_BTN10:
        gslc_SetPageCur(&m_gui, E_PG_MAIN);
        break;
      case E_ELEM_PASSINPUT:
        // Clicked on edit field, so show popup box and associate with this text field
        gslc_ElemXKeyPadInputAsk(&m_gui, m_pElemKeyPadAlpha, E_POP_KEYPAD_ALPHA, passwordInput);
        break;
      case E_ELEM_BTN11:
        gslc_SetPageCur(&m_gui, E_PG_WIFI);
        break;
      case E_ELEM_WIFIOKBTN:
        gslc_SetPageCur(&m_gui, E_PG_MAIN);
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
bool CbKeypad(void* pvGui, void *pvElemRef, int16_t nState, void* pvData)
{
  gslc_tsGui*     pGui     = (gslc_tsGui*)pvGui;
  gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem*    pElem    = gslc_GetElemFromRef(pGui, pElemRef);

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
bool CbListbox(void* pvGui, void* pvElemRef, int16_t nSelId)
{
  gslc_tsGui*     pGui     = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem*    pElem    = gslc_GetElemFromRef(pGui, pElemRef);
  char            acTxt[MAX_STR + 1];

  if (pElemRef == NULL) {
    return false;
  }

  // From the element's ID we can determine which listbox was active.
  switch (pElem->nId) {
    //<Listbox Enums !Start!>

    case E_ELEM_WIFILISTBOX:
      if (nSelId != XLISTBOX_SEL_NONE) {
        gslc_ElemXListboxGetItem(&m_gui, pElemRef, nSelId, acTxt, MAX_STR);
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
bool CbSlidePos(void* pvGui, void* pvElemRef, int16_t nPos)
{
  gslc_tsGui*     pGui     = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem*    pElem    = gslc_GetElemFromRef(pGui, pElemRef);
  int16_t         nVal;
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

void setup()
{
  // ------------------------------------------------
  // Initialize
  // ------------------------------------------------
  pinMode(backlight, OUTPUT);
  digitalWrite(backlight, HIGH);
  pinMode(heater, OUTPUT);
  digitalWrite(heater, LOW);
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output

  Serial.begin(9600);
  // Wait for USB Serial
  //delay(1000);  // NOTE: Some devices require a delay after Serial.begin() before serial port can be used

  gslc_InitDebug(&DebugOut);

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
void loop()
{

  // ------------------------------------------------
  // Update GUI Elements
  // ------------------------------------------------
  int64_t curr_secs = esp_timer_get_time() / 1000000; //get system time in seconds
  if (timer_running && curr_secs != seconds_passed) { //check if a second has already passed, if yes and timer is running, then execute timer code
    if (timer_seconds > 0) { //as long as timer still has time left, decrease time.
      timer_seconds--;
      update_timer();
    } else { //if timer has run out, run alarm
        digitalWrite(heater, LOW); //turn heater off
      if (seconds_passed % 2) {
        gslc_ElemSetVisible(&m_gui, timerLabel, true); //timer visible
        ledcAttachPin(buzzer, 0);             //buzzer channel 0
        ledcWriteNote(0, NOTE_F, 4);    // channel 0 play note
      } else {
        gslc_ElemSetVisible(&m_gui, timerLabel, false); //timer invisible
        ledcDetachPin(buzzer);
      }
    }
  }
  seconds_passed = curr_secs;

  // ------------------------------------------------
  // Periodically call GUIslice update function
  // ------------------------------------------------
  gslc_Update(&m_gui);

}

//Update GUI element that displays WiFi signal strength
void update_wifi() {
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

//Update GUI element that displays egg hardness
void update_egg() {
  if (hardness == 0) {
    gslc_ElemSetVisible(&m_gui, eggImg_soft, true);
    gslc_ElemSetVisible(&m_gui, eggImg_med, false);
    gslc_ElemSetVisible(&m_gui, eggImg_hard, false);
  } else if (hardness == 1) {
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
  gslc_ElemSetTxtStr(&m_gui, eggSizeLabel, sizeStrings[size]);
  update_timer();
}

//Update GUI element that displays timer
void update_timer() {
  if (!timer_running)timer_seconds = 360 + 40 * size + 180 * hardness; //don't use inputs to change the timer if timer is running
  int minutes = timer_seconds / 60;
  int secs = timer_seconds % 60;
  char numstr[6];
  sprintf(numstr, "%02d:%02d", minutes, secs);
  gslc_ElemSetTxtStr(&m_gui, timerLabel, numstr);
}
