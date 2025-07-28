/* foda-se esse exercício, O(N^2) beats 0% */
int minNumber(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int common_num = 10;
    for (int i = 0; i < nums1Size; i++) {
        for (int j = 0; j < nums2Size; j++) {
            if (nums1[i] == nums2[j]) {
                common_num = (nums1[i] < common_num) ? nums1[i] : common_num;
            }
        }
    }

    if (common_num != 10) {
        return common_num;
    }

    int min1 = 10;
    int min2 = 10;
    for (int i = 0; i < nums1Size; i++) {
        min1 = (nums1[i] < min1) ? nums1[i] : min1;
    }
    for (int i = 0; i < nums2Size; i++) {
        min2 = (nums2[i] < min2) ? nums2[i] : min2;
    }

    int min = min1 < min2 ? min1 : min2;
    int max = min1 > min2 ? min1 : min2;
    return 10 * (min) + (max);
}
