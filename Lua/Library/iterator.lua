local _iter_values_ = {
    __call = function(self)
        local k, v = self.next(self.state, self.k)
        if k then
            self.k = k
            return v
        end
    end
}

local function iterator(next, state, k)
    local iter = { next = next, state = state, k = k }
    return setmetatable(iter, _iter_values_)
end

local function less(a, b)
    return a < b
end

local function greater(a, b)
    return a > b
end

local function ivalues(t)
    return iterator(ipairs(t))
end

local function keys(t)
    local next, t, k = pairs(t)
    return iterator(function(t, k)
        local k, _ = next(t, k)
        return k, k
    end, t, k)
end

local function values(t)
    return iterator(pairs(t))
end

local function entries(t)
    local next, t, k = pairs(t)
    return iterator(function(t, k)
        local k, v = next(t, k)
        return k, { k, v }
    end, t, k)
end

local function range(start, stop, step)
    if not stop then 
        stop = start or 0
        start = 1
    end

    if not step or step == 0 then step = 1 end

    local compare = step < 0 and less or greater

    local function _range()
        local function iter(_, i)
            if not compare(i, stop) then
                return i + step, i
            end
        end

        return iter, 0, start
    end

    return iterator(_range())
end

local function map(func, iter)
    return function()
        for v in iter do
            return func(v)
        end
    end
end

local function filter(func, iter)
    return function()
        for v in iter do
            if func(v) then
                return v
            end
        end
    end
end

local function enumerate(iter)
    return function()
        local i = 0
        for v in iter do
            i = i + 1
            return { i, v }
        end
    end
end

local function skip(count, iter)
    return function()
        for v in iter do
            count = count - 1
            if count < 0 then
                return v
            end
        end
    end
end

local function take(count, iter)
    return function()
        for v in iter do
            count = count - 1
            if count < 0 then
                break
            end
            return v
        end
    end
end

local function list(iter)
    local t = {}
    for v in iter do
        table.insert(t, v)
    end
    return t
end

local function counter(iter)
    local t = {}
    for v in iter do
        local n = t[v] or 0 
        t[v] = n + 1
    end
    return t
end

return {
    iterator = iterator,
    ivalues = ivalues,
    keys = keys,
    values = values,
    entries = entries,
    range = range,
    map = map,
    filter = filter,
    enumerate = enumerate,
    skip = skip,
    take = take,
    list = list,
    counter = counter,
}
