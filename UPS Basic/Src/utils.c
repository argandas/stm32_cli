/*****************************************************************************//**
 * @file    utils.c
 * @brief   General Purpose Utilities
 * @author  Robert Storme
 * @author  John Moore
 * @author  Scott Morgan
 * @author  Nick Carter
 * @date    20. July 2012
 * @version 1.0
 *****************************************************************************/
/**
 * @addtogroup Utility Utility Library
 * @{
 * @addtogroup utils Utility Functions
 * @{
 */
/*****************************************************************************
 * Inclusion Dependencies
 *****************************************************************************/
#include "utils.h"
#include <string.h>
#include <stdarg.h>

/*****************************************************************************
 * Macros
 *****************************************************************************/
/*****************************************************************************
 * Type and Constant Definitions
 *****************************************************************************/
/*****************************************************************************
 * Global Declarations
 *****************************************************************************/
/*****************************************************************************
 * Static Declarations
 *****************************************************************************/

/*****************************************************************************
 * Private Function Prototypes
 *****************************************************************************/
/*****************************************************************************
 * @brief       A simple, small sprintf.
 * @param       Standard sprintf format with only the following formatting
 *              characters and modifiers supported:
 *              c   - print a single character
 *              u   - print and unsigned integer
 *              d   - print a signed integer
 *              s   - print a string
 *              x   - print a hex value
 *****************************************************************************/
/*****************************************************************************
 * Private Function Implementations
 *****************************************************************************/
static void dvsprintf_maxlen_dvs(char *dest, char *fmt, va_list args, DVS_STACK *dvs)
{
    if ((dest) && (dvs))
    {
        dvs->precision = 2;
        dvs->lng = 0;
        dvs->maxdest = NULL;
        dvs->precision_found = 0;

        if (dvs->maxlen > 0) dvs->maxdest = (dest + dvs->maxlen) - 1;

        while ((*fmt) &&
               ((dvs->maxdest == NULL) || (dest < dvs->maxdest)))
        {
            if (*fmt != '%' || *++fmt == '%')
            {
                *dest++ = *fmt++;
                continue;
            }
            else
            {
                // Is the next character after % a number?
                if (*fmt > 0x030 && *fmt < 0x39)
                {
                    dvs->precision = (*fmt++) - 0x30;
                    dvs->precision_found = 1;
                }
            }

            dvs->c = *(fmt++);

            if (dvs->c == 'l')
            {
                dvs->c = *(fmt++);
                dvs->lng = 1;
            }

            switch (dvs->c)
            {
            case 'u':
            case 'd':
            case 'x':
            case 'X':
                if (dvs->lng)
                {
                    dvs->checksize = 2 * sizeof(long);
                } else {
                    dvs->checksize = 2 * sizeof(int);
                }
                break;
            default:
                dvs->checksize = 0;
            }

            if ((dvs->maxdest == NULL) ||
                ((dest + dvs->checksize) < dvs->maxdest)) {
                switch (dvs->c)
                {
                case 'c':
                    dvs->c = (char) va_arg (args, int);
                    *dest++ = dvs->c;
                    break;

                case 'd':
                    if (dvs->lng)
                    {
                        dvs->l = va_arg (args, long);
                        dest = int64_to_ascii_incremented_ptr(dest,dvs->l);
                    }
                    else
                    {
                        dvs->l = va_arg (args, int);
                        dest = int32_to_ascii_incremented_ptr(dest,dvs->l);
                    }
                    break;

                case 'u':
                    if (dvs->lng)
                    {
                        dvs->u = va_arg (args, unsigned long);
                        dest = uint64_to_ascii_incremented_ptr(dest,dvs->u);
                    }
                    else
                    {
                        dvs->u = va_arg (args, unsigned int);
                        dest = uint32_to_ascii_incremented_ptr(dest,dvs->u);
                    }
                    break;

                case 'x':
                case 'X':
                    if (dvs->lng)
                    {
                        dvs->u = va_arg (args, unsigned long);
                    }
                    else
                    {
                        dvs->u = va_arg (args, unsigned int);
                    }
                    if (dvs->precision_found) {
                        unsigned_decimal_to_hex_ascii(dest, dvs->u, dvs->precision);
                        dest += dvs->precision;
                        dvs->precision_found = 0;
                        dvs->precision = 2;
                    } else {
                        if (dvs->lng) {
                            dest = uint64_to_hex_ascii_incremented_ptr(dest,dvs->u);
                        } else {
                            dest = uint32_to_hex_ascii_incremented_ptr(dest,dvs->u);
                        }
                    }
                    break;

                case 's':
                    dvs->p = va_arg (args, char *);
                    // copy characters from string until null is reached
                    while ((*dvs->p) &&
                           ((dvs->maxdest == NULL) || (dest < dvs->maxdest)))
                    {
                        *dest++ = *dvs->p++;
                    }
                    break;
                }
            }
            else
            {
                fmt = NULL;
                dest = dvs->maxdest;
            }
        }
        *dest = 0;  // add null terminator
        dvs->in_use = 0;
    }
}

static void dvsprintf_maxlen(char *dest, char *fmt, va_list args, DVS_STACK *dvs)
{
    if (!dvs)
    {
        DVS_STACK lcl_dvs;
        lcl_dvs.maxlen = 0;

        dvsprintf_maxlen_dvs(dest, fmt, args, &lcl_dvs);
    }
    else
    {
        dvsprintf_maxlen_dvs(dest, fmt, args, dvs);
    }
}

static void dvsprintf(char *dest, char *fmt, va_list args)
{
    dvsprintf_maxlen(dest, fmt, args, NULL);
}

/*****************************************************************************
 * Public Function Implementations
 *****************************************************************************/
#if(UTIL_USE_DEC_TO_ASCII == 1)
uint8_t int8_to_ascii( char * dest, int8_t src )
{
    return int64_to_ascii(dest, (int64_t) src);
}

uint8_t int16_to_ascii( char * dest, int16_t src )
{
    return int64_to_ascii(dest, (int64_t) src);
}

uint8_t int32_to_ascii( char * dest, int32_t src )
{
    return int64_to_ascii(dest, (int64_t) src);
}

uint8_t int64_to_ascii( char * dest, int64_t src )
{
    uint8_t ascii_length = 0;

    //If the source is less than 0
    //add the '-' to the beginning
    //of the string and increment
    //the length of the string
    if(src < 0)
    {
        *dest++ = '-';
        src *= -1;
        ascii_length++;
    }

    //If the source is 0 set the
    //length of the string to 1
    //and set the destination to
    //'0'
    if(src == 0)
    {
        *dest++ = '0';
        ascii_length = 1;
    }
    else
    {
        ascii_length += uint64_to_ascii(dest, (uint64_t) src);
    }

    return (ascii_length);
}

uint8_t uint8_to_ascii( char * dest, uint8_t src )
{
    return uint64_to_ascii(dest, (uint64_t) src);
}

uint8_t uint16_to_ascii( char * dest, uint16_t src )
{
    return uint64_to_ascii(dest, (uint64_t) src);
}

uint8_t uint32_to_ascii( char * dest, uint32_t src )
{
    return uint64_to_ascii(dest, (uint64_t) src);
}

