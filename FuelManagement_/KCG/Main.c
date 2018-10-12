/* $********** SCADE Suite KCG 32-bit 6.6 (build i19) ***********
** Command: kcg66.exe -config D:/gd/ITA/CE-235/scade/fuel/FuelManagement_/KCG/config.txt
** Generation date: 2018-10-12T05:09:39
*************************************************************$ */

#include "kcg_consts.h"
#include "kcg_sensors.h"
#include "Main.h"

/* Main/ */
void Main(inC_Main *inC, outC_Main *outC)
{
  kcg_uint32 tmp;
  /* SM1: */
  SSM_ST_SM1 SM1_state_act;

  outC->FuelColor.Emit = kcg_true;
  outC->TankFullVisible.Emit = kcg_true;
  outC->FuelVisible.Emit = kcg_true;
  outC->FuelLevel.Emit = kcg_true;
  outC->FuelTypeEnable.Emit = kcg_true;
  outC->RefuelEnable.Emit = kcg_true;
  outC->LayerVisible = outC->_L1_ShowLayer_1;
  outC->_L1_ShowLayer_1 = kcg_false;
  /* @6/_L28=, @6/_L5= */
  if (inC->Refuel) {
    /* @6/_L13=, @6/_L24= */
    if (outC->_L5_SetFuelLevel_1 < kcg_lit_uint32(9000)) {
      outC->_L5_SetFuelLevel_1 = outC->_L5_SetFuelLevel_1 + FUEL_INCREMENT;
    }
    else {
      outC->_L5_SetFuelLevel_1 = kcg_lit_uint32(9900);
    }
  }
  else /* @6/_L32=, @6/_L4= */
  if (inC->EmptyTank) {
    outC->_L5_SetFuelLevel_1 = kcg_lit_uint32(0);
  }
  outC->TankFullVisible.Value = outC->_L5_SetFuelLevel_1 >= kcg_lit_uint32(9900);
  outC->FuelVisible.Value = !(outC->_L5_SetFuelLevel_1 == kcg_lit_uint32(0));
  outC->FuelLevel.Value = outC->_L5_SetFuelLevel_1;
  outC->FuelTypeEnable.Value = outC->_L5_SetFuelLevel_1 == kcg_lit_uint32(0);
  /* SM1: */
  switch (outC->SM1_state_nxt) {
    case SSM_st_TankOpen_SM1 :
      if (inC->TankStatus) {
        SM1_state_act = SSM_st_TankClosed_SM1;
      }
      else {
        SM1_state_act = SSM_st_TankOpen_SM1;
      }
      break;
    case SSM_st_TankClosed_SM1 :
      if (inC->TankStatus) {
        SM1_state_act = SSM_st_TankOpen_SM1;
      }
      else {
        SM1_state_act = SSM_st_TankClosed_SM1;
      }
      break;
    default :
      /* this default branch is unreachable */
      break;
  }
  /* SM1: */
  switch (SM1_state_act) {
    case SSM_st_TankOpen_SM1 :
      tmp = OPEN_ID;
      outC->SM1_state_nxt = SSM_st_TankOpen_SM1;
      break;
    case SSM_st_TankClosed_SM1 :
      tmp = CLOSED_ID;
      outC->SM1_state_nxt = SSM_st_TankClosed_SM1;
      break;
    default :
      /* this default branch is unreachable */
      break;
  }
  outC->RefuelEnable.Value = (inC->FuelType > kcg_lit_uint16(1)) & (tmp ==
      OPEN_ID) & (outC->_L5_SetFuelLevel_1 < kcg_lit_uint32(9900));
  /* @5/_L5= */
  switch (inC->FuelType) {
    case kcg_lit_uint16(2) :
      outC->FuelColor.Value = ALCOHOL_COLOR;
      break;
    case kcg_lit_uint16(3) :
      outC->FuelColor.Value = DIESEL_COLOR;
      break;
    default :
      outC->FuelColor.Value = GASOLINE_COLOR;
      break;
  }
}

#ifndef KCG_USER_DEFINED_INIT
void Main_init(outC_Main *outC)
{
  outC->_L1_ShowLayer_1 = kcg_true;
  outC->LayerVisible = kcg_true;
  outC->FuelColor.Emit = kcg_true;
  outC->FuelColor.Value = kcg_lit_uint8(0);
  outC->TankFullVisible.Emit = kcg_true;
  outC->TankFullVisible.Value = kcg_true;
  outC->FuelTypeEnable.Emit = kcg_true;
  outC->FuelTypeEnable.Value = kcg_true;
  outC->RefuelEnable.Emit = kcg_true;
  outC->RefuelEnable.Value = kcg_true;
  outC->FuelLevel.Emit = kcg_true;
  outC->FuelLevel.Value = kcg_lit_uint32(0);
  outC->FuelVisible.Emit = kcg_true;
  outC->FuelVisible.Value = kcg_true;
  outC->SM1_state_nxt = SSM_st_TankClosed_SM1;
  outC->_L5_SetFuelLevel_1 = kcg_lit_uint32(0);
}
#endif /* KCG_USER_DEFINED_INIT */


#ifndef KCG_NO_EXTERN_CALL_TO_RESET
void Main_reset(outC_Main *outC)
{
  outC->_L1_ShowLayer_1 = kcg_true;
  outC->SM1_state_nxt = SSM_st_TankClosed_SM1;
  outC->_L5_SetFuelLevel_1 = kcg_lit_uint32(0);
}
#endif /* KCG_NO_EXTERN_CALL_TO_RESET */

/*
  Expanded instances for: Main/
  @6: (SetFuelLevel#1)
  @5: (SetFuelColor#1)
*/

/* $********** SCADE Suite KCG 32-bit 6.6 (build i19) ***********
** Main.c
** Generation date: 2018-10-12T05:09:39
*************************************************************$ */

