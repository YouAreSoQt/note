local function isnullorempty(s)
    return s == nil or s == ''
end

local function isempty(s)
    return s == ''
end

local function split(s, sep)
    seq = sep or '%s'
    local r = {}
    for str in string.gmatch(s, '([^"..sep.."]+)') do
        table.insert(r, str)
    end
    return r
end

return {
    isnullorempty = isnullorempty,
    isempty = isempty,
    split = split,
}