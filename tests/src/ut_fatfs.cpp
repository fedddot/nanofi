#include <array>
#include <cstring>
#include <map>

#include "gtest/gtest.h"

#include "custom_ffconf.h"
#include "ff.h"
#include "diskio.h"

#define BLOCK_SIZE 512UL
#define SECTOR_COUNT 2048UL
#define DISK_SIZE (BLOCK_SIZE * SECTOR_COUNT)

std::map<BYTE, std::array<char, DISK_SIZE>> g_disks;

TEST(ut_fatfs, fatfs_sanity) {
    const TCHAR *fs_path = "";
    // MKFS_PARM mkfs_parm = {
    //     .fmt = FM_FAT32,
    //     .n_fat = 1,
    //     .align = 1,
    //     .n_root = 16,
    //     .au_size = 4096
    // };
    std::array<BYTE, FF_MAX_SS> work;

    auto fs_result = f_mkfs(fs_path, nullptr, (void *)work.data(), (UINT)work.size());
    ASSERT_EQ(FRESULT::FR_OK, fs_result);
    
    FATFS fs;
    fs_result = f_mount(&fs, fs_path, 0);
    ASSERT_EQ(FRESULT::FR_OK, fs_result);
    
    FIL file; 
    const auto file_path = "test.txt";
    fs_result = f_open(&file, file_path, FA_WRITE | FA_CREATE_NEW);
    ASSERT_EQ(FRESULT::FR_OK, fs_result);

    const auto data = "Hello, world!";
    UINT bytes_written;
    fs_result = f_write(&file, data, std::strlen(data), &bytes_written);
    ASSERT_EQ(FRESULT::FR_OK, fs_result);
    ASSERT_EQ(std::strlen(data), bytes_written);

    fs_result = f_close(&file);
    ASSERT_EQ(FRESULT::FR_OK, fs_result);
}

DRESULT disk_ioctl(BYTE pdrv, BYTE cmd, void* buff) {
    switch (cmd) {
    case GET_BLOCK_SIZE:
        *(DWORD *)buff = (DWORD)BLOCK_SIZE;
        return DRESULT::RES_OK;
    case GET_SECTOR_COUNT:
        *(LBA_t *)buff = (LBA_t)SECTOR_COUNT;
        return DRESULT::RES_OK;
    case CTRL_SYNC:
        return DRESULT::RES_OK;
    default:
        return DRESULT::RES_ERROR;
    }
}

DSTATUS disk_initialize(BYTE pdrv) {
    if (g_disks.find(pdrv) == g_disks.end()) {
        g_disks[pdrv] = std::array<char, DISK_SIZE>();
    }
    return 0;
}

DSTATUS disk_status(BYTE pdrv) {
    if (g_disks.find(pdrv) == g_disks.end()) {
        return STA_NOINIT;
    }
    return 0;
}

DRESULT disk_read(BYTE pdrv, BYTE* buff, LBA_t sector, UINT count) {
    enum { SECTOR_SIZE = 512 };
    std::memcpy(buff, g_disks[pdrv].data() + sector * SECTOR_SIZE, count * SECTOR_SIZE);
    return DRESULT::RES_OK;
}

DRESULT disk_write(BYTE pdrv, const BYTE* buff, LBA_t sector, UINT count) {
    enum { SECTOR_SIZE = 512 };
    std::memcpy(g_disks[pdrv].data() + sector * SECTOR_SIZE, buff, count * SECTOR_SIZE);
    return DRESULT::RES_OK;
}

DWORD get_fattime(void) {
    return 0;
}