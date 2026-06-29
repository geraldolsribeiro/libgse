# GSE Library

## Introduction

This project implements the Generic Stream Encapsulation (GSE) standard
specified by ETSI for Linux and other Unix-compatible systems. It provides
encapsulation and de-encapsulation capabilities for applications.

## License

The GSE library is released under the LGPL, version 3 or later.
The full text is available in `COPYING.LESSER`.
Most of `src/common/crc.h` and `src/common/crc.c` is under the BSD license;
see `COPYING.BSD`.

## Usage

The sources are in the `src/` directory. They build a single library that
handles both encapsulation and de-encapsulation. See `INSTALL` for build
instructions.

Example:

```sh
gcc `pkg-config libgse --cflags` `pkg-config libgse --libs` -o myappli myappli.c
```

## Tests

The `test/` directory contains non-regression test programs. See the test
source headers and `INSTALL` for usage details.

## Contributors

Maintained by Viveris Technologies and Thales Alenia Space, with contributions
from:

- Cédric Baudoin <cedric.baudoin@thalesaleniaspace.com>
- Didier Barvaux <didier.barvaux@toulouse.viveris.com>
- Julien Bernard <julien.bernard@toulouse.viveris.com>
- Audric Schiltknecht <audric.schiltknecht@toulouse.viveris.com>
- Joaquin Muguerza <joaquin.muguerza@toulouse.viveris.com>
- Geraldo Ribeiro <geraldolsribeiro@gmail.com>

## References

- ETSI TS 102 606 — Digital Video Broadcasting (DVB) Generic Stream
  Encapsulation (GSE) Protocol
- DVB Document A134 — Generic Stream Encapsulation (GSE) Implementation
  Guidelines

