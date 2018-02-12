/*****************************************************************************//**
 * @file    utils.h
 * @brief   General Purpose Utilities Header File
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
/*****************************************************************************/
#ifndef _UTILS_H_
#define _UTILS_H_
/*****************************************************************************
 * Inclusion Dependencies
 *****************************************************************************/
#include <stdio.h>
#include <stdarg.h>

/*****************************************************************************
 * Macros
 *****************************************************************************/
#define TRUE 1
#define FALSE 0

#define ABS(x)    (((x) < 0) ? -(x) : (x))          /**< */
#define MAX(a,b)  ((a < b) ? (b) : (a))             /**< */
#define MIN(a,b)  ((a < b) ? (a) : (b))             /**< */
#define SIGN(x,y) (((y) < 0) ? (-(abs(x))): (abs(x)))   /**< */
#define ARRAYSIZE(x)    (sizeof(x)/sizeof(x[0]))

#define UTIL_USE_ASCII_TO_DEC           (1)     /**< */
#define UTIL_USE_DEC_TO_ASCII           (1)     /**< */
#define UTIL_USE_STRING_TO_DEC          (1)     /**< */
#define UTIL_USE_DEC_TO_STRING          (1)     /**< */
#define UTIL_USE_DEC_TO_HEX_ASCII       (1)     /**< */
#define UTIL_USE_DEC_TO_HEX_STRING      (0)     /**< */
#define UTIL_USE_REMOVE_ASCII           (0)     /**< */
#define UTIL_USE_ASCII_CHECK            (1)     /**< */
#define UTIL_USE_ASCII_CONVERSION       (1)     /**< */
#define UTIL_USE_ENDIAN_SWAP            (1)     /**< */
#define UTIL_USE_ENDIAN_ARRAY_SWAP      (0)     /**< */
#define UTIL_USE_DEC_TO_ASCII_PTR       (1)     /**< */
#define UTIL_USE_DEC_TO_HEX_ASCII_PTR   (1)     /**< */
#define UTIL_USE_SEARCH_ASCII           (0)     /**< */
#define UTIL_USE_ASCII_TO_HEX           (0)     /**< */
#define UTIL_USE_HEX_TO_ASCII           (0)     /**< */

#define UTIL_HEX_BYTE_STRING_LENGTH     (2)     /**< */
#define UTIL_HEX_SHORT_STRING_LENGTH    (4)     /**< */
#define UTIL_HEX_INT_STRING_LENGTH      (8)     /**< */
#define UTIL_HEX_LONG_STRING_LENGTH     (16)    /**< */

#define UTIL_HEX_X_STRING_FORMAT        (1)     /**< */
#define UTIL_HEX_0X_STRING_FORMAT       (2)     /**< */
#define UTIL_HEX_STRING_FORMAT          (3)     /**< */
#define UTIL_DEC_STRING_FORMAT          (4)     /**< */

#define UTIL_ALPHA_LOWER_CASE           (1)     /**< */
#define UTIL_ALPHA_UPPER_CASE           (2)     /**< */

#define UTIL_MAX_UINT8                  (0xFF)
#define UTIL_MAX_UINT16                 (0xFFFF)
#define UTIL_MAX_UINT32                 (0xFFFFFFFF)
#define UTIL_MAX_UINT64                 (0xFFFFFFFFFFFFFFFF)
#define UTIL_MAX_INT8                   (0x7F)
#define UTIL_MAX_INT16                  (0x7FFF)
#define UTIL_MAX_INT32                  (0x7FFFFFFF)
#define UTIL_MAX_INT64                  (0x7FFFFFFFFFFFFFFF)
#define UTIL_MIN_INT8                   (-128LL)
#define UTIL_MIN_INT16                  (-32768LL)
#define UTIL_MIN_INT32                  (-2147483648LL)
#define UTIL_MIN_INT64                  (-9223372036854775808LL)

#define VALUE_4BYTES(x) ((x <= 0xFFFFFFFF) && ( x > 0x00FFFFFF))
#define VALUE_3BYTES(x) ((x <= 0x00FFFFFF) && ( x > 0x0000FFFF))
#define VALUE_2BYTES(x) ((x <= 0x0000FFFF) && ( x > 0x000000FF))
#define VALUE_1BYTES(x) ((x <= 0x000000FF) && ( x > 0x00000000))

#ifndef DVS_STACK_DEF
#define DVS_STACK_DEF
typedef struct dvs_stack {
    long long l;
    unsigned long long u;

    char *p;
    char *maxdest;
    char *logqslot;
    int cur_time;
    int maxlen;

    unsigned char precision;
    char c;
    char lng;
    char checksize;

    char precision_found;
    char in_use;
} DVS_STACK;
#endif

/*****************************************************************************
 * Global Declarations
 *****************************************************************************/
/*****************************************************************************
 * Public Function Prototypes
 *****************************************************************************/
#if (UTIL_USE_DEC_TO_ASCII == 1)
/*****************************************************************************//**
 * @brief       Converts a int8_t value to ascii chars (No NULL Terminator)
 * @param       *dest - character array to store the converted ascii chars
 * @param       *src - source signed char value to convert to ascii chars
 * @retval      The number of characters written to the ascii buffer
 *****************************************************************************/
