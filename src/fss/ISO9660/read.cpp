#include "ISO9660.hpp"
#include <userspace/ISO9660.hpp>
#include <cstdio>
#include <shared_memory>

bool ISO9660::read(Inode inode, uint8_t* data, size_t page) {
	std::SMID smid = std::smMake();
	uint8_t* buffer = (uint8_t*)std::smMap(smid);
	std::smAllow(smid, pid);

	bool ret = std::rpc(pid, std::ISO9660::READ, smid, inode, page, 1);
	memcpy(data, buffer, PAGE_SIZE);

	std::munmap(buffer);
	std::smDrop(smid);
	return ret;
}