uint8_t uint64_to_ascii( char * dest, uint64_t src )
{
    uint8_t ascii_length = 0;

    if(NULL != dest)
    {
        if(0 == src)
        {
            *dest++ = '0';
            ascii_length = 1;
        }
        else
        {
            uint64_t tmp_src = src;
            uint8_t num_of_chars = 0;
            char * dest_ptr = dest;

            //Find out how many ascii numbers
            //there are in the value
            while(0 != tmp_src)
            {
                num_of_chars++;
                tmp_src /= 10;
            }

            ascii_length = num_of_chars;

            //Convert the decimal number to ascii
            //if the number of characters are
            //greater than 0
            if(0 < num_of_chars)
            {
                dest += num_of_chars;
                dest_ptr = dest;
                dest_ptr--;

                while(num_of_chars-- > 0)
                {
                    *dest_ptr-- = ((src % 10) + '0');
                    src /= 10;
                }
            }
        }
    }

    return (ascii_length);
}
#endif

#if(UTIL_USE_DEC_TO_ASCII_PTR == 1)
char * int8_to_ascii_incremented_ptr( char * dest, int8_t src )
{
    char * address_ptr = NULL;
    uint8_t string_length = 0;

    string_length = int8_to_ascii(dest, src);

    if(0 < string_length)
    {
        address_ptr = (dest + string_length);
    }

    return address_ptr;
}

char * int16_to_ascii_incremented_ptr( char * dest, int16_t src )
{
    char * address_ptr = NULL;
    uint8_t string_length = 0;

    string_length = int16_to_ascii(dest, src);

    if(0 < string_length)
    {
        address_ptr = (dest + string_length);
    }

    return address_ptr;
}

char * int32_to_ascii_incremented_ptr( char * dest, int32_t src )
{
    char * address_ptr = NULL;
    uint8_t string_length = 0;

    string_length = int32_to_ascii(dest, src);

    if(0 < string_length)
    {
        address_ptr = (dest + string_length);
    }

    return address_ptr;
}

char * int64_to_ascii_incremented_ptr( char * dest, int64_t src )
{
    char * address_ptr = NULL;
    uint8_t string_length = 0;

    string_length = int64_to_ascii(dest, src);

    if(0 < string_length)
    {
        address_ptr = (dest + string_length);
    }

    return address_ptr;
}

char * uint8_to_ascii_incremented_ptr( char * dest, uint8_t src )
{
    char * address_ptr = NULL;
    uint8_t string_length = 0;

    string_length = uint8_to_ascii(dest, src);

    if(0 < string_length)
    {
        address_ptr = (dest + string_length);
    }

    return address_ptr;
}

char * uint16_to_ascii_incremented_ptr( char * dest, uint16_t src )
{
    char * address_ptr = NULL;
    uint8_t string_length = 0;

    string_length = uint16_to_ascii(dest, src);

    if(0 < string_length)
    {
        address_ptr = (dest + string_length);
    }

    return address_ptr;
}

char * uint32_to_ascii_incremented_ptr( char * dest, uint32_t src )
{
    char * address_ptr = NULL;
    uint8_t string_length = 0;

    string_length = uint32_to_ascii(dest, src);

    if(0 < string_length)
    {
        address_ptr = (dest + string_length);
    }

    return address_ptr;
}

char * uint64_to_ascii_incremented_ptr( char * dest, uint64_t src )
{
    char * address_ptr = NULL;
    uint8_t string_length = 0;

    string_length = uint64_to_ascii(dest, src);

    if(0 < string_length)
    {
        address_ptr = (dest + string_length);
    }

    return address_ptr;
}
#endif

#if ((UTIL_USE_DEC_TO_STRING == 1) && (UTIL_USE_DEC_TO_ASCII == 1))
uint8_t int8_to_string( char * dest, int8_t src )
{
    uint8_t string_length = 0;

    string_length = int8_to_ascii(dest, src);

    if(0 < string_length)
    {
        dest[string_length] = 0;
        string_length += 1;
    }

    return string_length;
}

uint8_t int16_to_string( char * dest, int16_t src )
{
    uint8_t string_length = 0;

    string_length = int16_to_ascii(dest, src);

    if(0 < string_length)
    {
        dest[string_length] = 0;
        string_length += 1;
    }

    return string_length;
}

uint8_t int32_to_string( char * dest, int32_t src )
{
    uint8_t string_length = 0;

    string_length = int32_to_ascii(dest, src);

    if(0 < string_length)
    {
        dest[string_length] = 0;
        string_length += 1;
    }

    return string_length;
}

uint8_t int64_to_string( char * dest, int64_t src )
{
    uint8_t string_length = 0;

    string_length = int64_to_ascii(dest, src);

    if(0 < string_length)
    {
        dest[string_length] = 0;
        string_length += 1;
    }

    return string_length;
}

uint8_t uint8_to_string( char * dest, uint8_t src )
{
    uint8_t string_length = 0;

    string_length = uint8_to_ascii(dest, src);

    if(0 < string_length)
    {
        dest[string_length++] = 0;
    }

    return string_length;
}

uint8_t uint16_to_string( char * dest, uint16_t src )
{
    uint8_t string_length = 0;

    string_length = uint16_to_ascii(dest, src);

    if(0 < string_length)
    {
        dest[string_length++] = 0;
    }

    return string_length;
}

uint8_t uint32_to_string( char * dest, uint32_t src )
{
    uint8_t string_length = 0;

    string_length = uint32_to_ascii(dest, src);

    if(0 < string_length)
    {
        dest[string_length++] = 0;
    }

    return string_length;
}

uint8_t uint64_to_string( char * dest, uint64_t src )
{
    uint8_t string_length = 0;

    string_length = uint64_to_ascii(dest, src);

    if(0 < string_length)
    {
        dest[string_length++] = 0;
    }

    return string_length;
}
#endif

#if ((UTIL_USE_DEC_TO_HEX_ASCII == 1) && (UTIL_USE_DEC_TO_ASCII == 1))
uint8_t uint8_to_hex_ascii( char * dest, uint8_t src )
{
    unsigned_decimal_to_hex_ascii(dest, src, UTIL_HEX_BYTE_STRING_LENGTH);
    return UTIL_HEX_BYTE_STRING_LENGTH;
}

uint8_t uint16_to_hex_ascii( char * dest, uint16_t src )
{
    unsigned_decimal_to_hex_ascii(dest, src, UTIL_HEX_SHORT_STRING_LENGTH);
    return UTIL_HEX_SHORT_STRING_LENGTH;
}

uint8_t uint32_to_hex_ascii( char * dest, uint32_t src )
{
    unsigned_decimal_to_hex_ascii(dest, src, UTIL_HEX_INT_STRING_LENGTH);
    return UTIL_HEX_INT_STRING_LENGTH;
}

uint8_t uint64_to_hex_ascii( char * dest, uint64_t src )
{
    unsigned_decimal_to_hex_ascii(dest, src, UTIL_HEX_LONG_STRING_LENGTH);
    return UTIL_HEX_LONG_STRING_LENGTH;
}