uint8_t int8_to_ascii( char *dest, int8_t src );
char hexchar_to_ascii(char src);
/*****************************************************************************//**
 * @brief       Converts a int16_t value to ascii chars (No NULL Terminator)
 * @param       *dest - character array to store the converted ascii chars
 * @param       *src - source signed short value to convert to ascii chars
 * @retval      The number of characters written to the ascii buffer
 *****************************************************************************/
uint8_t int16_to_ascii( char *dest, int16_t src );
/*****************************************************************************//**
 * @brief       Converts a int32_t value to ascii chars (No NULL Terminator)
 * @param       *dest - character array to store the converted ascii chars
 * @param       *src - source signed int value to convert to ascii chars
 * @retval      The number of characters written to the ascii buffer
 *****************************************************************************/
uint8_t int32_to_ascii( char *dest, int32_t src );
/*****************************************************************************//**
 * @brief       Converts a int64_t value to ascii chars (No NULL Terminator)
 * @param       *dest - character array to store the converted ascii chars
 * @param       *src - source signed long value to convert to ascii chars
 * @retval      The number of characters written to the ascii buffer
 *****************************************************************************/
uint8_t int64_to_ascii( char *dest, int64_t src );
/*****************************************************************************//**
 * @brief       Converts a uint8_t value to ascii chars (No NULL Terminator)
 * @param       *dest - character array to store the converted ascii chars
 * @param       *src - source unsigned char value to convert to ascii chars
 * @retval      The number of characters written to the ascii buffer
 *****************************************************************************/
uint8_t uint8_to_ascii( char *dest, uint8_t src );
/*****************************************************************************//**
 * @brief       Converts a uint16_t value to ascii chars (No NULL Terminator)
 * @param       *dest - character array to store the converted ascii chars
 * @param       *src - source unsigned short value to convert to ascii chars
 * @retval      The number of characters written to the ascii buffer
 *****************************************************************************/
uint8_t uint16_to_ascii( char *dest, uint16_t src );
/*****************************************************************************//**
 * @brief       Converts a uint32_t value to ascii chars (No NULL Terminator)
 * @param       *dest - character array to store the converted ascii chars
 * @param       *src - source unsigned int value to convert to ascii chars
 * @retval      The number of characters written to the ascii buffer
 *****************************************************************************/
uint8_t uint32_to_ascii( char *dest, uint32_t src );
/*****************************************************************************//**
 * @brief       Converts a uint64_t value to ascii chars (No NULL Terminator)
 * @param       *dest - character array to store the converted ascii chars
 * @param       *src - source unsigned long value to convert to ascii chars
 * @retval      The number of characters written to the ascii buffer
 *****************************************************************************/
uint8_t uint64_to_ascii( char *dest, uint64_t src );
#endif

#if ((UTIL_USE_DEC_TO_STRING == 1) && (UTIL_USE_DEC_TO_ASCII == 1))
/*****************************************************************************//**
 * @brief       Converts a int8_t value to a NULL terminated ascii string
 * @param       *dest - character array to store the converted ascii string
 * @param       *src - source signed char value to convert to ascii string
 * @retval      The number of characters written to the ascii string
 *****************************************************************************/
uint8_t int8_to_string( char *dest, int8_t src );
/*****************************************************************************//**
 * @brief       Converts a int16_t value to a NULL terminated ascii string
 * @param       *dest - character array to store the converted ascii string
 * @param       *src - source signed short value to convert to ascii string
 * @retval      The number of characters written to the ascii string
 *****************************************************************************/
uint8_t int16_to_string( char *dest, int16_t src );
/*****************************************************************************//**
 * @brief       Converts a int32_t value to a NULL terminated ascii string
 * @param       *dest - character array to store the converted ascii string
 * @param       *src - source signed int value to convert to ascii string
 * @retval      The number of characters written to the ascii string
 *****************************************************************************/
uint8_t int32_to_string( char *dest, int32_t src );
/*****************************************************************************//**
 * @brief       Converts a int64_t value to a NULL terminated ascii string
 * @param       *dest - character array to store the converted ascii string
 * @param       *src - source signed long value to convert to ascii string
 * @retval      The number of characters written to the ascii string
 *****************************************************************************/
uint8_t int64_to_string( char *dest, int64_t src );
/*****************************************************************************//**
 * @brief       Converts a uint8_t value to a NULL terminated ascii string
 * @param       *dest - character array to store the converted ascii string
 * @param       *src - source unsigned char value to convert to ascii string
 * @retval      The number of characters written to the ascii string
 *****************************************************************************/
uint8_t uint8_to_string( char *dest, uint8_t src );
/*****************************************************************************//**
 * @brief       Converts a uint16_t value to a NULL terminated ascii string
 * @param       *dest - character array to store the converted ascii string
 * @param       *src - source unsigned short value to convert to ascii string
 * @retval      The number of characters written to the ascii string
 *****************************************************************************/
uint8_t uint16_to_string( char *dest, uint16_t src );
/*****************************************************************************//**
 * @brief       Converts a uint32_t value to a NULL terminated ascii string
 * @param       *dest - character array to store the converted ascii string
 * @param       *src - source unsigned int value to convert to ascii string
 * @retval      The number of characters written to the ascii string
 *****************************************************************************/
