#include "cpio.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * asc_ul()
 *	convert hex/octal character string into a u_long. We do not have to
 *	check for overflow! (the headers in all supported formats are not large
 *	enough to create an overflow).
 *	NOTE: strings passed to us are NOT TERMINATED.
 * Return:
 *	unsigned long value
 */

static u_long asc_ul(char *str, int len, int base)
{
	char *stop;
	u_long tval = 0;

	stop = str + len;

	/*
	 * skip over leading blanks and zeros
	 */
	while ((str < stop) && ((*str == ' ') || (*str == '0')))
		++str;

	/*
	 * for each valid digit, shift running value (tval) over to next digit
	 * and add next digit
	 */
	if (base == HEX) {
		while (str < stop) {
			if ((*str >= '0') && (*str <= '9'))
				tval = (tval << 4) + (*str++ - '0');
			else if ((*str >= 'A') && (*str <= 'F'))
				tval = (tval << 4) + 10 + (*str++ - 'A');
			else if ((*str >= 'a') && (*str <= 'f'))
				tval = (tval << 4) + 10 + (*str++ - 'a');
			else
				break;
		}
	} else {
		while ((str < stop) && (*str >= '0') && (*str <= '7'))
			tval = (tval << 3) + (*str++ - '0');
	}
	return(tval);
}

/*
 * ul_asc()
 *	convert an unsigned long into an hex/oct ascii string. pads with LEADING
 *	ascii 0's to fill string completely
 *	NOTE: the string created is NOT TERMINATED.
 */

static int ul_asc(u_long val, char *str, int len, int base)
{
	char *pt;
	u_long digit;

	/*
	 * WARNING str is not '\0' terminated by this routine
	 */
	pt = str + len - 1;

	/*
	 * do a tailwise conversion (start at right most end of string to place
	 * least significant digit). Keep shifting until conversion value goes
	 * to zero (all digits were converted)
	 */
	if (base == HEX) {
		while (pt >= str) {
			if ((digit = (val & 0xf)) < 10)
				*pt-- = '0' + (char)digit;
			else
				*pt-- = 'a' + (char)(digit - 10);
			if ((val = (val >> 4)) == (u_long)0)
				break;
		}
	} else {
		while (pt >= str) {
			*pt-- = '0' + (char)(val & 0x7);
			if ((val = (val >> 3)) == (u_long)0)
				break;
		}
	}

	/*
	 * pad with leading ascii ZEROS. We return -1 if we ran out of space.
	 */
	while (pt >= str)
		*pt-- = '0';
	if (val != (u_long)0)
		return(-1);
	return(0);
}

/*
 * asc_ot()
 *	convert hex/octal character string into a ot_type. We do not have
 *	to check for overflow! (the headers in all supported formats are
 *	not large enough to create an overflow).
 *	NOTE: strings passed to us are NOT TERMINATED.
 * Return:
 *	ot_type value
 */

static ot_type asc_ot(char *str, int len, int base)
{
	char *stop;
	ot_type tval = 0;

	stop = str + len;

	/*
	 * skip over leading blanks and zeros
	 */
	while ((str < stop) && ((*str == ' ') || (*str == '0')))
		++str;

	/*
	 * for each valid digit, shift running value (tval) over to next digit
	 * and add next digit
	 */
	if (base == HEX) {
		while (str < stop) {
			if ((*str >= '0') && (*str <= '9'))
				tval = (tval << 4) + (*str++ - '0');
			else if ((*str >= 'A') && (*str <= 'F'))
				tval = (tval << 4) + 10 + (*str++ - 'A');
			else if ((*str >= 'a') && (*str <= 'f'))
				tval = (tval << 4) + 10 + (*str++ - 'a');
			else
				break;
		}
	} else {
		while ((str < stop) && (*str >= '0') && (*str <= '7'))
			tval = (tval << 3) + (*str++ - '0');
	}
	return (tval);
}

/*
 * ot_asc()
 *	convert an ot_type into a hex/oct ascii string.
 *	pads with LEADING ascii 0s to fill string completely.
 *	NOTE: the string created is NOT TERMINATED.
 */