void unsigned_decimal_to_hex_ascii( char * dest, uint64_t src, uint8_t precision )
{
    if(NULL != dest)
    {
        uint64_t tmp_src;
        uint16_t src_len = 0;

        //This is used to determine the number of hex ascii
        //characters to save into the ascii buffer
        if((precision < 1) || (precision > 16))
        {
            precision = 16;
        }

        //If the source value is 0 then
        //increment the length
        if(src == 0)
        {
            src_len++;
        }
        else
        {
            tmp_src = src;

            while((tmp_src != 0) && (src_len < precision))
            {
                tmp_src >>= 4;
                src_len++;
            }
        }

        //Fill in the destination array with
        //all 0's
        while(src_len < precision--)
        {
            *dest++ = '0';
        }

        //Set the destination to the
        //end of the string and add the
        //NULL terminator
        dest += src_len;
        dest--;

        //Convert the number to hex in reverse order
        //starting from the end of the string
        while(src_len-- > 0)
        {
            int cur = src & 0x0f;

            if(cur < 10)
            {
                *dest-- = (char) (cur + '0');
            }
            else
            {
                *dest-- = (char) ((cur - 10) + 'A');
            }

            src >>= 4;
        }
    }
}
#endif

#if(UTIL_USE_DEC_TO_HEX_ASCII_PTR == 1)
char * uint8_to_hex_ascii_incremented_ptr( char * dest, uint8_t src )
{
    uint8_t string_length = 0;

    string_length = uint8_to_hex_ascii(dest, (uint64_t) src);

    if(0 < string_length)
    {
        dest += string_length;
    }

    return dest;
}

char * uint16_to_hex_ascii_incremented_ptr( char * dest, uint16_t src )
{
    uint8_t string_length = 0;

    string_length = uint16_to_hex_ascii(dest, (uint64_t) src);

    if(0 < string_length)
    {
        dest += string_length;
    }

    return dest;
}

char * uint32_to_hex_ascii_incremented_ptr( char * dest, uint32_t src )
{
    uint8_t string_length = 0;

    string_length = uint32_to_hex_ascii(dest, (uint64_t) src);

    if(0 < string_length)
    {
        dest += string_length;
    }

    return dest;
}

char * uint64_to_hex_ascii_incremented_ptr( char * dest, uint64_t src )
{
    uint8_t string_length = 0;

    string_length = uint64_to_hex_ascii(dest, (uint64_t) src);

    if(0 < string_length)
    {
        dest += string_length;
    }

    return dest;
}
#endif

#if((UTIL_USE_DEC_TO_HEX_STRING == 1) && (UTIL_USE_DEC_TO_HEX_ASCII == 1))
uint8_t uint8_to_hex_string( char * dest, uint8_t src )
{
    uint8_t string_length = 0;

    string_length = uint8_to_hex_ascii(dest, src);

    if(0 < string_length)
    {
        dest[string_length++] = 0;
    }

    return string_length;
}

uint8_t uint16_to_hex_string( char * dest, uint16_t src )
{
    uint8_t string_length = 0;

    string_length = uint16_to_hex_ascii(dest, src);

    if(0 < string_length)
    {
        dest[string_length++] = 0;
    }

    return string_length;
}

uint8_t uint32_to_hex_string( char * dest, uint32_t src )
{
    uint8_t string_length = 0;

    string_length = uint32_to_hex_ascii(dest, src);

    if(0 < string_length)
    {
        dest[string_length++] = 0;
    }

    return string_length;
}

uint8_t uint64_to_hex_string( char * dest, uint64_t src )
{
    uint8_t string_length = 0;

    string_length = uint64_to_hex_ascii(dest, src);

    if(0 < string_length)
    {
        dest[string_length++] = 0;
    }

    return string_length;
}

void unsigned_decimal_to_hex_string( char *dest, uint64_t src, uint8_t precision )
{
    if(NULL != dest)
    {
        unsigned_decimal_to_hex_ascii(dest,src,precision);
        dest[precision+1] = 0;
    }
}
#endif

#if((UTIL_USE_STRING_TO_DEC == 1) && (UTIL_USE_ASCII_TO_DEC == 1))
uint8_t string_to_int8( int8_t * dest, char * src, uint8_t number_string_format )
{
    uint8_t ret = FALSE;

    if(NULL != src)
    {
        uint8_t number_of_chars = 0;

        number_of_chars = strlen(src);

        if(0 < number_of_chars)
        {
            ret = ascii_to_int8(dest, src, number_of_chars, number_string_format);
        }
    }

    return ret;
}

uint8_t string_to_int16( int16_t * dest, char * src, uint8_t number_string_format )
{
    uint8_t ret = FALSE;

    if(NULL != src)
    {
        uint8_t number_of_chars = 0;

        number_of_chars = strlen(src);

        if(0 < number_of_chars)
        {
            ret = ascii_to_int16(dest, src, number_of_chars, number_string_format);
        }
    }

    return ret;
}

uint8_t string_to_int32( int32_t * dest, char * src, uint8_t number_string_format )
{
    uint8_t ret = FALSE;

    if(NULL != src)
    {
        uint8_t number_of_chars = 0;

        number_of_chars = strlen(src);

        if(0 < number_of_chars)
        {
            ret = ascii_to_int32(dest, src, number_of_chars, number_string_format);
        }
    }

    return ret;
}

uint8_t string_to_int64( int64_t * dest, char * src, uint8_t number_string_format )
{
    uint8_t ret = FALSE;

    if(NULL != src)
    {
        uint8_t number_of_chars = 0;

        number_of_chars = strlen(src);

        if(0 < number_of_chars)
        {
            ret = ascii_to_int64(dest, src, number_of_chars, number_string_format);
        }
    }

    return ret;
}

uint8_t string_to_uint8( uint8_t * dest, char * src, uint8_t number_string_format )
{
    uint8_t ret = 0;

    if(NULL != src)
    {
        uint8_t number_of_chars = 0;

        number_of_chars = strlen(src);

        if(0 < number_of_chars)
        {
            ret = ascii_to_uint8(dest, src, number_of_chars, number_string_format);
        }
    }

    return ret;
}

uint8_t string_to_uint16( uint16_t * dest, char * src, uint8_t number_string_format )
{
    uint8_t ret = 0;

    if(NULL != src)
    {
        uint8_t number_of_chars = 0;

        number_of_chars = strlen(src);

        if(0 < number_of_chars)
        {
            ret = ascii_to_uint16(dest, src, number_of_chars, number_string_format);
        }
    }

    return ret;
}

uint8_t string_to_uint32( uint32_t * dest, char * src, uint8_t number_string_format )
{
    uint8_t ret = 0;

    if(NULL != src)
    {
        uint8_t number_of_chars = 0;

        number_of_chars = strlen(src);

        if(0 < number_of_chars)
        {
            ret = ascii_to_uint32(dest, src, number_of_chars, number_string_format);
        }
    }

    return ret;
}

uint8_t string_to_uint64( uint64_t * dest, char * src, uint8_t number_string_format )
{
    uint8_t ret = 0;

    if(NULL != src)
    {
        uint8_t number_of_chars = 0;

        number_of_chars = strlen(src);

        if(0 < number_of_chars)
        {
            ret = ascii_to_uint64(dest, src, number_of_chars, number_string_format);
        }
    }

    return ret;
}
#endif