uint8_t uint32_to_string( char *dest, uint32_t src );
/*****************************************************************************//**
 * @brief       Converts a uint64_t value to a NULL terminated ascii string
 * @param       *dest - character array to store the converted ascii string
 * @param       *src - source unsigned long value to convert to ascii string
 * @retval      The number of characters written to the ascii string
 *****************************************************************************/
uint8_t uint64_to_string( char *dest, uint64_t src );
#endif
#if((UTIL_USE_DEC_TO_HEX_ASCII == 1) && (UTIL_USE_DEC_TO_ASCII == 1))
/*****************************************************************************//**
 * @brief       Converts a uint64_t value to hex ascii chars (No NULL Terminator)
 * @param       *dest - character array to store the converted ascii chars
 * @param       *src - source unsigned long value to convert hex ascii chars
 * @param       precision - number of hex digits to represent in the hex ascii chars
 *****************************************************************************/
void unsigned_decimal_to_hex_ascii( char *dest, uint64_t src, uint8_t precision );
/*****************************************************************************//**
 * @brief       Converts a uint8_t value to hex ascii (No NULL Terminator)
 * @param       *dest - character array to store the converted hex ascii
 * @param       *src - source unsigned char value to convert to hex ascii
 * @retval      the number of bytes written to the ascii buffer
 *****************************************************************************/
uint8_t uint8_to_hex_ascii( char *dest, uint8_t src );
/*****************************************************************************//**
 * @brief       Converts a uint16_t value to hex ascii (No NULL Terminator)
 * @param       *dest - character array to store the converted hex ascii
 * @param       *src - source unsigned short value to convert to hex ascii
 * @retval      The number of bytes written to the ascii buffer
 *****************************************************************************/
uint8_t uint16_to_hex_ascii( char *dest, uint16_t src );
/*****************************************************************************//**
 * @brief       Converts a uint32_t value to hex ascii (No NULL Terminator)
 * @param       *dest - character array to store the converted hex ascii
 * @param       *src - source unsigned int value to convert to hex ascii
 * @retval      The number of bytes written to the ascii buffer
 *****************************************************************************/
uint8_t uint32_to_hex_ascii( char *dest, uint32_t src );
/*****************************************************************************//**
 * @brief       Converts a uint64_t value to hex ascii (No NULL Terminator)
 * @param       *dest - character array to store the converted hex ascii
 * @param       *src - source unsigned long value to convert to hex ascii
 * @retval      The number of bytes written to the ascii buffer
 *****************************************************************************/
uint8_t uint64_to_hex_ascii( char *dest, uint64_t src );
#endif

#if((UTIL_USE_DEC_TO_HEX_STRING == 1) && (UTIL_USE_DEC_TO_HEX_ASCII == 1))
/*****************************************************************************//**
 * @brief       Converts a uint64_t value to hex NULL terminated string
 * @param       *dest - character array to store the converted string chars
 * @param       *src - source unsigned long value to convert hex string chars
 * @param       precision - number of hex digits to represent in the hex ascii chars
 *****************************************************************************/
void unsigned_decimal_to_hex_string( char *dest, uint64_t src, uint8_t precision );
/*****************************************************************************//**
 * @brief       Converts a uint8_t value to a NULL terminated string
 * @param       *src - source value to convert
 * @param       *dest - character array to store the converted string
 * @retval      The number of characters written to the hex string
 *****************************************************************************/
uint8_t uint8_to_hex_string( char *dest, uint8_t src );
/*****************************************************************************//**
 * @brief       Converts a uint16_t value to a NULL terminated string
 * @param       *src - source value to convert
 * @param       *dest - character array to store the converted string
 * @retval      The number of characters written to the hex string
 *****************************************************************************/
uint8_t uint16_to_hex_string( char *dest, uint16_t src );
/*****************************************************************************//**
 * @brief       Converts a uint32_t value to a NULL terminated string
 * @param       *src - source value to convert
 * @param       *dest - character array to store the converted string
 * @retval      The number of characters written to the hex string
 *****************************************************************************/
uint8_t uint32_to_hex_string( char *dest, uint32_t src );
/*****************************************************************************//**
 * @brief       Converts a uint64_t value to a NULL terminated string
 * @param       *src - source value to convert
 * @param       *dest - character array to store the converted string
 * @retval      The number of characters written to the hex string
 *****************************************************************************/
uint8_t uint64_to_hex_string( char *dest, uint64_t src );
#endif

#if(UTIL_USE_REMOVE_ASCII == 1)
/*****************************************************************************//**
 * @brief       Removes all non numeric characters from a character buffer
 * @param       *src - source buffer to remove characters
 * @param       length - number of characters to check
 * @retval      TRUE - ascii non numeric characters removed
 * @retval      FALSE - invalid input parameter specified
 *****************************************************************************/
uint8_t remove_non_numeric_ascii_chars( char *src, uint16_t length );
/*****************************************************************************//**
 * @brief       Removes all numeric characters from a character buffer
 * @param       *src - source buffer to remove characters
 * @param       length - number of characters to check
 * @retval      TRUE - ascii numeric characters removed
 * @retval      FALSE - invalid input parameter specified
 *****************************************************************************/
uint8_t remove_numeric_ascii_chars( char *src, uint32_t length );
/*****************************************************************************//**
 * @brief       Removes all non numeric characters from a character string
 * @param       *src - source string to remove characters
 * @retval      TRUE - ascii non numeric characters removed
 * @retval      FALSE - invalid input parameter specified
 *****************************************************************************/