static int ot_asc(ot_type val, char *str, int len, int base)
{
	char *pt;
	ot_type digit;

	/*
	 * WARNING str is not '\0' terminated by this routine
	 */
	pt = str + len - 1;

	/*
	 * do a tailwise conversion (start at right most end of string to place
	 * least significant digit). Keep shifting until conversion value goes
	 * to zero (all digits were converted)
	 */
	if (base == HEX) {
		while (pt >= str) {
			if ((digit = (val & 0xf)) < 10)
				*pt-- = '0' + (char)digit;
			else
				*pt-- = 'a' + (char)(digit - 10);
			if ((val = (val >> 4)) == (ot_type)0)
				break;
		}
	} else {
		while (pt >= str) {
			*pt-- = '0' + (char)(val & 0x7);
			if ((val = (val >> 3)) == (ot_type)0)
				break;
		}
	}

	/*
	 * pad with leading ascii ZEROS. We return -1 if we ran out of space.
	 */
	while (pt >= str)
		*pt-- = '0';
	if (val != (ot_type)0)
		return (-1);
	return (0);
}

static int vcpio_id(char *blk)
{
	if ((strncmp(blk, AVMAGIC, sizeof(AVMAGIC) - 1) != 0))
		return(-1);
	return(0);
}

static int vcpio_rd(void** ptr, CPIO_OBJ * cpio_obj) {
	HD_VCPIO *hd;
	int nsz;
	ot_type filesize, pad, dpad = 0;

	// check magic
	if(vcpio_id(*ptr)) {
		printf("NOT a cpio object!\n");
		return -1;
	}

	// cast to struct
	hd = *ptr;

	// get the length of the file name
	if ((nsz = (int)asc_ul(hd->c_namesize,sizeof(hd->c_namesize),HEX)) < 2) {
		printf("Invalid namesize!\n");
		return -1;
	}

	// get header padding. header + filename is aligned to 4 byte boundaries
	pad=VCPIO_PAD(sizeof(HD_VCPIO) + nsz);

	// get filesize
	filesize=asc_ot(hd->c_filesize, sizeof(hd->c_filesize), HEX);

	// get data padding
	dpad = VCPIO_PAD(filesize);

	// set data
	cpio_obj->hd = hd;
	cpio_obj->name = (char*)*ptr + sizeof(HD_VCPIO);
	cpio_obj->namesize = nsz;
	cpio_obj->data = (void*)*ptr + sizeof(HD_VCPIO) + nsz + pad;
	cpio_obj->filesize = filesize;

	// new pointer
	*ptr += sizeof(HD_VCPIO) + nsz + pad + filesize + dpad;

	return 0;
}

// returns size of cpio binary
int cpio_write(CPIO_OBJ* cpio_obj, int num, void* destination, unsigned size) {
	int i, pad;
	void* ptr = destination;

	for(i=0; i<num; i++) {
		// header
		HD_VCPIO* hd = ptr;
		if(ptr<(VCPIO_PAD(sizeof(HD_VCPIO)+cpio_obj[i].namesize) + sizeof(HD_VCPIO)+cpio_obj[i].namesize
			+ VCPIO_PAD(cpio_obj[i].filesize) + cpio_obj[i].data, cpio_obj[i].filesize)) {
			printf("%s: buffer is too small!\n", __func__);
		}

		memcpy(ptr, cpio_obj[i].hd, sizeof(HD_VCPIO));
		ptr+=sizeof(HD_VCPIO);

		// update sizes
		if(ot_asc(cpio_obj[i].filesize, hd->c_filesize, sizeof(hd->c_filesize), HEX)) {
			printf("ERROR update filesize\n");
			return -1;
		}
		if(ot_asc(cpio_obj[i].namesize, hd->c_namesize, sizeof(hd->c_namesize), HEX)) {
			printf("ERROR update namesize\n");
			return -1;
		}

		// name
		memcpy(ptr, cpio_obj[i].name, cpio_obj[i].namesize);
		ptr+=cpio_obj[i].namesize;

		// padding
		pad = VCPIO_PAD(sizeof(HD_VCPIO) + cpio_obj[i].namesize);
		memset(ptr, 0, pad);
		ptr+=pad;

		// data
		memcpy(ptr, cpio_obj[i].data, cpio_obj[i].filesize);
		ptr+=cpio_obj[i].filesize;

		// padding
		pad = VCPIO_PAD(cpio_obj[i].filesize);
		memset(ptr, 0, pad);
		ptr+=pad;
	}

	return ptr-destination;
}

// returns num of objects
int cpio_load(void* ptr, CPIO_OBJ* cpio_obj, unsigned long len) {
	void* obj_ptr = ptr;
	int count = 0;

	// read data
	while(obj_ptr<ptr+len) {
		int i = count++;

		if(vcpio_rd(&obj_ptr, &(cpio_obj[i]))) {
			printf("error parsing object! off=%lx\n", obj_ptr-ptr);
			return -1;
		}

		if(strcmp(cpio_obj[i].name, TRAILER)==0)
			break;
	}

	return count;
}
