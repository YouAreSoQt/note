local function bool(v)
    local vtype = type(v)

    if vtype == 'table' then
        return not not next(v)
    end

    if vtype == 'string' then
        return v ~= ''
    end

    if vtype == 'number' then
        return v ~= 0
    end

    if vtype == 'nil' then
        return false
    end

    return true
end

return {
    bool = bool,
}