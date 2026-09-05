/**
 * @file data.h
 * @author Alex Katrompas
 * @assignment Stacks II
 * @brief Defines the Data structure stored by the Stack.
 */

#ifndef DATA_H
#define DATA_H

#include <string>

/**
 * @struct Data
 * @brief Represents a self-contained unit of information with an identifier
 *        and associated payload.
 */
struct Data {
    int id;
    std::string information;
};

#endif // DATA_H
