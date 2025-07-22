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
 * @file      driver_sts21.h
 * @brief     driver sts21 header file
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

#ifndef DRIVER_STS21_H
#define DRIVER_STS21_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup sts21_driver sts21 driver function
 * @brief    sts21 driver modules
 * @{
 */

/**
 * @addtogroup sts21_base_driver
 * @{
 */

/**
 * @brief sts21 bool enumeration definition
 */
typedef enum
{
    STS21_BOOL_FALSE = 0x00,        /**< disable */
    STS21_BOOL_TRUE  = 0x01,        /**< enable */
} sts21_bool_t;

/**
 * @brief sts21 status enumeration definition
 */
typedef enum  
{
    SHT35_STATUS_VDD_OVER_2P25V = 0,        /**< vdd > 2.25v */
    SHT35_STATUS_VDD_LESS_2P25V = 1,        /**< vdd < 2.25v */
} sts21_status_t;

/**
 * @brief sts21 mode enumeration definition
 */
typedef enum
{
    STS21_MODE_HOLD_MASTER    = 0x00,        /**< hold master mode */
    STS21_MODE_NO_HOLD_MASTER = 0x01,        /**< no hold master mode */
} sts21_mode_t;

/**
 * @brief sts21 resolution enumeration definition
 */
typedef enum  
{
    STS21_RESOLUTION_T_14BIT = 0x00,        /**< resolution t 14bit */
    STS21_RESOLUTION_T_12BIT  = 0x01,        /**< resolution t 12bit */
    STS21_RESOLUTION_T_13BIT = 0x02,        /**< resolution t 13bit */
    STS21_RESOLUTION_T_11BIT = 0x03,        /**< resolution t 11bit */
} sts21_resolution_t;

/**
 * @brief sts21 handle structure definition
 */
typedef struct sts21_handle_s
{
    uint8_t (*iic_init)(void);                                                                     /**< point to an iic_init function address */
    uint8_t (*iic_deinit)(void);                                                                   /**< point to an iic_deinit function address */
    uint8_t (*iic_write_cmd)(uint8_t addr, uint8_t *buf, uint16_t len);                            /**< point to an iic_write_cmd function address */
    uint8_t (*iic_write)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);                   /**< point to an iic_write function address */
    uint8_t (*iic_read_cmd)(uint8_t addr, uint8_t *buf, uint16_t len);                             /**< point to an iic_read_cmd function address */
    uint8_t (*iic_read)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);                    /**< point to an iic_read function address */
    uint8_t (*iic_read_with_wait)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);          /**< point to an iic_read_with_wait function address */
    uint8_t (*iic_read_address16)(uint8_t addr, uint16_t reg, uint8_t *buf, uint16_t len);         /**< point to an iic_read_address16 function address */
    void (*delay_ms)(uint32_t ms);                                                                 /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);                                               /**< point to a debug_print function address */
    uint8_t resolution;                                                                            /**< resolution */
    uint8_t mode;                                                                                  /**< mode */
    uint8_t inited;                                                                                /**< inited flag */
} sts21_handle_t;

/**
 * @brief sts21 information structure definition
 */
typedef struct sts21_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} sts21_info_t;

/**
 * @}
 */

/**
 * @defgroup sts21_link_driver sts21 link driver function
 * @brief    sts21 link driver modules
 * @ingroup  sts21_driver
 * @{
 */

/**
 * @brief     initialize sts21_handle_t structure
 * @param[in] HANDLE pointer to a sts21 handle structure
 * @param[in] STRUCTURE sts21_handle_t
 * @note      none
 */
#define DRIVER_STS21_LINK_INIT(HANDLE, STRUCTURE)            memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link iic_init function
 * @param[in] HANDLE pointer to a sts21 handle structure
 * @param[in] FUC pointer to an iic_init function address
 * @note      none
 */
#define DRIVER_STS21_LINK_IIC_INIT(HANDLE, FUC)              (HANDLE)->iic_init = FUC

/**
 * @brief     link iic_deinit function
 * @param[in] HANDLE pointer to a sts21 handle structure
 * @param[in] FUC pointer to an iic_deinit function address
 * @note      none
 */
