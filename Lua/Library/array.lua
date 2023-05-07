local function len(t)
    return #t
end

local function first(t)
    if #t > 0 then
        return t[1]
    end
end

local function last(t)
    if #t > 0 then
        return t[#t]
    end
end

local function pop(t)
    table.remove(t)
end

local function push(t, v)
    table.insert(t, v)
end

local function shift(t)
    table.remove(t, 1)
end

local function unshift(t, v)
    table.insert(t, 1, v)
end

local function removeif(t, func)
    for i = #t, 1, -1 do
        if func(t[i]) then
            table.remove(t, i)
        end
    end
end

local function reverse(t)
    local len = #t
    for i = 1, (len // 2) do
        t[i], t[len - i + 1] = t[len - i + 1], t[i]
    end
end

local function index(t, v)
    for i, value in ipairs(t) do
        if v == value then
            return i
        end
    end

    return 0
end

local function rindex(t, v)
    for i = #t, 1, -1 do
        if t[i] == v then
            return i
        end
    end

    return 0
end

local function indexf(t, func)
    for i = 1, #t do
        if func(t[i]) then
            return i
        end
    end
    return 0
end

local function rindexf(t, func)
    for i = #t, 1, -1 do
        if func(t[i]) then
            return i
        end
    end
    return 0
end

local function has(t, v)
    for _, val in ipairs(t) do
        if val == v then
            return true
        end
    end

    return false
end

local function find(t, func)
    for _, v in ipairs(t) do
        if func(v) then
            return true
        end
    end

    return false
end

local function flat(t)
    local function _flat(t, r)
        if type(t) == 'table' then
            for _, v in ipairs(t) do
                _flat(t, r)
            end
        else
            r.insert(t)
        end
    end

    local r = {}
    _flat(t, r)
    return r
end

local function fill(t, v, bi, ei)
    v = v or 0
    bi = bi or 1
    ei = ei or #t

    for i = bi, ei do
        t[i] = v
    end
end

local function groupby(t, f)
    local r = {}
    for _, v in ipairs(t) do
        k = f(v)
        if not r[k] then r[k] = {} end
        table.insert(r[k], v) 
    end
    return r
end

local function count(t, v)
    local cnt = 0

    for _, val in ipairs(t) do
        if val == v then
            cnt = cnt + 1
        end
    end

    return cnt
end

local function countf(t, f)
    local cnt = 0
    for _, v in ipairs(t) do
        if f(v) then
            cnt = cnt + 1
        end
    end
    return cnt
end

local function counter(t)
    local r = {}

    for _, v in ipairs(t) do
        if not r[v] then r[v] = 0 end
        r[v] = r[v] + 1
    end

    return r
end

local function unique(t)
    local r = {}
    for i = #t, 1, -1 do
        if r[t[i]] then
            table.remove(t, i)
        else
            r[t[i]] = true
        end
    end
end

-- build iterator begin
local iter = import 'iterator'
local function values(t)
    return iter.iterator(ipairs(t))
end
-- build iterator end

return {
    len = len,
    first = first,
    last = last,
    pop = pop,
    push = push,
    shift = shift,
    unshift = unshift,
    removeif = removeif,
    reverse = reverse,
    index = index,
    rindex = rindex,
    indexf = indexf,
    rindexf = rindexf,
    has = has,
    find = find,
    flat = flat,
    fill = fill,
    groupby = groupby,
    count = count,
    countf = countf,
    counter = counter,
    unique = unique,
    values = values,
}