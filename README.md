# Reference Material
1. [Proving the Correctness of Multiprocess Progams](https://lamport.azurewebsites.net/pubs/proving.pdf)
1. [Lamport's Seminal Paper on Temporal Logic](https://lamport.azurewebsites.net/pubs/spec.pdf)
1. [Le et al, Correct and Efficient Bounded FIFO Queues](https://inria.hal.science/hal-00911893/document)
1. [Cache-aware design of general purpose SPSC queues](https://arpi.unipi.it/bitstream/11568/942147/7/master.pdf)
1. [Blog post exploring these papers](https://rlc.vlinder.ca/blog/2015/11/06/interesting-modifications-to-the-lamport-queue)


------------------------------------------------------------------------------------------
## Benchmarking
#### CPU Caches:
- L1 Data 64 KiB
- L1 Instruction 128 KiB
- L2 Unified 4096 KiB (x10)
Load Average: 1.95, 2.96, 3.74
#### Benchmark                                                Time             CPU   Iterations
BM_Queue_Spec<Mutex::MutexQueue<int, 1024>>         843308 ns       673266 ns         1052
BM_Queue_Spec<Lamport::LamportQueue<int, 1024>>     473487 ns       450476 ns         1474
BM_Queue_Spec<SPSC::RingBuffer<int, 1024>>          454338 ns       431179 ns         1618


## Observations
We can see a significant perf increase from not paying the mutex overhead.
My curiosity asked my the RingBuffer impl wasn't a significant performance increase over the original LamportQueue,
this lead me to find the existence of MFENCE. This is an expensive operation to pay normally that results from seq_cst on x86.
std::memory_order_seq_cst uses `ldar` and `stlr` on ARM to avoid this.

------------------------------------------------------------------------------------------


------------------------------------------------------------------------------------------
### Benchmark with alignas(64)
#### CPU Caches:
- L1 Data 64 KiB
- L1 Instruction 128 KiB
- L2 Unified 4096 KiB (x10)
Load Average: 3.29, 3.91, 3.90
#### Benchmark                                                Time             CPU   Iterations
BM_Queue_Spec<Mutex::MutexQueue<int, 1024>>         830879 ns       656196 ns         1070
BM_Queue_Spec<Lamport::LamportQueue<int, 1024>>     480804 ns       456452 ns         1488
BM_Queue_Spec<SPSC::RingBuffer<int, 1024>>          438413 ns       415397 ns         1628


### Observations
When using alignas(64) for `front_` and `back_` we can we another small bump in performance because we are avoiding bad cache evictions due to false sharing

------------------------------------------------------------------------------------------


------------------------------------------------------------------------------------------
### Benchmark with alignas(128)
#### CPU Caches:
- L1 Data 64 KiB
- L1 Instruction 128 KiB
- L2 Unified 4096 KiB (x10)
Load Average: 3.54, 3.54, 3.73
#### Benchmark                                                Time             CPU   Iterations
BM_Queue_Spec<Mutex::MutexQueue<int, 1024>>         843798 ns       666279 ns         1056
BM_Queue_Spec<Lamport::LamportQueue<int, 1024>>     536653 ns       513953 ns         1000
BM_Queue_Spec<SPSC::RingBuffer<int, 1024>>          446212 ns       421031 ns         1589


### Observations
Dealing with more cache interference as we over-align the data

------------------------------------------------------------------------------------------
