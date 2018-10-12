/*********************************************************
 **
 ** File  Main_UA_1_private.c
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
 * Functions to write and read float values                                                 *
 ********************************************************************************************/
#ifndef WRITE_FLOAT
void WRITE_FLOAT(buffer_el msg[], float d) {
 WRITE_ULONG( (msg),* ( (unsigned long *) (&(d)) )  );
}
#endif

#ifndef READ_FLOAT
float READ_FLOAT(const buffer_el buffer[]) 
{
  unsigned tmp = READ_ULONG(buffer);
  return  * ( (float *)(&tmp) );  
}
#endif

/********************************************************************************************
 * Functions to manage the Block Structure exchanger between UA and A661 server at Run Time *
 ********************************************************************************************/

/* Declare A661 message header  */
uaa_size a661_msg_cmd_header(buffer_el msg[], uaa_uint8 layer_id, 
                                              uaa_uint16 context_number)
{
  msg[0] = GET_BYTE_0(A661_BEGIN_BLOCK);
  msg[1] = GET_BYTE_0(layer_id);
  msg[2] = GET_BYTE_1(context_number);
  msg[3] = GET_BYTE_0(context_number);
  return 4;
}

/* Declare Set Parameter header */
uaa_size a661_msg_csp_header(buffer_el msg[], uaa_uint16 wid)
{
  msg[0] = GET_BYTE_1(A661_CMD_SET_PARAMETER);
  msg[1] = GET_BYTE_0(A661_CMD_SET_PARAMETER);
  msg[4] = GET_BYTE_1(wid);
  msg[5] = GET_BYTE_0(wid);
  msg[6] = 0;
  msg[7] = 0;
  return 8;
}

/* Identify if an element of the input is set to true */
uaa_size any_true (uaa_bool input[], uaa_size size){
  unsigned i = 0; 
  uaa_size res = 0;
  if (input != 0) {
    for (i; i < size; i++) {
      res = res || input[i];
    }
  } 
  return res;
}

/* Add zeros to align the content of message on 32 bits */
A661_INTERNAL uaa_size align32(buffer_el msg[])
{
  uaa_size delta = ((unsigned)msg) % 4;
  uaa_size n = 4 - delta;
  switch(delta)
    {
    case 1: msg[0] = 0;
            msg[1] = 0;
            msg[2] = 0; break;
    case 2: msg[0] = 0;
            msg[1] = 0; break;
    case 3: msg[0] = 0; break;
    default:
    case 0: n = 0; break;
    }
  return n;
}

/* Add zeros to align the content of message on 16 bits */
A661_INTERNAL uaa_size align16(buffer_el msg[])
{
  uaa_size delta = ((unsigned)msg) % 2;
  uaa_size n = 2 - delta;
  switch(delta)
    {
    case 1: msg[2] = 0; break;
    default:
    case 0: n = 0; break;
    }
  return n;
}

/* Return offset */
A661_INTERNAL uaa_size offset_align32(uaa_size n)
{
  uaa_size delta = n % 4;
  uaa_size offset = 4 - delta;
  return offset;
}

/* Return the number of element set to true inside input array */
A661_INTERNAL uaa_size emit_count(uaa_bool emit[], uaa_size size) {
  uaa_size i = 0;
  uaa_size res = 0;
  for(; i < size; i++) {
    if (emit[i]) {
      res = res + 1;
    }
  }
  return res;
}

/* Copy string with maximum size */
A661_INTERNAL uaa_size write_string(buffer_el msg[], buffer_el str[], uaa_size max)
{
  uaa_size i;
  for (i = 0; ( i < max ) && ( str[i] != '\0' ); i++) {
    msg[i] = str[i];
  }
  msg[i] = '\0';
  return i + 1;
}

/* Write bitfield on 8 bits */
A661_INTERNAL void write_bitfield_u8(buffer_el msg[], uaa_size val, uaa_size startbit, uaa_size nb_bits)
{
  unsigned long tmp = msg[0];
  unsigned long mask = (( 1 << nb_bits) - 1);
  tmp = tmp  | ( (val & mask) << startbit );
  msg[0] = tmp;
}

