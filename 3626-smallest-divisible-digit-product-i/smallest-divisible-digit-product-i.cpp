class Solution {
public:
    int smallestNumber(int n, int t) {
        for (int num = n; ; ++num) {
            if (divisible(num, t)) return num;
        }
        return -1;
    }

private:
    bool divisible(int num, int t) {
        long long product = 1;
        int x = num;
        while (x > 0) {
            product *= (x % 10);
            x /= 10;
        }
        return product % t == 0;
    }
};
