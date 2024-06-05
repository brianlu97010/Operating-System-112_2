#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define CYLINDERS 5000
#define REQUESTS 1000

/* 產生隨機磁碟請求 */
void generate_requests(int *requests) {
    for (int i = 0; i < REQUESTS; i++) {
        requests[i] = rand() % CYLINDERS;
    }
}

/* 比較函數，用於 qsort 對請求進行排序 */
int cmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}


/* 計算 FCFS 總磁頭移動距離 */
/* FCFS: 先到的請求先服務 */
int fcfs(int *requests, int initial_position) {
    int total_movement = 0;
    int current_position = initial_position;
    for (int i = 0; i < REQUESTS; i++) {
        total_movement += abs(requests[i] - current_position);
        current_position = requests[i];
    }
    return total_movement;
}


/* 計算 SSTF 總磁頭移動距離 */
/* SSTF: 最短搜尋時間的優先 */
/*  served 陣列用於標記哪些請求已經被處理。
    第一個迴圈一定會把N次做滿
    先把 closest_distance 設為無窮大
    則第一個 Not served requests 與 current positon 的distance就必定為closest_distance
    再依序更新closet_index...
    更新到最後的closet_distance即為最短的移動距離    
*/
int sstf(int *requests, int initial_position) {
    int total_movement = 0;
    int current_position = initial_position;
    int served[REQUESTS] = {0}; // 用於標記哪些請求已經被處理

    for (int i = 0; i < REQUESTS; i++) {
        int closest_index = -1;
        int closest_distance = CYLINDERS + 1;

        // 找到最近的請求
        for (int j = 0; j < REQUESTS; j++) {
            if (served[j] != 1) {
                int distance = abs(requests[j] - current_position);
                if (distance < closest_distance) {
                    closest_distance = distance;
                    closest_index = j;
                }
            }
        }

        // 處理最近的請求
        if (closest_index != -1) {
            total_movement += closest_distance;
            current_position = requests[closest_index];
            served[closest_index] = 1;
        }
    }
    return total_movement;
}

/* 計算 SCAN 總磁頭移動距離 */
/* SCAN: 磁頭來回掃描 */
int scan(int *requests, int initial_position) {
    int total_movement = 0;
    int current_position = initial_position;
    int sorted_requests[REQUESTS + 1];
    memcpy(sorted_requests, requests, sizeof(int) * REQUESTS);  // copy requests to sorted_requests
    sorted_requests[REQUESTS] = CYLINDERS - 1;  // add the last cylinder to the end of sorted_requests
    qsort(sorted_requests, REQUESTS + 1, sizeof(int), cmp); // sort sorted_requests
    int served[REQUESTS+1] = {0};

    // 找從哪裡開始
    int start_index = 0;
    while(  current_position > sorted_requests[start_index] && start_index != REQUESTS - 1){
        start_index++;
    }

    // right hand side
    for (int i = start_index; i < REQUESTS+1 && served[i]!=1 ; i++){
        total_movement += abs(current_position - sorted_requests[i]);
        current_position = sorted_requests[i];
        served[i] = 1;
    }   

    // left hand side
    for (int i = start_index - 1; i >=0 && served[i]!=1 ; i--){
        total_movement += abs(current_position - sorted_requests[i]);
        current_position = sorted_requests[i];
        served[i] = 1;
    }
    return total_movement;
}

/* 計算 C-SCAN 總磁頭移動距離 */
/* C-SCAN: 循環掃描 */
int cscan(int *requests, int initial_position) {
    int total_movement = 0;
    int current_position = initial_position;
    // 增加邊界 0 和 REQUESTS-1
    int sorted_requests[REQUESTS + 2];
    memcpy(sorted_requests, requests, sizeof(int) * REQUESTS);
    sorted_requests[REQUESTS] = CYLINDERS - 1;
    sorted_requests[REQUESTS + 1] = 0;
    qsort(sorted_requests, REQUESTS + 2, sizeof(int), cmp);

    int start_index = 0;
    while (start_index < REQUESTS + 2 && sorted_requests[start_index] < current_position) {
        start_index++;
    }

    for (int i = start_index; i < REQUESTS + 2; i++) {
        total_movement += abs(sorted_requests[i] - current_position);
        current_position = sorted_requests[i];
    }

    // 只有 start_index = 0 才不用回到0的位置繼續
    if (start_index > 0) {
        total_movement += CYLINDERS - 1;
        current_position = 0;
        for (int i = 0; i < start_index; i++) {
            total_movement += abs(sorted_requests[i] - current_position);
            current_position = sorted_requests[i];
        }
    }

    return total_movement;
}


/* 計算 LOOK 總磁頭移動距離 */
/* LOOK: 磁頭來回掃描，不到邊界 */
int look(int *requests, int initial_position) {
    int total_movement = 0;
    int current_position = initial_position;
    int sorted_requests[REQUESTS];
    memcpy(sorted_requests, requests, sizeof(int) * REQUESTS);  // copy requests to sorted_requests
    qsort(sorted_requests, REQUESTS + 1, sizeof(int), cmp); // sort sorted_requests
    int served[REQUESTS+1] = {0};

    // 找從哪裡開始
    int start_index = 0;
    while(  current_position > sorted_requests[start_index] && start_index != REQUESTS - 1){
        start_index++;
    }

    // right hand side
    for (int i = start_index; i < REQUESTS && served[i]!=1 ; i++){
        total_movement += abs(current_position - sorted_requests[i]);
        current_position = sorted_requests[i];
        served[i] = 1;
    }   

    // left hand side
    for (int i = start_index - 1; i >=0 && served[i]!=1 ; i--){
        total_movement += abs(current_position - sorted_requests[i]);
        current_position = sorted_requests[i];
        served[i] = 1;
    }
    return total_movement;
}

/* 計算 C-LOOK 總磁頭移動距離 */
/* C-LOOK: 循環來回掃描，不到邊界 */
int clook(int *requests, int initial_position) {
    int total_movement = 0;
    int current_position = initial_position;
    int sorted_requests[REQUESTS];
    memcpy(sorted_requests, requests, sizeof(int) * REQUESTS);
    qsort(sorted_requests, REQUESTS, sizeof(int), cmp);

    int start_index = 0;
    while (start_index < REQUESTS && sorted_requests[start_index] < current_position) {
        start_index++;
    }

    for (int i = start_index; i < REQUESTS; i++) {
        total_movement += abs(sorted_requests[i] - current_position);
        current_position = sorted_requests[i];
    }

    for (int i = 0; i < start_index; i++) {
        total_movement += abs(sorted_requests[i] - current_position);
        current_position = sorted_requests[i];
    }

    return total_movement;
}


/* 計算最佳算法（最小化總延遲/磁頭移動距離）的總磁頭移動距離 */
/* Optimal: 最佳算法 */
int optimal(int *requests, int initial_position) {
    int total_movement = 0;
    int current_position = initial_position;
    int request_list[REQUESTS];
    memcpy(request_list, requests, sizeof(int) * REQUESTS);

    qsort(request_list, REQUESTS, sizeof(int), cmp);

    for (int i = 0; i < REQUESTS; i++) {
        total_movement += abs(request_list[i] - current_position);
        current_position = request_list[i];
    }

    return total_movement;
}


