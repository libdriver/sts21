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
 * @file      driver_sts21_read_test.c
 * @brief     driver sts21 read test source file
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

#include "driver_sts21_read_test.h"

static sts21_handle_t gs_handle;        /**< sts21 handle */

/**
 * @brief     read test
 * @param[in] times test times
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t sts21_read_test(uint32_t times)
{
    uint8_t res;
    uint32_t i;
    sts21_info_t info;
    
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
    
    /* sts21 info */
    res = sts21_info(&info);
    if (res != 0)
    {
        sts21_interface_debug_print("sts21: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print chip information */
        sts21_interface_debug_print("sts21: chip is %s.\n", info.chip_name);
        sts21_interface_debug_print("sts21: manufacturer is %s.\n", info.manufacturer_name);
        sts21_interface_debug_print("sts21: interface is %s.\n", info.interface);
        sts21_interface_debug_print("sts21: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        sts21_interface_debug_print("sts21: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        sts21_interface_debug_print("sts21: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        sts21_interface_debug_print("sts21: max current is %0.2fmA.\n", info.max_current_ma);
        sts21_interface_debug_print("sts21: max temperature is %0.1fC.\n", info.temperature_max);
        sts21_interface_debug_print("sts21: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* start read test */
    sts21_interface_debug_print("sts21: start read test.\n");
    
    /* sts21 init */
    res = sts21_init(&gs_handle);
    if (res != 0)
    {
        sts21_interface_debug_print("sts21: init failed.\n");
       
        return 1;
    }
    
    /* disable heater */
    res = sts21_set_heater(&gs_handle, STS21_BOOL_FALSE);
    if (res != 0)
    {
        sts21_interface_debug_print("sts21: set heater failed.\n");
        (void)sts21_deinit(&gs_handle);
        
        return 1;
    }
    
    /* disable otp reload */
    res = sts21_set_disable_otp_reload(&gs_handle, STS21_BOOL_TRUE);
    if (res != 0)
    {
        sts21_interface_debug_print("sts21: set disable otp reload failed.\n");
        (void)sts21_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set hold master mode */
    res = sts21_set_mode(&gs_handle, STS21_MODE_HOLD_MASTER);
    if (res != 0)
    {
        sts21_interface_debug_print("sts21: set mode failed.\n");
        (void)sts21_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    sts21_interface_debug_print("sts21: set hold master mode.\n");
    
    /* set resolution t 14bit */
    res = sts21_set_resolution(&gs_handle, STS21_RESOLUTION_T_14BIT);
    if (res != 0)
    {
        sts21_interface_debug_print("sts21: set resolution failed.\n");
        (void)sts21_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    sts21_interface_debug_print("sts21: set resolution t 14bit.\n");
    
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        
        res = sts21_read(&gs_handle, (uint16_t *)&temperature_raw, (float *)&temperature_s);
        if (res != 0)
        {
            sts21_interface_debug_print("sts21: read failed.\n");
            (void)sts21_deinit(&gs_handle);
            
            return 1;
        }
        sts21_interface_debug_print("sts21: temperature is %0.2fC.\n", temperature_s);
    
        /* wait 1000 ms */
        sts21_interface_delay_ms(1000);
    }
    
    /* set resolution t 12bit */
    res = sts21_set_resolution(&gs_handle, STS21_RESOLUTION_T_12BIT);
    if (res != 0)
    {
        sts21_interface_debug_print("sts21: set resolution failed.\n");
        (void)sts21_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    sts21_interface_debug_print("sts21: set resolution t 12bit.\n");
    
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        
        res = sts21_read(&gs_handle, (uint16_t *)&temperature_raw, (float *)&temperature_s);
        if (res != 0)
        {
            sts21_interface_debug_print("sts21: read failed.\n");
            (void)sts21_deinit(&gs_handle);
            
            return 1;
        }
        sts21_interface_debug_print("sts21: temperature is %0.2fC.\n", temperature_s);
    
        /* wait 1000 ms */
        sts21_interface_delay_ms(1000);
    }
    
    /* set resolution t 13bit */
    res = sts21_set_resolution(&gs_handle, STS21_RESOLUTION_T_13BIT);
    if (res != 0)
    {
        sts21_interface_debug_print("sts21: set resolution failed.\n");
        (void)sts21_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    sts21_interface_debug_print("sts21: set resolution t 13bit.\n");
    
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        
        res = sts21_read(&gs_handle, (uint16_t *)&temperature_raw, (float *)&temperature_s);
        if (res != 0)
        {
            sts21_interface_debug_print("sts21: read failed.\n");
            (void)sts21_deinit(&gs_handle);
            
            return 1;
        }
        sts21_interface_debug_print("sts21: temperature is %0.2fC.\n", temperature_s);
    
        /* wait 1000 ms */
        sts21_interface_delay_ms(1000);
    }
    
    /* set resolution t 11bit */
    res = sts21_set_resolution(&gs_handle, STS21_RESOLUTION_T_11BIT);
    if (res != 0)
    {
        sts21_interface_debug_print("sts21: set resolution failed.\n");
        (void)sts21_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    sts21_interface_debug_print("sts21: set resolution t 11bit.\n");
    
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        
        res = sts21_read(&gs_handle, (uint16_t *)&temperature_raw, (float *)&temperature_s);
        if (res != 0)
        {
            sts21_interface_debug_print("sts21: read failed.\n");
            (void)sts21_deinit(&gs_handle);
            
            return 1;
        }
        sts21_interface_debug_print("sts21: temperature is %0.2fC.\n", temperature_s);
    
        /* wait 1000 ms */
        sts21_interface_delay_ms(1000);
    }
    
    /* set no hold master mode */
    res = sts21_set_mode(&gs_handle, STS21_MODE_NO_HOLD_MASTER);
    if (res != 0)
    {
        sts21_interface_debug_print("sts21: set mode failed.\n");
        (void)sts21_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    sts21_interface_debug_print("sts21: set no hold master mode.\n");
    
    /* set resolution t 14bit */
    res = sts21_set_resolution(&gs_handle, STS21_RESOLUTION_T_14BIT);
    if (res != 0)
    {
        sts21_interface_debug_print("sts21: set resolution failed.\n");
        (void)sts21_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    sts21_interface_debug_print("sts21: set resolution t 14bit.\n");
    
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        
        res = sts21_read(&gs_handle, (uint16_t *)&temperature_raw, (float *)&temperature_s);
        if (res != 0)
        {
            sts21_interface_debug_print("sts21: read failed.\n");
            (void)sts21_deinit(&gs_handle);
            
            return 1;
        }
        sts21_interface_debug_print("sts21: temperature is %0.2fC.\n", temperature_s);
    
        /* wait 1000 ms */
        sts21_interface_delay_ms(1000);
    }
    
    /* set resolution t 12bit */
    res = sts21_set_resolution(&gs_handle, STS21_RESOLUTION_T_12BIT);
    if (res != 0)
    {
        sts21_interface_debug_print("sts21: set resolution failed.\n");
        (void)sts21_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    sts21_interface_debug_print("sts21: set resolution t 12bit.\n");
    
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        
        res = sts21_read(&gs_handle, (uint16_t *)&temperature_raw, (float *)&temperature_s);
        if (res != 0)
        {
            sts21_interface_debug_print("sts21: read failed.\n");
            (void)sts21_deinit(&gs_handle);
            
            return 1;
        }
        sts21_interface_debug_print("sts21: temperature is %0.2fC.\n", temperature_s);
    
        /* wait 1000 ms */
        sts21_interface_delay_ms(1000);
    }
    
    /* set resolution t 13bit */
    res = sts21_set_resolution(&gs_handle, STS21_RESOLUTION_T_13BIT);
    if (res != 0)
    {
        sts21_interface_debug_print("sts21: set resolution failed.\n");
        (void)sts21_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    sts21_interface_debug_print("sts21: set resolution t 13bit.\n");
    
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        
        res = sts21_read(&gs_handle, (uint16_t *)&temperature_raw, (float *)&temperature_s);
        if (res != 0)
        {
            sts21_interface_debug_print("sts21: read failed.\n");
            (void)sts21_deinit(&gs_handle);
            
            return 1;
        }
        sts21_interface_debug_print("sts21: temperature is %0.2fC.\n", temperature_s);
    
        /* wait 1000 ms */
        sts21_interface_delay_ms(1000);
    }
    
    /* set resolution t 11bit */
    res = sts21_set_resolution(&gs_handle, STS21_RESOLUTION_T_11BIT);
    if (res != 0)
    {
        sts21_interface_debug_print("sts21: set resolution failed.\n");
        (void)sts21_deinit(&gs_handle);
        
        return 1;
    }
    
    /* output */
    sts21_interface_debug_print("sts21: set resolution t 11bit.\n");
    
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        
        res = sts21_read(&gs_handle, (uint16_t *)&temperature_raw, (float *)&temperature_s);
        if (res != 0)
        {
            sts21_interface_debug_print("sts21: read failed.\n");
            (void)sts21_deinit(&gs_handle);
            
            return 1;
        }
        sts21_interface_debug_print("sts21: temperature is %0.2fC.\n", temperature_s);
    
        /* wait 1000 ms */
        sts21_interface_delay_ms(1000);
    }
    
    /* finish read test */
    sts21_interface_debug_print("sts21: finish read test.\n");
    (void)sts21_deinit(&gs_handle);

    return 0;
}
