#include <iostream>
#include <map>
#include <string>
#include <sys/time.h>

#define DEBUG 0
#define DEFAULT_WIDOW 100

long millis() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return (t.tv_sec * 1000) + (t.tv_usec / 1000);
}

int main(int argc, char** argv) {
    std::map<std::string, long> cache;

    // Get the window size from the arguments
    int window = (argc > 1) ? atoi(argv[1]) : DEFAULT_WIDOW;

    // Read from stdin
    for (std::string line; std::getline(std::cin, line);) {

        // Clear the cache
        long now = millis();
        for (auto it = cache.cbegin(); it != cache.cend();) {
            long cacheMillis = it->second;
            if(cacheMillis + window < now) {
                cache.erase(it++);
            } else {
                ++it;
            }
        }

        // Check if the line was already in the cache
        std::map<std::string, long>::iterator cacheHit = cache.find(line);

        // If it's not present, print the line and add it to the cache
        if (cacheHit == cache.end()) {
            std::cout << line << std::endl;
            cache[line] = now;
        } else if (DEBUG) {
            std::printf(
                "!!! Ignored line \"%s\" - cache=%ld - now=%ld\n",
                line.c_str(),
                cacheHit->second,
                now
            );
        }
    }

    return 0;
}

