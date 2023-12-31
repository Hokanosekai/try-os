#ifndef __DRIVER_X86_H__
#define __DRIVER_X86_H__

#include <libc/stdint.h>
#include <libc/stdbool.h>

void __attribute__((cdecl)) x86_outb(uint16_t port, uint8_t value);
uint8_t __attribute__((cdecl)) x86_inb(uint16_t port);

bool __attribute__((cdecl)) x86_Disk_GetDriveParams(uint8_t drive,
                                                    uint8_t *driveType,
                                                    uint16_t *cylinders,
                                                    uint16_t *sectors,
                                                    uint16_t *heads);
bool __attribute__((cdecl)) x86_Disk_Reset(uint8_t drive);
bool __attribute__((cdecl)) x86_Disk_Read(uint8_t drive,
                                          uint16_t cylinder,
                                          uint16_t sector,
                                          uint16_t head,
                                          uint8_t count,
                                          void* lowerDataOut);

int __attribute__((cdecl)) x86_Video_GetVbeInfo(void* vbeInfoOut);
int __attribute__((cdecl)) x86_Video_GetModeInfo(uint16_t mode, void* modeInfoOut);
int __attribute__((cdecl)) x86_Video_SetMode(uint16_t mode);

#endif