#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <cmath>

using namespace std;

// CPP program for array
// implementation of queue

// A structure to represent a queue
/*class Queue {
public:
    Process front, rear;
    int size;
    unsigned capacity;
    Process* array;
};

// function to create a queue
// of given capacity.
// It initializes size of queue as 0
Queue* createQueue(unsigned capacity)
{
    Queue* queue = new Queue();
    queue->capacity = capacity;
    queue->front = queue->size = 0;

    // This is important, see the enqueue
    queue->rear = capacity - 1;
    queue->array = new int[queue->capacity];
    return queue;
}

// Queue is full when size
// becomes equal to the capacity
int isFull(Queue* queue)
{
    return (queue->size == queue->capacity);
}
 
// Queue is empty when size is 0
int isEmpty(Queue* queue)
{
    return (queue->size == 0);
}
 
// Function to add an item to the queue.
// It changes rear and size
void enqueue(Queue* queue, Process item)
{
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1)
                  % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
    cout << item << " enqueued to queue\n";
}
 
// Function to remove an item from queue.
// It changes front and size
int dequeue(Queue* queue)
{
    if (isEmpty(queue))
        return INT_MIN;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1)
                   % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}
 
// Function to get front of queue
int front(Queue* queue)
{
    if (isEmpty(queue))
        return INT_MIN;
    return queue->array[queue->front];
}
 
// Function to get rear of queue
int rear(Queue* queue)
{
    if (isEmpty(queue))
        return INT_MIN;
    return queue->array[queue->rear];
}*/

// Driver code
/*int main()
{
    Queue* queue = createQueue(1000);

    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);
    enqueue(queue, 40);

    cout << dequeue(queue)
         << " dequeued from queue\n";
 
    cout << "Front item is "
         << front(queue) << endl;
    cout << "Rear item is "
         << rear(queue) << endl;

    return 0;
}*/

class Process {
    private:
        int arrival_time;
        int completion_time;
        int total_bursts;
        int waiting_time;
        int response_time;
        int ta_time;
        int CPUBursts_counter;
        int IOTime_counter;
    public:
        vector<int> times;
        vector<int> burstTimes;
        Process(vector<int> t) {
            times = t;
        }
        
        vector<int> getIOTimes(){
            vector<int> IOTimes;
            for (int i = 1;i<times.size();i = i+2){
                IOTimes.push_back(times[i]);
            }
            return IOTimes;
        }

        vector<int> getBurstTimes(){
            vector<int> BurstTimes;
            int burstsTotal = 0;
            for (int i = 0;i<times.size();i=i+2){
                BurstTimes.push_back(times[i]);
                burstsTotal += times[i];
            }
            //sets total_bursts too
            this->total_bursts = burstsTotal;
            this->burstTimes = BurstTimes;
            return BurstTimes;
        }

        //keeps track of index in CPU Bursts vector
        int CPUBurstsCounterAdd(){
            return CPUBursts_counter++;
        }

        //keeps track of index in IO Times vector
        int IOTimesCounter(){
            return IOTime_counter++;
        }
        void setWaitingTime(int w){
            this->waiting_time = w;
        }
        void setArrivalTime(int a){
            this->arrival_time = a;
        }
        void setCompletionTime(int c){
            this->completion_time = c;
        }
};

vector<Process> popQ(vector<Process> v){
    v.erase(v.begin());
    return v;
}

vector<Process> pushQ(vector<Process> v, Process value){
    v.push_back(value);
    return v;
}

void fcfs(vector<Process> p){
    int timer = 0;
    int p_counter = 0;
    int running_counter = 0;
    int readyQ_index = 0;
    vector<Process> readyQ;
    vector<int> waitingTime (p.size(), 0);
    vector<int> arrivalTime (p.size(), 0);
    vector<int> responseTime (p.size(), -1);
    //adds initial values/processes to readyQ
    for (int i  = 0;i<p.size();i++){
        readyQ[i] = p[i];
    }
    vector<Process> runningQ;
    vector<Process> waitingQ;
    vector<Process> doneQ;
    while (doneQ.size() != 8){

        int p_index = readyQ_index;
        popQ(readyQ);

        //waiting time in readyQ
        waitingTime[p_index] += timer - arrivalTime[p_index];

        if (responseTime[p_index] == -1){
            responseTime[p_index] = timer- arrivalTime[p_index];
        }

        // adding recent burst to timer
        timer += p[p_index].burstTimes[p_index];

        
    }
}

int main(){
    /*vector<int> nums{1, 2, 3, 4, 5, 6};
    vector<int> new_nums = pushQ(nums, 7);
    for (int i = 0;i<new_nums.size();i++){
        cout << new_nums[i];
        //then why would I be doing that then
        //there is absolutely no reason why
    }*/
    vector<int> p1t {5, 27, 3, 31, 5, 43, 4, 18, 6, 22, 4, 26, 3, 24, 4};
    Process p1(p1t);
    vector<int> p2t {4, 48, 5, 44, 7, 42, 12, 37, 9, 76, 4, 41, 9, 31, 7, 43, 8};
    Process p2(p2t);
    vector<int> p3t {8, 33, 12, 41, 18, 65, 14, 21, 4, 61, 15, 18, 14, 26, 5, 31, 6};
    Process p3(p3t);
    vector<int> p4t {3, 35, 4, 41, 5, 45, 3, 51, 4, 61, 5, 54, 6, 82, 5, 77, 3};
    Process p4(p4t);
    vector<int> p5t {16, 24, 17, 21, 5, 36, 16, 26, 7, 31, 13, 28, 11, 21, 6, 13, 3, 11, 4};
    Process p5(p5t);
    vector<int> p6t {11, 22, 4, 8, 5, 10, 6, 12, 7, 14, 9, 18, 12, 24, 15, 30, 8};
    Process p6(p6t);
    vector<int> p7t {14, 46, 17, 41, 11, 42, 15, 21, 4, 32, 7, 19, 16, 33, 10};
    Process p7(p7t);
    vector<int> p8t {4, 14, 5, 33, 6, 51, 14, 73, 16, 87, 6};
    Process p8(p8t);
    vector<Process> processes = {p1, p2, p3, p4, p5, p6, p7, p8};
    cout << processes[0].times[0];
   // fcfs(processes);
    return 0;
}