#if((UTIL_USE_ASCII_TO_DEC == 1) && (UTIL_USE_ASCII_CHECK == 1))
uint8_t ascii_to_uint8( uint8_t * dest, char * src, uint8_t number_of_chars, uint8_t number_string_format  )
{
    uint64_t temp_value = 0;
    uint8_t ret = FALSE;

    ret = ascii_to_uint64(&temp_value, src, number_of_chars, number_string_format);

    if(TRUE == ret)
    {
        if(UTIL_MAX_UINT8 >= temp_value)
        {
            *dest = ((uint8_t)temp_value & UTIL_MAX_UINT8);
        }
        else
        {
            ret = FALSE;
        }
    }

    return ret;
}

uint8_t ascii_to_uint16(uint16_t * dest, char * src, uint8_t number_of_chars, uint8_t number_string_format  )
{
    uint64_t temp_value = 0;
    uint8_t ret = FALSE;

    ret = ascii_to_uint64(&temp_value, src, number_of_chars, number_string_format);

    if(TRUE == ret)
    {
        if(UTIL_MAX_UINT16 >= temp_value)
        {
            *dest = ((uint16_t)temp_value & UTIL_MAX_UINT16);
        }
        else
        {
            ret = FALSE;
        }
    }

    return ret;
}

uint8_t ascii_to_uint32( uint32_t * dest, char * src, uint8_t number_of_chars, uint8_t number_string_format )
{
    uint64_t temp_value = 0;
    uint8_t ret = FALSE;

    ret = ascii_to_uint64(&temp_value, src, number_of_chars, number_string_format);

    if(TRUE == ret)
    {
        if(UTIL_MAX_UINT32 >= temp_value)
        {
            *dest = ((uint32_t)temp_value & UTIL_MAX_UINT32);
        }
        else
        {
            ret = FALSE;
        }
    }

    return ret;
}

uint8_t ascii_to_uint64( uint64_t * dest, char * src, uint8_t number_of_chars, uint8_t number_string_format )
{
    uint8_t ret = FALSE;
    uint8_t digit_value;

    if(NULL != dest)
    {
        if(NULL != src)
        {
            uint64_t converted_number = 0;
            uint8_t actual_numbers_count = 0;
            uint8_t src_idx = 0;
            uint8_t string_number_format;
            char current_char = 0;

            if(FALSE == number_string_format)
            {
                //Find out if the string is a number string
                //and if this is a number string this function
                //returns the type (ex. 0x hex string, dec string,
                //x hex string, and normal hex string)
                string_number_format = is_number_ascii(src,number_of_chars);
            }
            else
            {
                //Use this specific format
                string_number_format = number_string_format;
            }

            //If its not a number string don't bother
            //converting the string
            if(FALSE != string_number_format)
            {
                if(UTIL_DEC_STRING_FORMAT == string_number_format)
                {
                    do
                    {
                        current_char = src[src_idx];

                        //Convert the string into a number.
                        //If a non-number is parsed then exit.
                        if(TRUE == is_dec_digit(current_char))
                        {
                            if(converted_number>0x1999999999999999LL)
                            {
                                /*****************************************
                                * If the following multiply is performed *
                                * the converted number will overflow, so *
                                * exit with FALSE to prevent the         *
                                * overflow thus indicating that the      *
                                * number being converted was too large.  *
                                *****************************************/
                                break;
                            }
                            converted_number *= 10;
                            digit_value = current_char - '0';
                            if(converted_number>(UTIL_MAX_UINT64-
                              digit_value))
                            {
                                /*****************************************
                                * If the following add is performed the  *
                                * converted number will overflow, so     *
                                * exit with FALSE to prevent the         *
                                * overflow thus indicating that the      *
                                * number being converted was too large.  *
                                *****************************************/
                                break;
                            }
                            converted_number += digit_value;
                            actual_numbers_count++;
                        }
                        else
                        {
                            break;
                        }
                    }
                    while(++src_idx < number_of_chars);

                    //If the number of counted characters equals number of
                    //characters to parse passed in by the user, then the
                    //conversion was successful and return TRUE and copy
                    //the number
                    if(number_of_chars == actual_numbers_count)
                    {
                        *dest = converted_number;
                        ret = TRUE;
                    }
                }
                else
                {
                    //If the number string is not a regular hex string
                    //then it must be a hex string with 0x hex format or
                    //x hex format so increment the start of the parsing
                    //passed the formatting
                    if(UTIL_HEX_STRING_FORMAT != string_number_format)
                    {
                        src_idx = string_number_format;
                    }

                    do
                    {
                        current_char = src[src_idx];
                        if(converted_number>=0x1000000000000000LL)
                        {
                            /*****************************************
                            * If the following multiply is performed *
                            * the converted number will overflow, so *
                            * exit with FALSE to prevent the         *
                            * overflow thus indicating that the      *
                            * number being converted was too large.  *
                            *****************************************/
                            break;
                        }
                        converted_number *= 16;
                        // Convert only if the character is an actual
                        // hex ascii digit
                        if(TRUE == is_hex_digit(current_char))
                        {
                            if(TRUE == is_lower_case(current_char))
                            {
                                digit_value = ((current_char - 'a') + 10);
                            }
                            else if(TRUE == is_upper_case(current_char))
                            {
                                digit_value = ((current_char - 'A') + 10);
                            }
                            else
                            {
                                digit_value = (current_char - '0');
                            }
                            if(converted_number>(UTIL_MAX_UINT64-
                              digit_value))
                            {
                                /*****************************************
                                * If the following add is performed the  *
                                * converted number will overflow, so     *
                                * exit with FALSE to prevent the         *
                                * overflow thus indicating that the      *
                                * number being converted was too large.  *
                                *****************************************/
                                break;
                            }
                            converted_number += digit_value;
                            actual_numbers_count++;
                        }
                        else
                        {
                            break;
                        }
                    }
                    while(++src_idx < number_of_chars);

                    if(0 < actual_numbers_count)
                    {
                        *dest = converted_number;
                        ret = TRUE;
                    }
                }
            }
        }
    }
    return(ret);
}

uint8_t ascii_to_int8( int8_t * dest, char * src, uint8_t number_of_chars, uint8_t number_string_format )
{
    int64_t temp_value = 0;
    uint8_t ret = FALSE;

    ret = ascii_to_int64(&temp_value, src, number_of_chars, number_string_format);

    if(TRUE == ret)
    {
        if((UTIL_MAX_INT8 >= temp_value)&&(UTIL_MIN_INT8 <= temp_value))
        {
            *dest = (int8_t)temp_value;
        }
        else
        {
            ret = FALSE;
        }
    }

    return ret;
}

uint8_t ascii_to_int16( int16_t * dest, char * src, uint8_t number_of_chars, uint8_t number_string_format )
{
    int64_t temp_value = 0;
    uint8_t ret = FALSE;

    ret = ascii_to_int64(&temp_value, src, number_of_chars, number_string_format);

    if(TRUE == ret)
    {
        if((UTIL_MAX_INT16 >= temp_value)&&(UTIL_MIN_INT16 <= temp_value))
        {
            *dest = (int16_t)temp_value;
        }
        else
        {
            ret = FALSE;
        }
    }

    return ret;
}

uint8_t ascii_to_int32( int32_t * dest, char * src, uint8_t number_of_chars, uint8_t number_string_format )
{
    int64_t temp_value = 0;
    uint8_t ret = FALSE;

    ret = ascii_to_int64(&temp_value, src, number_of_chars, number_string_format);

    if(TRUE == ret)
    {
        if((UTIL_MAX_INT32 >= temp_value)&&(UTIL_MIN_INT32 <= temp_value))
        {
            *dest = (int32_t)temp_value;
        }
        else
        {
            ret = FALSE;
        }
    }

    return ret;
}

