#include "../Vector.hpp"
#include "../Vextras.hpp"
#include <vector>
 #include <sys/time.h>


time_t timer() {
   struct timeval start = {};
   gettimeofday(&start, nullptr);
   time_t msecs_time = (start.tv_sec * 1000) + (start.tv_usec / 1000);
   return msecs_time;
}

time_t g_start1;
time_t g_end1;
time_t g_start2;
time_t g_end2;


int main() {
	ft::Vector<int> vector;
    std::vector<int> v;
	ft::Vector<int> tmp0(vector); // add Vector<int> vector;
    ft::Vector<int> tmp(10000000, 4), tmp2(10000000, 5);
    tmp = tmp2;
    ft::Vector<int> tmp3(tmp);
    g_start2 = timer();
    ft::Vector<int> tmp4(tmp.begin(), tmp.end());
    g_end2 = timer();
    v.push_back(tmp4.size());
    v.push_back(tmp4.capacity());
    v.push_back(tmp[2]);
    v.push_back(tmp3[2]);
    v.push_back(tmp4[2]);
    try { ft::Vector<int> tmp5(-1, -1); }
    catch (std::exception &e) { v.push_back(1); }
    return 0;


}