/* Write bitfield on 16 bits */
A661_INTERNAL void write_bitfield_u16(buffer_el msg[], uaa_size val, uaa_size startbit, uaa_size nb_bits)
{
  unsigned long tmp = READ_USHORT ( msg );
  unsigned long mask = (( 1 << nb_bits) - 1);
  tmp = tmp  | ( (val & mask) << startbit );
  WRITE_USHORT (msg, tmp);
}

/* Define macro to perfom clamping */
#ifndef CLAMP
#define CLAMP(x, low, high)  (((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))
#endif

#ifndef REAL_TO_FR
#define REAL_TO_FR

/* Convert floating point values to fr values */
#ifdef kcg_real
A661_INTERNAL uaa_int32 real_to_fr(kcg_real val, uaa_size nb_bit, uaa_size max)
{
  unsigned top = ( 1 << (nb_bit - 1));
  double tmp = (val * top) / max; 
  double clamp_min = -(double)top;
  double clamp_max = top - 1.0;
  
  tmp = CLAMP(tmp, clamp_min, clamp_max);
  return tmp;
}
#endif /* kcg_real */

#ifdef kcg_float32
A661_INTERNAL uaa_int32 float32_to_fr(kcg_float32 val, uaa_size nb_bit, uaa_size max)
{
  unsigned top = ( 1 << (nb_bit - 1));
  double tmp = (val * top) / max; 
  double clamp_min = -(double)top;
  double clamp_max = top - 1.0;
  
  tmp = CLAMP(tmp, clamp_min, clamp_max);
  return tmp;
}
#endif /* kcg_float32 */

#ifdef kcg_float64
A661_INTERNAL uaa_int32 float64_to_fr(kcg_float64 val, uaa_size nb_bit, uaa_size max)
{
  unsigned top = ( 1 << (nb_bit - 1));
  double tmp = (val * top) / max; 
  double clamp_min = -(double)top;
  double clamp_max = top - 1.0;
  
  tmp = CLAMP(tmp, clamp_min, clamp_max);
  return tmp;
}
#endif /* kcg_float64 */

#endif /*REAL_TO_FR*/

#ifdef kcg_real
/* Write fr values on 32 bits */
A661_INTERNAL uaa_size write_fr32_with_real(buffer_el msg[], kcg_real val, uaa_size max )
{
  WRITE_ULONG(msg, real_to_fr( val, 32, max)); 
  return 4;
}

/* Write fr values on 16 bits */
A661_INTERNAL uaa_size write_fr16_with_real(buffer_el msg[], kcg_real val, uaa_size max )
{
  WRITE_USHORT(msg, real_to_fr( val, 16, max));
  return 2;
}

/* Write fr values on 8 bits */
A661_INTERNAL uaa_size write_fr8_with_real(buffer_el msg[], kcg_real val, uaa_size max )
{
  msg[0] = real_to_fr( val, 8, max);
  return 1;
}
#endif /* kcg_real */

#ifdef kcg_float32
/* Write fr values on 32 bits */
A661_INTERNAL uaa_size write_fr32_with_float32(buffer_el msg[], kcg_float32 val, uaa_size max )
{
  WRITE_ULONG(msg, float32_to_fr( val, 32, max)); 
  return 4;
}

/* Write fr values on 16 bits */
A661_INTERNAL uaa_size write_fr16_with_float32(buffer_el msg[], kcg_float32 val, uaa_size max )
{
  WRITE_USHORT(msg, float32_to_fr( val, 16, max));
  return 2;
}

/* Write fr values on 8 bits */
A661_INTERNAL uaa_size write_fr8_with_float32(buffer_el msg[], kcg_float32 val, uaa_size max )
{
  msg[0] = float32_to_fr( val, 8, max);
  return 1;
}
#endif /* kcg_float32 */

