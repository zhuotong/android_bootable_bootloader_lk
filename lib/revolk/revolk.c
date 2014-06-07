#include <revolk.h>
#include <ext4.h>
#include <partition_parser.h>
#include <ext4_mmcdev.h>


int revolk_init(void) {
	int ret = 0;

#if BOOT_2NDSTAGE
	struct ext4_blockdev* mmcdev = ext4_mmcdev_get("userdata");
	if(!mmcdev){
		dprintf(CRITICAL, "MMC device ERROR\n");
		return -1;
	}

	ret = ext4_device_register(mmcdev, 0, "userdata");
	if(ret != EOK){
		dprintf(CRITICAL, "ext4_device_register ERROR = %d\n", ret);
		return ret;
	}

	ret = ext4_mount("userdata", "/data/");
	if(ret != EOK){
		dprintf(CRITICAL, "ext4_mount ERROR = %d\n", ret);
		return ret;
	}
#endif

	return ret;
}

int revolk_partition_read(uint64_t data_addr, uint32_t *out, uint32_t data_len) {
	int ret = 0;

#if BOOT_2NDSTAGE
	int index = INVALID_PTN;
	unsigned long long size;
	unsigned long long ptn;
	uint32_t bytes_read;
	ext4_file f;

	index = partition_get_index("boot");
	ptn = partition_get_offset(index);
	size = partition_get_size(index);

	if(data_addr>=ptn && data_addr<ptn+size) {
		ret = ext4_fopen(&f, "/data/revolk/boot.img", "r+");
		if(ret != EOK){
			dprintf(CRITICAL, "ext4_fopen ERROR = %d\n", ret);
			return -1;
		}

		ret = ext4_fseek(&f, data_addr-ptn, SEEK_SET);
		if(ret != EOK){
		    dprintf(CRITICAL, "ext4_fseek ERROR = %d\n", ret);
		    return -1;
		}

		ret = ext4_fread(&f, out, data_len, &bytes_read);
		if(ret != EOK){
		    dprintf(CRITICAL, "ext4_fread ERROR = %d\n", ret);
		    return -1;
		}

		ret = ext4_fclose(&f);
		if(ret != EOK){
		    printf("ext4_fclose ERROR = %d\n", ret);
		    return -1;
		}

		// return OK
		return 0;
	}
#endif

	// continue MMC read
	return 1;
}
