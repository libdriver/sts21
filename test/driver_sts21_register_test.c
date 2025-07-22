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
 * @file      driver_sts21_register_test.c
 * @brief     driver sts21 register test source file
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
 
#include "driver_sts21_register_test.h"

static sts21_handle_t gs_handle;        /**< sts21 handle */

/**
 * @brief  register test
 * @return status code
 *         - 0 success
 *         - 1 test failed
 * @note   none
 */
uint8_t sts21_register_test(void)
{
    uint8_t res;
    uint8_t sn[8];
    sts21_status_t status;
    sts21_bool_t enable;
    sts21_info_t info;
    sts21_mode_t mode;
    sts21_resolution_t resolution;
    
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
    
    /* start register test */
    sts21_interface_debug_print("sts21: start register test.\n");
    
    /* sts21 init */
    res = sts21_init(&gs_handle);
    if (res != 0)
    {
        sts21_interface_debug_print("sts21: init failed.\n");
       
        return 1;
    }
    
    /* sts21_set_mode/sts21_get_mode test */
    sts21_interface_debug_print("sts21: sts21_set_mode/sts21_get_mode test.\n");
    
    /* set hold master mode */
    res = sts21_set_mode(&gs_handle, STS21_MODE_HOLD_MASTER);
    if (res != 0)
    {
        sts21_interface_debug_print("sts21: set mode failed.\n");
        (void)sts21_deinit(&gs_handle);
        
        return 1;
    }
    sts21_interface_debug_print("sts21: set hold master mode.\n");
    res = sts21_get_mode(&gs_handle, &mode);
    if (res != 0)
    {
        sts21_interface_debug_print("sts21: get mode failed.\n");
        (void)sts21_deinit(&gs_handle);
        
        return 1;
    }
    sts21_interface_debug_print("sts21: check mode %s.\n", (mode == STS21_MODE_HOLD_MASTER) ? "ok" : "error");
    
    /* set no hold master mode */
    res = sts21_set_mode(&gs_handle, STS21_MODE_NO_HOLD_MASTER);
    if (res != 0)
    {
        sts21_interface_debug_print("sts21: set mode failed.\n");
        (void)sts21_deinit(&gs_handle);
        
        return 1;
    }
    sts21_interface_debug_print("sts21: set no hold master mode.\n");
    res = sts21_get_mode(&gs_handle, &mode);
    if (res != 0)
    {
        sts21_interface_debug_print("sts21: get mode failed.\n");
        (void)sts21_deinit(&gs_handle);
        
        return 1;
    }
    sts21_interface_debug_print("sts21: check mode %s.\n", (mode == STS21_MODE_NO_HOLD_MASTER) ? "ok" : "error");
    
    /* sts21_set_resolution/sts21_get_resolution test */
    sts21_interface_debug_print("sts21: sts21_set_resolution/sts21_get_resolution test.\n");
    
    /* set resolution t 14bit */
    res = sts21_set_resolution(&gs_handle, STS21_RESOLUTION_T_14BIT);
    if (res != 0)
    {
        sts21_interface_debug_print("sts21: set resolution failed.\n");
        (void)sts21_deinit(&gs_handle);
        
        return 1;
    }
    sts21_interface_debug_print("sts21: set resolution t 14bit.\n");
    res = sts21_get_resolution(&gs_handle, &resolution);
    if (res != 0)
    {
        sts21_interface_debug_print("sts21: get resolution failed.\n");
        (void)sts21_deinit(&gs_handle);
        
        return 1;
    }
    sts21_interface_debug_print("sts21: check resolution %s.\n", (resolution == STS21_RESOLUTION_T_14BIT) ? "ok" : "error");
    
    /* set resolution t 12bit */
    res = sts21_set_resolution(&gs_handle, STS21_RESOLUTION_T_12BIT);
    if (res != 0)
    {
        sts21_interface_debug_print("sts21: set resolution failed.\n");
        (void)sts21_deinit(&gs_handle);
        
        return 1;
    }
    sts21_interface_debug_print("sts21: set resolution t 12bit.\n");
    res = sts21_get_resolution(&gs_handle, &resolution);
    if (res != 0)
    {
        sts21_interface_debug_print("sts21: get resolution failed.\n");
        (void)sts21_deinit(&gs_handle);
        
        return 1;
    }
    sts21_interface_debug_print("sts21: check resolution %s.\n", (resolution == STS21_RESOLUTION_T_12BIT) ? "ok" : "error");
    
    /* set resolution t 13bit */
    res = sts21_set_resolution(&gs_handle, STS21_RESOLUTION_T_13BIT);
    if (res != 0)
    {
        sts21_interface_debug_print("sts21: set resolution failed.\n");
        (void)sts21_deinit(&gs_handle);
        
        return 1;
    }
    sts21_interface_debug_print("sts21: set resolution t 13bit.\n");
    res = sts21_get_resolution(&gs_handle, &resolution);
    if (res != 0)
    {
        sts21_interface_debug_print("sts21: get resolution failed.\n");
        (void)sts21_deinit(&gs_handle);
        
        return 1;
    }
    sts21_interface_debug_print("sts21: check resolution %s.\n", (resolution == STS21_RESOLUTION_T_13BIT) ? "ok" : "error");
    
    /* set resolution t 11bit */
    res = sts21_set_resolution(&gs_handle, STS21_RESOLUTION_T_11BIT);
    if (res != 0)
    {
        sts21_interface_debug_print("sts21: set resolution failed.\n");
        (void)sts21_deinit(&gs_handle);
        
        return 1;
    }
    sts21_interface_debug_print("sts21: set resolution t 11bit.\n");
    res = sts21_get_resolution(&gs_handle, &resolution);
    if (res != 0)
    {
        sts21_interface_debug_print("sts21: get resolution failed.\n");
        (void)sts21_deinit(&gs_handle);
        
        return 1;
    }
    sts21_interface_debug_print("sts21: check resolution %s.\n", (resolution == STS21_RESOLUTION_T_11BIT) ? "ok" : "error");
    
    /* sts21_set_heater/sts21_get_heater test */
    sts21_interface_debug_print("sts21: sts21_set_heater/sts21_get_heater test.\n");
    
    /* enable heater */
    res = sts21_set_heater(&gs_handle, STS21_BOOL_TRUE);
    if (res != 0)
    {
        sts21_interface_debug_print("sts21: set heater failed.\n");
        (void)sts21_deinit(&gs_handle);
        
        return 1;
    }
    sts21_interface_debug_print("sts21: enable heater.\n");
    res = sts21_get_heater(&gs_handle, &enable);
    if (res != 0)
    {
        sts21_interface_debug_print("sts21: get heater failed.\n");
        (void)sts21_deinit(&gs_handle);
        
        return 1;
    }
    sts21_interface_debug_print("sts21: check heater %s.\n", (enable == STS21_BOOL_TRUE) ? "ok" : "error");
    
    /* disable heater */
    res = sts21_set_heater(&gs_handle, STS21_BOOL_FALSE);
    if (res != 0)
    {
        sts21_interface_debug_print("sts21: set heater failed.\n");
        (void)sts21_deinit(&gs_handle);
        
        return 1;
    }
    sts21_interface_debug_print("sts21: disable heater.\n");
    res = sts21_get_heater(&gs_handle, &enable);
    if (res != 0)
    {
        sts21_interface_debug_print("sts21: get heater failed.\n");
        (void)sts21_deinit(&gs_handle);
        
        return 1;
    }
    sts21_interface_debug_print("sts21: check heater %s.\n", (enable == STS21_BOOL_FALSE) ? "ok" : "error");
    
    /* sts21_set_disable_otp_reload/sts21_get_disable_otp_reload test */
    sts21_interface_debug_print("sts21: sts21_set_disable_otp_reload/sts21_get_disable_otp_reload test.\n");
    
    /* enable disable otp reload */
    res = sts21_set_disable_otp_reload(&gs_handle, STS21_BOOL_TRUE);
    if (res != 0)
    {
        sts21_interface_debug_print("sts21: set disable otp reload failed.\n");
        (void)sts21_deinit(&gs_handle);
        
        return 1;
    }
    sts21_interface_debug_print("sts21: enable disable otp reload.\n");
    res = sts21_get_disable_otp_reload(&gs_handle, &enable);
    if (res != 0)
    {
        sts21_interface_debug_print("sts21: get disable otp reload failed.\n");
        (void)sts21_deinit(&gs_handle);
        
        return 1;
    }
    sts21_interface_debug_print("sts21: check disable otp reload %s.\n", (enable == STS21_BOOL_TRUE) ? "ok" : "error");
    
    /* disable disable otp reload */
    res = sts21_set_disable_otp_reload(&gs_handle, STS21_BOOL_FALSE);
    if (res != 0)
    {
        sts21_interface_debug_print("sts21: set disable otp reload failed.\n");
        (void)sts21_deinit(&gs_handle);
        
        return 1;
    }
    sts21_interface_debug_print("sts21: disable disable otp reload.\n");
    res = sts21_get_disable_otp_reload(&gs_handle, &enable);
    if (res != 0)
    {
        sts21_interface_debug_print("sts21: get disable otp reload failed.\n");
        (void)sts21_deinit(&gs_handle);
        
        return 1;
    }
    sts21_interface_debug_print("sts21: check disable otp reload %s.\n", (enable == STS21_BOOL_FALSE) ? "ok" : "error");
    
    /* sts21_get_status test */
    sts21_interface_debug_print("sts21: sts21_get_status test.\n");
    
    /* get status */
    res = sts21_get_status(&gs_handle, &status);
    if (res != 0)
    {
        sts21_interface_debug_print("sts21: get status failed.\n");
        (void)sts21_deinit(&gs_handle);
        
        return 1;
    }
    sts21_interface_debug_print("sts21: check vdd 2.25v status %s.\n", (status == SHT35_STATUS_VDD_OVER_2P25V) ? "over" : "less");
    
    /* sts21_get_serial_number test */
    sts21_interface_debug_print("sts21: sts21_get_serial_number test.\n");
    
    /* get serial number */
    res = sts21_get_serial_number(&gs_handle, sn);
    if (res != 0)
    {
        sts21_interface_debug_print("sts21: get serial number failed.\n");
        (void)sts21_deinit(&gs_handle);
        
        return 1;
    }
    sts21_interface_debug_print("sts21: sn 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X.\n", 
                                sn[0], sn[1], sn[2], sn[3], sn[4], sn[5], sn[6], sn[7]);
    
    /* sts21_soft_reset test */
    sts21_interface_debug_print("sts21: sts21_soft_reset test.\n");
    
    /* soft reset */
    res = sts21_soft_reset(&gs_handle);
    if (res != 0)
    {
        sts21_interface_debug_print("sts21: soft reset failed.\n");
        (void)sts21_deinit(&gs_handle);
        
        return 1;
    }
    sts21_interface_debug_print("sts21: soft reset.\n");
    
    /* finish register test */
    sts21_interface_debug_print("sts21: finish register test.\n");
    (void)sts21_deinit(&gs_handle);
    
    return 0;
}