uint8_t ascii_to_int64( int64_t * dest, char * src, uint8_t number_of_chars, uint8_t number_string_format )
{
    uint8_t ret = FALSE;

    if(NULL != dest)
    {
        if(NULL != src)
        {
            uint64_t converted_number = 0;
            uint8_t is_negative_number = 0;
            uint8_t src_idx = 0;
            uint8_t string_number_format;

            //If the first character in string is
            //negative number indicator, mark this
            //string as negative used for conversion
            //later
            if('-' == src[0])
            {
                is_negative_number = 1;
                src_idx = 1;
            }

            if(FALSE == number_string_format)
            {
                //Find out if the string is a valid number string and find
                //out the format
                string_number_format = is_number_ascii(&src[src_idx],number_of_chars - src_idx);
                if((UTIL_HEX_X_STRING_FORMAT==string_number_format)||
                  (UTIL_HEX_0X_STRING_FORMAT==string_number_format))
                {
                    src_idx += string_number_format;
                    string_number_format = UTIL_HEX_STRING_FORMAT;
                }
            }
            else
            {
                string_number_format = number_string_format;
            }

            //Don't bother if the string is not a valid number string
            if(FALSE != string_number_format)
            {
                if(TRUE == (ascii_to_uint64(&converted_number,&src[src_idx],number_of_chars - src_idx, string_number_format)))
                {
                    if(converted_number<=UTIL_MAX_INT64)
                    {
                        ret = TRUE;
                        *dest = (int64_t)converted_number;
                        if(1 == is_negative_number)
                        {
                            *dest *= -1LL;
                        }
                    }
                    else if(converted_number==UTIL_MAX_INT64+1)
                    {
                        ret = TRUE;
                        *dest = UTIL_MIN_INT64;
                    }
                    else
                    {
                        // ret will = FALSE at this point
                    }
                }
            }
        }
    }
    return(ret);
}
#endif

#if(UTIL_USE_ASCII_CHECK == 1)
uint8_t is_ascii_char( char character )
{
    uint8_t ret = FALSE;

    if(TRUE == is_lower_case(character))
    {
        ret = UTIL_ALPHA_LOWER_CASE;
    }
    else if (TRUE == is_upper_case(character))
    {
        ret = UTIL_ALPHA_UPPER_CASE;
    }

    return ret;
}

uint8_t is_upper_case( char character )
{
    uint8_t ret = FALSE;

    if(('Z' >= character) && ('A' <= character))
    {
        ret = TRUE;
    }

    return ret;
}

uint8_t is_lower_case( char character )
{
    uint8_t ret = FALSE;

    if(('z' >= character) && ('a' <= character))
    {
        ret = TRUE;
    }

    return ret;
}

uint8_t is_hex_digit( char character )
{
    uint8_t ret = FALSE;

    if((('9' >= character) && ('0' <= character)) ||
       (('f' >= character) && ('a' <= character)) ||
       (('F' >= character) && ('A' <= character)))
    {
       ret = TRUE;
    }

    return ret;
}

uint8_t is_dec_digit( char character )
{
    uint8_t ret = FALSE;

    if(('9' >= character) && ('0' <= character))
    {
        ret = TRUE;
    }

    return ret;
}

uint8_t is_number_string( char * src )
{
    uint16_t string_length = 0;
    uint8_t ret = FALSE;

    if(NULL != src)
    {
        string_length = strlen(src);

        if(0 < string_length)
        {
            ret = is_number_ascii(src,string_length);
        }
    }

    return ret;
}

uint8_t is_number_ascii( char * src, uint16_t string_length )
{
    uint8_t ret = FALSE;

    if(NULL != src)
    {
        if(0 < string_length)
        {
            uint32_t number_of_chars = 0;
            uint8_t number_string_format = 0;
            uint8_t hex_string_flag = FALSE;
            uint8_t src_idx = 0;
            char current_char = 0;

            //If the first character in the string is X then
            //mark it as a hex string
            if((*src == 'x') || (*src == 'X'))
            {
                src_idx = number_string_format = UTIL_HEX_X_STRING_FORMAT;
                hex_string_flag = TRUE;
            }
            //If the first character in the string is 0 and the
            //second character x or X then mark it as a hex string
            else if((*src == '0') && (((*(src + 1)) == 'x') || ((*(src + 1)) == 'X')))
            {
                src_idx = number_string_format = UTIL_HEX_0X_STRING_FORMAT;
                hex_string_flag = TRUE;
            }


            do
            {
                current_char = src[src_idx];

                if(TRUE == is_dec_digit(current_char))
                {
                    number_of_chars++;
                }
                else if(TRUE == is_hex_digit(current_char))
                {
                    hex_string_flag = TRUE;
                    number_of_chars++;
                }
                else
                {
                    break;
                }
            }
            while(++src_idx < string_length);

            //This is used to verify the the number of characters read
            //is equal to the number of valid number characters
            if(number_of_chars == (string_length - number_string_format))
            {
                if(TRUE == hex_string_flag)
                {
                    if(0 < number_string_format)
                    {
                        ret = number_string_format;
                    }
                    else
                    {
                        ret = UTIL_HEX_STRING_FORMAT;
                    }
                }
                else
                {
                    ret = UTIL_DEC_STRING_FORMAT;
                }
            }
        }
    }

    return ret;
}
#endif

#if((UTIL_USE_REMOVE_ASCII == 1) && (UTIL_USE_ASCII_CHECK == 1))
uint8_t remove_non_numeric_ascii_chars( char * src, uint16_t length )
{
    uint8_t ret = FALSE;

    if(NULL != src)
    {
        if(0 < length)
        {
            char current_char = 0;
            uint8_t src_read_index = 0;
            uint8_t src_write_index = 0;
            uint8_t number_string_format = 0;

            //If the first character in the string is X then
            //mark it as a hex string
            number_string_format = is_number_ascii(src, length);

            //If the string is a decimal string
            if((UTIL_DEC_STRING_FORMAT == number_string_format) ||
               (FALSE == number_string_format))
            {
                do
                {
                    current_char = src[src_read_index];

                    if(TRUE == is_dec_digit(current_char))
                    {
                        src[src_write_index++] = current_char;
                    }
                }
                while(++src_read_index < length);
            }
            else
            {
                //If this is not a normal hex string without the
                //0x or x format then increase the index to the
                //pass any of them format characters
                if(UTIL_HEX_STRING_FORMAT != number_string_format)
                {
                    src_read_index = src_write_index = number_string_format;
                }

                do
                {
                    current_char = src[src_read_index];

                    if(TRUE == is_hex_digit(current_char))
                    {
                        src[src_write_index++] = current_char;
                    }
                }
                while(++src_read_index < length);
            }

            //This section of the code replaces the remaining ascii
            //values in the string with 0
            if(0 < src_write_index)
            {
                memset(&src[src_write_index], 0x00, (src_read_index - src_write_index));
                ret = TRUE;
            }
        }
    }

    return ret;
}

