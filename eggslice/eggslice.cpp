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

Preferences myPrefs;

//WiFi
uint8_t wifisignal = 0;
char* ssid;
char* pass;

//egg properties
uint8_t hardness = 1;
uint8_t size = 2;
char* sizeStrings[4] = { "S ", "M ", "L ", "XL" };

//timer
bool timer_running = false;
int timer_seconds = 0;
int64_t seconds_passed = 0;


//bit of anti-spam
uint32_t lastMillis;


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

// Define debug message function
/*static int16_t DebugOut(char ch) {
  if (ch == (char)'\n') Serial.println("");
  else Serial.write(ch);
  return 0;
}*/
void InitGUIslice_gen()
{
  gslc_tsElemRef* pElemRef = NULL;

  if (!gslc_Init(&m_gui,&m_drv,m_asPage,MAX_PAGE,m_asFont,MAX_FONT)) { return; }

  // ------------------------------------------------
  // Load Fonts
  // ------------------------------------------------
//<Load_Fonts !Start!>
    if (!gslc_FontSet(&m_gui,E_BUILTIN10X16,GSLC_FONTREF_PTR,NULL,2)) { return; }
    if (!gslc_FontSet(&m_gui,E_BUILTIN15X24,GSLC_FONTREF_PTR,NULL,3)) { return; }
    if (!gslc_FontSet(&m_gui,E_BUILTIN5X8,GSLC_FONTREF_PTR,NULL,1)) { return; }
    if (!gslc_FontSet(&m_gui,E_DOSIS_BOOK12,GSLC_FONTREF_PTR,&dosis_book12pt7b,1)) { return; }
    if (!gslc_FontSet(&m_gui,E_DOSIS_BOOK16,GSLC_FONTREF_PTR,&dosis_book16pt7b,1)) { return; }
    if (!gslc_FontSet(&m_gui,E_FREESANS14,GSLC_FONTREF_PTR,&FreeSans14pt7b,1)) { return; }
    if (!gslc_FontSet(&m_gui,E_FREESANS18,GSLC_FONTREF_PTR,&FreeSans18pt7b,1)) { return; }
    if (!gslc_FontSet(&m_gui,E_NOTOMONO24,GSLC_FONTREF_PTR,&NotoMono24pt7b,1)) { return; }
    if (!gslc_FontSet(&m_gui,E_NOTOSANSBOLD14,GSLC_FONTREF_PTR,&NotoSansBold14pt7b,1)) { return; }
    if (!gslc_FontSet(&m_gui,E_PIJLGLYPH,GSLC_FONTREF_PTR,&pijlFont,1)) { return; }
//<Load_Fonts !End!>

//<InitGUI !Start!>
  gslc_PageAdd(&m_gui,E_PG_MAIN,m_asPage1Elem,MAX_ELEM_PG_MAIN_RAM,m_asPage1ElemRef,MAX_ELEM_PG_MAIN);
  gslc_PageAdd(&m_gui,E_PG_WIFI,m_asPage2Elem,MAX_ELEM_PG_WIFI_RAM,m_asPage2ElemRef,MAX_ELEM_PG_WIFI);
  gslc_PageAdd(&m_gui,E_PG_PASSWD,m_asPage3Elem,MAX_ELEM_PG_PASSWD_RAM,m_asPage3ElemRef,MAX_ELEM_PG_PASSWD);
  gslc_PageAdd(&m_gui,E_POP_KEYPAD_ALPHA,m_asKeypadAlphaElem,1,m_asKeypadAlphaElemRef,1);  // KeyPad

  // NOTE: The current page defaults to the first page added. Here we explicitly
  //       ensure that the main page is the correct page no matter the add order.
  gslc_SetPageCur(&m_gui,E_PG_MAIN);

  // Set Background to a flat color
  gslc_SetBkgndColor(&m_gui,GSLC_COL_BLACK);

  // -----------------------------------
  // PAGE: E_PG_MAIN


  // Create E_ELEM_WIFIOFF using Image
  pElemRef = gslc_ElemCreateImg(&m_gui,E_ELEM_WIFIOFF,E_PG_MAIN,(gslc_tsRect){270,190,37,37},
    gslc_GetImageFromProg((const unsigned char*)wifinone,GSLC_IMGREF_FMT_BMP24));
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetClickEn(&m_gui, pElemRef, true);
  gslc_ElemSetTouchFunc(&m_gui, pElemRef, &CbBtnCommon);
  wifiImg_off = pElemRef;

  // Create E_ELEM_WIFI33 using Image
  pElemRef = gslc_ElemCreateImg(&m_gui,E_ELEM_WIFI33,E_PG_MAIN,(gslc_tsRect){270,190,37,37},
    gslc_GetImageFromProg((const unsigned char*)wifi33,GSLC_IMGREF_FMT_BMP24));
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetClickEn(&m_gui, pElemRef, true);
  gslc_ElemSetTouchFunc(&m_gui, pElemRef, &CbBtnCommon);
  wifiImg_33 = pElemRef;

  // Create E_ELEM_WIFI66 using Image
  pElemRef = gslc_ElemCreateImg(&m_gui,E_ELEM_WIFI66,E_PG_MAIN,(gslc_tsRect){270,190,37,37},
    gslc_GetImageFromProg((const unsigned char*)wifi66,GSLC_IMGREF_FMT_BMP24));
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetClickEn(&m_gui, pElemRef, true);
  gslc_ElemSetTouchFunc(&m_gui, pElemRef, &CbBtnCommon);
  wifiImg_66 = pElemRef;

  // Create E_ELEM_WIFI100 using Image
  pElemRef = gslc_ElemCreateImg(&m_gui,E_ELEM_WIFI100,E_PG_MAIN,(gslc_tsRect){270,190,37,37},
    gslc_GetImageFromProg((const unsigned char*)wifi100,GSLC_IMGREF_FMT_BMP24));
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetClickEn(&m_gui, pElemRef, true);
  gslc_ElemSetTouchFunc(&m_gui, pElemRef, &CbBtnCommon);
  wifiImg_100 = pElemRef;

  // Create E_ELEM_EGGIMG_SOFT using Image
  pElemRef = gslc_ElemCreateImg(&m_gui,E_ELEM_EGGIMG_SOFT,E_PG_MAIN,(gslc_tsRect){190,40,58,80},
    gslc_GetImageFromProg((const unsigned char*)soft_egg80,GSLC_IMGREF_FMT_BMP24));
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  eggImg_soft = pElemRef;

  // Create E_ELEM_EGGIMG_MED using Image
  pElemRef = gslc_ElemCreateImg(&m_gui,E_ELEM_EGGIMG_MED,E_PG_MAIN,(gslc_tsRect){190,40,58,80},
    gslc_GetImageFromProg((const unsigned char*)medium_egg80,GSLC_IMGREF_FMT_BMP24));
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  eggImg_med = pElemRef;

  // Create E_ELEM_EGGIMG_HARD using Image
  pElemRef = gslc_ElemCreateImg(&m_gui,E_ELEM_EGGIMG_HARD,E_PG_MAIN,(gslc_tsRect){190,40,58,80},
    gslc_GetImageFromProg((const unsigned char*)hard_egg80,GSLC_IMGREF_FMT_BMP24));
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  eggImg_hard = pElemRef;

  // create E_ELEM_BIGGER button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BIGGER,E_PG_MAIN,
    (gslc_tsRect){270,40,40,40},(char*)" +",0,E_NOTOSANSBOLD14,&CbBtnCommon);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);

  // create E_ELEM_SMALLER button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_SMALLER,E_PG_MAIN,
    (gslc_tsRect){270,90,40,40},(char*)"-",0,E_NOTOSANSBOLD14,&CbBtnCommon);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);

    // Create E_ELEM_SIZE text label
  static char mstr1[20] = "XL";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_SIZE,E_PG_MAIN,(gslc_tsRect){235,25,30,25},
    mstr1, sizeof(mstr1),E_DOSIS_BOOK16);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE);
  eggSizeLabel = pElemRef;

  // create E_ELEM_SOFTER button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_SOFTER,E_PG_MAIN,
    (gslc_tsRect){170,130,40,40},(char*)" <",0,E_NOTOSANSBOLD14,&CbBtnCommon);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_LEFT);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);

  // create E_ELEM_HARDER button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_HARDER,E_PG_MAIN,
    (gslc_tsRect){227,130,40,40},(char*)" >",0,E_NOTOSANSBOLD14,&CbBtnCommon);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_LEFT);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);

    // Create E_ELEM_TIMER text label
  static char mstr2[20] = "00:00";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TIMER,E_PG_MAIN,(gslc_tsRect){12,50,150,50},
    mstr2, sizeof(mstr2),E_NOTOMONO24);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE);
  timerLabel = pElemRef;

    // create E_ELEM_STARTBTN button with text label
  static char mstr3[20] = "Start";
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_STARTBTN,E_PG_MAIN,
    (gslc_tsRect){40,125,100,50},mstr3,sizeof(mstr3),E_FREESANS18,&CbBtnCommon);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  startLabel = pElemRef;

  // -----------------------------------
  // PAGE: E_PG_WIFI


  // Create wrapping box for listbox E_ELEM_WIFILISTBOX and scrollbar
  pElemRef = gslc_ElemCreateBox(&m_gui,GSLC_ID_AUTO,E_PG_WIFI,(gslc_tsRect){10,10,300,180});
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE,GSLC_COL_BLACK,GSLC_COL_BLACK);

  // Create listbox
  pElemRef = gslc_ElemXListboxCreate(&m_gui,E_ELEM_WIFILISTBOX,E_PG_WIFI,&m_sListbox2,
    (gslc_tsRect){10+2,10+4,300-4-40,180-7},E_FREESANS14,
    (uint8_t*)&m_acListboxBuf2,sizeof(m_acListboxBuf2),0);
  gslc_ElemXListboxSetSize(&m_gui, pElemRef, 4, 1); // 4 rows, 1 columns
  gslc_ElemXListboxItemsSetSize(&m_gui, pElemRef, -1, 35);
  gslc_ElemSetTxtMarginXY(&m_gui, pElemRef, 5, 5);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE,GSLC_COL_BLACK,GSLC_COL_BLACK);
  gslc_ElemXListboxSetSelFunc(&m_gui, pElemRef, &CbListbox);
  gslc_ElemXListboxItemsSetGap(&m_gui, pElemRef, 6,GSLC_COL_BLACK);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  wifiListBox = pElemRef;

  // Create vertical scrollbar for listbox
  pElemRef = gslc_ElemXSliderCreate(&m_gui,E_LISTSCROLL2,E_PG_WIFI,&m_sListScroll2,
          (gslc_tsRect){10+300-2-40,10+4,40,180-8},0,15,0,5,true);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE,GSLC_COL_BLACK,GSLC_COL_BLUE);
  gslc_ElemXSliderSetPosFunc(&m_gui,pElemRef,&CbSlidePos);
  m_pListSlider2 = pElemRef;

  // create E_ELEM_BTN10 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN10,E_PG_WIFI,
    (gslc_tsRect){10,195,80,40},(char*)" ",0,E_PIJLGLYPH,&CbBtnCommon);

  // -----------------------------------
  // PAGE: E_PG_PASSWD


  // Create E_ELEM_WIFINAME text label
  static char mstr4[32] = "";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_WIFINAME,E_PG_PASSWD,(gslc_tsRect){10,10,300,20},
    mstr4,sizeof(mstr4),E_DOSIS_BOOK12);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  wifiNameLabel = pElemRef;

  // Create E_ELEM_PASSINPUT text input field
  static char m_sInputText2[101] = "";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_PASSINPUT,E_PG_PASSWD,(gslc_tsRect){10,50,300,50},
    (char*)m_sInputText2,101,E_DOSIS_BOOK16);
  gslc_ElemSetTxtMargin(&m_gui,pElemRef,5);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  gslc_ElemSetClickEn(&m_gui, pElemRef, true);
  gslc_ElemSetTouchFunc(&m_gui, pElemRef, &CbBtnCommon);
  passwordInput = pElemRef;

  // create E_ELEM_BTN11 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN11,E_PG_PASSWD,
    (gslc_tsRect){10,195,80,40},(char*)" ",0,E_PIJLGLYPH,&CbBtnCommon);
  //gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE,GSLC_COL_BLUE_DK2,GSLC_COL_BLUE);

  // create E_ELEM_WIFIOKBTN button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_WIFIOKBTN,E_PG_PASSWD,
    (gslc_tsRect){230,195,80,40},(char*)"OK",0,E_FREESANS14,&CbBtnCommon);
  //gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_BLUE,GSLC_COL_BLUE_DK2,GSLC_COL_BLUE);

  //gslc_ElemSetFillEn(&m_gui,pElemRef,false);

  // -----------------------------------
  // PAGE: E_POP_KEYPAD_ALPHA

  static gslc_tsXKeyPadCfg_Alpha sCfgTx;
  sCfgTx = gslc_ElemXKeyPadCfgInit_Alpha();
  sCfgTx.sBaseCfg.nButtonSzW=16;
  sCfgTx.sBaseCfg.nButtonSzH=36;
  sCfgTx.sBaseCfg.eLayoutDef=1;
  m_pElemKeyPadAlpha = gslc_ElemXKeyPadCreate_Alpha(&m_gui, E_ELEM_KEYPAD_ALPHA, E_POP_KEYPAD_ALPHA,
    &m_sKeyPadAlpha, -2, 51, E_DOSIS_BOOK12, &sCfgTx);
  gslc_ElemXKeyPadValSetCb(&m_gui, m_pElemKeyPadAlpha, &CbKeypad);
