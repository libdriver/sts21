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
 * @file      driver_sts21.c
 * @brief     driver sts21 source file
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

#include "driver_sts21.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "Sensirion STS21"        /**< chip name */
#define MANUFACTURER_NAME         "Sensirion"              /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        2.1f                     /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        3.6f                     /**< chip max supply voltage */
#define MAX_CURRENT               0.33f                    /**< chip max current */
#define TEMPERATURE_MIN           -40.0f                   /**< chip min operating temperature */
#define TEMPERATURE_MAX           125.0f                   /**< chip max operating temperature */
#define DRIVER_VERSION            1000                     /**< driver version */

/**
 * @brief chip command definition
 */
#define STS21_COMMAND_TRIGGER_T_MEASUREMENT_HOLD_MASTER            0xE3           /**< trigger t measurement hold master command */
#define STS21_COMMAND_TRIGGER_T_MEASUREMENT_NO_HOLD_MASTER         0xF3           /**< trigger t measurement no hold master command */
#define STS21_COMMAND_WRITE_REG                                    0xE6           /**< write user register command */
#define STS21_COMMAND_READ_REG                                     0xE7           /**< read user register command */
#define STS21_COMMAND_SOFT_RESET                                   0xFE           /**< soft reset command */
#define STS21_COMMAND_GET_SN1                                      0xFA0FU        /**< read from memory location 1 command */
#define STS21_COMMAND_GET_SN2                                      0xFCC9U        /**< read from memory location 2 command */

/**
 * @brief chip address definition
 */
#define STS21_ADDRESS             0x94        /**< iic device address */

/**
 * @brief     write command
 * @param[in] *handle pointer to a sts21 handle structure
 * @param[in] *data pointer to a data buffer
 * @param[in] len data length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
static uint8_t a_sts21_write_command(sts21_handle_t *handle, uint8_t *data, uint16_t len)
{
    if (handle->iic_write_cmd(STS21_ADDRESS, data, len) != 0)        /* iic write */
    {
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

/**
 * @brief      read command
 * @param[in]  *handle pointer to a sts21 handle structure
 * @param[out] *data pointer to a data buffer
 * @param[in]  len data length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
static uint8_t a_sts21_read_command(sts21_handle_t *handle, uint8_t *data, uint16_t len)
{
    if (handle->iic_read_cmd(STS21_ADDRESS, data, len) != 0)        /* iic read */
    {
        return 1;                                                   /* return error */
    }
    
    return 0;                                                       /* success return 0 */
}

/**
 * @brief     write bytes
 * @param[in] *handle pointer to a sts21 handle structure
 * @param[in] reg iic register address
 * @param[in] *data pointer to a data buffer
 * @param[in] len data length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
static uint8_t a_sts21_write(sts21_handle_t *handle, uint8_t reg, uint8_t *data, uint16_t len)
{
    if (handle->iic_write(STS21_ADDRESS, reg, data, len) != 0)        /* iic write */
    {
        return 1;                                                     /* return error */
    }
    
    return 0;                                                         /* success return 0 */
}

/**
 * @brief      read bytes
 * @param[in]  *handle pointer to a sts21 handle structure
 * @param[in]  reg iic register address
 * @param[out] *data pointer to a data buffer
 * @param[in]  len data length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
static uint8_t a_sts21_read(sts21_handle_t *handle, uint8_t reg, uint8_t *data, uint16_t len)
{
    if (handle->iic_read(STS21_ADDRESS, reg, data, len) != 0)        /* iic read */
    {
        return 1;                                                    /* return error */
    }
    
    return 0;                                                        /* success return 0 */
}

/**
 * @brief      read bytes with hold master
 * @param[in]  *handle pointer to a sts21 handle structure
 * @param[in]  reg iic register address
 * @param[out] *data pointer to a data buffer
 * @param[in]  len data length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
static uint8_t a_sts21_read_hold(sts21_handle_t *handle, uint8_t reg, uint8_t *data, uint16_t len)
{
    if (handle->iic_read_with_wait(STS21_ADDRESS, reg, data, len) != 0)        /* iic read */
    {
        return 1;                                                              /* return error */
    }
    
    return 0;                                                                  /* success return 0 */
}