uint8_t remove_non_numeric_string_chars( char * src )
{
    uint8_t string_length = 0;
    uint8_t ret = FALSE;

    if(NULL != src)
    {
        string_length = strlen(src);

        if(0 < string_length)
        {
            ret = remove_non_numeric_ascii_chars(src, string_length);
        }
    }

    return ret;
}

uint8_t remove_numeric_ascii_chars( char * src, uint32_t length )
{
    uint8_t src_read_index = 0;
    uint8_t src_write_index = 0;
    uint8_t ret = FALSE;

    if(NULL != src)
    {
        if(0 < length)
        {
            char current_char = 0;

            //If the current character is not a ascii alphabet character
            //then increment the index otherwise copy the character
            //to the buffer then increment the write index
            do
            {
                current_char = src[src_read_index];

                if(FALSE != is_ascii_char(current_char))
                {
                    src[src_write_index++] = current_char;
                }
            }
            while(++src_read_index < length);

            if(0 < src_write_index)
            {
                memset(&src[src_write_index], 0x00, src_read_index - src_write_index);
                ret = TRUE;
            }
        }
    }

    return ret;
}

uint8_t remove_numeric_string_chars( char * src )
{
    uint8_t string_length = 0;
    uint8_t ret = FALSE;

    if(NULL != src)
    {
        string_length = strlen(src);

        if(0 < string_length)
        {
            ret = remove_numeric_ascii_chars(src, string_length);
        }
    }

    return ret;
}
#endif

#if(UTIL_USE_ASCII_CONVERSION == 1)
void ascii_to_lower_case( char *src, uint8_t ascii_length )
{
    uint8_t src_idx = 0;

    if(NULL != src)
    {
        do
        {
            if((*src >= 'A') && (*src <= 'Z'))
            {
                *src = ('a' + (*src - 'A'));
            }
            src++;
        }
        while(src_idx++ < ascii_length);
    }
}

void string_to_lower_case( char * src )
{
    if(NULL != src)
    {
        uint8_t string_length = 0;

        string_length = strlen(src);

        if(0 < string_length)
        {
            ascii_to_lower_case(src,string_length);
        }
    }
}

void ascii_to_upper_case( char * src, uint8_t ascii_length )
{
    uint8_t src_idx = 0;

    if(NULL != src)
    {
        do
        {
            if((*src >= 'a') && (*src <= 'z'))
            {
                *src = (*src - ('a' - 'A'));
            }
            src++;
        }
        while(src_idx++ < ascii_length);
    }
}

void string_to_upper_case( char *src )
{
    if(NULL != src)
    {
        uint8_t string_length = 0;

        string_length = strlen(src);

        if(0 < string_length)
        {
            ascii_to_upper_case(src,string_length);
        }
    }
}
#endif

#if (UTIL_USE_ENDIAN_SWAP == 1)
void endian_swap_uint64( uint64_t * dest, uint64_t * src )
{
    if((NULL != dest) && (NULL != src))
    {
        uint8_t * dest_ptr;
        uint8_t * src_ptr;

        dest_ptr = (uint8_t *) dest;
        src_ptr = (uint8_t *) src;

        dest_ptr[0] = src_ptr[7];
        dest_ptr[1] = src_ptr[6];
        dest_ptr[2] = src_ptr[5];
        dest_ptr[3] = src_ptr[4];
        dest_ptr[4] = src_ptr[3];
        dest_ptr[5] = src_ptr[2];
        dest_ptr[6] = src_ptr[1];
        dest_ptr[7] = src_ptr[0];
    }
}

uint8_t * endian_swap_uint64_to_ptr( uint8_t * dest, uint64_t src )
{
    uint8_t * ret = NULL;

    if(NULL != dest)
    {
        uint8_t *src_ptr;

        src_ptr = (uint8_t *) &src;

        dest[0] = src_ptr[7];
        dest[1] = src_ptr[6];
        dest[2] = src_ptr[5];
        dest[3] = src_ptr[4];
        dest[4] = src_ptr[3];
        dest[5] = src_ptr[2];
        dest[6] = src_ptr[1];
        dest[7] = src_ptr[0];

        ret = (dest + 8);
    }

    return ret;
}

uint8_t * endian_swap_ptr_to_uint64( uint64_t * dest, uint8_t * src )
{
    uint8_t * ret = NULL;

    if((NULL != dest) && (NULL != src))
    {
        uint8_t * dest_ptr;

        dest_ptr = (uint8_t *) dest;

        dest_ptr[0] = src[7];
        dest_ptr[1] = src[6];
        dest_ptr[2] = src[5];
        dest_ptr[3] = src[4];
        dest_ptr[4] = src[3];
        dest_ptr[5] = src[2];
        dest_ptr[6] = src[1];
        dest_ptr[7] = src[0];

        ret = (src + 8);
    }

    return ret;
}
#ifdef REV_SUPPORT
inline uint32_t endian_swap_uint32( uint32_t src )
#else
uint32_t endian_swap_uint32( uint32_t src )
#endif
{
#ifdef REV_SUPPORT
    return __REV(src);
#else
    uint8_t *dest_ptr, *src_ptr;
    uint32_t dest;

    dest_ptr = (uint8_t *) &dest;
    src_ptr = (uint8_t *) &src;

    dest_ptr[0] = src_ptr[3];
    dest_ptr[1] = src_ptr[2];
    dest_ptr[2] = src_ptr[1];
    dest_ptr[3] = src_ptr[0];

    return dest;
#endif
}

uint8_t * endian_swap_uint32_to_ptr( uint8_t *dest, uint32_t src)
{
    uint8_t * ret = NULL;

    if(NULL != dest)
    {
        uint8_t * src_ptr;

        src_ptr = (uint8_t *) &src;

        dest[0] = src_ptr[3];
        dest[1] = src_ptr[2];
        dest[2] = src_ptr[1];
        dest[3] = src_ptr[0];

        ret = (dest + 4);
    }

    return ret;
}

uint8_t * endian_swap_ptr_to_uint32( uint32_t *dest , uint8_t *src)
{
    uint8_t * ret = NULL;

    if((NULL != dest) && (NULL != src))
    {
        uint8_t *dest_ptr;

        dest_ptr = (uint8_t *) dest;

        dest_ptr[0] = src[3];
        dest_ptr[1] = src[2];
        dest_ptr[2] = src[1];
        dest_ptr[3] = src[0];

        ret = (src + 4);
    }

    return ret;
}

#ifdef REV_SUPPORT
inline uint16_t endian_swap_uint16( uint16_t src )
#else
uint16_t endian_swap_uint16( uint16_t src )
#endif
{
#ifdef REV_SUPPORT
    return ((uint16_t)__REV16(src));
#else
    uint8_t *dest_ptr, *src_ptr;
    uint16_t dest;

    dest_ptr = (uint8_t *) &dest;
    src_ptr = (uint8_t *) &src;

    dest_ptr[0] = src_ptr[1];
    dest_ptr[1] = src_ptr[0];

    return dest;
#endif
}

uint8_t * endian_swap_uint16_to_ptr( uint8_t *dest, uint16_t src )
{
    uint8_t * ret = NULL;

    if(NULL != dest)
    {
        uint8_t * src_ptr;

        src_ptr = (uint8_t *) &src;

        dest[0] = src_ptr[1];
        dest[1] = src_ptr[0];

        ret = (dest + 2);
    }

    return ret;
}

