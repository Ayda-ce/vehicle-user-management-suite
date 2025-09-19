#ifndef _BUFFER_H_
#define _BUFFER_H_

#include <iostream>
#include <limits>

/**
 * Clears the input buffer by discarding any leftover characters
 * in the input stream up to and including the newline character.
 */
void clearInputBuffer() 
{
    std::cin.clear(); // Clear any error flags on std::cin
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore characters up to the newline
}

#endif /* _BUFFER_H_ */