/**
 * @brief      read16 bytes
 * @param[in]  *handle pointer to a sts21 handle structure
 * @param[in]  reg iic register address
 * @param[out] *data pointer to a data buffer
 * @param[in]  len data length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
static uint8_t a_sts21_read16(sts21_handle_t *handle, uint16_t reg, uint8_t *data, uint16_t len)
{
    if (handle->iic_read_address16(STS21_ADDRESS, reg, data, len) != 0)        /* iic read */
    {
        return 1;                                                              /* return error */
    }
    
    return 0;                                                                  /* success return 0 */
}

/**
 * @brief     calculate the crc
 * @param[in] *data pointer to a data buffer
 * @param[in] len data length
 * @return    crc
 * @note      none
 */
static uint8_t a_sts21_crc(uint8_t *data, uint16_t len)
{
    const uint16_t POLYNOMIAL = 0x131;
    uint8_t crc = 0x00;
    uint16_t i;
    uint16_t j;
  
    for (i = 0; i < len; i++)                         /* loop all */
    {
        crc ^= (data[i]);                             /* calc crc */
        for (j= 8; j > 0; j--)                        /* loop */
        {
            if ((crc & 0x80) != 0)                    /* 1 */
            {
                crc = (crc << 1) ^ POLYNOMIAL;        /* calc crc */
            }
            else                                      /* 0 */
            {
                crc = (crc << 1);                     /* calc crc */
            }
        }
    }
    
    return crc;                                       /* return crc */
}

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
uint8_t sts21_init(sts21_handle_t *handle)
{
    uint8_t res;
    uint8_t command;
    
    if (handle == NULL)                                                      /* check handle */
    {
        return 2;                                                            /* return error */
    }
    if (handle->debug_print == NULL)                                         /* check debug_print */
    {
        return 3;                                                            /* return error */
    }
    if (handle->iic_init == NULL)                                            /* check iic_init */
    {
        handle->debug_print("sts21: iic_init is null.\n");                   /* iic_init is null */
       
        return 3;                                                            /* return error */
    }
    if (handle->iic_deinit == NULL)                                          /* check iic_deinit */
    {
        handle->debug_print("sts21: iic_deinit is null.\n");                 /* iic_deinit is null */
       
        return 3;                                                            /* return error */
    }
    if (handle->iic_read_cmd == NULL)                                        /* check iic_read_cmd */
    {
        handle->debug_print("sts21: iic_read_cmd is null.\n");               /* iic_read_cmd is null */
       
        return 3;                                                            /* return error */
    }
    if (handle->iic_read == NULL)                                            /* check iic_read */
    {
        handle->debug_print("sts21: iic_read is null.\n");                   /* iic_read is null */
       
        return 3;                                                            /* return error */
    }
    if (handle->iic_read_address16 == NULL)                                  /* check iic_read_address16 */
    {
        handle->debug_print("sts21: iic_read_address16 is null.\n");         /* iic_read_address16 is null */
       
        return 3;                                                            /* return error */
    }
    if (handle->iic_read_with_wait == NULL)                                  /* check iic_read_with_wait */
    {
        handle->debug_print("sts21: iic_read_with_wait is null.\n");         /* iic_read_with_wait is null */
       
        return 3;                                                            /* return error */
    }
    if (handle->iic_write_cmd == NULL)                                       /* check iic_write_cmd */
    {
        handle->debug_print("sts21: iic_write_cmd is null.\n");              /* iic_write_cmd is null */
       
        return 3;                                                            /* return error */
    }
    if (handle->iic_write == NULL)                                           /* check iic_write */
    {
        handle->debug_print("sts21: iic_write is null.\n");                  /* iic_write is null */
       
        return 3;                                                            /* return error */
    }
    if (handle->delay_ms == NULL)                                            /* check delay_ms */
    {
        handle->debug_print("sts21: delay_ms is null.\n");                   /* delay_ms is null */
       
        return 3;                                                            /* return error */
    }
    
    if (handle->iic_init() != 0)                                             /* iic init */
    {
        handle->debug_print("sts21: iic init failed.\n");                    /* iic init failed */
       
        return 1;                                                            /* return error */
    }
    
    command = STS21_COMMAND_SOFT_RESET;                                      /* set command */
    res = a_sts21_write_command(handle, &command, 1);                        /* write command */
    if (res != 0)                                                            /* check result */
    {
        handle->debug_print("sts21: write command failed.\n");               /* write command failed */
        (void)handle->iic_deinit();                                          /* close iic */
        
        return 1;                                                            /* return error */
    }
    handle->delay_ms(15);                                                    /* delay 15ms */
    handle->inited = 1;                                                      /* flag finish initialization */
    
    return 0;                                                                /* success return 0 */
}

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
uint8_t sts21_deinit(sts21_handle_t *handle)
{
    uint8_t res;
    uint8_t command;
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    command = STS21_COMMAND_SOFT_RESET;                               /* set command */
    res = a_sts21_write_command(handle, &command, 1);                 /* write command */
    if (res != 0)                                                     /* check result */
    {
        handle->debug_print("sts21: write command failed.\n");        /* write command failed */
        
        return 1;                                                     /* return error */
    }
    handle->delay_ms(15);                                             /* delay 15ms */
    if (handle->iic_deinit() != 0)                                    /* iic deinit */
    {
        handle->debug_print("sts21: iic deinit failed.\n");           /* iic deinit failed */
       
        return 1;                                                     /* return error */
    }
    handle->inited = 0;                                               /* flag close */
    
    return 0;                                                         /* success return 0 */
}

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
uint8_t sts21_soft_reset(sts21_handle_t *handle)
{
    uint8_t res;
    uint8_t command;
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    command = STS21_COMMAND_SOFT_RESET;                               /* set command */
    res = a_sts21_write_command(handle, &command, 1);                 /* write command */
    if (res != 0)                                                     /* check result */
    {
        handle->debug_print("sts21: write command failed.\n");        /* write command failed */
           
        return 1;                                                     /* return error */
    }
    handle->delay_ms(15);                                             /* delay 15ms */
    
    return 0;                                                         /* success return 0 */
}

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
uint8_t sts21_set_resolution(sts21_handle_t *handle, sts21_resolution_t resolution)
{
    uint8_t res;
    uint8_t command;
    uint8_t prev;
    
    if (handle == NULL)                                          /* check handle */
    {
        return 2;                                                /* return error */
    }
    if (handle->inited != 1)                                     /* check handle initialization */
    {
        return 3;                                                /* return error */
    }
    
    command = STS21_COMMAND_READ_REG;                            /* set command */
    res = a_sts21_read(handle, command, &prev, 1);               /* read reg */
    if (res != 0)                                                /* check result */
    {
        handle->debug_print("sts21: read reg failed.\n");        /* read reg failed */
       
        return 1;                                                /* return error */
    }
    prev &= ~(1 << 7);                                           /* clear bit7 */
    prev &= ~(1 << 0);                                           /* clear bit0 */
    prev |= (((uint8_t)(resolution) >> 1) & 0x01) << 7;          /* set resolution */
    prev |= (((uint8_t)(resolution) >> 0) & 0x01) << 0;          /* set resolution */
    command = STS21_COMMAND_WRITE_REG;                           /* set command */
    res = a_sts21_write(handle, command, &prev, 1);              /* write reg */
    if (res != 0)                                                /* check result */
    {
        handle->debug_print("sts21: write reg failed.\n");       /* write reg failed */
       
        return 1;                                                /* return error */
    }
    handle->resolution = resolution;                             /* set resolution */
    
    return 0;                                                    /* success return 0 */
}

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
uint8_t sts21_get_resolution(sts21_handle_t *handle, sts21_resolution_t *resolution)
{
    uint8_t res;
    uint8_t command;
    uint8_t prev;
    uint8_t r;
    
    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }
    
    command = STS21_COMMAND_READ_REG;                                     /* set command */
    res = a_sts21_read(handle, command, &prev, 1);                        /* read reg */
    if (res != 0)                                                         /* check result */
    {
        handle->debug_print("sts21: read reg failed.\n");                 /* read reg failed */
       
        return 1;                                                         /* return error */
    }
    r = (((prev >> 7) & 0x01) << 1) | (((prev >> 0) & 0x01) << 0);        /* get data*/
    *resolution = (sts21_resolution_t)(r);
    
    return 0;                                                             /* success return 0 */
}

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
uint8_t sts21_set_heater(sts21_handle_t *handle, sts21_bool_t enable)
{
    uint8_t res;
    uint8_t command;
    uint8_t prev;
    
    if (handle == NULL)                                          /* check handle */
    {
        return 2;                                                /* return error */
    }
    if (handle->inited != 1)                                     /* check handle initialization */
    {
        return 3;                                                /* return error */
    }
    
    command = STS21_COMMAND_READ_REG;                            /* set command */
    res = a_sts21_read(handle, command, &prev, 1);               /* read reg */
    if (res != 0)                                                /* check result */
    {
        handle->debug_print("sts21: read reg failed.\n");        /* read reg failed */
       
        return 1;                                                /* return error */
    }
    prev &= ~(1 << 2);                                           /* clear settings */
    prev |= enable << 2;                                         /* set bool */
    command = STS21_COMMAND_WRITE_REG;                           /* set command */
    res = a_sts21_write(handle, command, &prev, 1);              /* write reg */
    if (res != 0)                                                /* check result */
    {
        handle->debug_print("sts21: write reg failed.\n");       /* write reg failed */
       
        return 1;                                                /* return error */
    }
    
    return 0;                                                    /* success return 0 */
}

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
uint8_t sts21_get_heater(sts21_handle_t *handle, sts21_bool_t *enable)
{
    uint8_t res;
    uint8_t command;
    uint8_t prev;
    
    if (handle == NULL)                                          /* check handle */
    {
        return 2;                                                /* return error */
    }
    if (handle->inited != 1)                                     /* check handle initialization */
    {
        return 3;                                                /* return error */
    }
    
    command = STS21_COMMAND_READ_REG;                            /* set command */
    res = a_sts21_read(handle, command, &prev, 1);               /* read reg */
    if (res != 0)                                                /* check result */
    {
        handle->debug_print("sts21: read reg failed.\n");        /* read reg failed */
       
        return 1;                                                /* return error */
    }
    *enable = (sts21_bool_t)((prev >> 2) & 0x01);                /* get bool */
    
    return 0;                                                    /* success return 0 */
}

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
uint8_t sts21_set_disable_otp_reload(sts21_handle_t *handle, sts21_bool_t enable)
{
    uint8_t res;
    uint8_t command;
    uint8_t prev;
    
    if (handle == NULL)                                          /* check handle */
    {
        return 2;                                                /* return error */
    }
    if (handle->inited != 1)                                     /* check handle initialization */
    {
        return 3;                                                /* return error */
    }
    
    command = STS21_COMMAND_READ_REG;                            /* set command */
    res = a_sts21_read(handle, command, &prev, 1);               /* read reg */
    if (res != 0)                                                /* check result */
    {
        handle->debug_print("sts21: read reg failed.\n");        /* read reg failed */
       
        return 1;                                                /* return error */
    }
    prev &= ~(1 << 1);                                           /* clear settings */
    prev |= enable << 1;                                         /* set bool */
    command = STS21_COMMAND_WRITE_REG;                           /* set command */
    res = a_sts21_write(handle, command, &prev, 1);              /* write reg */
    if (res != 0)                                                /* check result */
    {
        handle->debug_print("sts21: write reg failed.\n");       /* write reg failed */
       
        return 1;                                                /* return error */
    }
    
    return 0;                                                    /* success return 0 */
}

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
uint8_t sts21_get_disable_otp_reload(sts21_handle_t *handle, sts21_bool_t *enable)
{
    uint8_t res;
    uint8_t command;
    uint8_t prev;
    
    if (handle == NULL)                                          /* check handle */
    {
        return 2;                                                /* return error */
    }
    if (handle->inited != 1)                                     /* check handle initialization */
    {
        return 3;                                                /* return error */
    }
    
    command = STS21_COMMAND_READ_REG;                            /* set command */
    res = a_sts21_read(handle, command, &prev, 1);               /* read reg */
    if (res != 0)                                                /* check result */
    {
        handle->debug_print("sts21: read reg failed.\n");        /* read reg failed */
       
        return 1;                                                /* return error */
    }
    *enable = (sts21_bool_t)((prev >> 1) & 0x01);                /* set bool */
    
    return 0;                                                    /* success return 0 */
}

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
uint8_t sts21_get_status(sts21_handle_t *handle, sts21_status_t *status)
{
    uint8_t res;
    uint8_t command;
    uint8_t prev;
    
    if (handle == NULL)                                          /* check handle */
    {
        return 2;                                                /* return error */
    }
    if (handle->inited != 1)                                     /* check handle initialization */
    {
        return 3;                                                /* return error */
    }
    
    command = STS21_COMMAND_READ_REG;                            /* set command */
    res = a_sts21_read(handle, command, &prev, 1);               /* read reg */
    if (res != 0)                                                /* check result */
    {
        handle->debug_print("sts21: read reg failed.\n");        /* read reg failed */
       
        return 1;                                                /* return error */
    }
    *status = (sts21_status_t)((prev >> 6) & 0x01);              /* set status */
    
    return 0;                                                    /* success return 0 */
}

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
uint8_t sts21_set_mode(sts21_handle_t *handle, sts21_mode_t mode)
{
    if (handle == NULL)                  /* check handle */
    {
        return 2;                        /* return error */
    }
    if (handle->inited != 1)             /* check handle initialization */
    {
        return 3;                        /* return error */
    }
    
    handle->mode = (uint8_t)mode;        /* set mode */
    
    return 0;                            /* success return 0 */
}

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
uint8_t sts21_get_mode(sts21_handle_t *handle, sts21_mode_t *mode)
{
    if (handle == NULL)                          /* check handle */
    {
        return 2;                                /* return error */
    }
    if (handle->inited != 1)                     /* check handle initialization */
    {
        return 3;                                /* return error */
    }
    
    *mode = (sts21_mode_t)(handle->mode);        /* get mode */
    
    return 0;                                    /* success return 0 */
}

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
uint8_t sts21_read(sts21_handle_t *handle, uint16_t *temperature_raw, float *temperature_s)
{
    uint8_t res;
    uint8_t command;
    uint8_t data[3];
    
    if (handle == NULL)                                                                  /* check handle */
    {
        return 2;                                                                        /* return error */
    }
    if (handle->inited != 1)                                                             /* check handle initialization */
    {
        return 3;                                                                        /* return error */
    }
    
    if(handle->mode == (uint8_t)(STS21_MODE_HOLD_MASTER))                                /* hold master */
    {
        command = STS21_COMMAND_TRIGGER_T_MEASUREMENT_HOLD_MASTER;                       /* set command */
        res = a_sts21_read_hold(handle, command, data, 3);                               /* read hold */
        if (res != 0)                                                                    /* check result */
        {
            handle->debug_print("sts21: read reg failed.\n");                            /* read reg failed */
           
            return 1;                                                                    /* return error */
        }
        if (a_sts21_crc(data, 2) != data[2])                                             /* check crc */
        {
            handle->debug_print("sts21: crc check failed.\n");                           /* crc check failed */
           
            return 4;                                                                    /* return error */
        }
        *temperature_raw = (uint16_t)((((uint16_t)data[0]) << 8) | data[1]);             /* set raw temperature */
        (*temperature_raw) &= ~0x0003;                                                   /* clear status bits */
        *temperature_s = (float)(*temperature_raw) / 65536.0f * 175.72f - 46.85f;        /* convert raw temperature */
    }
    else                                                                                 /* no hold master */
    {
        command = STS21_COMMAND_TRIGGER_T_MEASUREMENT_NO_HOLD_MASTER;                    /* set command */
        res = a_sts21_write_command(handle, &command, 1);                                /* write command */
        if (res != 0)                                                                    /* check result */
        {
            handle->debug_print("sts21: write reg failed.\n");                           /* write reg failed */
           
            return 1;                                                                    /* return error */
        }
        if (handle->resolution == STS21_RESOLUTION_T_14BIT)                              /* 14bit */
        {
            handle->delay_ms(86);                                                        /* delay 86ms */
        }
        else if (handle->resolution == STS21_RESOLUTION_T_12BIT)                         /* 12bit */
        {
            handle->delay_ms(23);                                                        /* delay 23ms */
        }
        else if (handle->resolution == STS21_RESOLUTION_T_13BIT)                         /* 13bit */
        {
            handle->delay_ms(44);                                                        /* delay 44ms */
        }
        else                                                                             /* 11bit */
        {
            handle->delay_ms(12);                                                        /* delay 12ms */
        }
        res = a_sts21_read_command(handle, data, 3);                                     /* read command */
        if (res != 0)                                                                    /* check result */
        {
            handle->debug_print("sts21: read reg failed.\n");                            /* read reg failed */
           
            return 1;                                                                    /* return error */
        }
        if (a_sts21_crc(data, 2) != data[2])                                             /* check crc */
        {
            handle->debug_print("sts21: crc check failed.\n");                           /* crc check failed */
           
            return 4;                                                                    /* return error */
        }
        *temperature_raw = (uint16_t)((((uint16_t)data[0]) << 8) | data[1]);             /* set raw temperature */
        (*temperature_raw) &= ~0x0003;                                                   /* clear status bits */
        *temperature_s = (float)(*temperature_raw) / 65536.0f * 175.72f - 46.85f;        /* convert raw temperature */
    }
    
    return 0;                                                                            /* success return 0 */
}

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
uint8_t sts21_get_serial_number(sts21_handle_t *handle, uint8_t sn[8])
{
    uint8_t res;
    uint16_t command;
    uint8_t data[8];
    
    if (handle == NULL)                                             /* check handle */
    {
        return 2;                                                   /* return error */
    }
    if (handle->inited != 1)                                        /* check handle initialization */
    {
        return 3;                                                   /* return error */
    }
    
    command = STS21_COMMAND_GET_SN1;                                /* get serial number command */
    res = a_sts21_read16(handle, command, (uint8_t *)data, 8);      /* read data */
    if (res != 0)                                                   /* check result */
    {
        handle->debug_print("sts21: read data failed.\n");          /* read data failed */
       
        return 1;                                                   /* return error */
    }
    if (a_sts21_crc((uint8_t *)&data[0], 1) != data[1])             /* check crc */
    {
        handle->debug_print("sts21: crc check failed.\n");          /* crc check failed */
       
        return 4;                                                   /* return error */
    }
    if (a_sts21_crc((uint8_t *)&data[2], 1) != data[3])             /* check crc */
    {
        handle->debug_print("sts21: crc check failed.\n");          /* crc check failed */
       
        return 4;                                                   /* return error */
    }
    if (a_sts21_crc((uint8_t *)&data[4], 1) != data[5])             /* check crc */
    {
        handle->debug_print("sts21: crc check failed.\n");          /* crc check failed */
       
        return 4;                                                   /* return error */
    }
    if (a_sts21_crc((uint8_t *)&data[6], 1) != data[7])             /* check crc */
    {
        handle->debug_print("sts21: crc check failed.\n");          /* crc check failed */
       
        return 4;                                                   /* return error */
    }
    sn[5] = data[0];                                                /* set sn5 */
    sn[4] = data[2];                                                /* set sn4 */
    sn[3] = data[4];                                                /* set sn3 */
    sn[2] = data[6];                                                /* set sn2 */
    
    command = STS21_COMMAND_GET_SN2;                                /* get serial number command */
    res = a_sts21_read16(handle, command, (uint8_t *)data, 6);      /* read data */
    if (res != 0)                                                   /* check result */
    {
        handle->debug_print("sts21: read data failed.\n");          /* read data failed */
       
        return 1;                                                   /* return error */
    }
    if (a_sts21_crc((uint8_t *)data, 2) != data[2])                 /* check crc */
    {
        handle->debug_print("sts21: crc check failed.\n");          /* crc check failed */
       
        return 4;                                                   /* return error */
    }
    if (a_sts21_crc((uint8_t *)&data[3], 2) != data[5])             /* check crc */
    {
        handle->debug_print("sts21: crc check failed.\n");          /* crc check failed */
       
        return 4;                                                   /* return error */
    }
    sn[1] = data[0];                                                /* set sn1 */
    sn[0] = data[1];                                                /* set sn0 */
    sn[7] = data[3];                                                /* set sn7 */
    sn[6] = data[4];                                                /* set sn6 */
    
    return 0;                                                       /* success return 0 */
}

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
uint8_t sts21_set_reg(sts21_handle_t *handle, uint8_t reg, uint8_t *data, uint16_t len)
{
    if (handle == NULL)                                 /* check handle */
    {
        return 2;                                       /* return error */
    }
    if (handle->inited != 1)                            /* check handle initialization */
    {
        return 3;                                       /* return error */
    }
    
    return a_sts21_write(handle, reg, data, len);       /* write command */
}

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
uint8_t sts21_get_reg(sts21_handle_t *handle, uint8_t reg, uint8_t *data, uint16_t len)
{
    if (handle == NULL)                                /* check handle */
    {
        return 2;                                      /* return error */
    }
    if (handle->inited != 1)                           /* check handle initialization */
    {
        return 3;                                      /* return error */
    }
    
    return a_sts21_read(handle, reg, data, len);       /* read data */
}

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
uint8_t sts21_get_reg16(sts21_handle_t *handle, uint16_t reg, uint8_t *data, uint16_t len)
{
    if (handle == NULL)                                  /* check handle */
    {
        return 2;                                        /* return error */
    }
    if (handle->inited != 1)                             /* check handle initialization */
    {
        return 3;                                        /* return error */
    }
    
    return a_sts21_read16(handle, reg, data, len);       /* read data */
}

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
uint8_t sts21_set_cmd(sts21_handle_t *handle, uint8_t *data, uint16_t len)
{
    if (handle == NULL)                                    /* check handle */
    {
        return 2;                                          /* return error */
    }
    if (handle->inited != 1)                               /* check handle initialization */
    {
        return 3;                                          /* return error */
    }
    
    return a_sts21_write_command(handle, data, len);       /* write command */
}

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
uint8_t sts21_get_cmd(sts21_handle_t *handle, uint8_t *data, uint16_t len)
{
    if (handle == NULL)                                   /* check handle */
    {
        return 2;                                         /* return error */
    }
    if (handle->inited != 1)                              /* check handle initialization */
    {
        return 3;                                         /* return error */
    }
    
    return a_sts21_read_command(handle, data, len);       /* read data */
}

/**
 * @brief      get chip's information
 * @param[out] *info pointer to a sts21 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t sts21_info(sts21_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }
    
    memset(info, 0, sizeof(sts21_info_t));                          /* initialize sts21 info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "IIC", 8);                             /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */
    
    return 0;                                                       /* success return 0 */
}
