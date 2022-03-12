#include <string_view>

#include <cassert>
#include <cstdio>
#include <cstring>

extern "C"
{
    void print_message()
    {
        std::printf("Hello world!\n"); // it is important to print '\n' to flush text to console
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

    void invoke_assert()
    {
        assert(false);
    }

    void throw_exception()
    {
        throw std::logic_error("logic error");
    }
}
