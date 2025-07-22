/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_sts21_basic.h
 * @brief     driver sts21 basic header file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2025-07-30
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2025/07/30  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#ifndef DRIVER_STS21_BASIC_H
#define DRIVER_STS21_BASIC_H

#include "driver_sts21_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup sts21_example_driver sts21 example driver function
 * @brief    sts21 example driver modules
 * @ingroup  sts21_driver
 * @{
 */

/**
 * @brief sts21 basic example default definition
 */
#define STS21_BASIC_DEFAULT_MODE                      STS21_MODE_NO_HOLD_MASTER        /**< no hold mode */
#define STS21_BASIC_DEFAULT_RESOLUTION                STS21_RESOLUTION_T_14BIT         /**< resolution t 14bit */
#define STS21_BASIC_DEFAULT_HEATER                    STS21_BOOL_FALSE                 /**< disable heater */
#define STS21_BASIC_DEFAULT_DISABLE_OTP_RELOAD        STS21_BOOL_TRUE                  /**< disable otp reload */

/**
 * @brief  basic example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t sts21_basic_init(void);

/**
 * @brief      basic example read
 * @param[out] *temperature pointer to a converted temperature buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t sts21_basic_read(float *temperature);

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t sts21_basic_deinit(void);

/**
 * @brief      basic example get serial number
 * @param[out] *sn pointer to a serial number buffer
 * @return     status code
 *             - 0 success
 *             - 1 get failed
 * @note       none
 */
uint8_t sts21_basic_get_serial_number(uint8_t sn[8]);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
