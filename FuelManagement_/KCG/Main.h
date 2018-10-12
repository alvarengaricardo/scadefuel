/* $********** SCADE Suite KCG 32-bit 6.6 (build i19) ***********
** Command: kcg66.exe -config D:/gd/ITA/CE-235/scade/fuel/FuelManagement_/KCG/config.txt
** Generation date: 2018-10-12T05:09:39
*************************************************************$ */
#ifndef _Main_H_
#define _Main_H_

#include "kcg_types.h"

/* ========================  input structure  ====================== */
typedef struct {
  kcg_bool /* TankStatus/ */ TankStatus;
  kcg_uint16 /* @4/FuelType/,
     @4/_L1/,
     @5/FuelType/,
     @5/_L1/,
     FuelType/,
     _L11/,
     _L13/ */ FuelType;
  kcg_bool /* @6/Refuel/, @6/_L2/, @6/_L27/, Refuel/, _L3/ */ Refuel;
  kcg_bool /* @6/Empty/, @6/_L1/, @6/_L29/, EmptyTank/, _L4/ */ EmptyTank;
} inC_Main;

/* =====================  no output structure  ====================== */

/* ========================  context type  ========================= */
typedef struct {
  /* ---------------------------  outputs  --------------------------- */
  kcg_bool /* @3/LayerVisible/, @3/_L2/, LayerVisible/, _L1/ */ LayerVisible;
  BoolMsg /* @1/FuelVisible/, @1/_L9/, FuelVisible/, _L7/ */ FuelVisible;
  intMsg /* @1/FuelLevel/, @1/_L4/, FuelLevel/, _L8/ */ FuelLevel;
  BoolMsg /* @4/RefuelEnable/, @4/_L17/, RefuelEnable/, _L5/ */ RefuelEnable;
  BoolMsg /* @4/FuelTypeEnable/,
     @4/_L18/,
     FuelTypeEnable/,
     _L6/ */ FuelTypeEnable;
  BoolMsg /* @2/TankFullVisible/,
     @2/_L7/,
     TankFullVisible/,
     _L9/ */ TankFullVisible;
  intMsg2 /* @5/FuelColor/, @5/_L6/, FuelColor/, _L10/ */ FuelColor;
  /* -----------------------  no local probes  ----------------------- */
  /* ----------------------- local memories  ------------------------- */
  SSM_ST_SM1 /* SM1: */ SM1_state_nxt;
  kcg_uint32 /* @6/_L5/ */ _L5_SetFuelLevel_1;
  kcg_bool /* @3/_L1/ */ _L1_ShowLayer_1;
  /* -------------------- no sub nodes' contexts  -------------------- */
  /* ----------------- no clocks of observable data ------------------ */
} outC_Main;

/* ===========  node initialization and cycle functions  =========== */
/* Main/ */
extern void Main(inC_Main *inC, outC_Main *outC);

#ifndef KCG_NO_EXTERN_CALL_TO_RESET
extern void Main_reset(outC_Main *outC);
#endif /* KCG_NO_EXTERN_CALL_TO_RESET */

#ifndef KCG_USER_DEFINED_INIT
extern void Main_init(outC_Main *outC);
#endif /* KCG_USER_DEFINED_INIT */

/*
  Expanded instances for: Main/
  @1: (RepaintFuelLevel#1)
  @2: (SetTankFullVisible#1)
  @3: (ShowLayer#1)
  @4: (EnableWidgets#1)
  @5: (SetFuelColor#1)
  @6: (SetFuelLevel#1)
*/

#endif /* _Main_H_ */
/* $********** SCADE Suite KCG 32-bit 6.6 (build i19) ***********
** Main.h
** Generation date: 2018-10-12T05:09:39
*************************************************************$ */

