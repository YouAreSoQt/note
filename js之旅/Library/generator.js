const less = (left, right) => left < right;
const greater = (left, right) => left > right;
const equal = (left, right) => left == right;
const add = (left, right) => left + right;

export const range = function*(start, stop, step) {
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

export const enumerate = function*(generator) {
    let i = 0;
    for (const v of generator)
        yield [i++, v];
}

export const map = function*(generator, f) {
    for (const v of generator)
        yield f(v);
}

export const filter = function*(generator, f) {
    for (const v of generator)
        if (f(v)) yield v;
}

export const sum = (generator, f = add) => {
    let result;
    for (const v of generator)
        result = result == undefined ? v : f(result, v);
    return result;
};

export const toArray = generator => [...generator];

export const counter = generator => {
    const counter = new Map();
    for (const v of generator) {
        const count = counter.get(v) || 0;
        counter.set(v, count + 1);
    }
    return counter;
};