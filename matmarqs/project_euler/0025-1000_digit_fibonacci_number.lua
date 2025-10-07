local dump_table = require("utils").dump_table

local function sum_digits(d1, d2)
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

local f1 = { 1 }
local f2 = { 1 }
local f3 = sum_digits(f1, f2)

local count = 3

while #f3 < 1000 do
	f1 = f2
	f2 = f3
	f3 = sum_digits(f1, f2)
	count = count + 1
end

print(count)
