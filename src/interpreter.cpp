#if defined(_MSC_VER)
#define _CRT_SECURE_NO_WARNINGS
#endif

// You can define H9PLUS_MODE to ignore the Q command (making it a H9+
// interpreter), and you can define HQ9PLUSPLUS mode to parse ++ as
// instantiating a new subclass of a generic superclass (making it a HQ9++
// interpreter).

#if defined(H9PLUS_MODE) && defined(HQ9PLUSPLUS_MODE)
#error "H9+ mode and HQ9++ mode can't be active at the same time."
#endif

#include <cctype>
#include <cinttypes>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <vector>

#if !defined(H9PLUS_MODE)
static void print_char_vector(const std::vector<char> vector) {
    for (char current : vector) {
        putc(current, stdout);
    }
}
#endif

static void print_99_bottles() {
    for (int counter = 99; counter > 0; --counter) {
        const char *before = (counter >= 2) ? " bottles" : " bottle";
        const char *after = (counter > 2) ? " bottles" : " bottle";

        printf("%d %s of beer on the wall,\n", counter, before);
        printf("%d %s of beer.\n", counter, before);
        printf("Take one down, pass it around,\n");

        if (counter > 1) {
            printf("%d %s of beer on the wall.\n", counter - 1, after);
        } else {
            printf("no more bottles of beer on the wall.\n");
        }
    }
}

static std::vector<char> read_source() {
    std::vector<char> result;
    char current = '\0';
    while (true) {
        current = getc(stdin);
	if (current == EOF || current == '\n') break;
        result.push_back(current);
    }
    return result;
}

int main(int argc, char **argv) {
    bool verbose = false;
    uintmax_t accumulator = 0;

    --argc, ++argv;
    for (int i = 0; i < argc; ++i) {
        if (strcmp(argv[i], "--verbose") == 0) {
            verbose = true;
        }
    }

    const std::vector<char> source = read_source();

#if defined(HQ9PLUSPLUS_MODE)
    char previous = '\0';
    class generic_superclass {};
#endif

    for (char c : source) {
#if defined(HQ9PLUSPLUS_MODE)
        if (c != '+')
            previous = c;
#endif
        switch (toupper(c)) {
            case 'H':
                printf("Hello, world!\n");
                break;
#if !defined(H9PLUS_MODE)
            case 'Q':
                print_char_vector(source);
		putc('\n', stdout);
                break;
#endif
            case '9':
                print_99_bottles();
                break;
            case '+':
#if defined(HQ9PLUSPLUS_MODE)
                if (previous == '+') {
                    previous = '\0';
                    class unreachable_subclass : public generic_superclass {};
                    unreachable_subclass *address = new unreachable_subclass;
                    if (verbose)
                        printf("New subclass at address %" PRIuPTR ".\n",
                               uintptr_t(address));
                } else {
                    previous = '+';
                }
#endif
                ++accumulator;
                if (verbose)
                    printf("Accumulator increased to %" PRIuMAX ".\n",
                           accumulator);
                break;
            default:
                break;
        }
    }

    if (verbose)
        printf("Accumulator is at %" PRIuMAX ".\n", accumulator);
    return 0;
}