uint8_t * endian_swap_ptr_to_uint16( uint16_t *dest, uint8_t *src )
{
    uint8_t * ret = NULL;

    if((NULL != dest) && (NULL != src))
    {
        *dest = (uint16_t) src[0];

        *dest <<= 8;
        *dest |= src[1];

        ret = (src + 2);
    }

    return ret;
}

uint8_t * endian_swap_uint8_to_ptr( uint8_t * dest, uint8_t src )
{
    uint8_t * ret = NULL;

    if(NULL != dest)
    {
        *dest = src;
        ret = (dest + 1);
    }

    return ret;
}

uint8_t * endian_swap_ptr_to_uint8( uint8_t *dest, uint8_t *src )
{
    uint8_t * ret = NULL;
    if(NULL != dest)
    {
        *dest = *src;
        ret = (src + 1);
    }

    return ret;
}
#endif

#if(UTIL_USE_SEARCH_ASCII == 1)
char * find_first_numeric_char_ascii( char * src, int len )
{
    char * src_ptr = NULL;

    if(NULL != src)
    {
        int idx = 0;
        src_ptr = src;

        while((idx < len) && (FALSE == is_dec_digit(*src_ptr)))
        {
            if(*src_ptr == 0)
            {
                idx = len;
            }
            else
            {
                src_ptr++;
                idx++;
            }
        }

        if(idx == len)
        {
            src_ptr = NULL;
        }
    }

    return (src_ptr);
}

char * find_first_numeric_char_string( char * src )
{
    char * src_ptr = NULL;

    if(src != NULL)
    {
        short string_length = strlen(src);

        if(0 < string_length)
        {
            src_ptr = find_first_numeric_char_ascii(src,string_length);
        }
    }

    return src_ptr;
}
#endif

int find_next_index( int current_idx, int low_limit, int high_limit )
{
    current_idx++;

    if(current_idx >= high_limit)
    {
        current_idx = low_limit;
    }

    return (current_idx);
}

int find_prev_index( int current_idx, int low_limit, int high_limit )
{
    current_idx--;

    if(current_idx < low_limit)
    {
        current_idx = high_limit - 1;
    }

    return (current_idx);
}

char *strpbrk_p( char *stringp, const char *delim )
{
    char *ret = NULL;

    if(delim != NULL)
    {
        int delim_size = strlen(delim);
        char ch = delim[0];

        while(stringp != NULL)
        {
            if((stringp = strchr(stringp, ch)) != NULL)
            {
                if(strncmp(stringp, delim, delim_size) == 0)
                {
                    ret = stringp;
                    break;
                }
                else
                {
                    stringp++; // past ch
                }
            }
        }
    }
    return (ret);
}

char *strchr_p( char *haystack, char needle )
{
    if(needle == 0)
    {
        haystack = NULL;
    }
    else if(haystack)
    {
        while(*haystack != needle)
        {
            if(*haystack == 0)
            {
                haystack = NULL;
                break;
            }
            haystack++;
        }
    }
    return (haystack);
}

char *strsep_d( char **stringp, const char *delim, char delim_and )
{
    char *begin = NULL;

    // if NULL passed in from any pointer,
    // return NULL, else parse stringp
    if((*stringp != NULL) && (delim != NULL))
    {
        char *end = NULL;
        char ch = delim[0];

        begin = *stringp;
        if((delim[0] == '\0') || (delim[1] == '\0'))
        {
            // empty or single char delim
            if(ch == '\0')
            {
                // empty delim - change stringp to NULL,
                //               and since begin points
                //               to stringp, return NULL
                end = NULL;
            }
            else
            {
                if(*begin == ch)
                {
                    // stringp starts with delim -
                    //      return empty string,
                    //      stringp -> stringp[1]
                    end = begin;
                }
                else if(*begin == '\0')
                {
                    // empty stringp - change stringp to NULL,
                    //                 and since begin points
                    //                 to stringp, return NULL
                    end = NULL;
                }
                else
                {
                    // strchr returns pointer to
                    // delim in stringp, or NULL.
                    // start search at stringp[1]
                    // since we checked for first char
                    // being the delim up above
                    end = strchr_p(begin + 1, ch);
                }
            }
        }
        else if(!delim_and)
        {
            // multi char delim - handle as any char match
            // strpbrk returns pointer to delim in stringp, or NULL.
            end = strpbrk(begin, delim);
        }
        else
        {
            // multi char delim - handle as all char match
            // find entire delim in stringp
            end = strpbrk_p(begin, delim);
            if(end != NULL)
            {
                int idx;
                int delim_size = strlen(delim);

                // NULL out delim in stringp except last char -
                // then final cleanup will set to desired result
                for(idx = 0; idx < delim_size - 1; idx++)
                {
                    *end++ = '\0';
                }
            }
        }

        // Final Cleanup - if end points to a valid char, empty it
        //                 and set stringp to end + 1, otherwise
        //                 set stringp to NULL
        if(end)
        {
            *end++ = '\0';
            *stringp = end;
        }
        else
        {
            *stringp = NULL;
        }
    }

    // if input parameters were valid and delim was found,
    // begin will be start of original stringp,
    // otherwise it is NULL
    return begin;
}

char *strsep( char **stringp, const char *delim )
{
    return (strsep_d(stringp, delim, 0));
}

void dsml_printf(char *dest, char *fmt, va_list args, int maxlen)
{
    dvsprintf_maxlen(dest, fmt, args, NULL);
}

void dsml_printf_dvs(char *dest, char *fmt, va_list args, DVS_STACK *dvs)
{
    dvsprintf_maxlen(dest, fmt, args, dvs);
}

void dsprintf( char * dest, char *fmt, ... )
{
    va_list args;

    va_start(args, fmt);
    dvsprintf(dest, fmt, args);
    va_end(args);
}

void filter_for_ascii( char *victim, uint8_t maxlen, char canonical )
{
    if(victim)
    {
        int valid_idx = 0;
        int read_idx = 0;
        char cur_char = 32; // start with SPACE

        while((read_idx < maxlen) && (cur_char != 0))
        {
            cur_char = victim[read_idx++];
            // accept : valid ascii from SPACE thru tilde,
            //          NULL char, or if canonical,
            //          backspace thru carriage ret
            if(((cur_char >= 32) && (cur_char <= 126)) || (cur_char == 0) || ((canonical) && (cur_char >= 8) && (cur_char <= 13)))
            {
                victim[valid_idx++] = cur_char;
            }
        }
    }
}

// filter dest non-ascii and backspace, newlines, etc
void filter_for_noncanonical_ascii( char *victim, uint8_t maxlen )
{
    filter_for_ascii(victim, maxlen, 0);
}

// filter dest non-ascii only
void filter_for_canonical_ascii( char *victim, uint8_t maxlen )
{
    filter_for_ascii(victim, maxlen, 1);
}

