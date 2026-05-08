#include "gtest/gtest.h"
#include <array>
#include <cstddef>
#include <cstring>
#include <map>

#include "custom_ffconf.h"
#include "ff.h"
#include "diskio.h"

TEST(ut_fatfs, fatfs_sanity) {
    const TCHAR *fs_path = "/dev/sd0";
    MKFS_PARM mkfs_parm = {
        .fmt = FM_FAT32,
        .n_fat = 1,
        .align = 1,
        .n_root = 16,
        .au_size = 4096
    };
    std::array<BYTE, FF_MAX_SS> work;

    auto fs_result = f_mkfs(fs_path, &mkfs_parm, (void *)work.data(), (UINT)work.size());
    ASSERT_EQ(FRESULT::FR_OK, fs_result);
    
    FATFS fs;
    fs_result = f_mount(&fs, fs_path, 1);
    ASSERT_EQ(FRESULT::FR_OK, fs_result);
    
    FIL file; 
    const auto file_path = "/dev/sd0/test.txt";
    fs_result = f_open(&file, file_path, FA_WRITE | FA_CREATE_ALWAYS);
    ASSERT_EQ(FRESULT::FR_OK, fs_result);
}

const std::size_t g_disk_size = 1024 * 1024; // 1MB
std::map<BYTE, std::array<char, g_disk_size>> g_disks;

DSTATUS disk_initialize(BYTE pdrv) {
    g_disks[pdrv] = std::array<char, g_disk_size>();
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

DRESULT disk_ioctl(BYTE pdrv, BYTE cmd, void* buff) {
    switch (cmd) {
    case GET_BLOCK_SIZE:
        *(DWORD*)buff = 512;
        return DRESULT::RES_OK;
    case GET_SECTOR_COUNT:
        *(WORD*)buff = (WORD)2048;
        return DRESULT::RES_OK;
    case CTRL_SYNC:
        return DRESULT::RES_OK;
    default:
        return DRESULT::RES_ERROR;
    }
}

DWORD get_fattime(void) {
    return 0;
}