#ifdef kcg_float64
/* Write fr values on 32 bits */
A661_INTERNAL uaa_size write_fr32_with_float64(buffer_el msg[], kcg_float64 val, uaa_size max )
{
  WRITE_ULONG(msg, float64_to_fr( val, 32, max)); 
  return 4;
}

/* Write fr values on 16 bits */
A661_INTERNAL uaa_size write_fr16_with_float64(buffer_el msg[], kcg_float64 val, uaa_size max )
{
  WRITE_USHORT(msg, float64_to_fr( val, 16, max));
  return 2;
}

/* Write fr values on 8 bits */
A661_INTERNAL uaa_size write_fr8_with_float64(buffer_el msg[], kcg_float64 val, uaa_size max )
{
  msg[0] = float64_to_fr( val, 8, max);
  return 1;
}
#endif /* kcg_float64 */

#ifndef FR_TO_REAL
#define FR_TO_REAL

/* Convert fr values to real */
#ifdef kcg_real
A661_INTERNAL kcg_real fr_to_real ( uaa_size val, uaa_size nb_bit, uaa_size max)
{
  unsigned top = ( 1 << (nb_bit - 1 ));
  return (kcg_real)(((double)val * (double)max) / top );
}
#endif /* kcg_real */

#ifdef kcg_float32
A661_INTERNAL kcg_float32 fr_to_float32 ( uaa_size val, uaa_size nb_bit, uaa_size max)
{
  unsigned top = ( 1 << (nb_bit - 1 ));
  return (kcg_float32)(((double)val * (double)max) / top );
}
#endif /* kcg_float32 */

#ifdef kcg_float64
A661_INTERNAL kcg_float64 fr_to_float64 ( uaa_size val, uaa_size nb_bit, uaa_size max)
{
  unsigned top = ( 1 << (nb_bit - 1 ));
  return (kcg_float64)(((double)val * (double)max) / top );
}
#endif /* kcg_float64 */

#endif /* FR_TO_REAL */

#ifndef READ_FR
#define READ_FR

#ifdef kcg_real
/* Convert fr values on 32 bits to kcg_real */
A661_INTERNAL kcg_real read_fr32_to_real(const buffer_el buffer[], uaa_size max) 
{
  uaa_size tmp = READ_ULONG(buffer);
  return  fr_to_real (tmp, 32, max);  
}

/* Convert fr values on 16 bits to kcg_real */
A661_INTERNAL kcg_real read_fr16_to_real(const buffer_el buffer[], uaa_size max) 
{
  uaa_size tmp = READ_USHORT(buffer);
  return  fr_to_real (tmp, 16, max);  
}

/* Convert fr values on 8 bits to kcg_real */
A661_INTERNAL kcg_real read_fr8_to_real(const buffer_el buffer[], uaa_size max) 
{
  uaa_size tmp = buffer[0];
  return  fr_to_real (tmp, 8, max);  
}
#endif /* kcg_real */

#ifdef kcg_float32
/* Convert fr values on 32 bits to kcg_float32 */
A661_INTERNAL kcg_float32 read_fr32_to_float32(const buffer_el buffer[], uaa_size max) 
{
  uaa_size tmp = READ_ULONG(buffer);
  return  fr_to_float32 (tmp, 32, max);  
}

/* Convert fr values on 16 bits to kcg_float32 */
A661_INTERNAL kcg_float32 read_fr16_to_float32(const buffer_el buffer[], uaa_size max) 
{
  uaa_size tmp = READ_USHORT(buffer);
  return  fr_to_float32 (tmp, 16, max);  
}

/* Convert fr values on 8 bits to kcg_float32 */
A661_INTERNAL kcg_float32 read_fr8_to_float32(const buffer_el buffer[], uaa_size max) 
{
  uaa_size tmp = buffer[0];
  return  fr_to_float32 (tmp, 8, max);  
}
#endif /* kcg_float32 */

#ifdef kcg_float64
A661_INTERNAL kcg_float64 read_fr32_to_float64(const buffer_el buffer[], uaa_size max) 
{
  uaa_size tmp = READ_ULONG(buffer);
  return  fr_to_float64 (tmp, 32, max);  
}

