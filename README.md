<!------------------------------------------------------------------ HEADER -->
<pre align="center">
  ▄▀▀▀▀▄▀▀▄ █▀▀▀▀▀▀▀█ █▀▀▀█▀▀▀█    ▄▀▀▀▀▀▀▀▄ ▄▀▀▀▀▀▀▀▄ ▄▀▀▀▀▀▀▀▄ ▄▀▀▀▀▀▀▀▄    █▀▀▀█▀▀▀█
  █    █  █ █   ▄▄▄▄█ █   █   █    █   ▄▄  █ █   ▄   █ █  ▄ ▄  █ █  ▄ ▄  █    █   █   █
  █  █ █  █ █       █ █   █   █    █   █████ █   █   █ █  █ █  █ █  █ █  █    █       █
  █  █    █ █   ▀▀▀▀█ █   ▀   █    █   ▀▀  █ █   ▀   █ █  █ █  █ █  █ █  █    █   █   █
  ▀▄▄▀▄▄▄▄▀ █▄▄▄▄▄▄▄█ ▀▄▄▄▄▄▄▄▀ ██ ▀▄▄▄▄▄▄▄▀ ▀▄▄▄▄▄▄▄▀ █▄▄█▄█▄▄█ █▄▄█▄█▄▄█ ██ █▄▄▄█▄▄▄█
</pre>

<p align="center">
  <img src="https://img.shields.io/badge/C11-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white" alt="C11">
  <img src="https://img.shields.io/badge/C++11-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="C++11">

  <a href="./LICENSE">
    <img src="https://img.shields.io/badge/license-mulan_psl_v2-green.svg?style=for-the-badge" alt="license-mulan-psl-v2">
  </a>
</p>

<p align="center">
  Some C/C++ utilities for communication.
</p>


<!------------------------------------------------------- TABLE OF CONTENTS -->
<details open="open">
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#documentation">Documentation</a>
      <ul>
        <li><a href="#n_crc32">n_crc32</a></li>
        <li><a href="#n_packet">n_packet</a></li>
      </ul>
    </li>
    <li><a href="#license">LICENSE</a></li>
  </ol>
</details>


<!--------------------------------------------------------- GETTING STARTED -->
## Getting Started
### Prerequisites
C/C++ compiler that supports C11/C++11.


### Installation
Put `neu.comm.h` into your project.


<!----------------------------------------------------------- DOCUMENTATION -->
## Documentation
### n_crc32
```c
uint32_t n_crc32(const void* data, const size_t length, const uint32_t* prev)
```

#### Parameters
- `data`: The data array which CRC32 is calculated from.
- `length`: The length of the data array when it is casted to `uint8_t*`.
- `prev`: Previous CRC32 result. Pass `NULL`/`nullptr` to this argument if no previous CRC32 result is available.

#### Returns
- The CRC32 value.


<!----------------------------------------------------------------- LICENSE -->
## License
Distributed under the [Mulan PSL v2](http://license.coscl.org.cn/MulanPSL2/)
license. See [LICENSE](LICENSE) for more information.
