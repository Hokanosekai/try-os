#ifndef __DRIVER_DISK_H__
#define __DRIVER_DISK_H__

#include <libc/stdint.h>
#include <libc/stdbool.h>

typedef struct {
  uint8_t id;
  uint16_t cylinder;
  uint16_t sectors;
  uint16_t heads;
} disk_t;

bool disk_init(disk_t* disk, uint8_t id);
bool disk_read(disk_t* disk, uint32_t lba, uint8_t sectors, void* dataOut);

#endif