uint8_t remove_non_numeric_string_chars( char *src );
/*****************************************************************************//**
 * @brief       Removes all numeric characters from a character string
 * @param       *src - source string to remove characters
 * @retval      TRUE - ascii non numeric characters removed
 * @retval      FALSE - invalid input parameter specified
 *****************************************************************************/
uint8_t remove_numeric_string_chars( char *src );
#endif

#if(UTIL_USE_ASCII_CHECK == 1)
/*****************************************************************************//**
 * @brief       Figures out if the input character is a valid ascii alphabet character
 * @param       character - ascii character to check
 * @retval      TRUE - the input character is an ascii alphabet character
 * @retval      FALSE - the input character is not an ascii alphabet character
 *****************************************************************************/
uint8_t is_ascii_char( char character );
/*****************************************************************************//**
 * @brief       Figures out if the input character is a valid hex ascii character
 * @param       character - ascii character to check
 * @retval      TRUE - the input character is a hex ascii alphabet character
 * @retval      FALSE - the input character is not a hex ascii alphabet character
 *****************************************************************************/
uint8_t is_hex_digit( char character );
/*****************************************************************************//**
 * @brief       Figures out if the input character is a valid dec ascii digit
 * @param       character - ascii character to check
 * @retval      TRUE - the input character is a dec ascii digit
 * @retval      FALSE - the input character is not a dec ascii digit
 *****************************************************************************/
uint8_t is_dec_digit( char character );
/*****************************************************************************//**
 * @brief       Figures out if the input character is a valid number string
 * @param       *src - ascii string to check
 * @retval      UTIL_HEX_X_STRING_FORMAT - the source string is a hex string with x format
 * @retval      UTIL_HEX_0X_STRING_FORMAT - the source string is a hex string with 0x format
 * @retval      UTIL_HEX_STRING_FORMAT - the source string is a hex string
 * @retval      UTIL_DEC_STRING_FORMAT - the source string is a decimal string
 * @retval      FALSE - the source string is not a valid number string
 *****************************************************************************/
uint8_t is_number_string( char *src );
/*****************************************************************************//**
 * @brief       Figures out if the input character is a valid number group of ascii characters
 * @param       *src - ascii to check
 * @param       string_length - number of ascii characters to scan
 * @retval      UTIL_HEX_X_STRING_FORMAT - the source string is a hex string with x format
 * @retval      UTIL_HEX_0X_STRING_FORMAT - the source string is a hex string with 0x format
 * @retval      UTIL_HEX_STRING_FORMAT - the source string is a hex string
 * @retval      UTIL_DEC_STRING_FORMAT - the source string is a decimal string
 * @retval      FALSE - the source string is not a valid number string
 *****************************************************************************/
uint8_t is_number_ascii( char *src, uint16_t string_length );
/*****************************************************************************//**
 * @brief       Figures out if the input character is an upper case letter
 * @param       character - ascii character to check
 * @retval      TRUE - the input character is an upper case alphabet character
 * @retval      FALSE - the input character is not an upper case alphabet character
 *****************************************************************************/
uint8_t is_upper_case( char character );
/*****************************************************************************//**
 * @brief       Figures out if the input character is an lower case letter
 * @param       character - ascii character to check
 * @retval      TRUE - the input character is a lower case alphabet character
 * @retval      FALSE - the input character is not a lower case alphabet character
 *****************************************************************************/
uint8_t is_lower_case( char character );
#endif

#if(UTIL_USE_ASCII_CONVERSION == 1)
/*****************************************************************************//**
 * @brief       Converts ascii alphabet characters in a buffer from upper case to lower case
 * @param       *src - input ascii buffer
 * @param       ascii_length - number of characters to check
 *****************************************************************************/
void ascii_to_lower_case( char *src, uint8_t ascii_length );
/*****************************************************************************//**
 * @brief       Converts ascii alphabet characters in a buffer from lower case to upper case
 * @param       *src - input ascii buffer
 * @param       ascii_length - number of characters to check
 *****************************************************************************/
void ascii_to_upper_case( char *src, uint8_t ascii_length );
/*****************************************************************************//**
 * @brief       Converts ascii alphabet characters in a string from upper case to lower case
 * @param       *src - input ascii string
 * @param       ascii_length - number of characters to check
 *****************************************************************************/
void string_to_lower_case( char *src );
/*****************************************************************************//**
 * @brief       Converts ascii alphabet characters in a string from lower case to upper case
 * @param       *src - input ascii string
 * @param       ascii_length - number of characters to check
 *****************************************************************************/
void string_to_upper_case( char *src );
#endif

#if(UTIL_USE_ASCII_TO_DEC == 1)
/*****************************************************************************//**
 * @brief       Converts ascii characters in a buffer to an int8_t value
 * @param       *dest - int8_t ptr to store the converted value
 * @param       *src - ascii buffer to convert
 * @param       number_of_chars - the number of ascii characters to convert
 * @retval      TRUE - the conversion from ascii to dec was successful
 * @retval      FALSE - the conversion from ascii to dec was unsuccessful
 *****************************************************************************/
