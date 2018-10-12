/*********************************************************
 **
 ** File  Main_UA_1.c
 **
 ** Automatically generated by SCADE Suite UA Adaptor
 ** Version 19.2 (build 20180628)
 ** 
 ** Date of generation: 2018-10-12T05:12:27
 ** Command line: C:/Program Files/ANSYS Inc/v192/SCADE/SCADE/bin/uaadaptor.exe -sdy D:\gd\ITA\CE-235\scade\fuel\FuelManagement_\FuelManagement_.sdy -n C:\Program Files\ANSYS Inc\v192\SCADE\SCADE Display\config\a661_description\a661.xml -outdir D:/gd/ITA/CE-235/scade/fuel/FuelManagement_/Simulation -k D:/gd/ITA/CE-235/scade/fuel/FuelManagement_/Simulation/kcg_trace.xml -o Main_UA_1 -i FuelManagement__interface.h -encoding ASCII D:\gd\ITA\CE-235\scade\fuel\fuelManagement\fuelManagement.sgfx
 *********************************************************/
#include "kcg_sensors.h"
#include "Main_UA_1.h"
#include "Main_UA_1_constants.h"
#include "Main_UA_1_private.h"

/********************************************************************************************
 * Send messages to the A661 server                                                         *
 ********************************************************************************************/
 uaa_size Main_UA_1_send(buffer_el msg[], 
  outC_Main* scade_ctx,  extern_out_ctx_t * extern_ctx){
  uaa_size offset = 0;
  
  offset = offset + a661_com_layer_1(msg + offset, scade_ctx, extern_ctx);
  return offset ;
}

/********************************************************************************************
 * Receive notifications from the A661 server                                               *
 ********************************************************************************************/
uaa_size Main_UA_1_receive(buffer_el buffer[],  uaa_size buffer_size, 
  inC_Main* scade_ctx,  extern_in_ctx_t * extern_ctx){
  uaa_size widget_event_structure_current_size = 0;
  uaa_size A661_Run_Time_Command_limit = 0;
  uaa_size root_current_size = 0;
  uaa_size n = 0;
  uaa_size next_n = 0;
  /*  type root */
  switch (buffer[ n ]){
    case A661_BEGIN_BLOCK : 
      root_current_size = READ_ULONG(( buffer + ( 4 + n ) ));
      next_n = ( ( n + root_current_size ) - 4 );
      /*  LayerIdent */
      switch (buffer[ ( 1 + n ) ]){
        case 1 : 
          /*  root */
          n = ( 8 + n );
          A661_Run_Time_Command_limit = ( ( n + root_current_size ) - 12 );
          while(( n < A661_Run_Time_Command_limit )){
            /*  type A661_Run_Time_Command */
            switch (READ_USHORT(( buffer + n ))){
              case A661_NOTIFY_WIDGET_EVENT : 
                widget_event_structure_current_size = READ_USHORT(( buffer + ( 2 + n ) ));
                next_n = ( n + widget_event_structure_current_size );
                /*  WidgetIdent */
                switch (READ_USHORT(( buffer + ( 4 + n ) ))){
                  case 10 : 
                    /*  widget_event_structure */
                    n = ( 6 + n );
                    /*  type EventStructure */
                    switch (READ_USHORT(( buffer + ( 2 + n ) ))){
                      case A661_EVT_SEL_ENTRY_CHANGE : 
                        /*  ComboBox_A661_EVT_SEL_ENTRY_CHANGE */
                        /*  EvtEntryNumber */
                        scade_ctx->FuelType = READ_USHORT(( buffer + ( 4 + n ) ));
                        break;
                      default : break;
                    }
                    n = next_n;
                    break;
                  case 9 : 
                    /*  widget_event_structure */
                    n = ( 6 + n );
                    /*  type EventStructure */
                    switch (READ_USHORT(( buffer + ( 2 + n ) ))){
                      case A661_EVT_SELECTION : 
                        /*  PushButton_A661_EVT_SELECTION */
                        /*  Notify */
                        scade_ctx->EmptyTank = kcg_true;
                        break;
                      default : break;
                    }
                    n = next_n;
                    break;
                  case 8 : 
                    /*  widget_event_structure */
                    n = ( 6 + n );
                    /*  type EventStructure */
                    switch (READ_USHORT(( buffer + ( 2 + n ) ))){
                      case A661_EVT_SELECTION : 
                        /*  PushButton_A661_EVT_SELECTION */
                        /*  Notify */
                        scade_ctx->Refuel = kcg_true;
                        break;
                      default : break;
                    }
                    n = next_n;
                    break;
                  case 7 : 
                    /*  widget_event_structure */
                    n = ( 6 + n );
                    /*  type EventStructure */
                    switch (READ_USHORT(( buffer + ( 2 + n ) ))){
                      case A661_EVT_STATE_CHANGE : 
                        /*  ToggleButton_A661_EVT_STATE_CHANGE */
                        /*  Notify */
                        scade_ctx->TankStatus = kcg_true;
                        break;
                      default : break;
                    }
                    n = next_n;
                    break;
                  default : break;
                }
                break;
              default : 
                next_n = ( n + READ_USHORT(( buffer + ( 2 + n ) )) );
                n = next_n;
                break;
            }
            n = next_n;
          }
          n = ( 4 + n );
          break;
        default : break;
      }
      break;
    default : break;
  }
  return n ;
}

/********************************************************************************************
 * Clear notifications                                                                      *
 ********************************************************************************************/
void Main_UA_1_receive_clear(inC_Main* scade_ctx, 
  extern_in_ctx_t * extern_ctx){
  scade_ctx->TankStatus = kcg_false;
  scade_ctx->Refuel = kcg_false;
  scade_ctx->EmptyTank = kcg_false;
}

/*********************************************************
 ** End of file
 ** End of generation: 2018-10-12T05:12:27
 *********************************************************/

