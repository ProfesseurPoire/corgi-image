#pragma once

#include <bitset>
#include <cmath>

namespace corgi::binary
{
/**
 * @brief   Get the value of one bit inside data. Returns -1 if the index wasn't
 *
 *          @param bit_index : Index of the bit we're looking for
 *          @param data : data we're searching for the bit
 *          @param size : total size of @p data
 */
int get_bit(int bit_index, unsigned char* data, int size)
{
    if(bit_index < 0 || bit_index >= size * 8)
        return -1;

    int byteoffset           = bit_index / 8;
    int bit_position_in_byte = bit_index % 8;

    int value = data[byteoffset] >> bit_position_in_byte & (1);

    return value;
}

long long get_binary_value(int            bit_index,
                           int            bit_chunk_size,
                           unsigned char* data,
                           int            size)
{
    // if(bit_index < 0 || bit_index * 8 >= size * 8)
    //     return -1;
    // if(bit_index + bit_chunk_size < 0 || bit_index + bit_chunk_size >= size *
    // 8)
    //     return -1;

    // TODO : I should probably use this everywhere I use a flag
    std::bitset<8> bits;

    int bit_position_in_byte = bit_index % 8;

    long long result     = 0;
    long long bit_offset = 0;

    int current_bits_done = 0;

    // While we didn't read every bit
    while(bit_chunk_size != 0)
    {
        long long byte_offset        = bit_index / 8;
        long long bit_offset_in_byte = bit_index % 8;

        unsigned char byt = data[byte_offset];

        long long max_space = 8 - bit_offset_in_byte;
        long long s         = bit_chunk_size;

        if(bit_chunk_size > max_space)
        {
            bit_chunk_size -= max_space;
            s = max_space;
        }
        else
        {
            bit_chunk_size = 0;
        }

        // I could always do this bit by bit
        long long a = static_cast<long long>(std::pow(2, s) - 1);
        ;

        long long b = a << bit_offset_in_byte;
        // So far so good

        b &= byt;

        result = result + ((b >> (bit_offset_in_byte) << current_bits_done));
        bit_index += s;
        current_bits_done += s;
    }
    return result;
}

}    // namespace corgi::binary