uint8_t ascii_to_int8( int8_t * dest, char * src, uint8_t number_of_chars, uint8_t number_string_format );
/*****************************************************************************//**
 * @brief       Converts ascii characters in a buffer to an int16_t value
 * @param       *dest - int16_t ptr to store the converted value
 * @param       *src - ascii buffer to convert
 * @param       number_of_chars - the number of ascii characters to convert
 * @retval      TRUE - the conversion from ascii to dec was successful
 * @retval      FALSE - the conversion from ascii to dec was unsuccessful
 *****************************************************************************/
uint8_t ascii_to_int16( int16_t * dest, char * src, uint8_t number_of_chars, uint8_t number_string_format );
/*****************************************************************************//**
 * @brief       Converts ascii characters in a buffer to an int32_t value
 * @param       *dest - int32_t ptr to store the converted value
 * @param       *src - ascii buffer to convert
 * @param       number_of_chars - the number of ascii characters to convert
 * @retval      TRUE - the conversion from ascii to dec was successful
 * @retval      FALSE - the conversion from ascii to dec was unsuccessful
 *****************************************************************************/
uint8_t ascii_to_int32( int32_t * dest, char * src, uint8_t number_of_chars, uint8_t number_string_format );
/*****************************************************************************//**
 * @brief       Converts ascii characters in a buffer to an int64_t value
 * @param       *dest - int64_t ptr to store the converted value
 * @param       *src - ascii buffer to convert
 * @param       number_of_chars - the number of ascii characters to convert
 * @retval      TRUE - the conversion from ascii to dec was successful
 * @retval      FALSE - the conversion from ascii to dec was unsuccessful
 *****************************************************************************/
uint8_t ascii_to_int64( int64_t * dest, char * src, uint8_t number_of_chars, uint8_t number_string_format );
/*****************************************************************************//**
 * @brief       Converts ascii characters in a buffer to an uint8_t value
 * @param       *dest - uint8_t ptr to store the converted value
 * @param       *src - ascii buffer to convert
 * @param       number_of_chars - the number of ascii characters to convert
 * @retval      TRUE - the conversion from ascii to dec was successful
 * @retval      FALSE - the conversion from ascii to dec was unsuccessful
 *****************************************************************************/
uint8_t ascii_to_uint8( uint8_t *dest, char *src, uint8_t number_of_chars, uint8_t number_string_format );
/*****************************************************************************//**
 * @brief       Converts ascii characters in a buffer to an uint16_t value
 * @param       *dest - int16_t ptr to store the converted value
 * @param       *src - ascii buffer to convert
 * @param       number_of_chars - the number of ascii characters to convert
 * @retval      TRUE - the conversion from ascii to dec was successful
 * @retval      FALSE - the conversion from ascii to dec was unsuccessful
 *****************************************************************************/
uint8_t ascii_to_uint16( uint16_t *dest, char *src, uint8_t number_of_chars, uint8_t number_string_format );
/*****************************************************************************//**
 * @brief       Converts ascii characters in a buffer to an int32_t value
 * @param       *dest - int32_t ptr to store the converted value
 * @param       *src - ascii buffer to convert
 * @param       number_of_chars - the number of ascii characters to convert
 * @retval      TRUE - the conversion from ascii to dec was successful
 * @retval      FALSE - the conversion from ascii to dec was unsuccessful
 *****************************************************************************/
uint8_t ascii_to_uint32( uint32_t *dest, char *src, uint8_t number_of_chars, uint8_t number_string_format );
/*****************************************************************************//**
 * @brief       Converts ascii characters in a buffer to an int64_t value
 * @param       *dest - int64_t ptr to store the converted value
 * @param       *src - ascii buffer to convert
 * @param       number_of_chars - the number of ascii characters to convert
 * @retval      TRUE - the conversion from ascii to dec was successful
 * @retval      FALSE - the conversion from ascii to dec was unsuccessful
 *****************************************************************************/
uint8_t ascii_to_uint64( uint64_t * dest, char * src, uint8_t number_of_chars, uint8_t number_string_format );
#endif

#if((UTIL_USE_STRING_TO_DEC == 1) && (UTIL_USE_ASCII_TO_DEC == 1))
/*****************************************************************************//**
 * @brief       Converts ascii characters in a buffer to an uint8_t value
 * @param       *dest - uint8_t ptr to store the converted value
 * @param       *src - ascii string to convert
 * @retval      TRUE - the conversion from string to dec was successful
 * @retval      FALSE - the conversion from string to dec was unsuccessful
 *****************************************************************************/
uint8_t string_to_uint8( uint8_t * dest, char * src, uint8_t number_string_format );
/*****************************************************************************//**
 * @brief       Converts ascii characters in a buffer to an uint16_t value
 * @param       *dest - uint16_t ptr to store the converted value
 * @param       *src - ascii string to convert
 * @retval      TRUE - the conversion from string to dec was successful
 * @retval      FALSE - the conversion from string to dec was unsuccessful
 *****************************************************************************/
uint8_t string_to_uint16( uint16_t * dest, char * src, uint8_t number_string_format );
/*****************************************************************************//**
 * @brief       Converts ascii characters in a buffer to an uint32_t value
 * @param       *dest - uint32_t ptr to store the converted value
 * @param       *src - ascii string to convert
 * @retval      TRUE - the conversion from string to dec was successful
 * @retval      FALSE - the conversion from string to dec was unsuccessful
 *****************************************************************************/
