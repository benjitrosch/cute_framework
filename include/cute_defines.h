/*
	Cute Framework
	Copyright (C) 2023 Randy Gaul https://randygaul.github.io/

	This software is provided 'as-is', without any express or implied
	warranty.  In no event will the authors be held liable for any damages
	arising from the use of this software.

	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it
	freely, subject to the following restrictions:

	1. The origin of this software must not be misrepresented; you must not
	   claim that you wrote the original software. If you use this software
	   in a product, an acknowledgment in the product documentation would be
	   appreciated but is not required.
	2. Altered source versions must be plainly marked as such, and must not be
	   misrepresented as being the original software.
	3. This notice may not be removed or altered from any source distribution.
*/

#ifndef CUTE_DEFINES_H
#define CUTE_DEFINES_H

#ifndef _CRT_SECURE_NO_WARNINGS
#	define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef _CRT_NONSTDC_NO_DEPRECATE
#	define _CRT_NONSTDC_NO_DEPRECATE
#endif

#if defined(_WIN32)
#	define CUTE_WINDOWS 1
#elif defined(__linux__) || defined(__unix__) && !defined(__APPLE__) && !defined(__EMSCRIPTEN__)
#	define CUTE_LINUX 1
#elif defined(__APPLE__)
#	include <TargetConditionals.h>
#	if TARGET_IPHONE_SIMULATOR || TARGET_OS_IPHONE
#		define CUTE_IOS 1
#	elif TARGET_OS_MAC
#		define CUTE_MACOSX 1
#	else
#		error "Unknown Apple platform"
#	endif
#elif defined(__ANDROID__)
#	define CUTE_ANDROID 1
#elif defined(__EMSCRIPTEN__)
#	define CUTE_EMSCRIPTEN 1
#endif

// Vista and later only. This helps MingW builds.
#ifdef CUTE_WINDOWS
#	include <sdkddkver.h>
#	ifdef _WIN32_WINNT
#		if _WIN32_WINNT < 0x0600
#			undef _WIN32_WINNT
#			define _WIN32_WINNT 0x0600
#		endif
#	endif
#endif

#include <stdint.h>

#ifndef NOMINMAX
#	define NOMINMAX WINDOWS_IS_ANNOYING_AINT_IT
#endif

#ifndef CUTE_STATIC
#	ifdef _MSC_VER
#		ifdef CUTE_EXPORT
#			define CUTE_API __declspec(dllexport)
#		else
#			define CUTE_API __declspec(dllimport)
#		endif
#	else
#		if ((__GNUC__ >= 4) || defined(__clang__))
#			define CUTE_API __attribute__((visibility("default")))
#		else
#			define CUTE_API
#		endif
#	endif
#	define SOKOL_DLL
#else
#	define CUTE_API
#endif

#ifdef CUTE_WINDOWS
#	define CUTE_CALL __cdecl
#else
#	define CUTE_CALL
#endif

#define CUTE_UNUSED(x) (void)x
#define CUTE_ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CUTE_INLINE inline
#define CUTE_KB 1024
#define CUTE_MB (CUTE_KB * CUTE_KB)
#define CUTE_GB (CUTE_MB * CUTE_MB)
#define CUTE_SERIALIZE_CHECK(x) do { if ((x) != SERIALIZE_SUCCESS) goto cute_error; } while (0)
#define CUTE_STATIC_ASSERT(condition, error_message_string) static_assert(condition, error_message_string)
#define CUTE_STRINGIZE_INTERNAL(...) #__VA_ARGS__
#define CUTE_STRINGIZE(...) CUTE_STRINGIZE_INTERNAL(__VA_ARGS__)
#define CUTE_OFFSET_OF(T, member) ((size_t)((uintptr_t)(&(((T*)0)->member))))
#define CUTE_DEBUG_PRINTF(...)
#define CUTE_ALIGN_TRUNCATE(v, n) ((v) & ~((n) - 1))
#define CUTE_ALIGN_FORWARD(v, n) CUTE_ALIGN_TRUNCATE((v) + (n) - 1, (n))
#define CUTE_ALIGN_TRUNCATE_PTR(p, n) ((void*)CUTE_ALIGN_TRUNCATE((uintptr_t)(p), n))
#define CUTE_ALIGN_FORWARD_PTR(p, n) ((void*)CUTE_ALIGN_FORWARD((uintptr_t)(p), n))

