#include "eggslice_GSLC.h"

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
    if (!gslc_FontSet(&m_gui,E_FREESANS40,GSLC_FONTREF_PTR,&FreeSans40pt7b,1)) { return; }
    if (!gslc_FontSet(&m_gui,E_FREESANS60,GSLC_FONTREF_PTR,&FreeSans60pt7b,1)) { return; }
    if (!gslc_FontSet(&m_gui,E_NOTOMONO24,GSLC_FONTREF_PTR,&NotoMono24pt7b,1)) { return; }
    if (!gslc_FontSet(&m_gui,E_NOTOSANSBOLD14,GSLC_FONTREF_PTR,&NotoSansBold14pt7b,1)) { return; }
    if (!gslc_FontSet(&m_gui,E_PIJLGLYPH,GSLC_FONTREF_PTR,&pijlFont,1)) { return; }
    if (!gslc_FontSet(&m_gui,E_PLUSMINUS,GSLC_FONTREF_PTR,&plusminFont,1)) { return; }
//<Load_Fonts !End!>

//<InitGUI !Start!>
  gslc_PageAdd(&m_gui,E_PG_MAIN,m_asPage1Elem,MAX_ELEM_PG_MAIN_RAM,m_asPage1ElemRef,MAX_ELEM_PG_MAIN);
  gslc_PageAdd(&m_gui,E_PG_WIFI,m_asPage2Elem,MAX_ELEM_PG_WIFI_RAM,m_asPage2ElemRef,MAX_ELEM_PG_WIFI);
  gslc_PageAdd(&m_gui,E_PG_PASSWD,m_asPage3Elem,MAX_ELEM_PG_PASSWD_RAM,m_asPage3ElemRef,MAX_ELEM_PG_PASSWD);
  gslc_PageAdd(&m_gui,E_PLANNER,m_asPage4Elem,MAX_ELEM_PLANNER_RAM,m_asPage4ElemRef,MAX_ELEM_PLANNER);
  gslc_PageAdd(&m_gui,E_POP_KEYPAD_NUM,m_asKeypadNumElem,1,m_asKeypadNumElemRef,1);  // KeyPad
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
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_TIMER,E_PG_MAIN,(gslc_tsRect){12,50,150,50},
    mstr2, sizeof(mstr2),E_NOTOMONO24,&CbBtnCommon);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,false);
  timerLabel = pElemRef;

    // create E_ELEM_STARTBTN button with text label
  static char mstr3[20] = "Start";
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_STARTBTN,E_PG_MAIN,
    (gslc_tsRect){40,125,100,50},mstr3,sizeof(mstr3),E_FREESANS18,&CbBtnCommon);
  gslc_ElemSetRoundEn(&m_gui, pElemRef, true);
  startLabel = pElemRef;

  // Create E_ELEM_MAIN_ALARMCLOCK using Image
  pElemRef = gslc_ElemCreateImg(&m_gui,E_ELEM_MAIN_ALARMCLOCK,E_PG_MAIN,(gslc_tsRect){10,190,40,50},
    gslc_GetImageFromProg((const unsigned char*)wekkerdonkerblauwklein,GSLC_IMGREF_FMT_BMP24));
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetVisible(&m_gui, pElemRef, false);
  imgAlarmMain = pElemRef;


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

  // create E_ELEM_BACK1 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BACK1,E_PG_WIFI,
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

  // create E_ELEM_BACK2 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BACK2,E_PG_PASSWD,
    (gslc_tsRect){10,195,80,40},(char*)" ",0,E_PIJLGLYPH,&CbBtnCommon);

  // create E_ELEM_WIFIOKBTN button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_WIFIOKBTN,E_PG_PASSWD,
    (gslc_tsRect){230,195,80,40},(char*)"OK",0,E_FREESANS14,&CbBtnCommon);


  // -----------------------------------
  // PAGE: E_PLANNER


  // Create E_ELEM_TEXT10 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT10,E_PLANNER,(gslc_tsRect){144,20,25,64},
    (char*)":",0,E_FREESANS60);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE);

  // create E_ELEM_BACK3 button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BACK3,E_PLANNER,
    (gslc_tsRect){10,195,80,40},(char*)" ",0,E_PIJLGLYPH,&CbBtnCommon);

  // Create E_ELEM_ALARM_ON using Image
  pElemRef = gslc_ElemCreateImg(&m_gui,E_ELEM_ALARM_ON,E_PLANNER,(gslc_tsRect){270,185,40,50},
    gslc_GetImageFromProg((const unsigned char*)wekkerblauwklein,GSLC_IMGREF_FMT_BMP24));
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetClickEn(&m_gui, pElemRef, true);
  gslc_ElemSetTouchFunc(&m_gui, pElemRef, &CbBtnCommon);
  pImgAlarmOn = pElemRef;

  // Create E_ELEM_ALARM_OFF using Image
  pElemRef = gslc_ElemCreateImg(&m_gui,E_ELEM_ALARM_OFF,E_PLANNER,(gslc_tsRect){270,185,40,50},
    gslc_GetImageFromProg((const unsigned char*)wekkerdonkerblauwklein,GSLC_IMGREF_FMT_BMP24));
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetClickEn(&m_gui, pElemRef, true);
  gslc_ElemSetTouchFunc(&m_gui, pElemRef, &CbBtnCommon);
  pImgAlarmOff = pElemRef;

  // Create E_ELEM_HOURINPUT numeric input field
  static char m_sInputNumber1[3] = "00";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_HOURINPUT,E_PLANNER,(gslc_tsRect){10,5,135,110},
    (char*)m_sInputNumber1,3,E_FREESANS60);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetTxtMargin(&m_gui,pElemRef,5);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  gslc_ElemSetClickEn(&m_gui, pElemRef, true);
  gslc_ElemSetTouchFunc(&m_gui, pElemRef, &CbBtnCommon);
  m_pHourInput = pElemRef;

  // Create E_ELEM_MINUTEINPUT numeric input field
  static char m_sInputNumber2[3] = "00";
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_MINUTEINPUT,E_PLANNER,(gslc_tsRect){180,5,135,110},
    (char*)m_sInputNumber2,3,E_FREESANS60);
  gslc_ElemSetTxtMargin(&m_gui,pElemRef,5);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLUE);
  gslc_ElemSetFrameEn(&m_gui,pElemRef,true);
  gslc_ElemSetClickEn(&m_gui, pElemRef, true);
  gslc_ElemSetTouchFunc(&m_gui, pElemRef, &CbBtnCommon);
  m_pMinuteInput = pElemRef;

  // create E_ELEM_HOURDOWN button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_HOURDOWN,E_PLANNER,
    (gslc_tsRect){10,116,60,60},(char*)" ",0,E_PLUSMINUS,&CbBtnCommon);
  //gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_TOP_MID);

  // create E_ELEM_HOURUP button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_HOURUP,E_PLANNER,
    (gslc_tsRect){85,116,60,60},(char*)"!",0,E_PLUSMINUS,&CbBtnCommon);

  // create E_ELEM_MINUTEDOWN button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_MINUTEDOWN,E_PLANNER,
    (gslc_tsRect){180,116,60,60},(char*)" ",0,E_PLUSMINUS,&CbBtnCommon);

  // create E_ELEM_BTNMINUTEUP button with text label
  pElemRef = gslc_ElemCreateBtnTxt(&m_gui,E_ELEM_BTNMINUTEUP,E_PLANNER,
    (gslc_tsRect){255,116,60,60},(char*)"!",0,E_PLUSMINUS,&CbBtnCommon);

  // -----------------------------------
  // PAGE: E_POP_KEYPAD_NUM

  static gslc_tsXKeyPadCfg_Num sCfg;
  sCfg = gslc_ElemXKeyPadCfgInit_Num();
  sCfg.sBaseCfg.nButtonSzW=40;
  sCfg.sBaseCfg.nButtonSzH=40;
  gslc_ElemXKeyPadCfgSetFloatEn_Num(&sCfg, false);
  gslc_ElemXKeyPadCfgSetSignEn_Num(&sCfg, false);
  m_pElemKeyPadNum = gslc_ElemXKeyPadCreate_Num(&m_gui, E_ELEM_KEYPAD_NUM, E_POP_KEYPAD_NUM,
    &m_sKeyPadNum, -2, 110, E_DOSIS_BOOK12, &sCfg);
  gslc_ElemXKeyPadValSetCb(&m_gui, m_pElemKeyPadNum, &CbKeypad);

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
