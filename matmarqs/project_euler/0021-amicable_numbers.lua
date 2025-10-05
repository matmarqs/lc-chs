local dump_table = require("utils").dump_table
local nt = require("nt")

local function sum_of_proper_divisors(n)
	local decomp = nt.get_prime_decomposition(n)
	local prod = 1
	for p, e in pairs(decomp) do
		prod = prod * ((p ^ (e + 1) - 1) / (p - 1))
	end
	return prod - n
end

local map = {}
local limit = 10000

for n = 1, limit do
	map[n] = sum_of_proper_divisors(n)
end

--dump_table(map)

--local amicables = {}

local sum = 0
for n = 1, limit do
	if n == map[map[n]] and n ~= map[n] then -- a ~= b, amicable pair
		--amicables[n] = map[n]
		sum = sum + n
	end
end

--dump_table(amicables)
print(sum)
