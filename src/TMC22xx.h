/********************************************************************************************
 * File:        /TMC22xx.h
 * Project:     uStepper 8b (compatible with uStepper S-lite)
 * Description: Part of the uStepper 8b library. TMC22xx (TMC2208/TMC2209) compatible.
 * Author:      Thomas Olsen
 * Copyright:   (C) 2020-2026 uStepper ApS
 * License:     Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International
 * Warranty:    Provided "AS IS" without warranty of any kind. Use at your own risk.
 * Website:     https://www.ustepper.com
 * Contact:     administration@ustepper.com
 ********************************************************************************************/
/** @file TMC22xx.h
 * @brief      Function prototypes and definitions for the uStepper TMC22xx driver
 *             library
 *
 *             This file contains class and function prototypes for the library,
 *             as well as necessary constants and global variables.
 *
 * @author     Thomas Olsen (thomas@ustepper.com)
 */

#ifndef TMC22XX_H_
#define TMC22XX_H_

	#include <stdlib.h>
	#include <stdint.h>
	#include <avr/pgmspace.h>
	#include <Arduino.h>
	#include <util/delay.h>
	
	/** @name default values	 
	*	default values for non-zero registers
	*/
	///@{
	#define R00 0x00000041
	#define R10 0x00001F00
	#define R6C 0x10000053
	#define R70 0xC10D0024
	///@}
	
	/** @name Register addresses	 */
	///@{
	// ===== TMC22xx & 2202 & TMC22xx & 2220 & 2225 "Donkey Kong" family register set =====
	#define TMC22xx_GCONF         0x00
	#define TMC22xx_GSTAT         0x01
	#define TMC22xx_IFCNT         0x02
	#define TMC22xx_SLAVECONF     0x03
	#define TMC22xx_OTP_PROG      0x04
	#define TMC22xx_OTP_READ      0x05
	#define TMC22xx_IOIN          0x06
	#define TMC22xx_FACTORY_CONF  0x07

	#define TMC22xx_IHOLD_IRUN    0x10
	#define TMC22xx_TPOWERDOWN    0x11
	#define TMC22xx_TSTEP         0x12
	#define TMC22xx_TPWMTHRS      0x13

	#define TMC22xx_VACTUAL       0x22

	#define TMC22xx_MSCNT         0x6A
	#define TMC22xx_MSCURACT      0x6B
	#define TMC22xx_CHOPCONF      0x6C
	#define TMC22xx_DRVSTATUS     0x6F
	#define TMC22xx_PWMCONF       0x70
	#define TMC22xx_PWMSCALE      0x71
	#define TMC22xx_PWM_AUTO      0x72
	///@}
	
	/**
	* \defgroup Bit masks and shift patterns for every bit in each register
	* @{
	*/
	// Write-Bit
	#define TMC22xx_WRITE_BIT 0x80

	#define TMC22xx_I_SCALE_ANALOG_MASK          0x01 // GCONF // I_scale_analog  (Reset default=1)
	#define TMC22xx_I_SCALE_ANALOG_SHIFT         0 // min.: 0, max.: 1, default: 0
	#define TMC22xx_INTERNAL_RSENSE_MASK         0x02 // GCONF // internal_Rsense (Reset default: OTP)
	#define TMC22xx_INTERNAL_RSENSE_SHIFT        1 // min.: 0, max.: 1, default: 0
	#define TMC22xx_EN_SPREADCYCLE_MASK          0x04 // GCONF // en_spreadCycle (Reset default: OTP)
	#define TMC22xx_EN_SPREADCYCLE_SHIFT         2 // min.: 0, max.: 1, default: 0
	#define TMC22xx_SHAFT_MASK                   0x08 // GCONF // controls motor direction
	#define TMC22xx_SHAFT_SHIFT                  3 // min.: 0, max.: 1, default: 0
	#define TMC22xx_INDEX_OTPW_MASK              0x10 // GCONF // index_otpw
	#define TMC22xx_INDEX_OTPW_SHIFT             4 // min.: 0, max.: 1, default: 0
	#define TMC22xx_INDEX_STEP_MASK              0x20 // GCONF // index_step
	#define TMC22xx_INDEX_STEP_SHIFT             5 // min.: 0, max.: 1, default: 0
	#define TMC22xx_PDN_DISABLE_MASK             0x40 // GCONF // pdn_disable
	#define TMC22xx_PDN_DISABLE_SHIFT            6 // min.: 0, max.: 1, default: 0
	#define TMC22xx_MSTEP_REG_SELECT_MASK        0x80 // GCONF // mstep_reg_select
	#define TMC22xx_MSTEP_REG_SELECT_SHIFT       7 // min.: 0, max.: 1, default: 0
	#define TMC22xx_MULTISTEP_FILT_MASK          0x0100 // GCONF // multistep_filt (Reset default=1)
	#define TMC22xx_MULTISTEP_FILT_SHIFT         8 // min.: 0, max.: 1, default: 0
	#define TMC22xx_TEST_MODE_MASK               0x0200 // GCONF // test_mode 0
	#define TMC22xx_TEST_MODE_SHIFT              9 // min.: 0, max.: 1, default: 0
	#define TMC22xx_RESET_MASK                   0x01 // GSTAT // reset
	#define TMC22xx_RESET_SHIFT                  0 // min.: 0, max.: 1, default: 0
	#define TMC22xx_DRV_ERR_MASK                 0x02 // GSTAT // drv_err
	#define TMC22xx_DRV_ERR_SHIFT                1 // min.: 0, max.: 1, default: 0
	#define TMC22xx_UV_CP_MASK                   0x04 // GSTAT // uv_cp
	#define TMC22xx_UV_CP_SHIFT                  2 // min.: 0, max.: 1, default: 0
	#define TMC22xx_IFCNT_MASK                   0xFF // IFCNT // Interface  transmission  counter.  This  register  becomes incremented  with  each successful UART  interface write access.  Read  out  to  check  the  serial  transmission  for lost  data.  Read  accesses  do  not  change  the  content. The counter wraps around from 255 to 0.
	#define TMC22xx_IFCNT_SHIFT                  0 // min.: 0, max.: 255, default: 0
	#define TMC22xx_SLAVECONF_MASK               0x0F00 // SLAVECONF // SENDDELAY for read access (time until reply is sent): 0, 1:   8 bit times  2, 3:   3*8 bit times  4, 5:   5*8 bit times  6, 7:   7*8 bit times  8, 9:   9*8 bit times  10, 11:  11*8 bit times  12, 13:  13*8 bit times  14, 15:  15*8 bit times
	#define TMC22xx_SLAVECONF_SHIFT              8 // min.: 0, max.: 15, default: 0
	#define TMC22xx_OTPBIT_MASK                  0x07 // OTP_PROG // Selection of OTP bit to be programmed to the selected byte location (n=0..7: programs bit n to a logic 1)
	#define TMC22xx_OTPBIT_SHIFT                 0 // min.: 0, max.: 7, default: 0
	#define TMC22xx_OTPBYTE_MASK                 0x30 // OTP_PROG // Selection of OTP programming location (0, 1 or 2)
	#define TMC22xx_OTPBYTE_SHIFT                4 // min.: 0, max.: 3, default: 0
	#define TMC22xx_OTPMAGIC_MASK                0xFF00 // OTP_PROG // Set  to  0xBD  to  enable  programming.  A  programming time of  minimum 10ms per bit is  recommended (check by reading OTP_READ).
	#define TMC22xx_OTPMAGIC_SHIFT               8 // min.: 0, max.: 255, default: 0
	#define TMC22xx_OTP0_BYTE_0_READ_DATA_MASK   0x01 // OTP_READ // to be detailed
	#define TMC22xx_OTP0_BYTE_0_READ_DATA_SHIFT  0 // min.: 0, max.: 255, default: 0
	#define TMC22xx_OTP1_BYTE_1_READ_DATA_MASK   0x02 // OTP_READ // to be detailed
	#define TMC22xx_OTP1_BYTE_1_READ_DATA_SHIFT  8 // min.: 0, max.: 255, default: 0
	#define TMC22xx_OTP2_BYTE_2_READ_DATA_MASK   0x04 // OTP_READ // to be detailed
	#define TMC22xx_OTP2_BYTE_2_READ_DATA_SHIFT  16 // min.: 0, max.: 255, default: 0
	#define TMC22xx_ENN_MASK                     0x01 // IOIN // 
	#define TMC22xx_ENN_SHIFT                    0 // min.: 0, max.: 1, default: 0
	#define TMC22xx_MS1_MASK                     0x04 // IOIN // 
	#define TMC22xx_MS1_SHIFT                    2 // min.: 0, max.: 1, default: 0
	#define TMC22xx_MS2_MASK                     0x08 // IOIN // 
	#define TMC22xx_MS2_SHIFT                    3 // min.: 0, max.: 1, default: 0
	#define TMC22xx_DIAG_MASK                    0x10 // IOIN // 
	#define TMC22xx_DIAG_SHIFT                   4 // min.: 0, max.: 1, default: 0
	#define TMC22xx_PDN_UART_MASK                0x40 // IOIN // 
	#define TMC22xx_PDN_UART_SHIFT               6 // min.: 0, max.: 1, default: 0
	#define TMC22xx_STEP_MASK                    0x80 // IOIN // 
	#define TMC22xx_STEP_SHIFT                   7 // min.: 0, max.: 1, default: 0
	#define TMC22xx_SEL_A_MASK                   0x0100 // IOIN // Driver type
	#define TMC22xx_SEL_A_SHIFT                  8 // min.: 0, max.: 1, default: 0
	#define TMC22xx_DIR_MASK                     0x0200 // IOIN // 
	#define TMC22xx_DIR_SHIFT                    9 // min.: 0, max.: 1, default: 0
	#define TMC22xx_VERSION_MASK                 0xFF000000 // IOIN // VERSION: 0x20=first version of the IC Identical numbers mean full digital compatibility.
	#define TMC22xx_VERSION_SHIFT                24 // min.: 0, max.: 255, default: 0
	#define TMC22xx_FCLKTRIM_MASK                0x1F // FACTORY_CONF // FCLKTRIM (Reset default: OTP)           0â€¦31:  Lowest  to  highest  clock  frequency.  Check  at  charge  pump  output.  The  frequency  span  is  not  guaranteed,  but  it  is  tested,  that  tuning  to  12MHz  internal  clock  is  possible.  The  devices  come  preset  to  12MHz clock frequency by OTP programming.
	#define TMC22xx_FCLKTRIM_SHIFT               0 // min.: 0, max.: 31, default: 0
	#define TMC22xx_OTTRIM_MASK                  0x30 // FACTORY_CONF // OTTRIM (Default: OTP) %00:   OT=143Â°C, OTPW=120Â°C %01:  OT=150Â°C, OTPW=120Â°C %10:  OT=150Â°C, OTPW=143Â°C %11:  OT=157Â°C, OTPW=143Â°C
	#define TMC22xx_OTTRIM_SHIFT                 8 // min.: 0, max.: 3, default: 0
	#define TMC22xx_IHOLD_MASK                   0x1F // IHOLD_IRUN // IHOLD (Reset default: OTP) Standstill current (0=1/32...31=32/32) In  combination  with  stealthChop  mode,  setting  IHOLD=0  allows  to  choose  freewheeling  or  coil  short circuit (passive braking) for motor stand still.
	#define TMC22xx_IHOLD_SHIFT                  0 // min.: 0, max.: 31, default: 0
	#define TMC22xx_IRUN_MASK                    0x1F00 // IHOLD_IRUN // IRUN (Reset default=31) Motor run current (0=1/32...31=32/32) Hint:  Choose  sense  resistors  in  a  way,  that  normal  IRUN is 16 to 31 for best microstep performance.
	#define TMC22xx_IRUN_SHIFT                   8 // min.: 0, max.: 31, default: 0
	#define TMC22xx_IHOLDDELAY_MASK              0x0F0000 // IHOLD_IRUN // IHOLDDELAY (Reset default: OTP) Controls  the  number  of  clock  cycles  for  motor  power down after standstill is detected (stst=1) and  TPOWERDOWN  has  expired.  The  smooth  transition  avoids a motor jerk upon power down. 0:   instant power down 1..15:   Delay per current reduction step in multiple  of 2^18 clocks
	#define TMC22xx_IHOLDDELAY_SHIFT             16 // min.: 0, max.: 15, default: 0
	#define TMC22xx_TPOWERDOWN_MASK              0xFF // TPOWERDOWN // (Reset default=20) Sets  the  delay  time  from  stand  still  (stst)  detection  to  motor current power down. Time range is about 0 to 5.6 seconds.  0...((2^8)-1) * 2^18 tclk Attention:  A  minimum  setting  of  2  is  required  to  allow automatic tuning of stealthChop PWM_OFFS_AUTO.
	#define TMC22xx_TPOWERDOWN_SHIFT             0 // min.: 0, max.: 255, default: 0
	#define TMC22xx_TSTEP_MASK                   0x0FFFFF // TSTEP // Actual  measured  time  between  two  1/256  microsteps  derived  from  the  step  input  frequency  in  units  of  1/fCLK.  Measured  value is (2^20)-1 in case of overflow or stand still.  The  TSTEP  related  threshold  uses  a  hysteresis  of  1/16  of  the  compare value to compensate for jitter in the clock or the step  frequency:  (Txxx*15/16)-1  is  the  lower  compare  value  for  each  TSTEP based comparison. This  means,  that  the  lower  switching  velocity  equals  the  calculated setting, but the upper switching velocity is higher as  defined by the hysteresis setting.
	#define TMC22xx_TSTEP_SHIFT                  0 // min.: 0, max.: 1048575, default: 0
	#define TMC22xx_TPWMTHRS_MASK                0x0FFFFF // TPWMTHRS // Sets the upper velocity for stealthChop voltage PWM mode.          For TSTEP = TPWMTHRS, stealthChop PWM mode is enabled, if configured. When  the  velocity  exceeds  the  limit  set  by  TPWMTHRS,  the  driver switches to spreadCycle. 0 = Disabled
	#define TMC22xx_TPWMTHRS_SHIFT               0 // min.: 0, max.: 1048575, default: 0
	#define TMC22xx_VACTUAL_MASK                 0xFFFFFF // VACTUAL // VACTUAL allows moving the motor by UART control. It gives the motor velocity in +-(2^23)-1 [Âµsteps / t] 0: Normal operation. Driver reacts to STEP input. /=0:  Motor  moves  with  the  velocity  given  by  VACTUAL.  Step  pulses  can  be  monitored  via  INDEX  output.  The  motor  direction is controlled by the sign of VACTUAL.
	#define TMC22xx_VACTUAL_SHIFT                0 // min.: -8388608, max.: 8388607, default: 0
	#define TMC22xx_MSCNT_MASK                   0x03FF // MSCNT // Microstep  counter.  Indicates  actual  position in the microstep table for  CUR_A.  CUR_B  uses an  offset  of  256  into  the  table.  Reading  out MSCNT  allows  determination  of  the  motor position within the electrical wave.
	#define TMC22xx_MSCNT_SHIFT                  0 // min.: 0, max.: 1023, default: 0
	#define TMC22xx_CUR_A_MASK                   0x01FF // MSCURACT // (signed) Actual  microstep current for motor phase  A  as  read  from  the internal  sine  wave  table  (not scaled by current setting)
	#define TMC22xx_CUR_A_SHIFT                  0 // min.: -255, max.: 255, default: 0
	#define TMC22xx_CUR_B_MASK                   0x01FF0000 // MSCURACT // (signed) Actual  microstep current for motor phase  B  as  read  from  the internal  sine  wave  table  (not scaled by current setting)
	#define TMC22xx_CUR_B_SHIFT                  16 // min.: -255, max.: 255, default: 0
	#define TMC22xx_TOFF_MASK                    0x0F // CHOPCONF // chopper off time and driver enable, Off time setting controls duration of slow decay phase (Nclk = 12 + 32*Toff),  %0000: Driver disable, all bridges off %0001: 1 â€“ use only with TBL = 2 %0010 ... %1111: 2 â€¦ 15 (Default: OTP, resp. 3 in stealthChop mode)
	#define TMC22xx_TOFF_SHIFT                   0 // min.: 0, max.: 7, default: 0
	#define TMC22xx_HSTRT_MASK                   0x70 // CHOPCONF // hysteresis start value added to HEND, %000 â€¦ %111: Add 1, 2, â€¦, 8 to hysteresis low value HEND (1/512 of this setting adds to current setting) Attention: Effective HEND+HSTRT = 16. Hint: Hysteresis decrement is done each 16 clocks. (Default: OTP, resp. 0 in stealthChop mode)
	#define TMC22xx_HSTRT_SHIFT                  4 // min.: 0, max.: 7, default: 0
	#define TMC22xx_HEND_MASK                    0x0780 // CHOPCONF // hysteresis low value OFFSET sine wave offset, %0000 â€¦ %1111: Hysteresis is -3, -2, -1, 0, 1, â€¦, 12 (1/512 of this setting adds to current setting) This is the hysteresis value which becomes used for the hysteresis chopper. (Default: OTP, resp. 5 in stealthChop mode)
	#define TMC22xx_HEND_SHIFT                   7 // min.: 0, max.: 255, default: 0
	#define TMC22xx_TBL_MASK                     0x018000 // CHOPCONF // blank time select, %00 â€¦ %11: Set comparator blank time to 16, 24, 32 or 40 clocks Hint: %00 or %01 is recommended for most applications (Default: OTP)
	#define TMC22xx_TBL_SHIFT                    15 // min.: 0, max.: 255, default: 0
	#define TMC22xx_VSENSE_MASK                  0x020000 // CHOPCONF // sense resistor voltage based current scaling
	#define TMC22xx_VSENSE_SHIFT                 17 // min.: 0, max.: 1, default: 0
	#define TMC22xx_MRES_MASK                    0x0F000000 // CHOPCONF // MRES micro step resolution,          %0000: Native 256 microstep setting.          %0001 â€¦ %1000: 128, 64, 32, 16, 8, 4, 2, FULLSTEP: Reduced microstep resolution.  The  resolution  gives  the  number  of  microstep  entries  per sine quarter wave. When  choosing  a  lower  microstep  resolution,  the  driver automatically  uses  microstep  positions  which  result  in  a symmetrical wave. Number of microsteps per step pulse = 2^MRES (Selection  by  pins  unless  disabled  by  GCONF. mstep_reg_select)
	#define TMC22xx_MRES_SHIFT                   24 // min.: 0, max.: 255, default: 0
	#define TMC22xx_INTPOL_MASK                  0x10000000 // CHOPCONF // interpolation to 256 microsteps
	#define TMC22xx_INTPOL_SHIFT                 28 // min.: 0, max.: 1, default: 0
	#define TMC22xx_DEDGE_MASK                   0x20000000 // CHOPCONF // enable double edge step pulses
	#define TMC22xx_DEDGE_SHIFT                  29 // min.: 0, max.: 1, default: 0
	#define TMC22xx_DISS2G_MASK                  0x40000000 // CHOPCONF // short to GND protection disable
	#define TMC22xx_DISS2G_SHIFT                 30 // min.: 0, max.: 1, default: 0
	#define TMC22xx_DISS2VS_MASK                 0x80000000 // CHOPCONF // Low side short protection disable
	#define TMC22xx_DISS2VS_SHIFT                31 // min.: 0, max.: 1, default: 0
	#define TMC22xx_OTPW_MASK                    0x01 // DRV_STATUS // overtemperature prewarning flag
	#define TMC22xx_OTPW_SHIFT                   0 // min.: 0, max.: 1, default: 0
	#define TMC22xx_OT_MASK                      0x02 // DRV_STATUS // overtemperature flag
	#define TMC22xx_OT_SHIFT                     1 // min.: 0, max.: 1, default: 0
	#define TMC22xx_S2GA_MASK                    0x04 // DRV_STATUS // short to ground indicator phase A
	#define TMC22xx_S2GA_SHIFT                   2 // min.: 0, max.: 1, default: 0
	#define TMC22xx_S2GB_MASK                    0x08 // DRV_STATUS // short to ground indicator phase B
	#define TMC22xx_S2GB_SHIFT                   3 // min.: 0, max.: 1, default: 0
	#define TMC22xx_S2VSA_MASK                   0x10 // DRV_STATUS // low side short indicator phase A
	#define TMC22xx_S2VSA_SHIFT                  4 // min.: 0, max.: 1, default: 0
	#define TMC22xx_S2VSB_MASK                   0x20 // DRV_STATUS // low side short indicator phase B
	#define TMC22xx_S2VSB_SHIFT                  5 // min.: 0, max.: 1, default: 0
	#define TMC22xx_OLA_MASK                     0x40 // DRV_STATUS // open load indicator phase A
	#define TMC22xx_OLA_SHIFT                    6 // min.: 0, max.: 1, default: 0
	#define TMC22xx_OLB_MASK                     0x80 // DRV_STATUS // open load indicator phase B
	#define TMC22xx_OLB_SHIFT                    7 // min.: 0, max.: 1, default: 0
	#define TMC22xx_T120_MASK                    0x0100 // DRV_STATUS // 120Â°C comparator
	#define TMC22xx_T120_SHIFT                   8 // min.: 0, max.: 1, default: 0
	#define TMC22xx_T143_MASK                    0x0200 // DRV_STATUS // 143Â°C comparator
	#define TMC22xx_T143_SHIFT                   9 // min.: 0, max.: 1, default: 0
	#define TMC22xx_T150_MASK                    0x0400 // DRV_STATUS // 150Â°C comparator
	#define TMC22xx_T150_SHIFT                   10 // min.: 0, max.: 1, default: 0
	#define TMC22xx_T157_MASK                    0x0800 // DRV_STATUS // 157Â°C comparator
	#define TMC22xx_T157_SHIFT                   11 // min.: 0, max.: 1, default: 0
	#define TMC22xx_CS_ACTUAL_MASK               0x1F0000 // DRV_STATUS // actual motor current
	#define TMC22xx_CS_ACTUAL_SHIFT              16 // min.: 0, max.: 31, default: 0
	#define TMC22xx_STEALTH_MASK                 0x40000000 // DRV_STATUS // stealthChop indicator
	#define TMC22xx_STEALTH_SHIFT                30 // min.: 0, max.: 1, default: 0
	#define TMC22xx_STST_MASK                    0x80000000 // DRV_STATUS // standstill indicator
	#define TMC22xx_STST_SHIFT                   31 // min.: 0, max.: 1, default: 0
	#define TMC22xx_PWM_OFS_MASK                 0xFF // PWMCONF // User defined PWM amplitude offset (0-255) related to full motor current (CS_ACTUAL=31) in stand still. (Reset default=36) When  using  automatic  scaling  (pwm_autoscale=1)  the  value  is  used  for  initialization,  only.  The  autoscale  function  starts  with  PWM_SCALE_AUTO=PWM_OFS  and finds  the  required  offset  to  yield  the  target  current  automatically. PWM_OFS  =  0  will  disable  scaling  down  motor  current below  a  motor  specific  lower  measurement  threshold. This  setting  should  only  be  used  under  certain  conditions, i.e.  when the power supply voltage can vary  up  and  down  by  a  factor  of  two  or  more.  It  prevents the  motor  going  out  of  regulation,  but  it  also  prevents  power down below the regulation limit. PWM_OFS > 0 allows automatic scaling to low PWM duty  cycles  even  below  the  lower  regulation  threshold.  This  allows  low  (standstill)  current  settings  based  on  the  actual (hold) current scale (register IHOLD_IRUN). 
	#define TMC22xx_PWM_OFS_SHIFT                0 // min.: 0, max.: 255, default: 0
	#define TMC22xx_PWM_GRAD_MASK                0xFF00 // PWMCONF // Velocity dependent gradient for PWM amplitude:  PWM_GRAD * 256 / TSTEP This  value  is  added  to  PWM_AMPL  to  compensate  for  the velocity-dependent motor back-EMF.  With  automatic  scaling  (pwm_autoscale=1)  the  value  is  used  for  first  initialization,  only.  Set  PWM_GRAD  to  the  application  specific  value  (it  can  be  read  out  from  PWM_GRAD_AUTO)  to  speed  up  the  automatic  tuning  process.  An  approximate  value can be stored to  OTP  by  programming OTP_PWM_GRAD.
	#define TMC22xx_PWM_GRAD_SHIFT               8 // min.: 0, max.: 255, default: 0
	#define TMC22xx_PWM_FREQ_MASK                0x030000 // PWMCONF // %00:   fPWM=2/1024 fCLK          %01:   fPWM=2/683 fCLK          %10:   fPWM=2/512 fCLK          %11:   fPWM=2/410 fCLK
	#define TMC22xx_PWM_FREQ_SHIFT               16 // min.: 0, max.: 3, default: 0
	#define TMC22xx_PWM_AUTOSCALE_MASK           0x040000 // PWMCONF // 
	#define TMC22xx_PWM_AUTOSCALE_SHIFT          18 // min.: 0, max.: 1, default: 0
	#define TMC22xx_PWM_AUTOGRAD_MASK            0x080000 // PWMCONF // 
	#define TMC22xx_PWM_AUTOGRAD_SHIFT           19 // min.: 0, max.: 1, default: 0
	#define TMC22xx_FREEWHEEL_MASK               0x300000 // PWMCONF // Stand still option when motor current setting is zero (I_HOLD=0).  %00:   Normal operation %01:   Freewheeling %10:   Coil shorted using LS drivers %11:   Coil shorted using HS drivers
	#define TMC22xx_FREEWHEEL_SHIFT              20 // min.: 0, max.: 3, default: 0
	#define TMC22xx_PWM_REG_MASK                 0x0F000000 // PWMCONF // User defined  maximum  PWM amplitude  change per  half  wave when using pwm_autoscale=1. (1...15): 1: 0.5 increments (slowest regulation) 2: 1 increment (default with OTP2.1=1) 3: 1.5 increments 4: 2 increments ... 8: 4 increments (default with OTP2.1=0) ...  15: 7.5 increments (fastest regulation)
	#define TMC22xx_PWM_REG_SHIFT                24 // min.: 0, max.: 25, default: 0
	#define TMC22xx_PWM_LIM_MASK                 0xF0000000 // PWMCONF // Limit  for  PWM_SCALE_AUTO  when  switching  back  from  spreadCycle to stealthChop. This value defines  the upper  limit  for  bits  7  to  4  of  the  automatic  current  control  when switching back. It can be set to reduce the current  jerk during mode change back to stealthChop. It does not limit PWM_GRAD or PWM_GRAD_AUTO offset. (Default = 12)
	#define TMC22xx_PWM_LIM_SHIFT                28 // min.: 0, max.: 15, default: 0
	#define TMC22xx_PWM_SCALE_SUM_MASK           0xFF // PWM_SCALE // Actual  PWM  duty  cycle.  This value  is  used  for  scaling  the values  CUR_A  and  CUR_B  read from the sine wave table.
	#define TMC22xx_PWM_SCALE_SUM_SHIFT          0 // min.: 0, max.: 255, default: 0
	#define TMC22xx_PWM_SCALE_AUTO_MASK          0x01FF0000 // PWM_SCALE // 9 Bit signed offset added to the calculated  PWM  duty  cycle.  This is  the  result  of  the  automatic amplitude  regulation  based  on current measurement.
	#define TMC22xx_PWM_SCALE_AUTO_SHIFT         16 // min.: -255, max.: 255, default: 0
	#define TMC22xx_PWM_OFS_AUTO_MASK            0xFF // PWM_AUTO // Automatically  determined  offset value
	#define TMC22xx_PWM_OFS_AUTO_SHIFT           0 // min.: 0, max.: 255, default: 0
	#define TMC22xx_PWM_GRAD_AUTO_MASK           0xFF0000 // PWM_AUTO // Automatically  determined gradient value
	#define TMC22xx_PWM_GRAD_AUTO_SHIFT          16 // min.: 0, max.: 255, default: 0
	/**@}*/

	/** Define to calculate size of array*/
	#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))
	
	/** @name software UART pins	 
	*	Defines to map pins of the software UART for the driver chip
	*/
	///@{
	#define UARTTXPORT PORTC
	#define UARTTXDDR DDRC
	#define UARTTXPIN 3
	#define UARTRXPORT PORTC
	#define UARTRXDDR DDRC
	#define UARTRXPIN 2
	///@}

	#define NORMALDIRECTION 0
	#define INVERSEDIRECTION 1

	// 2us delay (30 nops @ 62.5ns = 1.875us + C overhead ~ 2us) 500k baud
	/** */
	#define UARTCLKDELAY() 	__asm__ volatile ( 	"nop \n\t" "nop \n\t" "nop \n\t" "nop \n\t" "nop \n\t" "nop \n\t" "nop \n\t" "nop \n\t" "nop \n\t" "nop \n\t" "nop \n\t" "nop \n\t" )

