/*
 * (c) Copyright 2015 by Einar Saukas. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * The name of its author may not be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

// stolen from https://github.com/mateoconlechuga/convbin/blob/5ed1a0823a0c3298252f01a9e92b18c5397e7c2e/src/deps/zx7/dzx7.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char *input_data;
unsigned char *output_data;
size_t input_index;
size_t output_index;
int bit_mask;
int bit_value;

static int read_byte() {
    return input_data[input_index++];
}

static int read_bit() {
    bit_mask >>= 1;
    if (bit_mask == 0) {
        bit_mask = 128;
        bit_value = read_byte();
    }
    return bit_value & bit_mask ? 1 : 0;
}

static int read_elias_gamma() {
    int i;
    int value;

    i = 0;
    while (!read_bit()) {
        i++;
    }
    if (i > 15) {
        return -1;
    }
    value = 1;
    while (i--) {
        value = value << 1 | read_bit();
    }
    return value;
}

static int read_offset() {
    int value;
    int i;

    value = read_byte();
    if (value < 128) {
        return value;
    } else {
        i = read_bit();
        i = i << 1 | read_bit();
        i = i << 1 | read_bit();
        i = i << 1 | read_bit();
        return (value & 127 | i << 7) + 128;
    }
}

static void write_byte(int value) {
    output_data[output_index++] = value;
}

static void write_bytes(int offset, int length) {
    int i;
    while (length-- > 0) {
        i = output_index-offset;
        if(i < 0) printf("i < 0 in decompress\n");
        write_byte(output_data[i]);
    }
}

static void decompress() {
    int length;

    input_index = 0;
    output_index = 0;
    bit_mask = 0;

    write_byte(read_byte());
    while (1) {
        if (!read_bit()) {
            write_byte(read_byte());
        } else {
            length = read_elias_gamma()+1;
            if (length == 0) {
                return;
            }
            write_bytes(read_offset()+1, length);
        }
    }
}

void zx7_Decompress(void *dest, const void *src) {
	input_data = src;
	output_data = dest;
	decompress();
}
