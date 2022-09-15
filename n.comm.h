/******************************************************************************
Copyright (c) 2022 Jihang Li
n.comm.h is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan
PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details.


Last update: 2022-09-14 15:40
Version: v0.1.2
******************************************************************************/
#ifndef NEU_COMM_H
#define NEU_COMM_H

#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef N_INLINE
#ifdef __cplusplus
#define N_INLINE inline
#else
#define N_INLINE static inline
#endif
#endif


#ifdef __cplusplus
extern "C" {
#endif
//***************************************************************** Function{{{
N_INLINE uint32_t n_crc32(const void* data, const size_t length, const uint32_t* prev)
{
  uint8_t* d = (uint8_t*)data;
  size_t l = length;
  int i = 0;

  uint32_t crc = prev ? ~(*prev) : 0xFFFFFFFF;

  while (l--)
  {
    crc ^= *d++;

    for (i = 0; i < 8; ++i)
    {
      crc = (crc >> 1) ^ (- (int32_t)(crc & 1) & 0xEDB88320);
    }
  }

  return ~crc;
}
// Function}}}

//***************************************************************** n_packet{{{
struct n_packet_info
{
  uint16_t sof;  // start of frame
  uint16_t ctl;  // control code
  uint32_t cnt;  // total count of packets
  uint32_t idx;  // index of current packet
  uint32_t crc;  // CRC of packet
  uint32_t len;  // length of the chunk
};

struct n_packet
{
  struct n_packet_info info;
  uint8_t* chunk;
};

N_INLINE uint32_t n_packet_crc(struct n_packet* packet, const uint32_t* prev)
{
  if (packet == NULL || packet->chunk == NULL)
  {
    return 0;
  }

  // NOTE: The packet is transmitted correctly if recv == calc.
  //       Users should compare them after calling n_packet_crc.
  uint32_t recv = 0;  // received CRC
  uint32_t calc = 0;  // calculated CRC

  recv = packet->info.crc;
  packet->info.crc = 0;  // CRC itself should not be involved.

  size_t ilen = sizeof(struct n_packet_info);
  uint8_t* buf = (uint8_t*)malloc(ilen + packet->info.len);
  memcpy(buf, &packet->info, ilen);
  memcpy(buf + ilen, packet->chunk, packet->info.len);

  calc = n_crc32(buf, sizeof(packet->info) + packet->info.len, prev);

  packet->info.crc = recv;

  free(buf);

  return calc;
}

N_INLINE errno_t n_packet_init(
    struct n_packet* packet, const uint16_t ctl, const uint32_t cnt,
    const uint32_t idx, const uint32_t len, const void* chunk,
    const uint32_t* prev_crc)
{
  if (packet == NULL)
  {
    return EINVAL;
  }

  memset(packet, 0, sizeof(struct n_packet));

  if (len > 0 && chunk != NULL)
  {
    packet->chunk = (uint8_t*)chunk;
  }

  packet->info.sof = 0x55AA;
  packet->info.ctl = ctl;
  packet->info.cnt = cnt;
  packet->info.idx = idx;
  packet->info.len = len;
  packet->info.crc = n_packet_crc(packet, prev_crc);

  return 0;
}

N_INLINE size_t n_packet_size(const struct n_packet* packet)
{
  if (packet == NULL)
  {
    return 0;
  }

  return sizeof(struct n_packet_info) + packet->info.len;
}

N_INLINE errno_t n_packet_to_string(
    char* buffer, const size_t size, const struct n_packet* packet)
{
  if (packet == NULL || buffer == NULL)
  {
    return EINVAL;
  }

  size_t ilen = sizeof(struct n_packet_info);

  if (size < (ilen + packet->info.len + 1))
  {
    return ENOBUFS;
  }

  char bytes[4] = {0};
  char* data_1 = (char*)(&packet->info);
  char* data_2 = (char*)(packet->chunk);

  for (size_t i = 0; i < ilen; ++i)
  {
    snprintf(bytes, 4, "%02X ", (uint8_t)data_1[i]);
    strcat_s(buffer, size, bytes);
  }

  for (size_t i = 0; i < packet->info.len; ++i)
  {
    snprintf(bytes, 4, "%02X ", (uint8_t)data_2[i]);
    strcat_s(buffer, size, bytes);
  }

  return 0;
}
// n_packet}}}

#ifdef __cplusplus
}
#endif


#endif  // NEU_COMM_H