/**
 * @brief      Prototype of class for accessing all features of the TMC22xx in
 *             a single object.
 *
 *             This class enables the user of the library to access the implemented features
 *             of the TMC22xx driver, by use of a single object.
 */
class Tmc22xx
{
public:
	/**
	* @brief      Constructor
	*
	*             This is the constructor of the TMC22xx class.
	*/
	Tmc22xx(void);

	/**
	* @brief      Initializes the different parts of the TMC22xx object
	*
	*             This function initializes the different parts of the TMC22xx
	*             object, and is called in the setup() function of the
	*             uStepper S-lite object. This function is needed to setup basic registers of the TMC22xx.
	*
	*/	
	void setup(void);

	/**
	* @brief      Disable the stepper motor driver - TMC22xx.
	*
	*             This function lets the user disable the stepper driver.
	*
	*/
	void disableDriver(void);

	/**
	* @brief      Enable the stepper motor driver - TMC22xx.
	*
	*             This function lets the user enable the stepper driver.
	*
	*/
	void enableDriver(void);

	/**
	* @brief      Change run and hold current settings of the stepper motor driver - TMC22xx.
	*
	*             This function lets the user manipulate both run and hold current settings.
	*			  Arguments accept natural number from zero (0) to hundred (100).
	*			  Calls setCurrent and setHoldCurrent.
	*
	* @param      runPercent     -	Run current in percentage of max current i.e. from 0 to 100.
	* @param      holdPercent    -	Hold current in percentage of max current i.e. from 0 to 100.
	*
	*/
	void setCurrent(uint8_t runPercent, uint8_t holdPercent);