//<InitGUI !End!>

//<Startup !Start!>
//<Startup !End!>

}
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
        if (!timer_running && size < 3) size++;
        myPrefs.putChar("size", size);
        update_size();
        break;
      case E_ELEM_SMALLER:
        //decrease egg size if timer is not running
        if (!timer_running && size > 0) size--;
        myPrefs.putChar("size", size);
        update_size();
        break;
      case E_ELEM_SOFTER:
        //decrease hardness if timer is not running
        if (!timer_running && hardness > 0) hardness--;
        myPrefs.putChar("hardness", hardness);
        update_egg();
        break;
      case E_ELEM_HARDER:
        //increase hardness if timer is not running
        if (!timer_running && hardness < 2) hardness++;
        myPrefs.putChar("hardness", hardness);
        update_egg();
        break;
      case E_ELEM_STARTBTN:
        //start or stop the timer
        timer_running = !timer_running;
        if (timer_running) {
          digitalWrite(heater, HIGH);  //turn on heating
          gslc_ElemSetTxtStr(&m_gui, startLabel, "Stop");
        } else {
          digitalWrite(heater, LOW);  //turn heater off
          gslc_ElemSetTxtStr(&m_gui, startLabel, "Start");
          //Reset timer
          gslc_ElemSetVisible(&m_gui, timerLabel, true);  //timer visible
          ledcDetachPin(buzzer);
          update_timer();
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
        //myPrefs.putString("ssid", String(ssid));
        //myPrefs.putString("pass", String(pass));
        //Serial.println(String(ssid));
        //Serial.println(String(pass));

        //Serial.println(String(ssid).length());
        //WiFi.disconnect();
        //WiFi.begin(ssid, pass);
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

//constructor
EggCooker::EggCooker(Sensor* secs, TextSensor* state)
  : secs_(secs), state_(state) { }

void EggCooker::setup() {

  //Serial.begin(9600);
  //delay(10);
  // ------------------------------------------------
  // Initialize
  // ------------------------------------------------
  pinMode(backlight, OUTPUT);
  digitalWrite(backlight, HIGH);
  pinMode(heater, OUTPUT);
  digitalWrite(heater, LOW);
  pinMode(buzzer, OUTPUT);  // Set buzzer - pin 9 as an output

  //load previous myPrefs
  myPrefs.begin("my-app", false);
  int8_t temp = myPrefs.getChar("hardness", -1);
  if (temp >= 0 && temp < 3) hardness = temp;
  temp = myPrefs.getChar("size", -1);
  if (temp >= 0 && temp < 4) size = temp;
  //load wifi
  String tempssid = myPrefs.getString("ssid", "");
  char sssid[tempssid.length() + 1];
  tempssid.toCharArray(sssid, sizeof(sssid));
  ssid = sssid;
  String temppass = myPrefs.getString("pass", "");
  char ppass[temppass.length() + 1];
  temppass.toCharArray(ppass, sizeof(ppass));
  pass = ppass;
  if (ssid != "" && tempssid.length() > 0) {
    WiFi.begin(ssid, pass);
  }

  //register Home Assistant service
  register_service(&EggCooker::stopService, "stop_service");

  // Wait for USB Serial
  //delay(1000);  // NOTE: Some devices require a delay after Serial.begin() before serial port can be used

  //gslc_InitDebug(&DebugOut);

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

  //send timer data to Home Assistant
  if (lastMillis - esphome::millis() > 50) {
    secs_->publish_state(timer_seconds);
    if (timer_seconds == 0) {
      state_->publish_state("Alarm");
    } else if (timer_running) {
      state_->publish_state("Running");
    } else {
      state_->publish_state("Stopped");
    }
  }
  lastMillis = esphome::millis();
}

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
  if (!timer_running) timer_seconds = 360 + 40 * size + 180 * hardness;  //don't use inputs to change the timer if timer is running
  int minutes = timer_seconds / 60;
  int secs = timer_seconds % 60;
  char numstr[6];
  sprintf(numstr, "%02d:%02d", minutes, secs);
  gslc_ElemSetTxtStr(&m_gui, timerLabel, numstr);
}

//find WiFi networks and put them in the GUI
void findWiFi(void* parameter) {
  wifirunning = true;
  int n = WiFi.scanNetworks(false, false, false, 150);
  if (n > 0) {
    //Serial.print(n);
    //Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
      gslc_ElemXListboxAddItem(&m_gui, wifiListBox, WiFi.SSID(i).c_str());
    }
  }
  wifirunning = false;
  vTaskDelete(WiFiSearchTask);
}
void EggCooker::stopService() {
  digitalWrite(heater, LOW);  //turn heater off
  gslc_ElemSetTxtStr(&m_gui, startLabel, "Start");
  //Reset timer
  gslc_ElemSetVisible(&m_gui, timerLabel, true);  //timer visible
  ledcDetachPin(buzzer);
  update_timer();

  timer_running = false;
}
