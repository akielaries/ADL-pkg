/*************************************************************************
 *
 *  Project
 *                         _____ _____  __  __ _____
 *                        / ____|  __ \|  \/  |  __ \
 *  ___  _ __   ___ _ __ | |  __| |__) | \  / | |__) |
 * / _ \| '_ \ / _ \ '_ \| | |_ |  ___/| |\/| |  ___/
 *| (_) | |_) |  __/ | | | |__| | |    | |  | | |
 * \___/| .__/ \___|_| |_|\_____|_|    |_|  |_|_|
 *      | |
 *      |_|
 *
 *
 * Copyright (C) Akiel Aries, <akiel@akiel.org>, et al.
 *
 * This software is licensed as described in the file LICENSE, which
 * you should have received as part of this distribution. The terms
 * among other details are referenced in the official documentation
 * seen here : https://akielaries.github.io/openGPMP/ along with
 * important files seen in this project.
 *
 * You may opt to use, copy, modify, merge, publish, distribute
 * and/or sell copies of the Software, and permit persons to whom
 * the Software is furnished to do so, under the terms of the
 * LICENSE file. As this is an Open Source effort, all implementations
 * must be of the same methodology.
 *
 *
 *
 * This software is distributed on an AS IS basis, WITHOUT
 * WARRANTY OF ANY KIND, either express or implied.
 *
 ************************************************************************/
/**
 * @file random.hpp
 * @brief Pseudorandom Number Generators
 */
#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <chrono>
#include <cstdint>

/** PRNG CONSTANTS */
#define __8MAX 127  /** 8 bit signed max    */
#define __U8MAX 255 /** 8 bit unsigned max */

#define __16MAX 32767  /** 16 bit signed max   */
#define __U16MAX 65535 /** 16 bit unsigned max */

#define __32MAX 2147483647L  /** 32 bit signed max   */
#define __U32MAX 4294967295U /** 32 bit unsigned max */

#define __64MAX 9223372036854775807LL    /** 64 bit signed max   */
#define __U64MAX 18446744073709551615ULL /** 64 bit unsigned max */

/*#define __PCG_STATE 0x4d595df4d0f33173
#define __PCG_MULTPLR 6364136223846793005u
#define __PCG_INCR 1442695040888963407u
*/
static uint64_t __PCG_STATE = 0x4d595df4d0f33173; // Or something seed-dependent
static uint64_t const __PCG_MULTPLR = 6364136223846793005u;
static uint64_t const __PCG_INCR =
    1442695040888963407u; // Or an arbitrary odd constant

namespace gpmp {

namespace core {

/**
 * @class
 */
namespace rndm {

/**
 * @brief Linear Congruential Generator
 * @param m = modulus      : 32-bit int max
 * @param a = multiplier   : 6364136223846793005 (from Knuth MMIX)
 * @param c = increment    : 1442695040888963407 (from Knuth MMIX)
 * @return generated number
 */
class LCG {
  public:
    using result_type = uint64_t;

    // Default constructor
    LCG();

    // Constructor with parameters similar to std::linear_congruential_engine
    LCG(uint64_t seed,
        uint64_t a = 6364136223846793005ULL,
        uint64_t c = 1442695040888963407ULL);

    // Function to generate a random number within a specific range
    uint64_t operator()();

    // Function to set the seed
    void seed(uint64_t new_seed);

    // Functions to retrieve parameters (optional)
    uint64_t get_multiplier() const;
    uint64_t get_increment() const;
    uint64_t get_seed() const;

  private:
    uint64_t state;      // State of the generator
    uint64_t multiplier; // Multiplier parameter
    uint64_t increment;  // Increment parameter
};

uint32_t rotr32(uint32_t x, unsigned r);

uint32_t pcg32(void);

void pcg32_init(uint64_t seed);

} // namespace rndm

} // namespace core

} // namespace gpmp

#endif