#define DRIVER_STS21_LINK_IIC_DEINIT(HANDLE, FUC)            (HANDLE)->iic_deinit = FUC

/**
 * @brief     link iic_write_cmd function
 * @param[in] HANDLE pointer to a sts21 handle structure
 * @param[in] FUC pointer to an iic_write_cmd function address
 * @note      none
 */
#define DRIVER_STS21_LINK_IIC_WRITE_COMMAND(HANDLE, FUC)     (HANDLE)->iic_write_cmd = FUC

/**
 * @brief     link iic_write function
 * @param[in] HANDLE pointer to a sts21 handle structure
 * @param[in] FUC pointer to an iic_write function address
 * @note      none
 */
#define DRIVER_STS21_LINK_IIC_WRITE(HANDLE, FUC)             (HANDLE)->iic_write = FUC

/**
 * @brief     link iic_read_cmd function
 * @param[in] HANDLE pointer to a sts21 handle structure
 * @param[in] FUC pointer to an iic_read_cmd function address
 * @note      none
 */
#define DRIVER_STS21_LINK_IIC_READ_COMMAND(HANDLE, FUC)      (HANDLE)->iic_read_cmd = FUC

/**
 * @brief     link iic_read function
 * @param[in] HANDLE pointer to a sts21 handle structure
 * @param[in] FUC pointer to an iic_read function address
 * @note      none
 */
#define DRIVER_STS21_LINK_IIC_READ(HANDLE, FUC)              (HANDLE)->iic_read = FUC

/**
 * @brief     link iic_read_with_wait function
 * @param[in] HANDLE pointer to a sts21 handle structure
 * @param[in] FUC pointer to an iic_read_with_wait function address
 * @note      none
 */
#define DRIVER_STS21_LINK_IIC_READ_WITH_WAIT(HANDLE, FUC)    (HANDLE)->iic_read_with_wait = FUC

/**
 * @brief     link iic_read_address16 function
 * @param[in] HANDLE pointer to a sts21 handle structure
 * @param[in] FUC pointer to an iic_read_address16 function address
 * @note      none
 */
#define DRIVER_STS21_LINK_IIC_READ_ADDRESS16(HANDLE, FUC)    (HANDLE)->iic_read_address16 = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE pointer to a sts21 handle structure
 * @param[in] FUC pointer to a delay_ms function address
 * @note      none
 */
#define DRIVER_STS21_LINK_DELAY_MS(HANDLE, FUC)              (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE pointer to a sts21 handle structure
 * @param[in] FUC pointer to a debug_print function address
 * @note      none
 */
#define DRIVER_STS21_LINK_DEBUG_PRINT(HANDLE, FUC)           (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup sts21_base_driver sts21 base driver function
 * @brief    sts21 base driver modules
 * @ingroup  sts21_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info pointer to a sts21 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t sts21_info(sts21_info_t *info);

/**
 * @brief     initialize the chip
 * @param[in] *handle pointer to a sts21 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t sts21_init(sts21_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle pointer to a sts21 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t sts21_deinit(sts21_handle_t *handle);

/**
 * @brief      read data
 * @param[in]  *handle pointer to a sts21 handle structure
 * @param[out] *temperature_raw pointer to a raw temperature buffer
 * @param[out] *temperature_s pointer to a converted temperature buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 crc check failed
 * @note       none
 */
uint8_t sts21_read(sts21_handle_t *handle, uint16_t *temperature_raw, float *temperature_s);

