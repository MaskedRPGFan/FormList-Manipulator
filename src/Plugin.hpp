#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include "RE/Skyrim.h"
#include "SKSE/SKSE.h"

#include <REL/Relocation.h>
#include <boost/regex.hpp>
#include <string_view>
#include <spdlog/sinks/basic_file_sink.h>
#include <ClibUtil/utils.hpp>
#include <ankerl/unordered_dense.h>

using namespace std::literals;

namespace logger = SKSE::log;
namespace string = clib_util::string;

using RNG = clib_util::RNG;

namespace util
{
	using SKSE::stl::report_and_fail;
}

#define DLLEXPORT __declspec(dllexport)

namespace Plugin
{
	inline constexpr REL::Version VERSION
	{
		// clang-format off
		1u,
		7u,
		0u,
		// clang-format on
	};

	inline constexpr auto NAME = "FormListManipulator"sv;
	inline constexpr auto AUTHOR = "MaskedRPGFan"sv;
}
