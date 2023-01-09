<!------------------------------------------------------------------ HEADER -->
<pre align="center">
  █▀▀▄ ▄▀▀█    ▄▀▀▀▀▀▀▀▄ ▄▀▀▀▀▀▀▀▄ ▄▀▀▀▀▀▀▀▄ ▄▀▀▀▀▀▀▀▄    █▀▀▀█▀▀▀█
  ▀▀▄ ▀ ▄▀▀    █   ▄▄  █ █   ▄   █ █  ▄ ▄  █ █  ▄ ▄  █    █   █   █
     █ █       █   █████ █   █   █ █  █ █  █ █  █ █  █    █       █
  ▄▄▀ ▄ ▀▄▄    █   ▀▀  █ █   ▀   █ █  █ █  █ █  █ █  █    █   █   █
  █▄▄▀ ▀▄▄█ ██ ▀▄▄▄▄▄▄▄▀ ▀▄▄▄▄▄▄▄▀ █▄▄█▄█▄▄█ █▄▄█▄█▄▄█ ██ █▄▄▄█▄▄▄█
</pre>

<p align="center">
  <img src="https://img.shields.io/badge/C-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white" alt="C">
  <img src="https://img.shields.io/badge/C++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="C++">

  <a href="./LICENSE">
    <img src="https://img.shields.io/badge/license-mulax_psl_v2-green.svg?style=for-the-badge" alt="license-mulan-psl-v2">
  </a>
</p>

<p align="center">
  Cross platform C/C++ utilities for communication.
</p>


<!------------------------------------------------------- TABLE OF CONTENTS -->
<details open="open">
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#installation">Installation</a></li>
        <li><a href="#usage">Usage</a></li>
      </ul>
    </li>
    <li><a href="#documentation">Documentation</a>
      <ul>
        <li><a href="#x_crc32">x_crc32</a></li>
        <li><a href="#x_rfc1071">x_rfc1071</a></li>
        <li><a href="#x_xor">x_xor</a></li>
        <li><a href="#x_hdr">x_hdr</a></li>
        <li><a href="#x_pkt">x_pkt</a></li>
      </ul>
    </li>
    <li><a href="#license">LICENSE</a></li>
  </ol>
</details>


<!--------------------------------------------------------- GETTING STARTED -->
## Getting Started
### Installation
Put `x.comm.h` into your project.


### Usage
`x.comm.h` is a single header file following the style of the
[stb libraries](https://github.com/nothings/stb), which means users must define
the macro `X_COMM_H_IMPLEMENTATION` in one and only one of their source files:

```c
// in some foo.c file
#define X_COMM_H_IMPLEMENTATION
#include "x.comm.h"

// in some bar.h or bar.c file
#include "x.comm.h"
```


<!----------------------------------------------------------- DOCUMENTATION -->
## Documentation
### x_crc32
Calculating the CRC32 checksum of a data array.

```c
uint32_t x_crc32(const void* data, const size_t size, const uint32_t* prev)
```

#### Parameters
- `data`: The data array from which the checksum is calculated.
- `size`: The length of the data array when it is casted to `uint8_t*`.
- `prev`: Previous CRC32 result. Pass `NULL`/`nullptr` to this argument if no
previous CRC32 result is available.

#### Returns
- The CRC32 checksum.


### x_rfc1071
Calculating the Internet checksum (following
[RFC1071](https://www.rfc-editor.org/rfc/rfc1071)) of a data array.

```c
uint16_t x_rfc1071(const void* data, const size_t size)
```

#### Parameters
- `data`: The data array from which the checksum is calculated.
- `size`: The length of the data array when it is casted to `uint8_t*`.

#### Returns
- The Internet checksum.


### x_rfc1071
Calculating the XOR checksum of a data array.

```c
uint8_t x_xor(const void* data, const size_t size)
```

#### Parameters
- `data`: The data array from which the checksum is calculated.
- `size`: The length of the data array when it is casted to `uint8_t*`.

#### Returns
- The XOR checksum.


### x_hdr
Header of a packet.

```c
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

#ifndef X_HDR_SOF
#define X_HDR_SOF (0x55AA)  // A commonly used start of frame.
#endif

#ifndef X_HDR_CNT_INF
#define X_HDR_CNT_INF UINT64_MAX  // Can be used for x_hdr::cnt.
#endif

#define X_HDR_INIT {X_HDR_SOF, 0, 0, 0, 0, 0, 0}  // Can be used to initialize x_hdr.
```

### x_pkt
Normally the header and body of a packet can be used separately, but providing
a simple encapsulation of them does no harm.

```c
typedef struct _x_pkt_
{
  x_hdr head;
  void* body;
} x_pkt;

#define X_PKT_SOF X_HDR_SOF

#define X_PKT_CNT_INF X_HDR_CNT_INF

#define X_PKT_INIT {X_HDR_INIT, NULL}  // Can be used to initialize x_pkt.
```

<!----------------------------------------------------------------- LICENSE -->
## License
Distributed under the [Mulan PSL v2](http://license.coscl.org.cn/MulanPSL2)
license. See [LICENSE](LICENSE) for more information.
