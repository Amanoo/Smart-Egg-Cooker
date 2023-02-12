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
//#include "NULLFreeSans18pt7b.h"
#include "NotoMono24pt7b.h"
#include "NotoSansBold14pt7b.h"
#include "dosis_book12pt7b.h"
#include "dosis_book16pt7b.h"
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
//<Resources !End!>

// ------------------------------------------------
// Enumerations for pages, elements, fonts, images
// ------------------------------------------------
//<Enum !Start!>
enum {E_PG_MAIN,E_PG_WIFI,E_PG_PASSWD,E_POP_KEYPAD_ALPHA};
enum {E_ELEM_BIGGER,E_ELEM_BTN10,E_ELEM_BTN11,E_ELEM_EGGIMG_HARD
      ,E_ELEM_EGGIMG_MED,E_ELEM_EGGIMG_SOFT,E_ELEM_HARDER
      ,E_ELEM_PASSINPUT,E_ELEM_SIZE,E_ELEM_SMALLER,E_ELEM_SOFTER
      ,E_ELEM_STARTBTN,E_ELEM_TEXT9,E_ELEM_TIMER,E_ELEM_WIFI100
      ,E_ELEM_WIFI33,E_ELEM_WIFI66,E_ELEM_WIFILISTBOX,E_ELEM_WIFINAME
      ,E_ELEM_WIFIOFF,E_ELEM_WIFIOKBTN,E_LISTSCROLL2
      ,E_ELEM_KEYPAD_ALPHA};
// Must use separate enum for fonts with MAX_FONT at end to use gslc_FontSet.
enum {E_BUILTIN10X16,E_BUILTIN15X24,E_BUILTIN5X8,E_DOSIS_BOOK12
        ,E_DOSIS_BOOK16,E_FREESANS14,E_FREESANS18,E_NOTOMONO24
      ,E_NOTOSANSBOLD14,MAX_FONT};
//<Enum !End!>

// ------------------------------------------------
// Instantiate the GUI
// ------------------------------------------------

// ------------------------------------------------
// Define the maximum number of elements and pages
// ------------------------------------------------
//<ElementDefines !Start!>
#define MAX_PAGE                4

#define MAX_ELEM_PG_MAIN 14 // # Elems total on page
#define MAX_ELEM_PG_MAIN_RAM MAX_ELEM_PG_MAIN // # Elems in RAM

#define MAX_ELEM_PG_WIFI 4 // # Elems total on page
#define MAX_ELEM_PG_WIFI_RAM MAX_ELEM_PG_WIFI // # Elems in RAM

#define MAX_ELEM_PG_PASSWD 5 // # Elems total on page
#define MAX_ELEM_PG_PASSWD_RAM MAX_ELEM_PG_PASSWD // # Elems in RAM
//<ElementDefines !End!>

// ------------------------------------------------
// Create element storage
// ------------------------------------------------
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
extern gslc_tsElemRef* m_pListSlider2;
extern gslc_tsElemRef* passwordInput;
extern gslc_tsElemRef* startLabel;
extern gslc_tsElemRef* timerLabel;
extern gslc_tsElemRef* wifiImg_100;
extern gslc_tsElemRef* wifiImg_33;
extern gslc_tsElemRef* wifiImg_66;
extern gslc_tsElemRef* wifiImg_off;
extern gslc_tsElemRef* wifiListBox;
extern gslc_tsElemRef* wifiNameLabel;
extern gslc_tsElemRef* m_pElemKeyPadAlpha;
//<Extern_References !End!>

// Define debug message function
static int16_t DebugOut(char ch);

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
  gslc_ElemXListboxAddItem(&m_gui, pElemRef, "htryhr");
  gslc_ElemXListboxAddItem(&m_gui, pElemRef, "hjstrj");
  gslc_ElemXListboxAddItem(&m_gui, pElemRef, "sjtrjtr");
  gslc_ElemXListboxAddItem(&m_gui, pElemRef, "jtsrjstr");
  gslc_ElemXListboxAddItem(&m_gui, pElemRef, "sjtrsrjt");
  gslc_ElemXListboxAddItem(&m_gui, pElemRef, "jtrsjtrssjtr");
  gslc_ElemXListboxAddItem(&m_gui, pElemRef, "jtrsjtrs");
  gslc_ElemXListboxAddItem(&m_gui, pElemRef, "jtrsjtrsjstr");
  gslc_ElemXListboxAddItem(&m_gui, pElemRef, "trjsjstrr");
  gslc_ElemXListboxAddItem(&m_gui, pElemRef, "trjssjtr");
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
    (gslc_tsRect){10,195,80,40},(char*)"<\xbc",0,E_BUILTIN15X24,&CbBtnCommon);

  // -----------------------------------
  // PAGE: E_PG_PASSWD
  
  
  // Create E_ELEM_WIFINAME text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_WIFINAME,E_PG_PASSWD,(gslc_tsRect){10,10,300,20},
    (char*)"",0,E_DOSIS_BOOK12);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  wifiNameLabel = pElemRef;
  
  // Create E_ELEM_PASSINPUT text input field
  static char m_sInputText2[101] = "";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_PASSINPUT,E_PG_PASSWD,(gslc_tsRect){10,50,320,25},
    (char*)m_sInputText2,101,E_DOSIS_BOOK16);
  gslc_ElemSetTxtMargin(&m_gui,pElemRef,5);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_WHITE);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  gslc_ElemSetClickEn(&m_gui, pElemRef, true);
  gslc_ElemSetTouchFunc(&m_gui, pElemRef, &CbBtnCommon);
  passwordInput = pElemRef;
  
  // create E_ELEM_BTN11 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTN11,E_PG_PASSWD,
    (gslc_tsRect){10,195,80,40},(char*)"<\xbc",0,E_BUILTIN15X24,&CbBtnCommon);
  
  // create E_ELEM_WIFIOKBTN button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_WIFIOKBTN,E_PG_PASSWD,
    (gslc_tsRect){230,195,80,40},(char*)"OK",0,E_FREESANS14,&CbBtnCommon);
  
  // Create E_ELEM_TEXT9 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT9,E_PG_PASSWD,(gslc_tsRect){250,150,49,18},
    (char*)"",0,E_BUILTIN10X16);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);

  // -----------------------------------
  // PAGE: E_POP_KEYPAD_ALPHA
  
  static gslc_tsXKeyPadCfg_Alpha sCfgTx;
  sCfgTx = gslc_ElemXKeyPadCfgInit_Alpha();
  m_pElemKeyPadAlpha = gslc_ElemXKeyPadCreate_Alpha(&m_gui, E_ELEM_KEYPAD_ALPHA, E_POP_KEYPAD_ALPHA,
    &m_sKeyPadAlpha, 65, 80, E_BUILTIN5X8, &sCfgTx);
  gslc_ElemXKeyPadValSetCb(&m_gui, m_pElemKeyPadAlpha, &CbKeypad);
//<InitGUI !End!>

//<Startup !Start!>
//<Startup !End!>

}

#endif // end _GUISLICE_GEN_H
