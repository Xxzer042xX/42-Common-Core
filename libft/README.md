# Libft

Libft is a standard C library I developed to provide common and often-used utility functions in C programming. It includes functions for string manipulation, memory management, and bonus features related to linked lists.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Examples](#examples)
- [Contributing](#contributing)
- [License](#license)

## Introduction

Libft is designed to offer functions similar to those found in the standard C libraries. It is particularly useful for projects where you need basic functionalities without relying on the standard C library.

## Features

### String Manipulation Functions

- `ft_strlen` - Returns the length of a string.
- `ft_strchr` - Finds the first occurrence of a character in a string.
- `ft_strcmp` - Compares two strings.

### Memory Management Functions

- `ft_memset` - Fills a block of memory with a given value.
- `ft_calloc` - Allocates and initializes a memory area.
- `ft_strdup` - Duplicates a string.

### Bonus Functions (Linked Lists)

- `ft_lstnew` - Creates a new list element.
- `ft_lstadd_front` - Adds an element to the beginning of the list.
- `ft_lstsize` - Counts the number of elements in the list.

## Installation

To compile and use Libft, follow these steps:

1. **Clone the repository:**

   ```bash
   git clone https://github.com/your-username/your-repo.git
   ```

2. **Navigate to the project directory:**

   ```bash
   cd your-repo
   ```

3. **Compile the library:**

   ```bash
   make
   ```

   This command will generate the `libft.a` file in the root directory of the project.

## Usage

To use Libft in your project, add the header file `libft.h` and link the `libft.a` library when compiling your project. Here’s an example of compilation:

```bash
gcc -o my_program my_program.c -L. -lft
```

Make sure to include the `include` directory in the header search paths if you chose to store your header files in an `include` directory.

## Examples

Here are some examples of using the main functions of Libft:

```c
#include "libft.h"
#include <stdio.h>

int main(void) {
    char str[] = "Hello, World!";
    printf("The length of the string is: %zu\n", ft_strlen(str));
    printf("First occurrence of 'W': %s\n", ft_strchr(str, 'W'));
    return 0;
}
```

## Contributing

If you want to contribute to Libft, you can:

1. **Make a pull request** by adding your modifications or improvements.
2. **Report issues** by opening an issue on the GitHub repository.
3. **Discuss potential improvements** by opening an issue or submitting proposals.

Please ensure to test your contributions and adhere to good coding practices.

## License

This project is under the [MIT](LICENSE) license.