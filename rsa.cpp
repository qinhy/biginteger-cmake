//
//  CasRSA_CL.c
//  CasRSA_CL
//
//  Created by Carter McCardwell on 11/18/15.
//  Copyright (c) 2015 Carter McCardwell. All rights reserved.
//

#define __NO_STD_VECTOR
#define MAX_SOURCE_SIZE (0x100000)


#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <chrono>

#include <CL/cl.h>
#include "integer.h"

#include <string>
#include <assert.h>

//#define ASSERT(e) if(!(e)) { }

const unsigned long WordMask = 0x00000000FFFFFFFFUL;

integer<2048> modulus = "\xDE\xCF\xB6\xFC\x3D\x33\xE9\x55\xFD\xAC\x90\xE8\x88\x17\xB0\x03\xA1\x6B\x9A\xAB\x72\x70\x79\x32\xA2\xA0\x8C\xBB\x33\x6F\xB0\x76\x96\x2E\xC4\xE9\x2E\xD8\x8F\x92\xC0\x2D\x4D\x41\x0F\xDE\x45\x1B\x25\x3C\xBE\x37\x6B\x45\x82\x21\xE6\x4D\xB1\x23\x81\x82\xB6\x81\x62\xB7\x30\xF4\x60\x4B\xC7\xF7\xF0\x17\x0C\xB5\x75\x88\x77\x93\x52\x63\x70\xF0\x0B\xC6\x73\x43\x41\xEE\xE4\xF0\x71\xEC\xC8\xC1\x32\xC4\xDC\xA9\x99\x1D\x31\xB8\xA4\x7E\xDD\x19\x04\x0F\x02\xA8\x1A\xAF\xB3\x48\x9A\x29\x29\x5E\x49\x84\xE0\x94\x11\xD1\x7E\xAB\xB2\xC0\x44\x7E\xA1\x1B\x5E\x9D\x0D\x1A\xF9\x02\x9A\x2E\x53\x03\x2D\x48\x96\x7C\x2C\xA6\xD7\xAC\xF1\xED\x2B\x18\xBB\x01\xCB\x13\xB9\xAC\xA6\xEE\x55\x00\x37\x7C\x69\x61\x62\x89\x01\x54\x77\x9F\x07\x5D\x26\x34\x3A\xA9\x49\xA5\xAF\xF2\x5E\x06\x51\xB7\x1C\xE0\xDE\xDA\x5C\x0B\x9F\x98\xC2\x15\xFD\xBA\xD8\xA9\x99\x00\xAB\xA4\x8E\x4A\x16\x9D\x66\x2A\xE8\x56\x64\xB2\xB6\xC0\x93\xAF\x4D\x38\xA0\x16\x5C\xE4\xBD\x62\xC2\x46\x6B\xC9\x5A\x59\x4A\x72\x58\xFD\xB2\xCC\x36\x87\x30\x85\xE8\xA1\x04\x5B\xE0\x17\x9B\xD0\xEC\x9B";
integer<2048> _sample = "\xC2\x6E\xAA\xCE\xDD\x4F\xF3\x1C\xD9\x70\x26\x2B\x2A\x6B\xE0\x6D\x5C\xEC\x11\x15\x52\x8C\xAA\x6F\x00\xBA\xDA\x3A\x6B\x9A\x88\x6B\x5E\x35\xDE\x4F\xB7\xE9\xE4\x35\x6C\x4B\x06\xB3\x10\xCC\xA1\x5A\xED\x2B\x7B\x43\x3D\xAB\x68\x1B\x03\x66\xCC\x3C\x76\x9F\x6D\x35\x79\xE6\xB8\x16\xA8\xF0\x1B\xE9\xC5\x8C\x1A\x61\xA5\xAB\x81\x7E\x2C\x2F\xC5\x5C\x8C\x70\xF5\x84\xD8\xD4\x85\xE7\x55\x84\xD7\x1A\x0E\xA1\xA6\x09\x27\x51\xDB\xE6\xBC\xBB\xE3\xC1\x19\xA4\xCB\xA5\xE3\x83\xE7\x40\x81\x31\x29\xAA\x4E\x9C\xB4\x9D\xD3\x96\xBB\x7F\x97\xF3\x32\xFA\xA2\x4F\x0A\x4B\xCB\xC3\x62\xE3\x4D\x4F\x09\xF1\x39\x5B\x56\x5C\xC6\x15\x3D\x37\xF0\x57\xA0\x49\x68\x86\xE6\x6E\x96\x5B\xE0\x8A\x10\x30\xEA\x03\x8B\xC4\x5D\xDF\x6D\x4F\x52\x7F\x3E\xD4\x1E\x25\x45\xC0\xE4\x77\x2E\xA6\xA3\xF9\x7D\xD2\xA0\xC7\x0D\x34\x07\x69\xE8\xAF\x21\x1C\xD1\xEE\xB5\x04\xA9\x6C\x70\xB4\xDE\x40\xAD\x14\x6B\xF6\x3F\x50\x9F\xD5\x6A\x55\x35\x82\x11\xCC\x27\xA9\x69\x14\x76\x9E\x50\x86\x4F\xF4\xEE\xA2\x45\xA5\xFF\xA9\x52\x65\xD5\x73\x3E\xDB\x0D\x33\xD9\xD1\x60\x2F\x5F\x3C\xC8\xE6";
const unsigned int exponent = 65537;

