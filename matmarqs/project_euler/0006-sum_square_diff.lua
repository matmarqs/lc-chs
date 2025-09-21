local function sumsquared(n)
	return math.floor((n * (n + 1)) / 2) ^ 2
end

local function squaresum(n)
	return math.floor((n * (n + 1) * (2 * n + 1)) / 6)
end

local function diff_sumsquared_squaresum(n)
	return sumsquared(n) - squaresum(n)
end

local n = 100
print(diff_sumsquared_squaresum(n))
