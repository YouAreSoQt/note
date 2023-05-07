const less = (left, right) => left < right;
const greater = (left, right) => left > right;
const equal = (left, right) => left == right;
const add = (left, right) => left + right;

export function *range(start, stop, step) {
    if (start == undefined) return;
    if (stop == undefined) {
        stop = start;
        start = 0;
        step = 1;
    } else step = step || 1;

    const compareTo = step > 0 ? less : greater;
    for (; compareTo(start, stop); start += step)
        yield start;
};

export function *enumerate(generator) {
    let i = 0;
    for (const v of generator)
        yield [i++, v];
}

export function *map(generator, f) {
    for (const v of generator)
        yield f(v);
}

export function *filter(generator, f) {
    for (const v of generator)
        if (f(v)) yield v;
}

export const sum = (generator, f = add) => {
    let result;
    for (const v of generator)
        result = result == undefined ? v : f(result, v);
    return result;
}

export const toArray = generator => {
    let arr = [];
    for (const v of generator)
        arr.push(v);
    return arr;
}