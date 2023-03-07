class Solution {
    public String addBinary(String a, String b) {
        int carry = 0;
        int i = a.length() - 1;
        int j = b.length() - 1;
        StringBuilder sb = new StringBuilder();
        while (carry > 0 || i >= 0 || j >= 0) {
            if (i >= 0) {
                carry += a.charAt(i) - '0';
                i--;
            }

            if (j >= 0) {
                carry += b.charAt(j) - '0';
                j--;
            }

            sb.append(carry % 2);
            carry /= 2;
        }

        return sb.reverse().toString();
    }
}