uint8_t string_to_uint32( uint32_t * dest, char * src, uint8_t number_string_format );
/*****************************************************************************//**
 * @brief       Converts ascii characters in a buffer to an uint64_t value
 * @param       *dest - uint64_t ptr to store the converted value
 * @param       *src - ascii string to convert
 * @retval      TRUE - the conversion from string to dec was successful
 * @retval      FALSE - the conversion from string to dec was unsuccessful
 *****************************************************************************/
uint8_t string_to_uint64( uint64_t * dest, char * src, uint8_t number_string_format );
/*****************************************************************************//**
 * @brief       Converts ascii characters in a buffer to an int8_t value
 * @param       *dest - int8_t ptr to store the converted value
 * @param       *src - ascii string to convert
 * @retval      TRUE - the conversion from string to dec was successful
 * @retval      FALSE - the conversion from string to dec was unsuccessful
 *****************************************************************************/
uint8_t string_to_int8( int8_t * dest, char * src, uint8_t number_string_format );
/*****************************************************************************//**
 * @brief       Converts ascii characters in a buffer to an int16_t value
 * @param       *dest - int16_t ptr to store the converted value
 * @param       *src - ascii string to convert
 * @retval      TRUE - the conversion from string to dec was successful
 * @retval      FALSE - the conversion from string to dec was unsuccessful
 *****************************************************************************/
uint8_t string_to_int16( int16_t * dest, char * src, uint8_t number_string_format );
/*****************************************************************************//**
 * @brief       Converts ascii characters in a buffer to an int32_t value
 * @param       *dest - int32_t ptr to store the converted value
 * @param       *src - ascii string to convert
 * @retval      TRUE - the conversion from string to dec was successful
 * @retval      FALSE - the conversion from string to dec was unsuccessful
 *****************************************************************************/
uint8_t string_to_int32( int32_t * dest, char * src, uint8_t number_string_format );
/*****************************************************************************//**
 * @brief       Converts ascii characters in a buffer to an int64_t value
 * @param       *dest - int64_t ptr to store the converted value
 * @param       *src - ascii string to convert
 * @retval      TRUE - the conversion from string to dec was successful
 * @retval      FALSE - the conversion from string to dec was unsuccessful
 *****************************************************************************/
uint8_t string_to_int64( int64_t * dest, char * src, uint8_t number_string_format );
#endif

#if(UTIL_USE_SEARCH_ASCII == 1)
/*****************************************************************************//**
 * @brief       Find the first ascii number in an ascii buffer
 * @param       *src - ascii buffer to scan
 * @param       len - number of ascii characters to scan in the ascii buffer
 * @return      a pointer to the location of the first numeric character otherwise NULL
 *****************************************************************************/
char * find_first_numeric_char_ascii( char *src, int len );
/*****************************************************************************//**
 * @brief       Find the first ascii number in an ascii string
 * @param       *src - ascii string to scan
 * @return      a pointer to the location of the first numeric character otherwise NULL
 *****************************************************************************/
char * find_first_numeric_char_string( char *src );
#endif

#if (UTIL_USE_ENDIAN_SWAP == 1)
/*************************************************************************//**
 * @brief       Change the endian-ness of a 64 bit value
 * @param       *src - the 64-bit value to swap bytes in
 ****************************************************************************/
void endian_swap_uint64( uint64_t *src, uint64_t *dest );
/*************************************************************************//**
 * @brief       Change the endian-ness of a 64 bit value
 * @param       *src - the 64-bit value to swap bytes in
 * @param       *dest - the buffer to put the swapped values into
 * @return      the memory location immediately following the last byte copied
 ****************************************************************************/
uint8_t * endian_swap_uint64_to_ptr( uint8_t *dest, uint64_t src );
/*************************************************************************//**
 * @brief       Change the endian-ness of a 64 bit value
 * @param       *src - the 64-bit value to swap bytes in
 * @param       *dest - the buffer to put the swapped values into
 * @return      the memory location immediately following the last byte copied
 ****************************************************************************/
uint8_t * endian_swap_ptr_to_uint64( uint64_t *dest, uint8_t *src );
/*************************************************************************//**
 * @brief       Change the endian-ness of a 32 bit value
 * @param       *src - the 32-bit value to swap bytes in
 * @return      the input value with the bytes swapped
 ****************************************************************************/
#ifdef REV_SUPPORT
inline uint32_t endian_swap_uint32( uint32_t src );
#else
uint32_t endian_swap_uint32( uint32_t src );
#endif
/*************************************************************************//**
 * @brief       Change the endian-ness of a 32 bit value
 * @param       *src - the 32-bit value to swap bytes in
 * @param       *dest - the buffer to put the swapped values into
 * @return      the memory location immediately following the last byte copied
 ****************************************************************************/
uint8_t * endian_swap_uint32_to_ptr( uint8_t *dest, uint32_t src );
/*************************************************************************//**
 * @brief       Change the endian-ness of a 32 bit value
 * @param       *src - the 32-bit value to swap bytes in
 * @param       *dest - the buffer to put the swapped values into
 * @return      the memory location immediately following the last byte copied
 ****************************************************************************/
uint8_t * endian_swap_ptr_to_uint32( uint32_t *dest, uint8_t *src );
/*************************************************************************//**
 * @brief       Change the endian-ness of a 16 bit value
 * @param       *src - the 16-bit value to swap bytes in
 * @return      the input value with the bytes swapped
 ****************************************************************************/
