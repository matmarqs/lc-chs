local M = {}

function M.sum_digits(d1, d2)
	local dmin = (#d1 < #d2) and d1 or d2
	local dmax = (#d1 < #d2) and d2 or d1

	local d = {}
	local carry = 0

	for i = 1, #dmin do
		d[i] = (dmin[i] + dmax[i] + carry) % 10
		carry = math.floor((dmin[i] + dmax[i] + carry) / 10)
	end

	for i = #dmin + 1, #dmax do
		d[i] = (dmax[i] + carry) % 10
		carry = math.floor((dmax[i] + carry) / 10)
	end

	if carry > 0 then
		d[#d + 1] = carry
	end

	return d
end

local function multiply_by_digit(d0, m)
	local d = {}
	local carry = 0

	for i = 1, #d0 do
		d[i] = (m * d0[i] + carry) % 10
		carry = math.floor((m * d0[i] + carry) / 10)
	end

	if carry > 0 then
		d[#d + 1] = carry
	end

	return d
end

local function shift_digits(d0, s)
	local d = {}
	for i = 1, s do
		d[i] = 0
	end
	for i = 1, #d0 do
		d[i + s] = d0[i]
	end
	return d
end

function M.from_integer(n)
	local d = {}
	local i = 1
	while n > 0 do
		d[i] = n % 10
		i = i + 1
		n = math.floor(n / 10)
	end
	return d
end

function M.to_string(digits)
	local str = ""
	for _, d in ipairs(digits) do
		str = d .. str
	end
	return str
end

local function trim_zeros(d0)
	for i = #d0, 1, -1 do
		if d0[i] == 0 then
			d0[i] = nil
		else
			return d0
		end
	end
	return { 0 }
end

function M.multiply(d1, d2)
	local dmin = (#d1 < #d2) and d1 or d2
	local dmax = (#d1 < #d2) and d2 or d1

	local d = {}

	for i = 1, #dmin do
		d = M.sum_digits(d, shift_digits(multiply_by_digit(dmax, dmin[i]), i - 1))
	end

	return trim_zeros(d)
end

function M.power(d, n)
	local result = { 1 }
	for _ = 1, n do
		result = M.multiply(result, d)
	end
	return result
end

-- funny: this function is actually slower than M.power v1
function M.power2(d, n)
	local result = { 1 }
	while n ~= 0 do
		if n % 2 == 1 then
			result = M.multiply(result, d)
		end
		n = math.floor(n / 2)
		d = M.multiply(d, d)
	end
	return result
end

return M
