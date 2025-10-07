local nt = require("nt")

local function number_of_consecutive_primes(a, b)
	local count = 0
	local n = 0
	while true do
		if not nt.is_prime(n * n + a * n + b) then
			return count
		end
		n = n + 1
		count = count + 1
	end
end

local max = 0
local max_a = 0
local max_b = 0

for a = -999, 999 do
	for b = -1000, 1000 do
		local num_consecutive = number_of_consecutive_primes(a, b)
		if num_consecutive > max then
			max_a = a
			max_b = b
			max = num_consecutive
		end
	end
end

print(max_a * max_b)