#ifdef REV_SUPPORT
inline uint16_t endian_swap_uint16( uint16_t src );
#else
uint16_t endian_swap_uint16( uint16_t src );
#endif
/*************************************************************************//**
 * @brief       Change the endian-ness of a 16 bit value
 * @param       *src - the 16-bit value to swap bytes in
 * @param       *dest - the buffer to put the swapped values into
 * @return      the memory location immediately following the last byte copied
 ****************************************************************************/
uint8_t * endian_swap_uint16_to_ptr( uint8_t *dest, uint16_t src );
/*************************************************************************//**
 * @brief       Change the endian-ness of a 16 bit value
 * @param       *src - the 16-bit value to swap bytes in
 * @param       *dest - the buffer to put the swapped values into
 * @return      the memory location immediately following the last byte copied
 ****************************************************************************/
uint8_t * endian_swap_ptr_to_uint16( uint16_t *dest, uint8_t *src );
/*************************************************************************//**
 * @brief       This is mainly for consistency, so the 8-bits can look like
 *              32's and 16's
 * @param       *src - an 8-bit value
 * @param       *dest - the buffer to put the 8-bit value into
 * @return      the memory location immediately following the byte copied
 ****************************************************************************/
uint8_t * endian_swap_uint8_to_ptr( uint8_t *dest, uint8_t src );
/*************************************************************************//**
 * @brief       This is mainly for consistency, so the 8-bits can look like
 *              32's and 16's
 * @param       *src - an 8-bit value
 * @param       *dest - the buffer to put the 8-bit value into
 * @return      the memory location immediately following the byte copied
 ****************************************************************************/
uint8_t * endian_swap_ptr_to_uint8( uint8_t *dest, uint8_t *src );
#endif

#if((UTIL_USE_DEC_TO_ASCII_PTR == 1) && (UTIL_USE_DEC_TO_HEX_ASCII == 1) && (UTIL_USE_DEC_TO_ASCII == 1))
/*************************************************************************//**
 * @brief       Converts a int8_t value to ascii and returns a ptr to the next available memory location
 * @param       *dest -  the memory location to copy converted decimal value
 * @param       *src - the signed char value to convert to ascii
 * @return      the memory location immediately following the converted ascii number
 ****************************************************************************/
char * int8_to_ascii_incremented_ptr( char *dest, int8_t src );
/*************************************************************************//**
 * @brief       Converts a int16_t value to ascii and returns a ptr to the next available memory location
 * @param       *dest -  the memory location to copy converted decimal value
 * @param       *src - the signed short value to convert to ascii
 * @return      the memory location immediately following the converted ascii number
 ****************************************************************************/
char * int16_to_ascii_incremented_ptr( char *dest, int16_t src );
/*************************************************************************//**
 * @brief       Converts a int32_t value to ascii and returns a ptr to the next available memory location
 * @param       *dest -  the memory location to copy converted decimal value
 * @param       *src - the signed int value to convert to ascii
 * @return      the memory location immediately following the converted ascii number
 ****************************************************************************/
char * int32_to_ascii_incremented_ptr( char *dest, int32_t src );
/*************************************************************************//**
 * @brief       Converts a int64_t value to ascii and returns a ptr to the next available memory location
 * @param       *dest -  the memory location to copy converted decimal value
 * @param       *src - the signed long value to convert to ascii
 * @return      the memory location immediately following the converted ascii number
 ****************************************************************************/
char * int64_to_ascii_incremented_ptr( char *dest, int64_t src );
/*************************************************************************//**
 * @brief       Converts a uint8_t value to ascii and returns a ptr to the next available memory location
 * @param       *dest -  the memory location to copy converted decimal value
 * @param       *src - the unsigned char value to convert to ascii
 * @return      the memory location immediately following the converted ascii number
 ****************************************************************************/
char * uint8_to_ascii_incremented_ptr( char *dest, uint8_t src );
/*************************************************************************//**
 * @brief       Converts a uint16_t value to ascii and returns a ptr to the next available memory location
 * @param       *dest -  the memory location to copy converted decimal value
 * @param       *src - the unsigned short value to convert to ascii
 * @return      the memory location immediately following the converted ascii number
 ****************************************************************************/
char * uint16_to_ascii_incremented_ptr( char *dest, uint16_t src );
/*************************************************************************//**
 * @brief       Converts a uint32_t value to ascii and returns a ptr to the next available memory location
 * @param       *dest -  the memory location to copy converted decimal value
 * @param       *src - the unsigned int value to convert to ascii
 * @return      the memory location immediately following the converted ascii number
 ****************************************************************************/
char * uint32_to_ascii_incremented_ptr( char *dest, uint32_t src );
/*************************************************************************//**
 * @brief       Converts a uint64_t value to ascii and returns a ptr to the next available memory location
 * @param       *dest -  the memory location to copy converted decimal value
 * @param       *src - the unsigned long value to convert to ascii
 * @return      the memory location immediately following the converted ascii number
 ****************************************************************************/
char * uint64_to_ascii_incremented_ptr( char *dest, uint64_t src );
#endif

