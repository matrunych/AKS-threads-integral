#include <iostream>
#include <math.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <thread>
#include <vector>
#include <mutex>
#include <utility>
#include <algorithm>
#include <cmath>

inline std::chrono::steady_clock::time_point get_current_time_fenced() {
    //assert(std::chrono::steady_clock::is_steady &&
    //     "Timer should be steady (monotonic).");
    std::atomic_thread_fence(std::memory_order_seq_cst);
    auto res_time = std::chrono::steady_clock::now();
    std::atomic_thread_fence(std::memory_order_seq_cst);
    return res_time;
}

template<class D>
inline long long to_us(const D &d) {
    return std::chrono::duration_cast<std::chrono::microseconds>(d).count();
}

struct configuration_t {
    double rel_err, abs_err;
    size_t num_of_thr;
    double x_low, x_upper, y_low, y_upper;
    size_t initial_steps;
    size_t m;
};

configuration_t read_conf(std::istream &cf) {
    std::ios::fmtflags flags(cf.flags()); // Save stream state
    cf.exceptions(std::ifstream::failbit); // Enable exception on fail

    configuration_t res;
    std::string temp;

    try {
        cf >> res.rel_err;
        getline(cf, temp); // Відкидаємо комент.
        cf >> res.abs_err;
        getline(cf, temp);
        cf >> res.num_of_thr;
        getline(cf, temp);
        cf >> res.x_low;
        getline(cf, temp);
        cf >> res.x_upper;
        getline(cf, temp);
        cf >> res.y_low;
        getline(cf, temp);
        cf >> res.y_upper;
        getline(cf, temp);
        cf >> res.initial_steps;
        getline(cf, temp);
        cf >> res.m;
        getline(cf, temp);
    } catch (std::ios_base::failure &fail) // Life without RAII is hard...
    {
        cf.flags(flags);
        throw; // re-throw exception
    }
    cf.flags(flags);
    if (res.x_upper <= res.x_low) {
        throw std::runtime_error("x1 should be <= x2");
    }
    if (res.y_upper <= res.y_low) {
        throw std::runtime_error("x1 should be <= x2");
    }
    if (res.initial_steps < 10) {
        throw std::runtime_error("Too few initial_steps");
    }
    if (res.abs_err <= 0 || res.rel_err <= 0) {
        throw std::runtime_error("Errors should be positive");
    }

    return res;
}


double function_sum(int m, double x1, double x2) {
    double sum_x1 = 0.0;
    double sum_x2 = 0.0;
    double result = 0.0;
    for (int i = 1; i <= m; i++) {
        sum_x1 += i * cos((i + 1) * x1 + 1);
        sum_x2 += i * cos((i + 1) * x2 + 1);
    }

    result = -sum_x1 * sum_x2;

    return result;
}


double integral_new(double ax, double bx, double ay, double by, int n, int m) {
    double step_x = (bx - ax) / n;
    double step_y = (by - ay) / n;
    double area = 0.0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            area += function_sum(m, ax + (i + 0.5) * step_x, ay + (j + 0.5) * step_y) * step_x * step_y;
        }
    }
    return area;
}


void integral_threads(double x_low, double x_upper, double y_low, double y_upper, size_t step, size_t m, std::mutex &mx,
                      double &res) {
    res = integral_new(x_low, x_upper, y_low, y_upper, step, m);
    std::lock_guard<std::mutex> lg{mx};

}


int main(int argc, char *argv[]) {

    std::string filename("config.txt");
    if (argc == 2)
        filename = argv[1];
    if (argc > 2) {
        std::cerr << "Too many arguments. Usage: \n"
                     "<program>\n"
                     "or\n"
                     "<program> <config-filename>\n" << std::endl;
        return 1;
    }
    std::ifstream config_stream(filename);
    if (!config_stream.is_open()) {
        std::cerr << "Failed to open configuration file " << filename << std::endl;
        return 2;
    }

    configuration_t config;
    try {
        config = read_conf(config_stream);
    }
    catch (std::exception &ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 3;
    }
    std::mutex mx;
    int num_of_thr = config.num_of_thr;
    int m = config.m;
    double x = config.x_low;
    double y = config.y_low;
    double steps = config.initial_steps;
    double y_upp = config.y_upper;

    double res_local[num_of_thr];

    double delta_x = (config.x_upper - config.x_low) / (double) num_of_thr;

    bool to_continue = true;
    double step_thr;
    double cur_res;
    double prev_res;
    double integ_res;
    double abs_err;
    double rel_err;


    auto start_time = get_current_time_fenced();
    while (to_continue) {

        x = config.x_low;
        step_thr = steps / num_of_thr;
        integ_res = 0.0;
        std::vector<std::thread> v;
        prev_res = cur_res;
        for (int i = 0; i < num_of_thr; i++) {
            v.emplace_back(integral_threads, x, x + delta_x, y, y_upp, step_thr, m, std::ref(mx),
                           std::ref(res_local[i]));
            x += delta_x;

        }
        for (auto &t: v) {
            t.join();
        }
        for (auto x: res_local) {
            integ_res += x;
        }
        cur_res = integ_res;
        steps *= 2;
        abs_err = std::abs(prev_res - cur_res);
        rel_err = std::abs(prev_res - cur_res) / std::abs(prev_res);
        to_continue = (abs_err > config.abs_err);
        to_continue = to_continue && (rel_err > config.rel_err);
    }

    auto finish_time = get_current_time_fenced();
    auto total_time = finish_time - start_time;
    std::cout << "Integral " << cur_res << std::endl;
    std::cout << "Abs error " << abs_err << std::endl;
    std::cout << "Rel error " << rel_err << std::endl;
    std::cout << "Time " << to_us(total_time) << std::endl;


    return 0;
}
