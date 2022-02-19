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

    void invoke_assert()
    {
        assert(false);
    }

    void write_to_file()
    {
        constexpr const char* filename = "tmp_file.txt";
        FILE* file = std::fopen(filename, "w+");
        if (file == nullptr)
        {
            std::perror("Can't open file");
            return;
        }

        std::fprintf(file, "Hello world!");

        std::fclose(file);
    }

    void read_from_file()
    {
        constexpr const char* filename = "tmp_file.txt";
        FILE* file = std::fopen(filename, "r+");
        if (file == nullptr)
        {
            std::perror("Can't open file\n");
            return;
        }

        int c = 0;
        while ((c = std::fgetc(file)) != EOF)
        {
           std::putchar(c);
        }

        std::printf("\n");

        std::fclose(file);
    }
}
