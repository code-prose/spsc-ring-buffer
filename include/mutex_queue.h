#include <atomic>
#include <mutex>
#include <optional>

namespace Mutex {

    template <typename T, std::size_t N>
    class MutexQueue {
    public:
        MutexQueue() = default;
        bool push(T elem);
        std::optional<T> pop();
    private:
        std::size_t front_{0};
        std::size_t back_{0};
        std::mutex mutex_;
        T data_[N];
    };

    template <typename T, std::size_t N>
    bool MutexQueue<T, N>::push(T elem) {
        std::size_t back, front;
        std::lock_guard<std::mutex> lock(mutex_);

        back = back_;
        front = front_; 
        if ((back + 1) % N == front) {
            return false;
        } else {

        }

        data_[back] = elem;
        back_ = (back + 1) % N;
        return true;
    }

    template <typename T, std::size_t N>
    std::optional<T> MutexQueue<T, N>::pop() {
        std::size_t back, front;
        std::lock_guard<std::mutex> lock(mutex_);

        front = front_;
        back = back_;
        if (back == front) {
            return std::nullopt;
        } else {

        }
        T elem = data_[front];
        front_ = (front + 1) % N;
        return elem;
    }

}
