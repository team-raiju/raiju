/**
 * @file distance.h
 *
 * @brief Distance sensors
 *
 * @author Daniel Nery <danielnso97@gmail.com>
 */

#if !defined(__DISTANCE_H__)
#define __DISTANCE_H__

#include <stdbool.h>

bool distance_is_front_seeing();

bool distance_is_left_seeing();

bool distance_is_right_seeing();

#endif // __DISTANCE_H__
