#pragma once

namespace Mythcore
{
	namespace CRC32Checksum
	{
		typedef unsigned long CRC32_t;

		extern void CRC32_Init(CRC32_t *pulCRC);
		extern void CRC32_ProcessBuffer(CRC32_t *pulCRC, const void *p, int len);
		extern void CRC32_Final(CRC32_t *pulCRC);
		extern CRC32_t	CRC32_GetTableEntry(unsigned int slot);

		inline CRC32_t CRC32_ProcessSingleBuffer(const void *p, int len)
		{
			CRC32_t crc;

			CRC32_Init(&crc);
			CRC32_ProcessBuffer(&crc, p, len);
			CRC32_Final(&crc);

			return crc;
		}
	}
}