int validate_ip( const char *src, int len )
{
    int goodlen = 0;
    int num_dots = 0;
    int got_number = 0;

    while(len-- > 0)
    {
        if((*src < '0') || (*src > '9'))
        {
            if(got_number)
            { // look for a dot
                if(num_dots == 3)
                {
                    // previously we got a number after the last dot,
                    // this is the first non-number,
                    // string valid and complete
                    break;
                }
                else if((num_dots < 3) && (*src == '.'))
                {
                    // one of three dots found, count in the length,
                    // count in the dots, and start looking
                    // for a number again
                    goodlen++;
                    num_dots++;
                    got_number = 0;
                }
                else
                {
                    // not enough dots found before
                    // non-number found; bad string
                    len = 0;
                    goodlen = 0;
                }
            }
            else
            {
                // got non-number before a number or dot; bad string
                len = 0;
                goodlen = 0;
            }
        }
        else
        {
            // number found;
            // count in the length and flag it
            goodlen++;
            got_number = 1;
        }
        src++;
    }

    if((got_number == 0) || (num_dots != 3))
    {
        goodlen = 0;
    }

    return (goodlen);
}

/*****************************************************************************
 * @brief   copy number of Strings
 * @param   initial destination
 * @param   array of Strings to copy
 * @param   number of Strings to copy
 * @return  final destination
 *****************************************************************************/
char *copyStrings(char *dest, const char **src, uint8_t len_src)
{
    int idx;

    if ((dest) && (src)) {
        for (idx=0; idx<len_src; idx++) {
            if (src[idx]) {
                strcpy(dest, src[idx]);
                dest += strlen(src[idx]);
            }
        }
    }
    return(dest);
}

/*************************************************************************
 * @brief   calculate digits necessary to print 32 bit hex value
 * @param   value to calculate from
 * @return  2, 4, 6, or 8
 *************************************************************************/
uint8_t calc_hex_precision(long value)
{
    uint8_t precision_needed = 2;
    uint8_t number_digits = 0;

    while ((value != 0) && (number_digits++ < 8)) value >>= 4;

    if (number_digits > 2) {
        if (number_digits > 4) {
            if (number_digits > 6) {    // 7 or 8
                precision_needed = 8;
            } else {                    // 5 or 6
                precision_needed = 6;
            }
        } else {                        // 3 or 4
            precision_needed = 4;
        }
    } else {                            // 1 or 2
        precision_needed = 2;
    }

    return(precision_needed);
}

void add_string(char *buff, char *addstr, int maxlen) {
    if ((strlen(buff) + strlen(addstr)) < maxlen) {
        strcpy(buff + strlen(buff), addstr);
    }
}

void add_string_on_off(char *buff, uint8_t tst, int maxlen) {
    if (tst) {
        add_string(buff, "ON", maxlen);
    } else {
        add_string(buff, "OFF", maxlen);
    }
}

const char *get_newline_s() { return ("\r\n"); }

char *format_version(char *dn_ptr, uint32_t div_value, uint32_t dlv) {
    if (dn_ptr) {
        int download_byte;

        while (div_value > 0) {
            if (div_value > 99) {
                download_byte = dlv/div_value;
            } else {
                download_byte = dlv;
            }
            if (download_byte < 10) {
                *dn_ptr++ = '0';
            } else {
                *dn_ptr++ = download_byte/10 + '0';
                download_byte %= 10;
            }
            *dn_ptr++ = download_byte + '0';
            if (div_value > 1) {
                *dn_ptr++ = '.';
            }
            if (div_value > 99) dlv %= div_value;
            div_value /= 100;
        }
    }

    return(dn_ptr);
}

char hexchar_to_ascii(char src) {
    char ret = '0';
    if (src < 10) {
        if (src >= 0) {
            ret = src + '0';
        }
    } else if (src < 16) {
        ret = (src - 10) + 'A';
    }
    return(ret);
}

char *toLowerCase(char *buff, int len) {
    char *ret_buff = buff;

    if (buff) {
        int idx;

        for(idx=0; idx<len && *buff; idx++, buff++) {
            char bc = *buff;

            if ((bc >= 'A') && (bc <= 'Z')) {
                *buff = 'a' + (bc - 'A');
            }
        }
    }

    return(ret_buff);
}

/*****************************************************************************
 * @brief       A simple, small integer base pow function.
 * @param       uint32_t base - unsigned base value
 * @param       uint8_t power - unsigned power value
 * @return      uint32_t of base to the power
 * @note        This function does not handle overflow
 *****************************************************************************/
uint32_t calc_pow(uint32_t base, uint8_t power)
{
    uint32_t value;
    uint32_t prev_value;

    for (value = 1; power > 0; power--)
    {
        prev_value = value;
        value *= base;
        if (value < prev_value)
        {
            // overflow occurred
            value = 0;
            break;
        }
    }

    return value;
}

uint8_t num_of_bytes_in_uint32(uint32_t data)
{
    uint8_t ret = 0;
    if(VALUE_4BYTES(data))
    {
        ret = 4;
    }
    else if(VALUE_3BYTES(data))
    {
        ret = 3;
    }
    else if(VALUE_2BYTES(data))
    {
        ret = 2;
    }
    else if(VALUE_1BYTES(data))
    {
        ret = 1;
    }
    return ret;
}

uint32_t endian_swap_and_fit_uint32( uint32_t src, uint8_t len )
{
    uint8_t *dest_ptr, *src_ptr;
    uint32_t dest = 0x00000000;
    uint8_t i = 0;
    dest_ptr = (uint8_t *) &dest;
    src_ptr = (uint8_t *) &src;

    if((len > 4) | (len == 0))
    {
        len = 4;
    }

    for(i = 0; i < len; i++)
    {
        dest_ptr[i] = src_ptr[len - (1 + i)];
    }

    return dest;
}

void append_ascii_hex_to_buffer(uint8_t* buff, uint8_t* data, uint16_t len)
{
	uint8_t lsb, msb;
	uint16_t idx = 0;
	uint8_t* buff_ptr;
	uint8_t* data_ptr;
	char cur_char;

	if((NULL != buff) && (NULL != data))
	{
		buff_ptr = buff;
		data_ptr = data;

		/* Add HEX version of data */
		for (idx = 0; idx < len; idx++, data_ptr++)
		{
			lsb = *data_ptr & 0x0F;
			msb = (*data_ptr >> 4) & 0x0F;

			if((0x09 >= lsb) && (0x00 <= lsb))
			{
				lsb = (uint8_t)(lsb + '0');
			}
			else if((0x0F >= lsb) && (0x0A <= lsb))
			{
				lsb = (uint8_t)((lsb - 0xA) + 'A');
			}

			if((0x09 >= msb) && (0x00 <= msb))
			{
				msb = (uint8_t)(msb + '0');
			}
			else if((0x0F >= msb) && (0x0A <= msb))
			{
				msb = (uint8_t)((msb - 0xA) + 'A');
			}

			*buff_ptr++ = msb;
			*buff_ptr++ = lsb;

			if(idx+1 < len)
			{
				*buff_ptr++ = ':';
			}
			else
			{
				*buff_ptr++ = ' ';
			}
		}

		/* Reset data pointer */
		data_ptr = data;

		/* Add ASCII version of data */
		*buff_ptr++ = '[';
		for(idx = 0; idx < len; idx++)
		{
			cur_char = *data_ptr++;

			/* Replace non-ASCII chars */
			if(!((cur_char >= ' ') && (cur_char <= '~')))
			{
				cur_char = '.';
			}

			*buff_ptr++ = cur_char;
		}
		*buff_ptr++ = ']';
	}

}
