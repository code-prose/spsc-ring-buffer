#include <print>
#include "lamport_queue.h"
#include "optimized_ring_buffer.h"
#include "mutex_queue.h"
#include <thread>


const int ITERATIONS = 1000;

void ringbuf_producer(SPSC::RingBuffer<int, ITERATIONS>& q);
void ringbuf_consumer(SPSC::RingBuffer<int, ITERATIONS>& q);
void lamport_producer(Lamport::LamportQueue<int, ITERATIONS>& q);
void lamport_consumer(Lamport::LamportQueue<int, ITERATIONS>& q);
void mutex_producer(Mutex::MutexQueue<int, ITERATIONS>& q);
void mutex_consumer(Mutex::MutexQueue<int, ITERATIONS>& q);

int main() {
    SPSC::RingBuffer<int, ITERATIONS> queue;
    std::thread p{ringbuf_producer, std::ref(queue)};
    std::thread c{ringbuf_consumer, std::ref(queue)};
    p.join();
    c.join();

    return 0;
}


void ringbuf_producer(SPSC::RingBuffer<int, ITERATIONS>& q) {
    for (int i = 0; i < ITERATIONS; i++) {
        q.push(i);
    }
}

void ringbuf_consumer(SPSC::RingBuffer<int, ITERATIONS>& q) {
    for (int i = 0; i < ITERATIONS; i++) {
        if (auto val = q.pop()) {
            std::print("consumer value: {}\n", *val);
        }
    }
}

void lamport_producer(Lamport::LamportQueue<int, ITERATIONS>& q) {
    for (int i = 0; i < ITERATIONS; i++) {
        q.push(i);
    }
}

void lamport_consumer(Lamport::LamportQueue<int, ITERATIONS>& q) {
    for (int i = 0; i < ITERATIONS; i++) {
        if (auto val = q.pop()) {
            std::print("consumer value: {}\n", *val);
        }
    }
}

void mutex_producer(Mutex::MutexQueue<int, ITERATIONS>& q) {
    for (int i = 0; i < ITERATIONS; i++) {
        q.push(i);
    }
}

void mutex_consumer(Mutex::MutexQueue<int, ITERATIONS>& q) {
    for (int i = 0; i < ITERATIONS; i++) {
        if (auto val = q.pop()) {
            std::print("consumer value: {}\n", *val);
        }
    }
}