/**
 * @brief     set chip mode
 * @param[in] *handle pointer to a sts21 handle structure
 * @param[in] mode chip mode
 * @return    status code
 *            - 0 success
 *            - 1 set mode failed
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t sts21_set_mode(sts21_handle_t *handle, sts21_mode_t mode);

/**
 * @brief      get chip mode
 * @param[in]  *handle pointer to a sts21 handle structure
 * @param[out] *mode pointer to a chip mode buffer
 * @return     status code
 *             - 0 success
 *             - 1 get mode failed
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t sts21_get_mode(sts21_handle_t *handle, sts21_mode_t *mode);

/**
 * @brief     soft reset the chip
 * @param[in] *handle pointer to a sts21 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 soft reset failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t sts21_soft_reset(sts21_handle_t *handle);

/**
 * @brief     set resolution
 * @param[in] *handle pointer to a sts21 handle structure
 * @param[in] resolution chip resolution
 * @return    status code
 *            - 0 success
 *            - 1 set resolution failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t sts21_set_resolution(sts21_handle_t *handle, sts21_resolution_t resolution);

/**
 * @brief      get resolution
 * @param[in]  *handle pointer to a sts21 handle structure
 * @param[out] *resolution pointer to a resolution buffer
 * @return     status code
 *             - 0 success
 *             - 1 get resolution failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t sts21_get_resolution(sts21_handle_t *handle, sts21_resolution_t *resolution);

/**
 * @brief     enable or disable heater
 * @param[in] *handle pointer to a sts21 handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set heater failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t sts21_set_heater(sts21_handle_t *handle, sts21_bool_t enable);

/**
 * @brief      get heater status
 * @param[in]  *handle pointer to a sts21 handle structure
 * @param[out] *enable pointer to bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get heater failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t sts21_get_heater(sts21_handle_t *handle, sts21_bool_t *enable);

/**
 * @brief     enable or disable disable otp reload
 * @param[in] *handle pointer to a sts21 handle structure
 * @param[in] enable bool value
 * @return    status code
 *            - 0 success
 *            - 1 set disable otp reload failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t sts21_set_disable_otp_reload(sts21_handle_t *handle, sts21_bool_t enable);

/**
 * @brief      get disable otp reload status
 * @param[in]  *handle pointer to a sts21 handle structure
 * @param[out] *enable pointer to a bool value buffer
 * @return     status code
 *             - 0 success
 *             - 1 get disable otp reload failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t sts21_get_disable_otp_reload(sts21_handle_t *handle, sts21_bool_t *enable);

/**
 * @brief      get status
 * @param[in]  *handle pointer to a sts21 handle structure
 * @param[out] *status pointer to a status buffer
 * @return     status code
 *             - 0 success
 *             - 1 get status failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t sts21_get_status(sts21_handle_t *handle, sts21_status_t *status);

/**
 * @brief      get serial number
 * @param[in]  *handle pointer to a sts21 handle structure
 * @param[out] *sn pointer to a serial number buffer
 * @return     status code
 *             - 0 success
 *             - 1 get serial number failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 crc check failed
 * @note       none
 */
uint8_t sts21_get_serial_number(sts21_handle_t *handle, uint8_t sn[8]);

/**
 * @}
 */

/**
 * @defgroup sts21_extend_driver sts21 extend driver function
 * @brief    sts21 extend driver modules
 * @ingroup  sts21_driver
 * @{
 */

/**
 * @brief     set the chip register
 * @param[in] *handle pointer to a sts21 handle structure
 * @param[in] reg iic register address
 * @param[in] *data pointer to a data buffer
 * @param[in] len data length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t sts21_set_reg(sts21_handle_t *handle, uint8_t reg, uint8_t *data, uint16_t len);

/**
 * @brief      get the chip register
 * @param[in]  *handle pointer to a sts21 handle structure
 * @param[in]  reg iic register address
 * @param[out] *data pointer to a data buffer
 * @param[in]  len data length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t sts21_get_reg(sts21_handle_t *handle, uint8_t reg, uint8_t *data, uint16_t len);

/**
 * @brief      get the chip register16
 * @param[in]  *handle pointer to a sts21 handle structure
 * @param[in]  reg iic register address
 * @param[out] *data pointer to a data buffer
 * @param[in]  len data length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t sts21_get_reg16(sts21_handle_t *handle, uint16_t reg, uint8_t *data, uint16_t len);

/**
 * @brief     set command
 * @param[in] *handle pointer to a sts21 handle structure
 * @param[in] *data pointer to a data buffer
 * @param[in] len data length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t sts21_set_cmd(sts21_handle_t *handle, uint8_t *data, uint16_t len);

/**
 * @brief      get command
 * @param[in]  *handle pointer to a sts21 handle structure
 * @param[out] *data pointer to a data buffer
 * @param[in]  len data length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t sts21_get_cmd(sts21_handle_t *handle, uint8_t *data, uint16_t len);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
