# SetEnhancedInstructionSets.cmake
include(CheckCXXCompilerFlag)


# 为 GCC 和 Clang 添加增强指令集
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    check_cxx_compiler_flag("-mavx2" COMPILER_SUPPORTS_AVX2)
    if(COMPILER_SUPPORTS_AVX2)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx2 -mfma")
        message(STATUS "Using AVX2 and FMA instructions on GCC or Clang.")
    else()
        check_cxx_compiler_flag("-mavx" COMPILER_SUPPORTS_AVX)
        if(COMPILER_SUPPORTS_AVX)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx")
            message(STATUS "Using AVX instructions on GCC or Clang.")
        else()
            check_cxx_compiler_flag("-msse4.2" COMPILER_SUPPORTS_SSE42)
            if(COMPILER_SUPPORTS_SSE42)
                set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse4.2")
                message(STATUS "Using SSE4.2 instructions on GCC or Clang.")
            else()
                message(WARNING "No enhanced instruction set supported by the compiler on GCC or Clang.")
            endif()
        endif()
    endif()


    # 检查并添加 AVX512 支持
    check_cxx_compiler_flag("-mavx512f" COMPILER_SUPPORTS_AVX512F)
    if(COMPILER_SUPPORTS_AVX512F)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx512f")
        message(STATUS "Using AVX512F instructions on GCC or Clang.")
    else()
        message(WARNING "AVX512F not supported by the compiler on GCC or Clang. Check your CPU and compiler version.")
    endif()
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    # 为 Visual C++ 添加增强指令集
    include(CheckCXXSourceRuns)
    check_cxx_source_runs("
        #include <immintrin.h>
        int main() {
            __m256 a = _mm256_set_ps(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f);
            return 0;
        }"
        COMPILER_SUPPORTS_AVX)
    if(COMPILER_SUPPORTS_AVX)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:AVX")
        message(STATUS "Using AVX instructions on MSVC.")
    else()
        check_cxx_source_runs("
            #include <emmintrin.h>
            int main() {
                __m128 a = _mm_set_ps(1.0f, 2.0f, 3.0f, 4.0f);
                return 0;
            }"
            COMPILER_SUPPORTS_SSE)
        if(COMPILER_SUPPORTS_SSE)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:SSE")
            message(STATUS "Using SSE instructions on MSVC.")
        else()
            message(WARNING "No enhanced instruction set supported by the compiler on MSVC.")
        endif()
    endif()


    # 检查并添加 AVX512 支持
    check_cxx_source_runs("
        #include <immintrin.h>
        int main() {
            __m512 a = _mm512_set_ps(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
            return 0;
        }"
        COMPILER_SUPPORTS_AVX512F)
    if(COMPILER_SUPPORTS_AVX512F)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:AVX512")
        message(STATUS "Using AVX512F instructions on MSVC.")
    else()
        message(WARNING "AVX512F not supported by the compiler on MSVC. Check your CPU and compiler version.")
    endif()
else()
    message(WARNING "Unknown compiler.")
endif()