#ifdef __cplusplus
#	ifndef CUTE_NO_CPP
#		define CUTE_CPP
#	endif
#endif

#define SOKOL_API_DECL CUTE_API

#if defined(CUTE_WINDOWS)
#	define SOKOL_D3D11
#elif defined(CUTE_LINUX)
#	define SOKOL_GLCORE33
#elif defined(CUTE_MACOSX)
#	define SOKOL_GLCORE33
#elif defined(CUTE_EMSCRIPTEN)
#	define SOKOL_GLES3
#	include <emscripten.h>
#endif

#define IMGUI_INCLUDE_IMCONFIG_H

#include <stdlib.h>

#ifndef __cplusplus
#include <stdbool.h>
#endif

#ifndef CUTE_NO_WARNINGS
#	define CUTE_WARN(...) fprintf(stderr, __VA_ARGS__)
#endif

#ifdef CUTE_CPP
// -------------------------------------------------------------------------------------------------
// Avoid including <utility> header to reduce compile times.

template <typename T>
struct cf_remove_reference
{
	using type = T;
};

template <typename T>
struct cf_remove_reference<T&>
{
	using type = T;
};

template <typename T>
struct cf_remove_reference<T&&>
{
	using type = T;
};

template <typename T>
constexpr typename cf_remove_reference<T>::type&& move(T&& arg) noexcept
{
	return (typename cf_remove_reference<T>::type&&)arg;
}

// -------------------------------------------------------------------------------------------------
// Avoid including <initializer_list> header to reduce compile times.
// Unfortunately this class *must* be in the std:: namespace or things won't compile. So we try to
// avoid defining this class if someone already included <initializer_list> before including
// cute framework <cute.h>.

#ifdef CUTE_WINDOWS

#if !defined(_INITIALIZER_LIST_) && !defined(_INITIALIZER_LIST) && !defined(_LIBCPP_INITIALIZER_LIST)
#define _INITIALIZER_LIST_ // MSVC
#define _INITIALIZER_LIST  // GCC
#define _LIBCPP_INITIALIZER_LIST // Clang
// Will probably need to add more here for more compilers later.

namespace std
{
template <typename T>
class initializer_list
{
public:
	using value_type = T;
	using reference = const T&;
	using const_reference = const T&;
	using size_type = size_t;

	using iterator = const T*;
	using const_iterator = const T*;

	constexpr initializer_list() noexcept
		: m_first(0)
		, m_last(0)
	{}

	constexpr initializer_list(const T* first, const T* last) noexcept
		: m_first(first)
		, m_last(last)
	{}

	constexpr const T* begin() const noexcept { return m_first; }
	constexpr const T* end() const noexcept { return m_last; }
	constexpr size_t size() const noexcept { return (size_t)(m_last - m_first); }

private:
	const T* m_first;
	const T* m_last;
};

template <class T> constexpr const T* begin(initializer_list<T> list) noexcept { return list.begin(); }
template <class T> constexpr const T* end(initializer_list<T> list) noexcept { return list.end(); }
}

#endif

#else // CUTE_WINDOWS

#include <initializer_list>

#endif // CUTE_WINDOWS

template <typename T>
using CF_InitializerList = std::initializer_list<T>;

namespace Cute
{
template <typename T>
using initializer_list = CF_InitializerList<T>;

template <typename T>
using remove_reference = cf_remove_reference<T>;
}

#endif // CUTE_CPP

// Not sure where to put this... Here is good I guess.
CUTE_INLINE uint64_t cf_fnv1a(const void* data, int size)
{
	const char* s = (const char*)data;
	uint64_t h = 14695981039346656037ULL;
	char c = 0;
	while (size--) {
		h = h ^ (uint64_t)(*s++);
		h = h * 1099511628211ULL;
	}
	return h;
}

#endif // CUTE_DEFINES_H
