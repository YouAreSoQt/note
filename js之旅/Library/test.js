const equal = (left, right) => {
    if (left == right) return true;
    if (Array.isArray(left) && Array.isArray(right) && left.length == right.length) {
        for (let i = 0; i < left.length; i++)
            if (left[i] != right[i]) return false;
        return true;
    }

    return false;
};

export const except = (name, exceptValue, value) => {
    if (equal(value, exceptValue))
        console.log(`${name} pass.`);
    else 
        console.error(`${name} fail: except value = ${exceptValue}, but real value is ${value}. `);
    console.log("==============================================================");
}