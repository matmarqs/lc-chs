// O(n^2), time limit exceeded
int maxProfit_Squared(int* prices, int pricesSize) {
    int max = 0;
    for (int i = 0; i < pricesSize; i++) {
        for (int j = i+1; j < pricesSize; j++) {
            int profit = prices[j] - prices[i];
            if (profit > max)
                max = profit;
        }
    }
    return max;
}

/* We have to track the min_price so far */
/* we don't need any data structure at all */
/* if prices[i] - min_price, just update the max_profit */

#define INFINITY 100000

/* O(n). Just keep track of minimum price so far */
int maxProfit(int* prices, int pricesSize) {
    int min_price = INFINITY; 
    int max_profit = 0;
    for (int i = 0; i < pricesSize; i++) {
        if (prices[i] < min_price) {
            min_price = prices[i];
        }
        if (prices[i] - min_price > max_profit) {
            max_profit = prices[i] - min_price;
        }
    }
    return max_profit;
}
