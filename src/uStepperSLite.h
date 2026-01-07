/**
 * @file uStepperSLite.h
 * @brief Backward-compatibility shim for legacy uStepper S-Lite sketches.
 *
 * This header exists solely to maintain source compatibility with projects that
 * previously included the S-Lite header. It forwards to uStepper8b.h and does
 * not introduce additional symbols or behavior.
 *
 * Usage:
 * - Legacy projects may continue to include this header unchanged.
 * - New projects should include "uStepper8b.h" directly.
 *
 * Notes:
 * - Targets TMC22xx-based drivers (TMC2208/TMC2209) via the uStepper 8b library.
 * - Protected by an include guard to prevent multiple inclusion.
 *
 * Warranty:
 * - Provided "AS IS" without warranty of any kind. Use at your own risk.
 *
 * @see uStepper8b.h
 */
/********************************************************************************************
 * File:        /uStepperSLite.h
 * Project:     uStepper 8b (compatible with uStepper S-lite)
 * Description: Part of the uStepper 8b library. TMC22xx (TMC2208/TMC2209) compatible.
 * Author:      Thomas Olsen
 * Copyright:   (C) 2020-2026 uStepper ApS
 * License:     Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International
 * Warranty:    Provided "AS IS" without warranty of any kind. Use at your own risk.
 * Website:     https://www.ustepper.com
 * Contact:     administration@ustepper.com
 ********************************************************************************************/


#ifndef _USTEPPER_S_LITE_H_
#define _USTEPPER_S_LITE_H_

#include "uStepper8b.h"

#endif