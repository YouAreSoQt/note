import { range, map, toArray, filter } from "./generator.js";
import { except } from "./test.js";

except("range function", [], [...range()]);
except("range function", [], [...range(0)]);
except("range function", [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10], [...range(11)]);
except("range function", [2, 3, 4], [...range(2, 5)]);
except("range function", [], [...range(2, 5, -1)]);
except("range function", [5, 4, 3], [...range(5, 2, -1)]);
except("range function", [5, 3], [...range(5, 2, -2)]);
except("range function", [2, 4, 6], [...range(2, 7, 2)]);

const f = function* (n) { 
    for (let i = 0; i < n; i++)
        yield i;
}

except("toArray function", [0, 1, 2], toArray(f(3)));

except("map function", [1, 4, 9], toArray(map([1, 2, 3], v => v * v)));

except("filter function", [1, 3, 5], toArray(filter(range(1, 6), v => v % 2 == 1)));