#if(UTIL_USE_DEC_TO_HEX_ASCII_PTR == 1)
/*************************************************************************//**
 * @brief       Converts a uint8_t value to hex ascii and returns a ptr to the next available memory location
 * @param       *dest -  the memory location to copy converted decimal value
 * @param       *src - the unsigned char value to convert to ascii
 * @return      the memory location immediately following the converted hex ascii number
 ****************************************************************************/
char * uint8_to_hex_ascii_incremented_ptr( char *dest, uint8_t src );
/*************************************************************************//**
 * @brief       Converts a uint16_t value to hex ascii and returns a ptr to the next available memory location
 * @param       *dest -  the memory location to copy converted decimal value
 * @param       *src - the unsigned short value to convert to ascii
 * @return      the memory location immediately following the converted ascii number
 ****************************************************************************/
char * uint16_to_hex_ascii_incremented_ptr( char *dest, uint16_t src );
/*************************************************************************//**
 * @brief       Converts a uint32_t value to hex ascii and returns a ptr to the next available memory location
 * @param       *dest -  the memory location to copy converted decimal value
 * @param       *src - the unsigned int value to convert to ascii
 * @return      the memory location immediately following the converted ascii number
 ****************************************************************************/
char * uint32_to_hex_ascii_incremented_ptr( char *dest, uint32_t src );
/*************************************************************************//**
 * @brief       Converts a uint8_t value to hex ascii and returns a ptr to the next available memory location
 * @param       *dest -  the memory location to copy converted decimal value
 * @param       *src - the unsigned long value to convert to ascii
 * @return      the memory location immediately following the converted ascii number
 ****************************************************************************/
char * uint64_to_hex_ascii_incremented_ptr( char *dest, uint64_t src );
#endif

/*************************************************************************//**
 * @brief       Finds the next available index in a circular buffer (going forward)
 * @param       current_index - the index value to check
 * @param       low_limit - the beginning of the circular buffer range
 * @param       high_limit - the end of the circular buffer range
 * @return      The next available index in the circular buffer
 ****************************************************************************/
int find_next_index( int current_idx, int low_limit, int high_limit );
/*************************************************************************//**
 * @brief       Finds the next available index in a circular buffer (going backward)
 * @param       current_index - the index value to check
 * @param       low_limit - the beginning of the circular buffer range
 * @param       high_limit - the end of the circular buffer range
 * @return      The next available index in the circular buffer
 ****************************************************************************/
int find_prev_index( int current_idx, int low_limit, int high_limit );

/*****************************************************************************//**
 * @brief       Finds next separator in a string
 * @param       stringp - a double pointer to the string to be separated
 * @param       delim - character string to delimit the original string
 * @return      a pointer to the original value of the string otherwise it returns NULL
 *****************************************************************************/
char * strsep( char **stringp, const char *delim );
char *strsep_d(char **stringp, const char *delim, char delim_and);

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
void dsprintf( char * dest, char *fmt, ... );
void dsml_printf(char *dest, char *fmt, va_list args, int maxlen);

// not available to APP
void dsml_printf_dvs(char *dest, char *fmt, va_list args, DVS_STACK *dvs);

/*****************************************************************************
 * @brief
 * @param
 *****************************************************************************/
void filter_for_ascii( char *victim, uint8_t maxlen, char canonical );

/*****************************************************************************
 * @brief
 * @param
 *****************************************************************************/
void filter_for_noncanonical_ascii( char *victim, uint8_t maxlen );

/*****************************************************************************
 * @brief
 * @param
 *****************************************************************************/
void filter_for_canonical_ascii( char *victim, uint8_t maxlen );

/*****************************************************************************
 * @brief
 * @param
 *****************************************************************************/
int validate_ip( const char *src, int len );

/*****************************************************************************
 * @brief   copy number of Strings
 * @param   initial destination
 * @param   array of Strings to copy
 * @param   number of Strings to copy
 * @return  final destination
 *****************************************************************************/
char *copyStrings(char *dest, const char **src, uint8_t len_src);

/*************************************************************************
 * @brief   calculate digits necessary to print a long value
 * @param   value to calculate from
 * @return  2, 4, or 8
 *************************************************************************/
uint8_t calc_hex_precision(long value);

void add_string(char *buff, char *addstr, int maxlen);
void add_string_on_off(char *buff, uint8_t tst, int maxlen);
const char *get_newline_s(void);
char *format_version(char *dest, uint32_t div_value, uint32_t download_version);
char *toLowerCase(char *buff, int len);

/*****************************************************************************//**
 * @brief       Calculate an 8-bit Fletcher checksum on a buffer.
 * @param       source - pointer to start of buffer
 * @param       length - length of buffer in bytes
 * @return      checksum value
 *****************************************************************************/
uint16_t calc_checksum(uint8_t* source, uint16_t length);

/*****************************************************************************
 * @brief       A simple, small integer base pow function.
 * @param       uint32_t base - unsigned base value
 * @param		uint8_t power - unsigned power value
 * @return		uint32_t of base to the power
 * @note		This function does not handle overflow
 *****************************************************************************/
uint32_t calc_pow(uint32_t base, uint8_t power);

uint8_t num_of_bytes_in_uint32(uint32_t data);
uint32_t endian_swap_and_fit_uint32( uint32_t src, uint8_t len );

void append_ascii_hex_to_buffer(uint8_t* buff, uint8_t* data, uint16_t len);

#endif /* _UTILS_H_ */
