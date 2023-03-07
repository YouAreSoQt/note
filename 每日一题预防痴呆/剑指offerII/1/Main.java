public class Main {
    public static void main(String[] args) {
        int[][] testArray = new int[][] {
                { Integer.MAX_VALUE, 2 },
                { Integer.MIN_VALUE, 2 },
                { Integer.MIN_VALUE, Integer.MAX_VALUE },
                { Integer.MAX_VALUE, Integer.MIN_VALUE },
                { Integer.MAX_VALUE, Integer.MAX_VALUE },
        };

        for (var pair : testArray) {
            System.out.println(String.format("%d / %d == %d is %b", pair[0], pair[1], pair[0] / pair[1], divide(pair[0], pair[1]) == pair[0] / pair[1]));
        }
    }

    public static int divide(int dividend, int divisor) {
        if (dividend == Integer.MIN_VALUE && divisor == -1)
            return Integer.MAX_VALUE;

        int negative = 2;
        if (dividend > 0) {
            dividend = -dividend;
            negative--;
        }
        if (divisor > 0) {
            divisor = -divisor;
            negative--;
        }

        int result = divideCore(dividend, divisor);
        return negative == 1 ? -result : result;
    }

    private static int divideCore(int dividend, int divisor) {
        int result = 0;

        while (dividend <= divisor) {
            int value = divisor;
            int quotient = 1;
            while (value >= 0xc0000000 && dividend <= value + value) {
                quotient += quotient;
                value += value;
            }
            dividend -= value;
            result += quotient;
        }

        return result;
    }
}
