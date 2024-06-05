#ifndef DISK_SCHEDULING_H
#define DISK_SCHEDULING_H

#define CYLINDERS 5000
#define REQUESTS 1000

/**
 * 產生隨機磁碟請求
 * @param requests - 保存生成的請求的數組
 */
void generate_requests(int *requests);


/**
 * 比較函數，用於 qsort 對請求進行排序
 * @param a - 指向第一個整數的指針
 * @param b - 指向第二個整數的指針
 * @return 比較結果
 */
int cmp(const void *a, const void *b);

/**
 * 計算 FCFS 總磁頭移動距離
 * @param requests - request array
 * @param initial_position - 磁頭的初始位置
 * @return 總磁頭移動距離
 */
int fcfs(int *requests, int initial_position);

/**
 * 計算 SSTF 總磁頭移動距離
 * @param requests - request array
 * @param initial_position - 磁頭的初始位置
 * @return 總磁頭移動距離
 */
int sstf(int *requests, int initial_position);

/**
 * 計算 SCAN 總磁頭移動距離
 * @param requests - request array
 * @param initial_position - 磁頭的初始位置
 * @return 總磁頭移動距離
 */
int scan(int *requests, int initial_position);

/**
 * 計算 C-SCAN 總磁頭移動距離
 * @param requests - request array
 * @param initial_position - 磁頭的初始位置
 * @return 總磁頭移動距離
 */
int cscan(int *requests, int initial_position);

/**
 * 計算 LOOK 總磁頭移動距離
 * @param requests - request array
 * @param initial_position - 磁頭的初始位置
 * @return 總磁頭移動距離
 */
int look(int *requests, int initial_position);

/**
 * 計算 C-LOOK 總磁頭移動距離
 * @param requests - request array
 * @param initial_position - 磁頭的初始位置
 * @return 總磁頭移動距離
 */
int clook(int *requests, int initial_position);

/**
 * 計算最佳算法（最小化總延遲/磁頭移動距離）的總磁頭移動距離
 * @param requests - request array
 * @param initial_position - 磁頭的初始位置
 * @return 總磁頭移動距離
 */
int optimal(int *requests, int initial_position);



#endif // DISK_SCHEDULING_H