	/**
	* @brief      Change hold current setting of the stepper motor driver - TMC22xx.
	*
	*             This function lets the user manipulate hold current.
	*			  Arguments accept natural number from zero (0) to hundred (100).
	*
	* @param      holdPercent    -	Hold current in percentage of max current i.e. from 0 to 100.
	*
	*/
	void setHoldCurrent(uint8_t holdPercent);

	/**
	* @brief      Change run current setting of the stepper motor driver - TMC22xx.
	*
	*             This function lets the user manipulate run current.
	*			  Arguments accept natural number from zero (0) to hundred (100).
	*
	* @param      runPercent     -	Run current in percentage of max current i.e. from 0 to 100.
	*
	*/	
	void setRunCurrent(uint8_t runPercent);

	/**
	* @brief      Set motor velocity in RPM.
	*
	*             This function lets the user command a run speed in RPM for open loop speed control.
	*
	* @param      RPM     -	Desired speed of the motor in RPM.
	*
	*/
	void setVelocity(float RPM);

	/**
	* @brief      Invert motor direction.
	*
	*             This function lets the user invert the motor direction - i.e. changing CW to CCW and vise versa.
	*
	* @param      normal     -	Can be set to either INVERSEDIRECTION or NORMALDIRECTION.
	*
	*/	
	void invertDirection(bool normal = INVERSEDIRECTION);
	float getRunCurrent(void);
	float getHoldCurrent(void);
protected:
	/** This variable holds the commanded run current
	*/	
	uint8_t runCurrent;

	/** This variable holds the commanded hold current
	*/	
	uint8_t holdCurrent;

	void writeRegister(uint8_t address, int32_t value);
	void readRegister(uint8_t address, int32_t *value);
	uint8_t calcCRC(uint8_t datagram[], uint8_t len);
	void uartInit(void);
	void uartSendByte(uint8_t value);
	bool uartReceivePacket(uint8_t *packet __attribute__((unused)), uint8_t size __attribute__((unused)));
		
};

#endif