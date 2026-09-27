#pragma once
#include "stdafx.h"
#ifndef DARTHTON_H
#define DARTHTON_H



struct PartData
{
	int32_t mask = 0;
	__m128i needle;


	PartData()
	{
		memset(&needle, 0, sizeof(needle));
	}
};

const void* Search(const uint8_t* data, const uint32_t size, const uint8_t* pattern, const char* mask)
{
	const uint8_t* result = nullptr;
	auto len = strlen(mask);
	auto first = strchr(mask, '?');
	size_t len2 = (first != nullptr) ? (first - mask) : len;
	auto firstlen = min(len2, 16);
	intptr_t num_parts = (len < 16 || len % 16) ? (len / 16 + 1) : (len / 16);
	PartData parts[4];

	for (intptr_t i = 0; i < num_parts; ++i, len -= 16)
	{
		for (size_t j = 0; j < min(len, 16) - 1; ++j)
			if (mask[16 * i + j] == 'x')
				_bittestandset((LONG*)&parts[i].mask, j);

		parts[i].needle = _mm_loadu_si128((const __m128i*)(pattern + i * 16));
	}

	bool abort = false;

#pragma omp parallel for
	for (intptr_t i = 0; i < static_cast<intptr_t>(size) / 32 - 1; ++i)
	{
#pragma omp flush (abort)
		if (!abort)
		{
			auto block = _mm256_loadu_si256((const __m256i*)data + i);
			if (_mm256_testz_si256(block, block))
				continue;

			auto offset = _mm_cmpestri(parts->needle, firstlen, _mm_loadu_si128((const __m128i*)(data + i * 32)), 16, _SIDD_CMP_EQUAL_ORDERED);
			if (offset == 16)
			{
				offset += _mm_cmpestri(parts->needle, firstlen, _mm_loadu_si128((const __m128i*)(data + i * 32 + 16)), 16, _SIDD_CMP_EQUAL_ORDERED);
				if (offset == 32)
					continue;
			}

			for (intptr_t j = 0; j < num_parts; ++j)
			{
				auto hay = _mm_loadu_si128((const __m128i*)(data + (2 * i + j) * 16 + offset));
				auto bitmask = _mm_movemask_epi8(_mm_cmpeq_epi8(hay, parts[j].needle));
				if ((bitmask & parts[j].mask) != parts[j].mask)
					goto next;
			}

			result = data + 32 * i + offset;
			abort = true;
#pragma omp flush (abort)
		}
		

	next:;
	}

	return result;
}

//struct DARTH_TON2 : public BenchBase
//{
//	virtual void init(Tests test)
//	{
//		switch (test)
//		{
//		case Tests::First:
//			pattern = "\x45\x43\x45\x55\x33\x9a\xfa\x00\x00\x00\x00\x45\x68\x21";
//			mask = "xxxxxxx????xxx";
//			break;
//		case Tests::Second:
//			pattern = "\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xaa\xbb\xaa\x00\x00\x00\x00\x45\x68\x21";
//			mask = "xxxxxxxxxxx????xxx";
//			break;
//		}
//	}
//
//	virtual LPVOID runOne(PBYTE baseAddress, DWORD size)
//	{
//		return const_cast<LPVOID>(Search(baseAddress, size, reinterpret_cast<const uint8_t*>(pattern), mask));
//	}
//	virtual const char* name() const
//	{
//		return "DarthTon v2";
//	}
//
//	const char* pattern = nullptr;
//	const char* mask = nullptr;
//};
//
//REGISTER(DARTH_TON2);

#endif 