/* Convert fr values on 16 bits to kcg_float64 */
A661_INTERNAL kcg_float64 read_fr16_to_float64(const buffer_el buffer[], uaa_size max) 
{
  uaa_size tmp = READ_USHORT(buffer);
  return  fr_to_float64 (tmp, 16, max);  
}

/* Convert fr values on 8 bits to kcg_float64 */
A661_INTERNAL kcg_float64 read_fr8_to_float64(const buffer_el buffer[], uaa_size max) 
{
  uaa_size tmp = buffer[0];
  return  fr_to_float64 (tmp, 8, max);  
}
#endif /* kcg_float64 */

#endif /* READ_FR */


/********************************************************************************************
 * Code for Simulation time : runtime check of string length                                *
 ********************************************************************************************/
#ifdef SIM

char * layerstring = "";
char * widgetstring = "";
char * parameterstring = "";
void check_string_access (const char * fieldname, uaa_size stringsize, uaa_size arraysize)
{
  char buffer[16000];
  if (stringsize > arraysize) {
    sprintf (buffer, "%s/%s/%s/%s overflow, the SCADE variable used as string size (%i) is larger than the array used for the string(%i).", 
    layerstring, widgetstring, parameterstring, fieldname, stringsize, arraysize);
    SsmOutputMessage(SIM_ERROR, buffer);
  }
}

#else /* SIM */
#endif /* SIM */

/********************************************************************************************
 * Functions to pack messages for the A661 server                                           *
 ********************************************************************************************/

/* Declare UA request header  */
A661_INTERNAL uaa_size a661_com_A661_CMD_UA_REQUEST_header(buffer_el msg[], uaa_size size) 
{
    WRITE_USHORT(msg, A661_CMD_UA_REQUEST);
    WRITE_USHORT(msg + 2, size);
    return 4;
}

/* Declare UA request on 8 bits */
uaa_size a661_com_A661_CMD_UA_REQUEST_8(buffer_el msg[], uaa_uint16 data1, uaa_uint16 data2)
{
    a661_com_A661_CMD_UA_REQUEST_header(msg, 8);
    WRITE_USHORT(msg + 4 , data1);
    WRITE_USHORT(msg + 4 + 2 , data2);
    return 8;
}

/* Sub functions to send messages:
    generate messages for widgets,
    send messages for widgets,
    perform UA request for layers,
    send messages for layers                    */

/* Generate message with generic function a661_com_msg_char */
/* Widget BlinkingContainer for parameter A661_VISIBLE */
/* Widget ComboBox for parameter A661_VISIBLE */
/* Widget GpRectangle for parameter A661_VISIBLE */
/* Widget GpRectangle for parameter A661_FILL_INDEX */
/* Widget GpRectangle for parameter A661_COLOR_INDEX */
/* Widget PushButton for parameter A661_VISIBLE */
 uaa_size a661_com_msg_char(buffer_el msg[], 
  uaa_uint16 pid,  uaa_bool A661_VISIBLE_Visible_){
  WRITE_USHORT(msg, pid);
  msg[2] = GET_BYTE_0(A661_VISIBLE_Visible_);
  msg[3] = GET_BYTE_0(0);
  return 4 ;
}

/* Generate message with generic function a661_com_msg_long */
/* Widget GpRectangle for parameter A661_SIZE_Y */
 uaa_size a661_com_msg_long(buffer_el msg[], 
  uaa_uint16 pid,  uaa_uint32 A661_SIZE_Y_SizeY_){
  WRITE_USHORT(msg, pid);
  WRITE_USHORT(msg + 2, 0);
  WRITE_ULONG(msg + 4, A661_SIZE_Y_SizeY_);
  return 8 ;
}

