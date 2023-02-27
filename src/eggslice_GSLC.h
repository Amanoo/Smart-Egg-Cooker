//<File !Start!>
// FILE: [eggslice_GSLC.h]
// Created by GUIslice Builder version: [0.17.b18]
//
// GUIslice Builder Generated GUI Framework File
//
// For the latest guides, updates and support view:
// https://github.com/ImpulseAdventure/GUIslice
//
//<File !End!>

#ifndef _GUISLICE_GEN_H
#define _GUISLICE_GEN_H

// ------------------------------------------------
// Headers to include
// ------------------------------------------------
#include "GUIslice.h"
#include "GUIslice_drv.h"

// Include any extended elements
//<Includes !Start!>
// Include extended elements
#include "elem/XKeyPad_Alpha.h"
#include "elem/XKeyPad_Num.h"
#include "elem/XListbox.h"
#include "elem/XSlider.h"

// Ensure optional features are enabled in the configuration
//<Includes !End!>

// ------------------------------------------------
// Headers and Defines for fonts
// Note that font files are located within the Adafruit-GFX library folder:
// ------------------------------------------------
//<Fonts !Start!>
#if !defined(DRV_DISP_TFT_ESPI)
  #error E_PROJECT_OPTIONS tab->Graphics Library should be Adafruit_GFX
#endif
#include <TFT_eSPI.h>
#include "FreeSans14pt7b.h"
#include "NotoMono24pt7b.h"
#include "NotoSansBold14pt7b.h"
#include "dosis_book12pt7b.h"
#include "dosis_book16pt7b.h"
#include "pijlGlyph.h"
#include "plusminus.h"
#include "FreeSans40pt7b.h"
#include "FreeSans60pt7b.h"
//<Fonts !End!>

// ------------------------------------------------
// Defines for resources
// ------------------------------------------------
//<Resources !Start!>
extern "C" const unsigned short hard_egg80[] PROGMEM;
extern "C" const unsigned short medium_egg80[] PROGMEM;
extern "C" const unsigned short soft_egg80[] PROGMEM;
extern "C" const unsigned short wifi100[] PROGMEM;
extern "C" const unsigned short wifi33[] PROGMEM;
extern "C" const unsigned short wifi66[] PROGMEM;
extern "C" const unsigned short wifinone[] PROGMEM;
extern "C" const unsigned short wekkerblauwklein[] PROGMEM;
extern "C" const unsigned short wekkerdonkerblauwklein[] PROGMEM;
//<Resources !End!>

// ------------------------------------------------
// Enumerations for pages, elements, fonts, images
// ------------------------------------------------
//<Enum !Start!>
enum {E_PG_MAIN,E_PG_WIFI,E_PG_PASSWD,E_PLANNER,E_POP_KEYPAD_NUM,E_POP_KEYPAD_ALPHA};
enum {E_ELEM_ALARM_OFF,E_ELEM_ALARM_ON,E_ELEM_BACK1,E_ELEM_BACK2
      ,E_ELEM_BACK3,E_ELEM_BIGGER,E_ELEM_TIMER,E_ELEM_BTNMINUTEUP
      ,E_ELEM_EGGIMG_HARD,E_ELEM_EGGIMG_MED,E_ELEM_EGGIMG_SOFT
      ,E_ELEM_HARDER,E_ELEM_HOURDOWN,E_ELEM_HOURINPUT,E_ELEM_HOURUP
      ,E_ELEM_MAIN_ALARMCLOCK,E_ELEM_MINUTEDOWN,E_ELEM_MINUTEINPUT
      ,E_ELEM_PASSINPUT,E_ELEM_SIZE,E_ELEM_SMALLER,E_ELEM_SOFTER
      ,E_ELEM_STARTBTN,E_ELEM_TEXT10,E_ELEM_WIFI100,E_ELEM_WIFI33
      ,E_ELEM_WIFI66,E_ELEM_WIFILISTBOX,E_ELEM_WIFINAME,E_ELEM_WIFIOFF
      ,E_ELEM_WIFIOKBTN,E_LISTSCROLL2,E_ELEM_KEYPAD_NUM
      ,E_ELEM_KEYPAD_ALPHA};
// Must use separate enum for fonts with MAX_FONT at end to use gslc_FontSet.
enum {E_BUILTIN10X16,E_BUILTIN15X24,E_BUILTIN5X8,E_DOSIS_BOOK12
      ,E_DOSIS_BOOK16,E_FREESANS14,E_FREESANS18,E_NOTOMONO24
      ,E_NOTOSANSBOLD14,E_PIJLGLYPH,E_FREESANS40,E_FREESANS60
      ,E_PLUSMINUS,MAX_FONT};
//<Enum !End!>

// ------------------------------------------------
// Instantiate the GUI
// ------------------------------------------------

// ------------------------------------------------
// Define the maximum number of elements and pages
// ------------------------------------------------
//<ElementDefines !Start!>
#define MAX_PAGE                6

#define MAX_ELEM_PG_MAIN 15 // # Elems total on page
#define MAX_ELEM_PG_MAIN_RAM MAX_ELEM_PG_MAIN // # Elems in RAM

