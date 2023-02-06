# JavaScript & TypeScript

## 常用工具函数 (Utils)

* RGB转换
```typescript
export const rgbToHex: (r: number, g: number, b: number) => string =
    (r, g, b) => "#" + (1 << 24 | r << 16 | g << 8 | b).toString(16).slice(1);

export const hexToRGB: (hex: string) => [number, number, number] = hex => {
    const res = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex);
    return res ? res.slice(1).map(s => parseInt(s, 16)) as [number, number, number] : [0, 0, 0];
}
```
* 集合操作
``` typescript
export const union: <T>(a: T[], b: T[]) => T[] = (a, b) => [...a, ...b.filter(v => !a.includes(v))];
export const intersection: <T>(a: T[], b: T[]) => T[] = (a, b) => a.filter(v => b.includes(v));
export const diff: <T>(a: T[], b: T[]) => T[] = (a, b) => [...a, ...b].filter(v => !a.includes(v) || !b.includes(v));
```

* 数组
``` typescript
export const shuffle: <T>(a: T[]) => T[] = a => {
    const ans = [];
    while (a.length > 0) {
        const random = Math.floor(Math.random() * a.length);
        ans.push(a[random]);
        a.splice(random, 1);
    }
    return ans;
}

export const set: <T>(a: T[]) => T[] = a => [...new Set(a)];

export const max: (a: number[]) => number = a => Math.max(...a);
export const min: (a: number[]) => number = a => Math.min(...a);
export const max_min: (a: number[]) => [number, number] = a => 
    a.reduce((pre, v) => [pre[0], pre[1]] = [Math.max(pre[0], v), Math.min(pre[1], v)], [a[0], a[0]]);

export const countOf: <T>(a: T[], v: T) => number = (a, v) => a.reduce((count, val) => count + (val === v ? 1 : 0), 0);

export const head: <T>(a: T[]) => T = a => a[0];
export const tail: <T>(a: T[]) => T = a => a[a.length - 1];
```

* 校验

邮箱验证最好方式是与邮箱进行邮件验证!正则验证最好只用于用户书写错误提醒
``` typescript
export const validateEmail: (s: string) => boolean = s => /\S+@\S+/.test(s);
```
手机号验证最好方式为发送严重码!正则验证最好只用于用户书写错误提醒
``` typescript
export const validatePhone: (s: string) => boolean = s => /^1[0-9]{10}$/.test(s);
```
验证只包含数字
``` typescript
export function onlyNum(str: string): boolean {
    return /^\d+$/.test(str);
}
```
验证只包含字母,数字和基本汉字
``` typescript
export function onlyLettersAndNumAndChinese(str: string): boolean {
    return /^[a-zA-Z0-9\u4e00-\u9fa5]+$/u.test(str);
}
```
汉字占两位,字母占一位(默认传入字符串只包含字母和汉字)
``` typescript
export function worldCount(str: string): number {
    let count = 0;
    for (const s of str) {
        count += s.codePointAt(0)! < 255 ? 1 : 2;
    }
    return count;
}
```
* 其它
``` typescript
export const digitize: (n: number) => number[] = n => [...n.toString()].map(i => parseInt(i));
```
``` typescript
export const random: (min: number, max: number) => number = (min, max) => Math.floor(min + Math.random() * (max - min));
```
同Python range
``` typescript
export function* range(start: number, stop?: number, step: number = 1) {
    if (step === 0) {
        throw new Error('ValueError');
    }
    let last: number = stop ?? 0;
    if (stop === undefined) {
        last = start;
        start = 0;
    }
    const compare = step > 0 ? ((i: number) => i < last) : ((i: number) => i > last);
    for (let i = start; compare(i); i += step) {
        yield i;
    }
}
```
同 C# string format
``` typescript
export function format(str: string, ...args: any[]): string {
    args.forEach((arg, index) => {
        const re = new RegExp(`\\{\\s*${index}\\s*\\}`, 'g');
        str = str.replace(re, arg?.toString());
    });
    return str;
}
```