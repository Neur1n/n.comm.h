/******************************************************************************
Copyright (c) 2022 Jihang Li
x.comm.h is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan
PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details.


Last update: 2022-12-09 14:41
Version: v0.2.0
******************************************************************************/
#ifndef X_COMM_H
#define X_COMM_H

#ifndef X_IS_WINDOWS
#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) \
  || defined(__TOS_WIX__) || defined(__WINDOWS__)
#define X_IS_WINDOWS (1)
#else
#define X_IS_WINDOWS (0)
#endif
#endif

#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//******************************************************************* C and C++
#ifdef __cplusplus
extern "C" {
#endif

uint32_t x_crc32(const void* data, const size_t size, const uint32_t* prev);

uint16_t x_rfc1071(const void* data, const size_t size);

uint8_t x_xor(const void* data, const size_t size);

//******************************************************************** x_pkt{{{
typedef struct _x_hdr_
{
  uint16_t sof;  // start of frame
  uint16_t ctl;  // control code
  uint32_t opt;  // option, just use it freely
  uint64_t cnt;  // total count of packets
  uint64_t idx;  // index of current packet
  uint64_t dsz;  // size of the data chunk
  uint64_t cks;  // checksum of packet
} x_hdr;

typedef struct _x_pkt_
{
  x_hdr head;
  void* body;
} x_pkt;

#ifndef X_HDR_SOF
#define X_HDR_SOF (0x55AA)
#endif
#define X_PKT_SOF X_HDR_SOF

#ifndef X_HDR_CNT_INF
#define X_HDR_CNT_INF UINT64_MAX
#endif
#define X_PKT_CNT_INF X_HDR_CNT_INF

#define X_HDR_INIT {X_HDR_SOF, 0, 0, 0, 0, 0, 0}
#define X_PKT_INIT {X_HDR_INIT, NULL}
// x_pkt}}}

#ifdef __cplusplus
}
#endif

#endif  // X_COMM_H

#ifdef X_COMM_H_IMPLEMENTATION
//******************************************************************* C and C++
#ifdef __cplusplus
extern "C" {
#endif

//******************************************************************* Gadget{{{
uint32_t x_crc32(const void* data, const size_t size, const uint32_t* prev)
{
  uint8_t* d = (uint8_t*)data;
  size_t count = size / sizeof(uint8_t);
  int i = 0;

  uint32_t crc = prev ? ~(*prev) : 0xFFFFFFFF;

  while (count--)
  {
    crc ^= *d++;

    for (i = 0; i < 8; ++i)
    {
      crc = (crc >> 1) ^ (- (int32_t)(crc & 1) & 0xEDB88320);
    }
  }

  return ~crc;
}

uint16_t x_rfc1071(const void* data, const size_t size)
{
  uint16_t* d = (uint16_t*)data;
  size_t count = size / sizeof(uint8_t);
  uint32_t checksum = 0;

  while (count > 1)
  {
    checksum += *d++;
    count -= 2;
  }

  if (count > 0)
  {
    checksum += *d;
  }

  while (checksum >> 16)
  {
    checksum = (checksum & 0xFFFF) + (checksum >> 16);
  }

  return ~checksum;
}

uint8_t x_xor(const void* data, const size_t size)
{
  uint8_t* d = (uint8_t*)data;
  size_t count = size / sizeof(uint8_t);
  uint8_t checksum = 0;

  while (count--)
  {
    checksum ^= *d++;
  }

  return checksum;
}
// Gadget}}}

#ifdef __cplusplus
}
#endif
#endif  // X_COMM_H_IMPLEMENTATION
