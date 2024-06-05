#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "disk_scheduling.h"

#define CYLINDERS 5000
#define REQUESTS 1000   /*  cylinder requests 的數量  */

int main(int argc, char *argv[]) {
    // 檢查命令行參數數量是否正確
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <initial position>\n", argv[0]);
        return 1;
    }
    // 預期命令列傳入 : ` ./test   [initial_position]`
    //                   argv[0]       argv[1]
    // 取得初始磁頭位置
    int initial_position = atoi(argv[1]);
    int requests[REQUESTS] = {0};

    // 初始化隨機數生成器
    srand(time(NULL));
    generate_requests(requests);

    // 計算各個algorithms總磁頭移動距離和平均延遲
    int total_movement_fcfs = fcfs(requests, initial_position);
    double average_latency_fcfs = (total_movement_fcfs / 100.0);

    int total_movement_sstf = sstf(requests, initial_position);
    double average_latency_sstf = (total_movement_sstf / 100.0);

    int total_movement_scan = scan(requests, initial_position);
    double average_latency_scan = (total_movement_scan / 100.0);

    int total_movement_cscan = cscan(requests, initial_position);
    double average_latency_cscan = (total_movement_cscan / 100.0);

    int total_movement_look = look(requests, initial_position);
    double average_latency_look = (total_movement_look / 100.0);

    int total_movement_clook = clook(requests, initial_position);
    double average_latency_clook = (total_movement_clook / 100.0);

    int total_movement_optimal = optimal(requests, initial_position);
    double average_latency_optimal = (total_movement_optimal / 100.0);

    // 輸出結果
    printf("FCFS Total Head Movement: %d\n", total_movement_fcfs);
    printf("FCFS Average Latency: %.2f ms\n\n", average_latency_fcfs);

    printf("SSTF Total Head Movement: %d\n", total_movement_sstf);
    printf("SSTF Average Latency: %.2f ms\n\n", average_latency_sstf);

    printf("SCAN Total Head Movement: %d\n", total_movement_scan);
    printf("SCAN Average Latency: %.2f ms\n\n", average_latency_scan);

    printf("C-SCAN Total Head Movement: %d\n", total_movement_cscan);
    printf("C-SCAN Average Latency: %.2f ms\n\n", average_latency_cscan);

    printf("LOOK Total Head Movement: %d\n", total_movement_look);
    printf("LOOK Average Latency: %.2f ms\n\n", average_latency_look);

    printf("C-LOOK Total Head Movement: %d\n", total_movement_clook);
    printf("C-LOOK Average Latency: %.2f ms\n\n", average_latency_clook);

    printf("Optimal Total Head Movement: %d\n", total_movement_optimal);
    printf("Optimal Average Latency: %.2f ms\n\n", average_latency_optimal);

    return 0;
}
