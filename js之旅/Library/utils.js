export const freeze = (obj) => { 
    Object.freeze(obj);
    Object.keys(obj).forEach(k => {
        if (typeof obj[k] === 'object')
            freeze(obj[k]);
    });
};

export function* fibs(n) {
    let a = 0, b = 1;
    for (let i = 0; i < n; i++) {
        yield a;
        [a, b] = [b, a + b];
    }   
}