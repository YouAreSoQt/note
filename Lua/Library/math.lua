-- depends on iterator.lua begin
local function sum(iter)
    local r = 0
    for v in iter do
        r = r + v
    end
    return r
end

local function average(iter)
    local n, r = 0, 0
    for v in iter do
        n = n + 1
        r = r + v
    end
    return r / n
end

local function max(iter)
    local r = iter()
    for v in iter do
        if r < v then
            r = v
        end
    end
    return r
end

local function min(iter)
    local r = iter()
    for v in iter do
        if r > v then
            r = v
        end
    end
    return r
end

-- depends on iterator.lua end

return {
    sum = sum,
    average = average,
    max = max,
}