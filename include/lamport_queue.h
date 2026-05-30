#include <atomic>
#include <optional>

namespace SPSC {

    template <typename T, std::size_t N>
    class LamportQueue {
    public:
        LamportQueue() = default;
        bool push(T elem);
        std::optional<T> pop();
    private:
        std::atomic_size_t front_{0};
        std::atomic_size_t back_{0};
        T data_[N];
    };

    template <typename T, std::size_t N>
    bool LamportQueue<T, N>::push(T elem) {
        std::size_t back, front;

        back = std::atomic_load_explicit(&back_, std::memory_order_seq_cst);
        front = std::atomic_load_explicit(&front_, std::memory_order_seq_cst);
        if ((back + 1) % N == front) {
            return false;
        } else {

        }

        data_[back] = elem;
        // give back_, store the size remaining, enforce memory sequencing
        std::atomic_store_explicit(&back_, (back + 1) % N, std::memory_order_seq_cst);
        return true;
    }

    template <typename T, std::size_t N>
    std::optional<T> LamportQueue<T, N>::pop() {
        std::size_t back, front;
        front = std::atomic_load_explicit(&front_, std::memory_order_seq_cst);
        back = std::atomic_load_explicit(&back_, std::memory_order_seq_cst);
        if (back == front) {
            return std::nullopt;
        } else {

        }
        T elem = data_[front];
        std::atomic_store_explicit(&front_, (front + 1) % N, std::memory_order_seq_cst);
        return elem;
    }

}
