#include <print>
#include "lamport_queue.h"

int main() {
    SPSC::LamportQueue<int, 5> queue;
    queue.push(4);
    queue.push(3);
    queue.push(2);
    queue.push(1);
    if (auto val = queue.pop()) {
        std::printf("{}", *val);
    }
    return 0;
}
