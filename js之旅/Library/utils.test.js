import { fibs, freeze } from "./utils.js";
import { except } from "./test.js";

const obj = {
    name: 'root',
    age: 18,
    hobbies: ['apple', 'sleep', 'fly'],
    score: {
        english: {
            num: 88,
            desc: 'A',
        },
        math: {
            num: 56,
            desc: 'C',
        },
    },
};

freeze(obj);

// obj.score.english.num = 16;

except("fib function", [...fibs(5)], [0, 1, 1, 2, 3]);