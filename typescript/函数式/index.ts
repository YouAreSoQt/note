function comparator<T>(pred: (x: T, y: T) => boolean) {
    return (x: T, y: T) => {
        if (pred(x, y))
            return -1;
        else if (pred(y, x))
            return 1;
        else
            return 0;
    };
}

function lessOrEqual<T>(x: T, y: T): boolean {
    return x <= y;
}

function greaterThan<T>(x: T, y: T): boolean {
    return x >= y;
}

function isOdd(n: number): boolean {
    return Boolean(n & 0x01);
}

function isEven(n: number): boolean {
    return Boolean(n & 0x00);
}

console.log([1, 2, -1, 45, -1545, 454, 4521].sort(comparator(lessOrEqual)));