std::string& readFile(const char* fileName)
{
	static std::string buffer;

	buffer = "";
	FILE* f = fopen(fileName, "r");
	if (f == NULL)
	{
		return buffer;
	}
	fseek(f, 0, SEEK_END);

	long fileSize = ftell(f);
	buffer.resize(fileSize);
	fread((void*)buffer.c_str(), 1, fileSize, f);
	fclose(f);
	return buffer;
}

int mul_inv(int a, int b)
{
	int b0 = b, t, q;
	int x0 = 0, x1 = 1;
	if (b == 1) return 1;
	while (a > 1) {
		q = a / b;
		t = b, b = a % b, a = t;
		t = x0, x0 = x1 - q * x0, x1 = t;
	}
	if (x1 < 0) x1 += b0;
	return x1;
}

int main(int argc, const char * argv[])
{    
    clock_t c_start, c_stop;

	integer<1024> p;
	integer<1024> q;
	integer<1024> message;
	integer<1024> result;

	integer<128> c = 42;
	integer<2048> a;

	assert(
		integer<128>("\xFF\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00")
		-
		integer<128>("\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01")
		==
		integer<128>("\xFE\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF")
	);

	assert(
		integer<128>("\xFF\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00")
		+
		integer<128>("\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01")
		==
		integer<128>("\xFF\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01")
	);

	assert(
		integer<2048>("\xde\xcf\xb6\xfc\x3d\x33\xe9\x55\xfd\xac\x90\xe8\x88\x17\xb0\x03\xa1\x6b\x9a\xab\x72\x70\x79\x32\xa2\xa0\x8c\xbb\x33\x6f\xb0\x76\x96\x2e\xc4\xe9\x2e\xd8\x8f\x92\xc0\x2d\x4d\x41\x0f\xde\x45\x1b\x25\x3c\xbe\x37\x6b\x45\x82\x21\xe6\x4d\xb1\x23\x81\x82\xb6\x81\x62\xb7\x30\xf4\x60\x4b\xc7\xf7\xf0\x17\x0c\xb5\x75\x88\x77\x93\x52\x63\x70\xf0\x0b\xc6\x73\x43\x41\xee\xe4\xf0\x71\xec\xc8\xc1\x32\xc4\xdc\xa9\x99\x1d\x31\xb8\xa4\x7e\xdd\x19\x04\x0f\x02\xa8\x1a\xaf\xb3\x48\x9a\x29\x29\x5e\x49\x84\xe0\x94\x11\xd1\x7e\xab\xb2\xc0\x44\x7e\xa1\x1b\x5e\x9d\x0d\x1a\xf9\x02\x9a\x2e\x53\x03\x2d\x48\x96\x7c\x2c\xa6\xd7\xac\xf1\xed\x2b\x18\xbb\x01\xcb\x13\xb9\xac\xa6\xee\x55\x00\x37\x7c\x69\x61\x62\x89\x01\x54\x77\x9f\x07\x5d\x26\x34\x3a\xa9\x49\xa5\xaf\xf2\x5e\x06\x51\xb7\x1c\xe0\xde\xda\x5c\x0b\x9f\x98\xc2\x15\xfd\xba\xd8\xa9\x99\x00\xab\xa4\x8e\x4a\x16\x9d\x66\x2a\xe8\x56\x64\xb2\xb6\xc0\x93\xaf\x4d\x38\xa0\x16\x5c\xe4\xbd\x62\xc2\x46\x6b\xc9\x5a\x59\x4a\x72\x58\xfd\xb2\xcc\x36\x87\x30\x85\xe8\xa1\x04\x5b\xe0\x17\x9b\xd0\xec\x9b")
		-
		integer<2048>("\xa9\xaa\xf4\xb5\x40\x55\x2a\xed\x22\xae\x23\x48\x3f\x28\x69\xa7\x7f\xb5\x3e\xb2\xad\xac\xc2\x44\x41\xbb\x7a\x5b\x4e\xb5\xd0\x9e\x65\x71\x6f\x63\xae\xde\x63\x65\x5d\x4b\x74\x3b\x13\xa2\xc6\x87\x8f\x5a\x05\x9f\xbc\x39\x09\x53\x89\xef\x2a\xe5\xd7\xfb\xf4\x50\xee\x43\x69\xbf\x67\x26\x9d\x22\xdf\x49\xb8\xe0\x03\x8e\xc0\xd2\x96\xde\x19\x62\xaa\x08\x34\x9a\x68\x09\xcd\xce\x3a\xa8\x1e\x60\xcd\x4c\xe6\x91\x4f\x4a\x17\xa7\xcc\x3e\x9f\x31\x63\x2b\x8e\xbe\x7c\xeb\xaf\x97\xa1\xda\x39\x25\x6c\xa5\xcf\x49\x89\x80\x7a\x2f\x56\xf8\xf2\x04\x03\xf6\x5a\x2c\x20\x6f\x16\xf2\x30\xe4\x7f\x37\x79\xf4\x70\x5f\x6b\x36\xfb\x1a\x75\x8e\x76\x3d\xb3\xb2\xda\xa9\xfb\x68\x94\xd2\x13\x14\x38\xf4\x69\xf2\x5e\x49\x90\xb0\x94\x7d\xd9\xf7\x99\xcc\xa0\xaa\x91\x98\xc3\xf9\x03\x07\x00\x31\xc5\x51\xf4\xd1\x65\x5e\x36\x3b\x64\xdc\x2e\x7a\x2e\x10\x0b\x5b\x37\x91\xcc\x0f\x23\x20\x75\xca\xe9\x44\xe1\x7a\xc9\x56\x91\x38\xc1\xb7\x81\x9d\x9a\x2b\xb7\x1b\x97\xd3\x43\x67\xd6\x10\x4c\xc1\x03\x3f\x53\x20\x36\x43\x01\x5a\xe6\x20\x34\xb4\x87\xd6\x13\x60\xb9\x23")
		==
		integer<2048>("\x35\x24\xc2\x46\xfc\xde\xbe\x68\xda\xfe\x6d\xa0\x48\xef\x46\x5c\x21\xb6\x5b\xf8\xc4\xc3\xb6\xee\x60\xe5\x12\x5f\xe4\xb9\xdf\xd8\x30\xbd\x55\x85\x7f\xfa\x2c\x2d\x62\xe1\xd9\x05\xfc\x3b\x7e\x93\x95\xe2\xb8\x97\xaf\x0c\x78\xce\x5c\x5e\x86\x3d\xa9\x86\xc2\x30\x74\x73\xc7\x34\xf9\x25\x2a\xd5\x10\xcd\x53\xd5\x71\xf9\xb6\xc0\xbb\x85\x57\x8d\x61\xbe\x3e\xa8\xd9\xe5\x17\x22\x37\x44\xaa\x60\x65\x77\xf6\x18\x49\xd3\x1a\x10\xd8\x40\x3d\xe7\xa0\xe3\x73\xe9\x9d\xc4\x03\xb0\xf8\x4e\xf0\x38\xdc\xdf\x11\x4a\x88\x51\x04\x7c\x5b\xc7\x52\x7a\x9d\x25\x04\x70\xec\xab\xe2\x10\x69\x49\xd3\xcb\xb3\x54\x26\x1c\xc1\x6f\xdc\x92\x7c\x5e\xb4\xdb\x07\x4e\xf0\x69\xbe\x44\x12\x1c\x41\xeb\xfe\x87\xff\x6f\x04\x3f\x70\xa3\xe3\x21\x2d\x65\x8c\x67\x99\xfe\xb8\x0c\xeb\xf9\x5a\xff\x51\x85\x57\x8e\xea\x08\xf6\xad\x69\x5d\x5d\x39\xcf\x40\xaa\x99\x8d\xa5\x74\x12\xc2\x3a\xf3\x7c\xf0\x5f\xff\x11\x83\x37\xed\x6a\x02\x76\x8b\x81\x1e\x78\xc2\xb9\x06\x47\x2a\x73\x28\x61\x84\x48\xfd\xb1\x55\xbe\x5f\xac\x00\x44\x2f\x2b\x02\x80\xcf\xa7\x58\x41\x88\x70\x33\x78")
	);

	assert(
		integer<2048>("\xde\xcf\xb6\xfc\x3d\x33\xe9\x55\xfd\xac\x90\xe8\x88\x17\xb0\x03\xa1\x6b\x9a\xab\x72\x70\x79\x32\xa2\xa0\x8c\xbb\x33\x6f\xb0\x76\x96\x2e\xc4\xe9\x2e\xd8\x8f\x92\xc0\x2d\x4d\x41\x0f\xde\x45\x1b\x25\x3c\xbe\x37\x6b\x45\x82\x21\xe6\x4d\xb1\x23\x81\x82\xb6\x81\x62\xb7\x30\xf4\x60\x4b\xc7\xf7\xf0\x17\x0c\xb5\x75\x88\x77\x93\x52\x63\x70\xf0\x0b\xc6\x73\x43\x41\xee\xe4\xf0\x71\xec\xc8\xc1\x32\xc4\xdc\xa9\x99\x1d\x31\xb8\xa4\x7e\xdd\x19\x04\x0f\x02\xa8\x1a\xaf\xb3\x48\x9a\x29\x29\x5e\x49\x84\xe0\x94\x11\xd1\x7e\xab\xb2\xc0\x44\x7e\xa1\x1b\x5e\x9d\x0d\x1a\xf9\x02\x9a\x2e\x53\x03\x2d\x48\x96\x7c\x2c\xa6\xd7\xac\xf1\xed\x2b\x18\xbb\x01\xcb\x13\xb9\xac\xa6\xee\x55\x00\x37\x7c\x69\x61\x62\x89\x01\x54\x77\x9f\x07\x5d\x26\x34\x3a\xa9\x49\xa5\xaf\xf2\x5e\x06\x51\xb7\x1c\xe0\xde\xda\x5c\x0b\x9f\x98\xc2\x15\xfd\xba\xd8\xa9\x99\x00\xab\xa4\x8e\x4a\x16\x9d\x66\x2a\xe8\x56\x64\xb2\xb6\xc0\x93\xaf\x4d\x38\xa0\x16\x5c\xe4\xbd\x62\xc2\x46\x6b\xc9\x5a\x59\x4a\x72\x58\xfd\xb2\xcc\x36\x87\x30\x85\xe8\xa1\x04\x5b\xe0\x17\x9b\xd0\xec\x9b")
		+
		integer<2048>("\xa9\xaa\xf4\xb5\x40\x55\x2a\xed\x22\xae\x23\x48\x3f\x28\x69\xa7\x7f\xb5\x3e\xb2\xad\xac\xc2\x44\x41\xbb\x7a\x5b\x4e\xb5\xd0\x9e\x65\x71\x6f\x63\xae\xde\x63\x65\x5d\x4b\x74\x3b\x13\xa2\xc6\x87\x8f\x5a\x05\x9f\xbc\x39\x09\x53\x89\xef\x2a\xe5\xd7\xfb\xf4\x50\xee\x43\x69\xbf\x67\x26\x9d\x22\xdf\x49\xb8\xe0\x03\x8e\xc0\xd2\x96\xde\x19\x62\xaa\x08\x34\x9a\x68\x09\xcd\xce\x3a\xa8\x1e\x60\xcd\x4c\xe6\x91\x4f\x4a\x17\xa7\xcc\x3e\x9f\x31\x63\x2b\x8e\xbe\x7c\xeb\xaf\x97\xa1\xda\x39\x25\x6c\xa5\xcf\x49\x89\x80\x7a\x2f\x56\xf8\xf2\x04\x03\xf6\x5a\x2c\x20\x6f\x16\xf2\x30\xe4\x7f\x37\x79\xf4\x70\x5f\x6b\x36\xfb\x1a\x75\x8e\x76\x3d\xb3\xb2\xda\xa9\xfb\x68\x94\xd2\x13\x14\x38\xf4\x69\xf2\x5e\x49\x90\xb0\x94\x7d\xd9\xf7\x99\xcc\xa0\xaa\x91\x98\xc3\xf9\x03\x07\x00\x31\xc5\x51\xf4\xd1\x65\x5e\x36\x3b\x64\xdc\x2e\x7a\x2e\x10\x0b\x5b\x37\x91\xcc\x0f\x23\x20\x75\xca\xe9\x44\xe1\x7a\xc9\x56\x91\x38\xc1\xb7\x81\x9d\x9a\x2b\xb7\x1b\x97\xd3\x43\x67\xd6\x10\x4c\xc1\x03\x3f\x53\x20\x36\x43\x01\x5a\xe6\x20\x34\xb4\x87\xd6\x13\x60\xb9\x23")
		==
		integer<2048>("\x88\x7a\xab\xb1\x7d\x89\x14\x43\x20\x5a\xb4\x30\xc7\x40\x19\xab\x21\x20\xd9\x5e\x20\x1d\x3b\x76\xe4\x5c\x07\x16\x82\x25\x81\x14\xfb\xa0\x34\x4c\xdd\xb6\xf2\xf8\x1d\x78\xc1\x7c\x23\x81\x0b\xa2\xb4\x96\xc3\xd7\x27\x7e\x8b\x75\x70\x3c\xdc\x09\x59\x7e\xaa\xd2\x50\xfa\x9a\xb3\xc7\x72\x65\x1a\xcf\x60\xc5\x95\x79\x17\x38\x65\xe9\x41\x8a\x52\xb5\xce\xa7\xdd\xa9\xf8\xb2\xbe\xac\x94\xe7\x22\x00\x11\xc3\x3a\xe8\x67\x49\x60\x70\xbd\x7c\x4a\x67\x3a\x91\x66\x97\x9b\x62\xe0\x3c\x03\x62\x83\xb6\x2a\xaf\xdd\x9b\x51\xf8\xdb\x09\xb9\x36\x82\xa5\x11\xb8\xc9\x2d\x8a\x0f\xf4\xcb\x12\xd2\x3a\xa7\x3d\x06\xdb\x97\xdd\xd2\xc7\x67\x7b\xa1\x56\x6e\xb4\xa5\xbd\xb5\x15\x3b\xc0\x68\x14\x70\x70\xd3\x53\xc0\xd2\x92\x05\x0c\x1c\xe1\x54\xc0\x00\xdb\x53\xdb\x3e\x73\xeb\x61\x0d\x51\xe8\xe2\x32\xd3\xab\xc1\x69\xd5\xd4\x26\xf2\x2c\x35\x06\xb9\xa4\x5b\xe3\x36\x5a\x59\x39\xbd\xdb\xf5\xd1\x9b\x46\x2d\x80\x17\x24\xe8\x0e\xf0\x21\xb3\xf7\x10\x74\x7e\x5a\x19\xaf\x31\x30\x69\x97\x33\x5c\x3d\x05\xec\x6c\xca\x31\xe0\xce\xc1\x39\x10\x67\xed\xaf\x31\xa5\xbe")
	);

	assert(
		integer<2048>("\xde\xcf\xb6\xfc\x3d\x33\xe9\x55\xfd\xac\x90\xe8\x88\x17\xb0\x03\xa1\x6b\x9a\xab\x72\x70\x79\x32\xa2\xa0\x8c\xbb\x33\x6f\xb0\x76\x96\x2e\xc4\xe9\x2e\xd8\x8f\x92\xc0\x2d\x4d\x41\x0f\xde\x45\x1b\x25\x3c\xbe\x37\x6b\x45\x82\x21\xe6\x4d\xb1\x23\x81\x82\xb6\x81\x62\xb7\x30\xf4\x60\x4b\xc7\xf7\xf0\x17\x0c\xb5\x75\x88\x77\x93\x52\x63\x70\xf0\x0b\xc6\x73\x43\x41\xee\xe4\xf0\x71\xec\xc8\xc1\x32\xc4\xdc\xa9\x99\x1d\x31\xb8\xa4\x7e\xdd\x19\x04\x0f\x02\xa8\x1a\xaf\xb3\x48\x9a\x29\x29\x5e\x49\x84\xe0\x94\x11\xd1\x7e\xab\xb2\xc0\x44\x7e\xa1\x1b\x5e\x9d\x0d\x1a\xf9\x02\x9a\x2e\x53\x03\x2d\x48\x96\x7c\x2c\xa6\xd7\xac\xf1\xed\x2b\x18\xbb\x01\xcb\x13\xb9\xac\xa6\xee\x55\x00\x37\x7c\x69\x61\x62\x89\x01\x54\x77\x9f\x07\x5d\x26\x34\x3a\xa9\x49\xa5\xaf\xf2\x5e\x06\x51\xb7\x1c\xe0\xde\xda\x5c\x0b\x9f\x98\xc2\x15\xfd\xba\xd8\xa9\x99\x00\xab\xa4\x8e\x4a\x16\x9d\x66\x2a\xe8\x56\x64\xb2\xb6\xc0\x93\xaf\x4d\x38\xa0\x16\x5c\xe4\xbd\x62\xc2\x46\x6b\xc9\x5a\x59\x4a\x72\x58\xfd\xb2\xcc\x36\x87\x30\x85\xe8\xa1\x04\x5b\xe0\x17\x9b\xd0\xec\x9b")
		>>
		1024
		==
		integer<1024>("\xde\xcf\xb6\xfc\x3d\x33\xe9\x55\xfd\xac\x90\xe8\x88\x17\xb0\x03\xa1\x6b\x9a\xab\x72\x70\x79\x32\xa2\xa0\x8c\xbb\x33\x6f\xb0\x76\x96\x2e\xc4\xe9\x2e\xd8\x8f\x92\xc0\x2d\x4d\x41\x0f\xde\x45\x1b\x25\x3c\xbe\x37\x6b\x45\x82\x21\xe6\x4d\xb1\x23\x81\x82\xb6\x81\x62\xb7\x30\xf4\x60\x4b\xc7\xf7\xf0\x17\x0c\xb5\x75\x88\x77\x93\x52\x63\x70\xf0\x0b\xc6\x73\x43\x41\xee\xe4\xf0\x71\xec\xc8\xc1\x32\xc4\xdc\xa9\x99\x1d\x31\xb8\xa4\x7e\xdd\x19\x04\x0f\x02\xa8\x1a\xaf\xb3\x48\x9a\x29\x29\x5e\x49\x84\xe0\x94\x11\xd1\x7e\xab\xb2\xc0\x44\x7e\xa1\x1b\x5e\x9d\x0d\x1a\xf9\x02\x9a\x2e\x53\x03\x2d\x48\x96\x7c\x2c\xa6\xd7\xac\xf1\xed\x2b\x18\xbb\x01\xcb\x13\xb9\xac\xa6\xee\x55\x00\x37\x7c\x69\x61\x62\x89\x01\x54\x77\x9f\x07\x5d\x26\x34\x3a\xa9\x49\xa5\xaf\xf2\x5e\x06\x51\xb7\x1c\xe0")
	);

	assert(
		integer<64>(0xe6a4065acc120001)
		*
		integer<64>(0xe6a4065acc120001)
		==
		integer<128>("\xcf\xcb\x24\x83\x4b\x2e\x30\xd6\xc4\x9c\xbd\xf9\x98\x24\x00\x01")
	);


	assert(
		integer<2048>("\xa9\xaa\xf4\xb5\x40\x55\x2a\xed\x22\xae\x23\x48\x3f\x28\x69\xa7\x7f\xb5\x3e\xb2\xad\xac\xc2\x44\x41\xbb\x7a\x5b\x4e\xb5\xd0\x9e\x65\x71\x6f\x63\xae\xde\x63\x65\x5d\x4b\x74\x3b\x13\xa2\xc6\x87\x8f\x5a\x05\x9f\xbc\x39\x09\x53\x89\xef\x2a\xe5\xd7\xfb\xf4\x50\xee\x43\x69\xbf\x67\x26\x9d\x22\xdf\x49\xb8\xe0\x03\x8e\xc0\xd2\x96\xde\x19\x62\xaa\x08\x34\x9a\x68\x09\xcd\xce\x3a\xa8\x1e\x60\xcd\x4c\xe6\x91\x4f\x4a\x17\xa7\xcc\x3e\x9f\x31\x63\x2b\x8e\xbe\x7c\xeb\xaf\x97\xa1\xda\x39\x25\x6c\xa5\xcf\x49\x89\x80\x7a\x2f\x56\xf8\xf2\x04\x03\xf6\x5a\x2c\x20\x6f\x16\xf2\x30\xe4\x7f\x37\x79\xf4\x70\x5f\x6b\x36\xfb\x1a\x75\x8e\x76\x3d\xb3\xb2\xda\xa9\xfb\x68\x94\xd2\x13\x14\x38\xf4\x69\xf2\x5e\x49\x90\xb0\x94\x7d\xd9\xf7\x99\xcc\xa0\xaa\x91\x98\xc3\xf9\x03\x07\x00\x31\xc5\x51\xf4\xd1\x65\x5e\x36\x3b\x64\xdc\x2e\x7a\x2e\x10\x0b\x5b\x37\x91\xcc\x0f\x23\x20\x75\xca\xe9\x44\xe1\x7a\xc9\x56\x91\x38\xc1\xb7\x81\x9d\x9a\x2b\xb7\x1b\x97\xd3\x43\x67\xd6\x10\x4c\xc1\x03\x3f\x53\x20\x36\x43\x01\x5a\xe6\x20\x34\xb4\x87\xd6\x13\x60\xb9\x23")
		*
		integer<2048>("\xde\xcf\xb6\xfc\x3d\x33\xe9\x55\xfd\xac\x90\xe8\x88\x17\xb0\x03\xa1\x6b\x9a\xab\x72\x70\x79\x32\xa2\xa0\x8c\xbb\x33\x6f\xb0\x76\x96\x2e\xc4\xe9\x2e\xd8\x8f\x92\xc0\x2d\x4d\x41\x0f\xde\x45\x1b\x25\x3c\xbe\x37\x6b\x45\x82\x21\xe6\x4d\xb1\x23\x81\x82\xb6\x81\x62\xb7\x30\xf4\x60\x4b\xc7\xf7\xf0\x17\x0c\xb5\x75\x88\x77\x93\x52\x63\x70\xf0\x0b\xc6\x73\x43\x41\xee\xe4\xf0\x71\xec\xc8\xc1\x32\xc4\xdc\xa9\x99\x1d\x31\xb8\xa4\x7e\xdd\x19\x04\x0f\x02\xa8\x1a\xaf\xb3\x48\x9a\x29\x29\x5e\x49\x84\xe0\x94\x11\xd1\x7e\xab\xb2\xc0\x44\x7e\xa1\x1b\x5e\x9d\x0d\x1a\xf9\x02\x9a\x2e\x53\x03\x2d\x48\x96\x7c\x2c\xa6\xd7\xac\xf1\xed\x2b\x18\xbb\x01\xcb\x13\xb9\xac\xa6\xee\x55\x00\x37\x7c\x69\x61\x62\x89\x01\x54\x77\x9f\x07\x5d\x26\x34\x3a\xa9\x49\xa5\xaf\xf2\x5e\x06\x51\xb7\x1c\xe0\xde\xda\x5c\x0b\x9f\x98\xc2\x15\xfd\xba\xd8\xa9\x99\x00\xab\xa4\x8e\x4a\x16\x9d\x66\x2a\xe8\x56\x64\xb2\xb6\xc0\x93\xaf\x4d\x38\xa0\x16\x5c\xe4\xbd\x62\xc2\x46\x6b\xc9\x5a\x59\x4a\x72\x58\xfd\xb2\xcc\x36\x87\x30\x85\xe8\xa1\x04\x5b\xe0\x17\x9b\xd0\xec\x9b")
		==
		integer<4096>("\x93\xab\xea\xb7\xc3\x2a\xc2\x42\xc1\x39\x8c\x28\xde\xac\x53\xd3\x75\x11\x3a\x3f\x4a\xc5\xea\x72\x13\x27\x46\x83\xe0\xa2\x0d\xcb\x13\x38\xa8\xfb\x17\x9f\x08\x60\x65\x6a\x9b\x62\x20\x26\x77\x86\xe5\xb0\x0a\x05\x18\x82\xfc\x30\xf2\xb0\x63\x44\xfb\x39\x31\x75\xbf\xa1\x90\x77\xda\xed\x0b\x47\xd8\x2a\xde\x97\x34\x8f\x54\xcd\xfd\x4b\x7a\x1f\xc1\xa1\x12\x26\xc7\xb2\x93\xd1\x04\xd3\xf4\x2b\x2d\x78\x2d\x89\xcd\x1c\x71\x4b\x03\xd7\x9d\xd5\xd0\xb7\xe5\x00\x96\x41\x0e\xba\x5f\x8f\xde\xe0\xa6\xd5\x4f\x49\xa1\x8b\x8b\x81\x4c\x98\xd1\x8a\xdf\xa6\x43\xb9\x59\x55\x2f\xea\x65\x5c\xbb\xce\x8e\x05\x33\x5a\x3a\x09\xb0\x95\x3d\x67\x75\x99\x2c\x1d\x49\xfa\x31\xa9\x7e\x74\x24\x6f\x21\xb9\x32\x08\x07\x5d\x91\x5a\xfa\x68\x1d\x85\xde\xc0\xcc\xe2\x1f\x8e\x1f\x3e\x8c\x9c\x07\xfb\xd2\x24\xff\xd6\x28\x3c\x46\xe7\x2c\xa7\x92\xd4\xd6\xfe\x59\xbb\x22\xc4\x19\x4a\x8c\xdf\x1b\xad\x15\xf3\xbe\x4e\x2d\xe8\x32\xdf\xca\x12\xca\x1e\x9c\xd0\x5e\xf8\xc1\x67\x96\x2d\x32\xe7\x59\xc0\x91\x43\xb0\x98\x85\x44\x94\x80\xff\xd8\xae\xf4\x92\x3a\x81\xcd\x0e\x08\xe3\xaf\x10\xec\x6d\x6e\x2b\x1f\x4b\xa1\x17\x2f\xdb\xad\x4f\x15\x37\x48\xbf\x71\xd9\xa7\x68\x97\xf9\xee\xcd\x78\xb7\xff\x3c\xeb\x54\x73\x9e\x8b\xcd\x34\x1e\xa4\x3a\xae\x30\x1e\xdb\x65\xce\x36\xfa\xe0\xe0\x43\x7e\xc1\xdf\xac\xac\x5e\x89\x98\x91\x8e\x13\x2b\xc3\x28\x72\xbd\x49\x53\x7b\x79\x9c\x20\x9f\x09\x0c\xe4\xa3\x82\x1c\x0b\xf4\x50\xa1\xfe\xef\x82\xfd\x36\x89\xf2\xcb\x95\x76\x5a\xb8\xa0\x18\xb4\xdc\x31\x49\xfe\x8b\xfc\x6d\x35\xa2\x95\x3e\x99\x05\x68\x6d\xa9\x91\xc4\xb9\x81\x29\x41\x54\x4f\xb7\xae\x42\x14\x47\xde\x22\x0c\xfb\xee\x73\x68\xba\x49\x28\xec\x74\x99\x2b\x15\xaf\x1c\xce\x6f\xff\xda\x31\x5d\x48\xeb\x20\xb6\x89\x48\xdb\x4a\xb0\x7e\x58\xfc\xe8\xc1\xec\xd4\x74\x4f\x21\x5c\x6a\x51\x62\x95\x01\x22\x94\x43\x2d\xde\x24\x3d\xee\xe9\x5a\x81\x6d\xc6\xf5\x2f\xa0\xac\x0d\x03\x93\xf4\xa4\xb8\x14\xc0\xd2\xf4\x64\x06\x49\x88\x0e\x6b\xa2\xd6\x1e\xfd\xd5\x47\x6c\x5d\x01\x7b\xfe\x81\x91\x2a\x56\x14\xbe\xe2\xa5\xb5\x3b\x2e\x64\x6f\xf9\x46\x20\xeb\x6b\xc3\x99\x06\xd2\xee\x03\x88\x39\x7d\x0d\x53\x29\x4e\x83\xac\x5c\x31")
	);

	
	assert(
		powmod(integer<128>((word)0x12345678aabbccdd), 0x100, integer<128>(0xabcdef0017569217))
		==
		integer<128>("\x00\x00\x00\x00\x00\x00\x00\x00\x39\x1d\xcf\x4e\x25\xf5\x3b\x1d")
	);
	return 0;

	//a <<= 64;
	//a -= integer<128>(1);
	//a += 0;
	//a >>= 1;
	//a /= integer<128>(0x100);
	//integer<128> c = integer<128>(2);
	//integer<128> m = 33;
	//auto d = (integer<128>((word)0xabcdef0017569217) *  integer<128>((word)0x7a88500ae544c291));
	//d.print();

	powmod(integer<128>((word)0x12345678aabbccdd), 0x100, integer<128>(0xabcdef0017569217)).print();
	//powmod(_sample, 0x1, modulus).print();
	return 0;
	//a <<= 64;
	//a -= 1;
	//integer<64> b = 200;
	//integer<128> c = a * b;
	//a -= 2;
	//a.print();
	//return 0;
	//c *= 2;

	/*p = BIT_MASK(64);
	for (int i = 0; i <128; i++)
	{
		if (i % 16 == 0) printf("\n");
		printf("%d ", p.bit(i)?1:0);
	}
	printf("\n");
	return 0;*/
	//printf("log: %d\n", ilog2<0xFFFFFF>::value);
	
	/*auto t = new integer<2048 * 0x100>();
	printf("sizeof(t) = %d\n", sizeof(*t));
	modulus.pow<0x100>(*t).print();
	delete t;*/

	//printf("%u\n", c.modularInverse(a));
	//printf("%d\n", mul_inv(42, 2017));
	//modulus.modularInverse(integer<2048>(0xFFFF)).print();
	return 0;

	std::chrono::milliseconds start = std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch());
	//modulus = 1;
	p = 2;
	unsigned long i;
	for (i = 0; i < 0x1000; i++)
	{
		c / integer<1024>(0xFFFF);
	}
	std::chrono::milliseconds end = std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch());
	if ((end - start).count() == 0)
	{
		printf("ops/sec = infinity\n");
	}
	else
	{
		printf("ops/sec = %d\n", i * 1000 / (end - start).count());
	}
	//modulus = integer<1024>(0xFF) + integer<1024>(2);


	modulus.print();
	return 0;

	printf("INPUT:\n\tM:"); message.print();
	printf("\n\tp:"); p.print();
	printf("\n\tq:"); q.print();
    
	std::string source = std::string("#pragma OPENCL EXTENSION cl_khr_byte_addressable_store : enable\n#define PLUS 1\n#define MINUS -1\n");
	source += readFile("kernel_rsa.cl");

    //Set OpenCL Context
    cl_int err;
    cl_platform_id platform;
    cl_context context;
    cl_command_queue queue;
    cl_device_id device;
	
    err = clGetPlatformIDs(1, &platform, NULL);
    if (err != CL_SUCCESS) { printf("platformid"); }

    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 1, &device, NULL);
    if (err != CL_SUCCESS) { printf("getdeivceid %i", err); }

    cl_uint numberOfCores;
    clGetDeviceInfo(device, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(numberOfCores), &numberOfCores, NULL);
    printf("\nThis GPU supports %i compute units", numberOfCores); //Utilize the maximum number of compute units

    cl_uint maxThreads;
    clGetDeviceInfo(device, CL_KERNEL_WORK_GROUP_SIZE, sizeof(maxThreads), &maxThreads, NULL);
    //printf("\nRunning with %i threads per compute units", maxThreads); //Utilize the maximum number of threads/cu

    context = clCreateContext(0, 1, &device, NULL, NULL, &err);
    if (err != CL_SUCCESS) { printf("context"); }

    queue = clCreateCommandQueue(context, device, 0, &err);
    if (err != CL_SUCCESS) { printf("queue"); }

	const char* append_str = source.c_str();
	const size_t length = source.length();
    cl_program program = clCreateProgramWithSource(context, 1, (const char**)&append_str, &length, &err); //Compile program with expanded key included in the source
    if (err != CL_SUCCESS) { printf("createprogram"); }

    printf("\nBuilding CL Kernel...");
    err = clBuildProgram(program, 1, &device, "-I ./ -cl-std=CL1.2", NULL, NULL); //The fourth parameter is specific to OpenCL 2.0

    if (err == CL_BUILD_PROGRAM_FAILURE) {
        printf("\nBuild Error = %i", err);
        // Determine the size of the log
        size_t log_size;
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);

        // Allocate memory for the log
        char *log = (char *) malloc(log_size);

        // Get the log
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, log_size, log, NULL);

        // Print the log
        //printf("%s\n", log);
		FILE* f = fopen("error.log", "w+");
		fwrite(log, 1, log_size, f);
		fclose(f);
    }
    printf("\t[Done]");

    cl_mem cl_p, cl_q, cl_M, cl_result;
    cl_int status = CL_SUCCESS;
    
    cl_p = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(integer<1024>), &p, &status);
    if (status != CL_SUCCESS || cl_p == NULL) { printf("\nCreate p: %i", status); }

    cl_q = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(integer<1024>), &q, &status);
    if (status != CL_SUCCESS || cl_q == NULL) { printf("\nCreate q: %i", status); }

    cl_M = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(integer<1024>), &message, &status);
    if (status != CL_SUCCESS || cl_M == NULL) { printf("\nCreate M: %i", status); }

    cl_result = clCreateBuffer(context, CL_MEM_WRITE_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(integer<1024>), &result, &status);
    if (status != CL_SUCCESS || cl_result == NULL) { printf("\nCreate result: %i", status); }

	c_start = clock(); //Create a clock to benchmark the time taken for execution

    cl_kernel rsa_kernel = clCreateKernel(program, "rsa_cypher", &status);
    if (status != CL_SUCCESS) { printf("\nclCreateKernel: %i", status); }

    status = clSetKernelArg(rsa_kernel, 0, sizeof(cl_mem), &cl_p);
    status = clSetKernelArg(rsa_kernel, 1, sizeof(cl_mem), &cl_q);
    status = clSetKernelArg(rsa_kernel, 2, sizeof(cl_mem), &cl_M);
    status = clSetKernelArg(rsa_kernel, 3, sizeof(cl_mem), &cl_result);
    status = clSetKernelArg(rsa_kernel, 4, sizeof(int), &exponent);
    if (status != CL_SUCCESS) { printf("\nclSetKernelArg: %i", status); }

    size_t local_ws = 1, global_ws = 1;
    printf("\nRun Parameters: Local: %zu - Global: %zu", local_ws, global_ws);

    status = clEnqueueNDRangeKernel(queue, rsa_kernel, 1, NULL, &global_ws, &local_ws, 0, NULL, NULL);
    if (status != CL_SUCCESS) { printf("\nclEnqueueNDRangeKernel: %i", status); }

    clFinish(queue);

    status = clEnqueueReadBuffer(queue, cl_result, CL_TRUE, 0, sizeof(integer<1024>), &result, 0, NULL, NULL);
    if (status != CL_SUCCESS) { printf("\nclEnqueueReadBuffer: %i", status); }

    printf("\nEncrypted Result: ");
	result.print();

	c_stop = clock();
    float diff = (((float)c_stop - (float)c_start) / CLOCKS_PER_SEC ) * 1000;
    
    printf("\nDone - Time taken: %f ms\n", diff);
    clReleaseMemObject(cl_p);
    clReleaseMemObject(cl_q);
    clReleaseMemObject(cl_M);
    clReleaseMemObject(cl_result);
    clReleaseContext(context);
    clReleaseCommandQueue(queue);
    return 0;
}

