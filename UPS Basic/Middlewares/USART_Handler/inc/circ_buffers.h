/*****************************************************************************//**
 * @file    usart_buffers.h
 * @brief   Brief description of the file
 * @author  Luis Ramirez (lramirez)
 * @author  Hugo Arganda (harganda)
 * @date    May 25, 2017
 * @version 1.0
 *****************************************************************************/

#ifndef _BUFFERS_H_
#define _BUFFERS_H_

/*****************************************************************************
 * Inclusion Dependencies
 *****************************************************************************/

#include "utils.h"

/*****************************************************************************
 * Macros
 *****************************************************************************/

/*****************************************************************************
 * Type and Constant definitions
 *****************************************************************************/

typedef struct
{
    uint8_t*  const buffer;
    uint8_t __buff;
    uint16_t head;
    uint16_t tail;
    uint16_t size;
} circ_buff_t;

/*****************************************************************************
 * Global Declarations
 *****************************************************************************/

/*****************************************************************************
 * Public Function Prototypes
 *****************************************************************************/

/*****************************************************************************//**
 * @brief       Describes what the function does.
 * @param       param1 - short description, value range
 * @param       param2 - short description, value range
 * @return      return description.
 * @note        Some added notes about the function if needed.
 *****************************************************************************/
void circ_buff_reset(circ_buff_t* cir_ptr);

/*****************************************************************************//**
 * @brief       Describes what the function does.
 * @param       param1 - short description, value range
 * @param       param2 - short description, value range
 * @return      return description.
 * @note        Some added notes about the function if needed.
 *****************************************************************************/
uint16_t circ_buff_data_length(circ_buff_t* cir_ptr);

/*****************************************************************************//**
 * @brief       Describes what the function does.
 * @param       param1 - short description, value range
 * @param       param2 - short description, value range
 * @return      return description.
 * @note        Some added notes about the function if needed.
 *****************************************************************************/
uint8_t circ_buff_push(circ_buff_t* cir_ptr, uint8_t data);

/*****************************************************************************//**
 * @brief       Describes what the function does.
 * @param       param1 - short description, value range
 * @param       param2 - short description, value range
 * @return      return description.
 * @note        Some added notes about the function if needed.
 *****************************************************************************/
uint8_t circ_buff_pop(circ_buff_t* cir_ptr, uint8_t* data);

/*****************************************************************************//**
 * @brief       Describes what the function does.
 * @param       param1 - short description, value range
 * @param       param2 - short description, value range
 * @return      return description.
 * @note        Some added notes about the function if needed.
 *****************************************************************************/
uint8_t circ_buff_write(circ_buff_t* cir_ptr, uint8_t* data, uint16_t len);

/*****************************************************************************//**
 * @brief       Describes what the function does.
 * @param       param1 - short description, value range
 * @param       param2 - short description, value range
 * @return      return description.
 * @note        Some added notes about the function if needed.
 *****************************************************************************/
uint16_t circ_buff_read(circ_buff_t* cir_ptr, uint8_t* data, uint16_t len, uint32_t timeout);

#endif /* _BUFFERS_H_ */

