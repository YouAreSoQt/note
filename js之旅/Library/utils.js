export const freeze = (obj) => { 
    Object.freeze(obj);
    Object.keys(obj).forEach(k => {
        if (typeof obj[k] === 'object')
            freeze(obj[k]);
    });
};