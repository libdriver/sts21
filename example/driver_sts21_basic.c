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
 * @file      driver_sts21_basic.c
 * @brief     driver sts21 basic source file
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

#include "driver_sts21_basic.h"

static sts21_handle_t gs_handle;        /**< sts21 handle */

/**
 * @brief  basic example init
 * @return status code
 *         - 0 success
 *         - 1 init failed
 * @note   none
 */
uint8_t sts21_basic_init(void)
{
    uint8_t res;
    
    /* link functions */
    DRIVER_STS21_LINK_INIT(&gs_handle, sts21_handle_t);
    DRIVER_STS21_LINK_IIC_INIT(&gs_handle, sts21_interface_iic_init);
    DRIVER_STS21_LINK_IIC_DEINIT(&gs_handle, sts21_interface_iic_deinit);
    DRIVER_STS21_LINK_IIC_READ_COMMAND(&gs_handle, sts21_interface_iic_read_command);
    DRIVER_STS21_LINK_IIC_READ(&gs_handle, sts21_interface_iic_read);
    DRIVER_STS21_LINK_IIC_READ_WITH_WAIT(&gs_handle, sts21_interface_iic_read_with_wait);
    DRIVER_STS21_LINK_IIC_READ_ADDRESS16(&gs_handle, sts21_interface_iic_read_address16);
    DRIVER_STS21_LINK_IIC_WRITE_COMMAND(&gs_handle, sts21_interface_iic_write_command);
    DRIVER_STS21_LINK_IIC_WRITE(&gs_handle, sts21_interface_iic_write);
    DRIVER_STS21_LINK_DELAY_MS(&gs_handle, sts21_interface_delay_ms);
    DRIVER_STS21_LINK_DEBUG_PRINT(&gs_handle, sts21_interface_debug_print);

    /* sts21 init */
    res = sts21_init(&gs_handle);
    if (res != 0)
    {
        sts21_interface_debug_print("sts21: init failed.\n");
        
        return 1;
    }  
    
    /* set default heater */
    res = sts21_set_heater(&gs_handle, STS21_BASIC_DEFAULT_HEATER);
    if (res != 0)
    {
        sts21_interface_debug_print("sts21: set heater failed.\n");
        (void)sts21_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default disable otp reload */
    res = sts21_set_disable_otp_reload(&gs_handle, STS21_BASIC_DEFAULT_DISABLE_OTP_RELOAD);
    if (res != 0)
    {
        sts21_interface_debug_print("sts21: set disable otp reload failed.\n");
        (void)sts21_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default mode */
    res = sts21_set_mode(&gs_handle, STS21_BASIC_DEFAULT_MODE);
    if (res != 0)
    {
        sts21_interface_debug_print("sts21: set mode failed.\n");
        (void)sts21_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default resolution */
    res = sts21_set_resolution(&gs_handle, STS21_BASIC_DEFAULT_RESOLUTION);
    if (res != 0)
    {
        sts21_interface_debug_print("sts21: set resolution failed.\n");
        (void)sts21_deinit(&gs_handle);
        
        return 1;
    }
    
    return 0;
}

/**
 * @brief      basic example read
 * @param[out] *temperature pointer to a converted temperature buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t sts21_basic_read(float *temperature)
{
    uint16_t temperature_raw;
   
    /* read data */
    if (sts21_read(&gs_handle, (uint16_t *)&temperature_raw, temperature) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t sts21_basic_deinit(void)
{
    /* close sts21 */
    if (sts21_deinit(&gs_handle) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief      basic example get serial number
 * @param[out] *sn pointer to a serial number buffer
 * @return     status code
 *             - 0 success
 *             - 1 get failed
 * @note       none
 */
uint8_t sts21_basic_get_serial_number(uint8_t sn[8])
{
    /* get serial number */
    if (sts21_get_serial_number(&gs_handle, sn) != 0)
    {
        return 1;
    }
    
    return 0;
}
