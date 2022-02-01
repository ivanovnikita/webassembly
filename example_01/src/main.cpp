#include <string_view>

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>

extern "C"
{
    void print_message()
    {
        std::printf("Hello world!\n");
    }

    const char* get_static_message()
    {
        return "Hello world!";
    }

    int copy_message(char* output_buffer, int max_len)
    {
        constexpr std::string_view message = "Hello world!\0";
        std::strncpy(output_buffer, message.data(), max_len);
        return std::min<int>(max_len, message.size());
    }

    const char* get_allocated_message()
    {
        constexpr std::string_view message = "Hello world!\0";
        char* const result = reinterpret_cast<char*>(std::malloc(message.size()));
        assert(result != nullptr);
        std::strncpy(result, message.data(), message.size() + 1);
        return result;
    }
}
