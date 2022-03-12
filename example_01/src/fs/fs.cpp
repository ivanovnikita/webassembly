#include <cstdio>
#include <cstring>

extern "C"
{
    void write_to_file(const char* filename, const char* text_to_print)
    {
        FILE* file = std::fopen(filename, "w+");
        if (file == nullptr)
        {
            std::perror("Can't open file");
            return;
        }

        std::fwrite(text_to_print, sizeof(char), std::strlen(text_to_print), file);
        std::fflush(file);

        std::fclose(file);
    }

    void read_from_file(const char* filename)
    {
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

        std::putchar('\n');

        std::fclose(file);
    }
}