/* Pack messages for widget PushButton: A661_VISIBLE */
 uaa_size a661_com_csp_widget_PushButton(buffer_el msg[], 
  uaa_uint16 wid,  uaa_bool A661_VISIBLE__emit__, 
  uaa_bool A661_VISIBLE_Visible_){
  uaa_size offset = 0;
  if (A661_VISIBLE__emit__){
    offset = 8;
    a661_msg_csp_header(msg, wid);
    if (A661_VISIBLE__emit__){
      offset = offset + a661_com_msg_char(msg + offset, A661_VISIBLE,
        A661_VISIBLE_Visible_);
    }
    WRITE_USHORT(msg + 2, offset);
  }
  return offset ;
}

/* Pack messages for widget GpRectangle: A661_COLOR_INDEX, A661_FILL_INDEX, A661_SIZE_Y, A661_VISIBLE */
 uaa_size a661_com_csp_widget_GpRectangle(buffer_el msg[], 
  uaa_uint16 wid,  uaa_bool A661_COLOR_INDEX__emit__, 
  kcg_uint8 A661_COLOR_INDEX_ColorIndex_,  uaa_bool A661_FILL_INDEX__emit__, 
  kcg_uint8 A661_FILL_INDEX_FillIndex_,  uaa_bool A661_SIZE_Y__emit__, 
  uaa_uint32 A661_SIZE_Y_SizeY_,  uaa_bool A661_VISIBLE__emit__, 
  uaa_bool A661_VISIBLE_Visible_){
  uaa_size offset = 0;
  if (A661_VISIBLE__emit__ ||
  A661_SIZE_Y__emit__ ||
  A661_FILL_INDEX__emit__ ||
  A661_COLOR_INDEX__emit__){
    offset = 8;
    a661_msg_csp_header(msg, wid);
    if (A661_VISIBLE__emit__){
      offset = offset + a661_com_msg_char(msg + offset, A661_VISIBLE,
        A661_VISIBLE_Visible_);
    }
    if (A661_SIZE_Y__emit__){
      offset = offset + a661_com_msg_long(msg + offset, A661_SIZE_Y,
        A661_SIZE_Y_SizeY_);
    }
    if (A661_FILL_INDEX__emit__){
      offset = offset + a661_com_msg_char(msg + offset, A661_FILL_INDEX,
        A661_FILL_INDEX_FillIndex_);
    }
    if (A661_COLOR_INDEX__emit__){
      offset = offset + a661_com_msg_char(msg + offset, A661_COLOR_INDEX,
        A661_COLOR_INDEX_ColorIndex_);
    }
    WRITE_USHORT(msg + 2, offset);
  }
  return offset ;
}

/* Pack messages for widget ComboBox: A661_VISIBLE */
 uaa_size a661_com_csp_widget_ComboBox(buffer_el msg[], 
  uaa_uint16 wid,  uaa_bool A661_VISIBLE__emit__, 
  uaa_bool A661_VISIBLE_Visible_){
  uaa_size offset = 0;
  if (A661_VISIBLE__emit__){
    offset = 8;
    a661_msg_csp_header(msg, wid);
    if (A661_VISIBLE__emit__){
      offset = offset + a661_com_msg_char(msg + offset, A661_VISIBLE,
        A661_VISIBLE_Visible_);
    }
    WRITE_USHORT(msg + 2, offset);
  }
  return offset ;
}

/* Pack messages for widget BlinkingContainer: A661_VISIBLE */
 uaa_size a661_com_csp_widget_BlinkingContainer(buffer_el msg[], 
  uaa_uint16 wid,  uaa_bool A661_VISIBLE__emit__, 
  uaa_bool A661_VISIBLE_Visible_){
  uaa_size offset = 0;
  if (A661_VISIBLE__emit__){
    offset = 8;
    a661_msg_csp_header(msg, wid);
    if (A661_VISIBLE__emit__){
      offset = offset + a661_com_msg_char(msg + offset, A661_VISIBLE,
        A661_VISIBLE_Visible_);
    }
    WRITE_USHORT(msg + 2, offset);
  }
  return offset ;
}

/*********************************************************
 ** End of file
 ** End of generation: 2018-10-12T05:12:27
 *********************************************************/

