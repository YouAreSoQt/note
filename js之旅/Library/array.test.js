import { distinct, empty, first, last, unique } from "./array.js";
import { except } from "./test.js";

let arr = [11, 2, 7, 2, 3];

except("first function", 11, first(arr));

except("last function", 3, last(arr));

except("empty function", false, empty(arr));
except("empty function", true, empty([]));

except("unique function", [...new Set(arr)], unique(arr));

except("distinct function", [11, 2, 7, 3], distinct(arr));
