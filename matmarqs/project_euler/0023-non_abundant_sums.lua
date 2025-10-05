local nt = require("nt")
local dump_table = require("utils").dump_table

local limit = 28123

local map = {}

for n = 1, limit do
	map[n] = nt.sum_of_proper_divisors(n)
end

local abundants = {}

for n = 1, limit do
	if map[n] > n then
		abundants[#abundants + 1] = n
	end
end

local sum_of_two_abundants = {}

for _, a in ipairs(abundants) do
	for _, b in ipairs(abundants) do
		if a + b <= limit then
			sum_of_two_abundants[a + b] = true
		end
	end
end

local not_sum_of_two_abundants = {}

local sum = 0
for n = 1, limit do
	if not sum_of_two_abundants[n] then
		not_sum_of_two_abundants[n] = true
		sum = sum + n
	end
end

--dump_table(not_sum_of_two_abundants)
print(sum)
