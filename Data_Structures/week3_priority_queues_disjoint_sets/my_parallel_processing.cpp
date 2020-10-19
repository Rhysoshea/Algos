#include <iostream>
#include <cassert>
#include <random>
#include <vector>
#include <algorithm>
#include <string>
#include <sys/time.h>
#include <csignal>
#include <queue>

using std::vector;
using std::cin;
using std::cout;
using namespace std;

/*
You have a program which is parallelized and uses 𝑛 independent threads to process the given list of 𝑚 jobs. Threads take jobs in the order they are given in the input. If there is a free thread, it immediately takes the next job from the list. If a thread has started processing a job, it doesn’t interrupt or stop until it finishes processing the job. If several threads try to take jobs from the list simultaneously, the thread with smaller index takes the job. For each job you know exactly how long will it take any thread to process this job, and this time is the same for all the threads. You need to determine for each job which thread will process it and when will it start processing.
*/
struct Thread {
  int id;
  long long finish_time;

};

class HeapBuilder {
  vector< Thread > data_;

public:
  HeapBuilder(int workers) {
    data_.resize(workers);
    for(int i = 0; i < workers; ++i){
      data_[i].id = i;
      data_[i].finish_time = 0;
    }
  }

  void siftDown(int i) {
    // cout << "i: " << i << "\n";
    int minIndex = i;
    int l = 2*i+1;
    int r = 2*i+2;

    if (l < data_.size() && data_[l].finish_time <= data_[minIndex].finish_time) {
      if (data_[l].finish_time < data_[minIndex].finish_time) {
        minIndex = l;
      }
      else if (data_[l].finish_time == data_[minIndex].finish_time && data_[l].id < data_[minIndex].id) {
        minIndex = l;
      }
    }
    if (r < data_.size() && data_[r].finish_time <= data_[minIndex].finish_time) {
      if (data_[r].finish_time < data_[minIndex].finish_time) {
        minIndex = r;
      }
      else if (data_[r].finish_time == data_[minIndex].finish_time && data_[r].id < data_[minIndex].id) {
        minIndex = r;
      }
    }

    if (i != minIndex) {
      swap(data_[i], data_[minIndex]);
      siftDown(minIndex);
    }
  }

  void CheckSwaps() {
    // for (int i = data_.size()/2; i >= 0; --i) {
    int i = 0;
    siftDown(i);
    // }
  }

  int AssignWorker(int duration) {
    int workerID = data_[0].id;
    data_[0].finish_time += duration;
    if (duration > 0) {
      CheckSwaps();
    }

    return workerID;
  }

  long long AssignFinish() {
    return data_[0].finish_time;
  }

  // void PrintData() {
  //   int size = data_.size();
  //   cout << "size: " << size << "\n";
  //   for (int i = 0; i < size; ++i) {
  //     cout << data_[i].id << " ";
  //   }
  //
  // }

 // public:
 //  void Solve() {
 //    PrintData();
 //    // ReadData();
 //    // GenerateSwaps();
 //  }
};




class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }
  void AssignJobs() {
    // TODO: replace this code with a faster algorithm.
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    HeapBuilder threads(num_workers_);
    // create a heap for the workers which contain a worker id and a finish time
    // the worker with the smallest finish time should always be the root
    // if they have equal finish time then the smallest id takes priority


    for (int i = 0; i < jobs_.size(); ++i) {
      int duration = jobs_[i];

      start_times_[i] = threads.AssignFinish();
      assigned_workers_[i] = threads.AssignWorker(duration);
    }
  }

  // void AssignJobs() {
  //   // TODO: replace this code with a faster algorithm.
  //   assigned_workers_.resize(jobs_.size());
  //   start_times_.resize(jobs_.size());
  //   vector<long long> next_free_time(num_workers_, 0);
  //   for (int i = 0; i < jobs_.size(); ++i) {
  //     int duration = jobs_[i];
  //     int next_worker = 0;
  //     for (int j = 0; j < num_workers_; ++j) {
  //       if (next_free_time[j] < next_free_time[next_worker])
  //         next_worker = j;
  //     }
  //     assigned_workers_[i] = next_worker;
  //     start_times_[i] = next_free_time[next_worker];
  //     next_free_time[next_worker] += duration;
  //   }
  // }

 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};



/*
Generator function for stress testing
*/
int generate(int a){

  int input = rand() % a + 1;
  return input;
}


/*
submission function
*/

int main() {
  std::ios_base::sync_with_stdio(false);

  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}



/*
test functions
*/
// int main() {
//
//   int n = generate(100000);
//   vector<int> a(n);
//   for (size_t i = 0; i < a.size(); ++i) {
//     a[i] = generate(1000000000);
//   }
//
//   struct timespec start, end;
//
//   // start time
//   clock_gettime(CLOCK_MONOTONIC, &start);
//   // function call
//   test_solution(a, 0, a.size());
//   // end time
//   clock_gettime(CLOCK_MONOTONIC, &end);
//   // calculate and print time
//   double time_taken = (end.tv_sec - start.tv_sec) * 1e9;
//   time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;
//   cout << "n: " << n << "\n";
//   cout << "Time taken: " << fixed << time_taken;
//   cout << "sec" << endl;
// }


/*
stress testing
*/
// int main() {
//   struct timespec start, end;
//
//   while (true) {
//     int n = generate(100000);
//     vector<int> a(n);
//     for (size_t i = 0; i < a.size(); ++i) {
//       a[i] = generate(1000000000);
//     }
//
//     // base solution timing and running
//     clock_gettime(CLOCK_MONOTONIC, &start);
//     int solution_base = base_solution(a, 0, a.size());
//     clock_gettime(CLOCK_MONOTONIC, &end);
//     double time_takenB = (end.tv_sec - start.tv_sec) * 1e9;
//     time_takenB = (time_takenB + (end.tv_nsec - start.tv_nsec)) * 1e-9;
//
//     // test solution timing and running
//     clock_gettime(CLOCK_MONOTONIC, &start);
//     int solution_test = test_solution(a, 0, a.size());
//     clock_gettime(CLOCK_MONOTONIC, &end);
//     double time_takenT = (end.tv_sec - start.tv_sec) * 1e9;
//     time_takenT = (time_takenT + (end.tv_nsec - start.tv_nsec)) * 1e-9;
//
//     if (solution_base != solution_test) {
//       cout << "Input: " << n << "\n";
//       cout << "Base: " << solution_base << " Test: " << solution_test << "\n";
//       // break;
//     }
//     cout << "Input: " << n << "\n";
//     cout << "Base: " << solution_base << " Test: " << solution_test << "\n";
//     cout << "Base time: " << fixed << time_takenB << "  Test time: " << fixed << time_takenT << "\n";
//     cout << "\n";
//   }
// }