#define MAX_ELEM_PG_WIFI 4 // # Elems total on page
#define MAX_ELEM_PG_WIFI_RAM MAX_ELEM_PG_WIFI // # Elems in RAM

#define MAX_ELEM_PG_PASSWD 5 // # Elems total on page
#define MAX_ELEM_PG_PASSWD_RAM MAX_ELEM_PG_PASSWD // # Elems in RAM

#define MAX_ELEM_PLANNER 10 // # Elems total on page
#define MAX_ELEM_PLANNER_RAM MAX_ELEM_PLANNER // # Elems in RAM
//<ElementDefines !End!>

// ------------------------------------------------
// Create element storage
// ------------------------------------------------
extern gslc_tsGui                      m_gui;
extern gslc_tsDriver                   m_drv;
extern gslc_tsFont                     m_asFont[MAX_FONT];
extern gslc_tsPage                     m_asPage[MAX_PAGE];

//<GUI_Extra_Elements !Start!>
extern gslc_tsElem                     m_asPage1Elem[MAX_ELEM_PG_MAIN_RAM];
extern gslc_tsElemRef                  m_asPage1ElemRef[MAX_ELEM_PG_MAIN];
extern gslc_tsElem                     m_asPage2Elem[MAX_ELEM_PG_WIFI_RAM];
extern gslc_tsElemRef                  m_asPage2ElemRef[MAX_ELEM_PG_WIFI];
extern gslc_tsElem                     m_asPage3Elem[MAX_ELEM_PG_PASSWD_RAM];
extern gslc_tsElemRef                  m_asPage3ElemRef[MAX_ELEM_PG_PASSWD];
extern gslc_tsElem                     m_asPage4Elem[MAX_ELEM_PLANNER_RAM];
extern gslc_tsElemRef                  m_asPage4ElemRef[MAX_ELEM_PLANNER];
extern gslc_tsElem                     m_asKeypadNumElem[1];
extern gslc_tsElemRef                  m_asKeypadNumElemRef[1];
extern gslc_tsElem                     m_asKeypadAlphaElem[1];
extern gslc_tsElemRef                  m_asKeypadAlphaElemRef[1];
extern gslc_tsXKeyPad                  m_sKeyPadNum;
extern gslc_tsXKeyPad                  m_sKeyPadAlpha;
extern gslc_tsXListbox                 m_sListbox2;
// - Note that XLISTBOX_BUF_OH_R is extra required per item
extern char                            m_acListboxBuf2[94 + XLISTBOX_BUF_OH_R];
extern gslc_tsXSlider                  m_sListScroll2;

#define MAX_STR                 100

//<GUI_Extra_Elements !End!>

// ------------------------------------------------
// Program Globals
// ------------------------------------------------

// Element References for direct access
//<Extern_References !Start!>
extern gslc_tsElemRef* eggImg_hard;
extern gslc_tsElemRef* eggImg_med;
extern gslc_tsElemRef* eggImg_soft;
extern gslc_tsElemRef* eggSizeLabel;
extern gslc_tsElemRef* imgAlarmMain;
extern gslc_tsElemRef* m_pHourInput;
extern gslc_tsElemRef* m_pMinuteInput;
extern gslc_tsElemRef* m_pListSlider2;
extern gslc_tsElemRef* pImgAlarmOff;
extern gslc_tsElemRef* pImgAlarmOn;
extern gslc_tsElemRef* passwordInput;
extern gslc_tsElemRef* startLabel;
extern gslc_tsElemRef* timerLabel;
extern gslc_tsElemRef* wifiImg_100;
extern gslc_tsElemRef* wifiImg_33;
extern gslc_tsElemRef* wifiImg_66;
extern gslc_tsElemRef* wifiImg_off;
extern gslc_tsElemRef* wifiListBox;
extern gslc_tsElemRef* wifiNameLabel;
extern gslc_tsElemRef* m_pElemKeyPadNum;
extern gslc_tsElemRef* m_pElemKeyPadAlpha;
//<Extern_References !End!>

// Define debug message function
//static int16_t DebugOut(char ch);

// ------------------------------------------------
// Callback Methods
// ------------------------------------------------
bool CbBtnCommon(void* pvGui,void *pvElemRef,gslc_teTouch eTouch,int16_t nX,int16_t nY);
bool CbCheckbox(void* pvGui, void* pvElemRef, int16_t nSelId, bool bState);
bool CbDrawScanner(void* pvGui,void* pvElemRef,gslc_teRedrawType eRedraw);
bool CbKeypad(void* pvGui, void *pvElemRef, int16_t nState, void* pvData);
bool CbListbox(void* pvGui, void* pvElemRef, int16_t nSelId);
bool CbSlidePos(void* pvGui,void* pvElemRef,int16_t nPos);
bool CbSpinner(void* pvGui, void *pvElemRef, int16_t nState, void* pvData);
bool CbTickScanner(void* pvGui,void* pvScope);

// ------------------------------------------------
// Create page elements
// ------------------------------------------------
void InitGUIslice_gen();

#endif // end _GUISLICE_GEN_H
