local collatz = {}
collatz[1] = 1

local function get_collatz(n)
	if collatz[n] == nil then
		local nn = (n % 2 == 0) and math.floor(n / 2) or 3 * n + 1
		collatz[n] = get_collatz(nn) + 1
	end
	return collatz[n]
end

local function print_table(t)
	print("{")
	for i, n in pairs(t) do
		print(string.format("\t%d: %d", i, n))
	end
	print("}")
end

local num_max = 1
local max = 1

for n = 1, 1000000 do
	if get_collatz(n) > max then
		num_max = n
		max = get_collatz(n)
	end
end

print(string.format("max_collatz = collatz[%d] = %d", num_max, max))
