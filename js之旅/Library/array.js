export const first = array => array[0];
export const last = array => array[array.length - 1];
export const empty = array => array.length == 0;
// 不保证顺序的去重
export const unique = array => [...new Set(array)];
// 保证顺序的去重
export const distinct = array => {
    let result = [];
    let record = new Set();
    for (const v of array) {
        if (record.has(v)) continue;
        record.add(v);
        result.push(v);
    }
    return result;
};