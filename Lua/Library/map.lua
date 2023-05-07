local function has_key(t, k)
    return not not t[k]
end

local function has_value(t, v)
    for _, val in pairs(t) do
        if val == v then
            return true
        end
    end

    return false
end

local function has(t, func)
    for k, v in pairs(t) do
        if func(v, k) then
            return true
        end
    end

    return false
end

local function find(t, func)
    for k, v in pairs(t) do
        if func(v, k) do
            return v, k
        end
    end
end

local function copy(t)
    local r = {}
    for k, v in pairs(t) do
        r[k] = v
    end
    return r
end

local function every(t, func)
    for k, v in pairs(t) do
        if not func(v, k) then
            return false
        end
    end

    return true
end

local function some(t, func)
    for k, v in pairs(t) do
        if func(v, k) then
            return true
        end
    end
    return false
end

local function remove(t, k)
    t[k] = nil
end

local function len(t)
    local cnt = 0
    for _ in pairs(t) do
        cnt = cnt + 1
    end
    return cnt
end

-- build iterator begin
local iter = import 'iterator'
local function values(t)
    return iter.iterator(pairs(t))
end

local function keys(t)
    local next, t, k = pairs(t)
    return iterator(function(t, k)
        local k, _ = next(t, k)
        return k, k
    end, t, k)
end

local function entries(t)
    local next, t, k = pairs(t)
    return iterator(function(t, k)
        local k, v = next(t, k)
        return k, { k, v }
    end, t, k)
end
-- build iterator end

return {
    has_key = has_key,
    has_value = has_value,
    has = has,
    find = find,
    copy = copy,
    every = every,
    some = some,
    remove = remove,
    len = len,
    values = values,
    keys = keys,
    entries = entries,
}