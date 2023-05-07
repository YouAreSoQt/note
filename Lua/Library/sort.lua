local function csort(t, conditions)
    local function st(a, b)
        for _, condition in ipairs(conditions) do
            local ctype = type(condition)

            if ctype == 'string' then
                if a[condition] ~= b[condition] then
                    return a[condition] < b[condition]
                end
            end

            if ctype == 'function' then
                local ra, rb = condition(a), condition(b)
                if ra ~= rb then
                    return ra < rb
                end
            end
        end
        return a < b
    end
    table.sort(t, st)
end

return {
    csort = csort,
}