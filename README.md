# Ft_printf(): My own implementation of the famous C function!


This project focuses on understanding variadic functions, format specifiers, and advanced C programming concepts.

## 📋 Table of Contents

- [About](#about)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Format Specifiers](#format-specifiers)
- [Function Reference](#function-reference)
- [Examples](#examples)
- [Technical Requirements](#technical-requirements)
- [Contributing](#contributing)

## About

**ft_printf** is a custom implementation of the standard `printf()` function that handles formatted output conversion. This project deepens understanding of:

- Variadic functions (`va_list`, `va_start`, `va_arg`, `va_end`)
- Format string parsing and processing
- Type conversions and formatting
- Memory management in complex scenarios
- Modular programming and code organization

The function mimics the behavior of the original `printf()` while implementing core format specifiers from scratch.

## Features

### Implemented Format Specifiers
- **`%c`** - Single character output
- **`%s`** - String output
- **`%p`** - Pointer address in hexadecimal format
- **`%d`** - Decimal (base 10) signed integer
- **`%i`** - Integer in base 10 (identical to %d)
- **`%u`** - Unsigned decimal (base 10) number
- **`%x`** - Hexadecimal (base 16) lowercase format
- **`%X`** - Hexadecimal (base 16) uppercase format
- **`%%`** - Literal percent sign


## Installation

1. **Clone the repository:**
   ```bash
   git clone https://github.com/viridian-green/My_Own_Printf.git
   cd ft_printf
   ```

2. **Compile the library:**
   ```bash
   make
   ```

3. **Clean build files (optional):**
   ```bash
   make clean    # Remove object files
   make fclean   # Remove object files and library
   make re       # Recompile everything
   ```



## 🔧 Function Reference

### Core Function
```c
int ft_printf(const char *format, ...);
```
- **Parameters**: 
  - `format`: Format string containing text and format specifiers
  - `...`: Variable arguments corresponding to format specifiers
- **Return Value**: Number of characters printed, or -1 on error
- **Description**: Processes format string and outputs formatted text

### Typical Helper Functions Structure
```c
/* Format parsing and processing */
int     parse_format(const char *format, va_list args);
int     handle_conversion(char specifier, va_list args);

/* Type-specific output functions */
int     print_char(int c);
int     print_string(char *str);
int     print_pointer(void *ptr);
int     print_decimal(int num);
int     print_unsigned(unsigned int num);
int     print_hex_lower(unsigned int num);
int     print_hex_upper(unsigned int num);

/* Utility functions */
int     print_nbr_base(unsigned long num, char *base);
int     get_num_digits(long num, int base);
```

### Comparison with Standard printf
```c
#include "ft_printf.h"
#include <stdio.h>

int main(void)
{
    int num = 42;
    char *str = "Test";
    
    printf("Standard printf:\n");
    printf("String: %s, Number: %d, Hex: %x\n", str, num, num);
    
    ft_printf("Custom ft_printf:\n");
    ft_printf("String: %s, Number: %d, Hex: %x\n", str, num, num);
    
    return (0);
}
```


## ⚙️ Technical Requirements

### Compilation Requirements
- **Language**: C
- **Compilation Flags**: `-Wall -Wextra -Werror`
- **Library Creation**: Must use `ar` command (not `libtool`)
- **Output File**: `libftprintf.a` at repository root

### External Functions Allowed
- `malloc`, `free` - Memory allocation and deallocation
- `write` - System call for output
- `va_start`, `va_arg`, `va_copy`, `va_end` - Variadic function macros


### Makefile Requirements
Must include the following rules:
- `NAME` - Variable containing library name
- `all` - Default rule to compile the library
- `clean` - Remove object files
- `fclean` - Remove object files and library
- `re` - Clean and recompile everything


### Implementation Notes
- **No Buffer Management**: Unlike the standard `printf()`, direct output via `write()`
- **libft Integration**: Can use previously created libft functions
- **Error Handling**: Must handle NULL pointers and edge cases gracefully
- **Memory Management**: Proper allocation/deallocation for any dynamic memory used
- **Norm Compliance**: Must follow 42 School coding standards


**Note**: This implementation focuses on the core functionality of `printf()` and serves as an excellent exercise in advanced C programming concepts. The project emphasizes understanding the internals of formatted output rather than optimizing for production use.

