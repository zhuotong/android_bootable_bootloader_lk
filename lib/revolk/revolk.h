#ifndef REVOLK_H
#define REVOLK_H

#include <stdint.h>

int revolk_init(void);
int revolk_partition_read(uint64_t data_addr, uint32_t *out, uint32_t data_len);

#endif /* REVOLK_H */
