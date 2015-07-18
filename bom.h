#ifndef OSX_BOM_H
#define OSX_BOM_H

// These structure define part of the NextSTEP/OSX BOM file format
// Author: Joseph Coffland
// Date: October, 2011
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// This program is in the public domain.

#include <stdint.h>

struct BOMHeader {
  char magic[8]; // = BOMStore
  uint32_t unknown0; // = 1?
  uint32_t unknown1; // = 73 = 0x49?
  uint32_t indexOffset; // Length of first part
  uint32_t indexLength; // Length of second part
  uint32_t varsOffset;
  uint32_t trailerLen; // TODO What does this data at the end mean?
} __attribute__((packed));


struct BOMIndex {
  uint32_t address;
  uint32_t length;
} __attribute__((packed));


struct BOMIndexHeader {
  uint32_t unknown0; // TODO What is this?  It's not the length of the array.
  BOMIndex index[];
} __attribute__((packed));


struct BOMTree { // 21 bytes
  char tree[4]; // = "tree"
  uint32_t unknown0;
  uint32_t child; // TODO Not sure about this one
  uint32_t unknown1;
  uint32_t unknown2;
  uint8_t unknown3;
} __attribute__((packed));


struct BOMVar {
  uint32_t index;
  uint8_t length;
  char name[]; // length
} __attribute__((packed));


struct BOMVars {
  uint32_t count; // Number of entries that follow
  BOMVar first[];
} __attribute__((packed));


struct BOMPathIndices {
  uint32_t index0;
  uint32_t index1;
} __attribute__((packed));


struct BOMPaths {
  uint16_t unknown0;
  uint16_t count;
  uint32_t unknown1; // = 0?
  uint32_t unknown2; // = 0?
  BOMPathIndices indices[];
} __attribute__((packed));


enum {
  TYPE_FILE = 1, // BOMPathInfo2 is exe=88 regular=35 bytes
  TYPE_DIR  = 2, // BOMPathInfo2 is 31 bytes
  TYPE_LINK = 3, // BOMPathInfo2 is 44? bytes
  TYPE_DEV  = 4, // BOMPathInfo2 is 35 bytes
};


// Not sure of all the corect values here
enum {
  ARCH_PPC = 0,
  ARCH_I386 = 1 << 12,
  ARCH_HPPA = 0,
  ARCH_SPARC = 0,
};


struct BOMPathInfo2 {
  uint8_t type; // See types above
  uint8_t unknown0; // = 1?
  uint16_t architecture; // Not sure exactly what this means
  uint16_t mode;
  uint32_t user;
  uint32_t group;
  uint32_t modtime;
  uint32_t size;
  uint8_t unknown1; // = 1?
  union {
    uint32_t checksum;
    uint32_t devType;
  };
  uint32_t linkNameLength;
  char linkName[];

  // TODO executable files have a buch of other crap here
} __attribute__((packed));


struct BOMPathInfo1 {
  uint32_t id;
  uint32_t index; // Pointer to BOMPathInfo2
} __attribute__((packed));


struct BOMFile {
  uint32_t parent; // Parent BOMPathInfo1->id
  char name[];
} __attribute__((packed));


#endif // OSX_BOM_H

