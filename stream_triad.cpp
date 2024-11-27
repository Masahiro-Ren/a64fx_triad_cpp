#include <iostream>
#include <chrono>
#include <numeric>
#include <cmath>
#include <omp.h>

using std::cout;
using std::endl;

using STREAM_DATA_TYPE = double;

static constexpr size_t ARR_SIZE = 1073741824;
static constexpr size_t TO_MB = 1024 * 1024;
static constexpr size_t NTIMES = 20;

static STREAM_DATA_TYPE* a;
static STREAM_DATA_TYPE* b;
static STREAM_DATA_TYPE* c;
static STREAM_DATA_TYPE scalar = 2.0;

void stream_triad(double* a, double* b, double* c, const double& scalar)
{
    #pragma omp parallel for schedule(static)
    for(size_t i = 0; i < ARR_SIZE; i++)
        a[i] = b[i] + scalar * c[i];
}


int main()
{
    size_t num_threads = omp_get_max_threads();
    cout << "Size per array: " << (ARR_SIZE * sizeof(STREAM_DATA_TYPE)) / TO_MB << " MB." << endl;
    cout << "Size per element: " << sizeof(STREAM_DATA_TYPE) << " bytes." << endl;
    cout << "Executing " << NTIMES << " times in " << num_threads << " threads." << endl;


    a = new STREAM_DATA_TYPE[ARR_SIZE];
    b = new STREAM_DATA_TYPE[ARR_SIZE];
    c = new STREAM_DATA_TYPE[ARR_SIZE];

    // Considering NUMA first touch
    #pragma omp parallel for schedule(static)
    for(size_t i = 0; i < ARR_SIZE; i++)
    {
        a[i] = 4.0;
        b[i] = 6.0;
        c[i] = 0.0;
    }

    double max_time = 0.0;
    double min_time = std::numeric_limits<double>::max();
    double avg_time = 0.0;

    for(size_t n = 0; n < NTIMES; n++)
    {
        auto t_start = std::chrono::high_resolution_clock::now();
        stream_triad(a, b, c, scalar);
        auto t_end = std::chrono::high_resolution_clock::now();

        auto elapsed = std::chrono::duration<double, std::micro>(t_end - t_start).count();
        // micro second to second
        elapsed *= 1.0E-6;
        max_time = std::max(max_time, elapsed);
        min_time = std::min(max_time, elapsed);
        avg_time += elapsed;
    }

    double TOTAL_SIZE = (3.0 * sizeof(STREAM_DATA_TYPE) * ARR_SIZE) / TO_MB;

    cout << "Best rate: " << TOTAL_SIZE / min_time << " MB/s" << endl;
    cout << "Max time:" << max_time << " s" << endl;
    cout << "Min time:" << min_time << " s" << endl;
    cout << "Avg time:" << avg_time / NTIMES << " s" << endl;

    delete[] a;
    delete[] b;
    delete[] c;

    return 0;
}
