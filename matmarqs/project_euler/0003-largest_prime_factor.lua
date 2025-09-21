-- What is the largest prime factor of the number 600851475143?

local target = 600851475143

-- if n is prime: O(sqrt(n))
-- T(n) <= O(sqrt(n)) + T(n/p), where p is the smallest prime factor of n
-- we know that p >= 2, so T(n/p) <= T(n/2)
-- T(n) <= O(sqrt(n)) + T(n/2)
-- T(n) <= O(sqrt(n)) + O(sqrt(n/2)) + O(sqrt(n/4)) + ...
-- T(n) <= O(sqrt(n)) + (1 + sqrt(1/2) + sqrt(1/4) + ...)
-- T(n) <= O(sqrt(n)) * O(1)
-- T(n) = O(sqrt(n))
local function largest_prime_factor(n)
	local i = 2
	while i * i <= n do
		if n % i == 0 then
			return largest_prime_factor(math.floor(n / i))
		end
		i = i + 1
	end
	-- if reached the end of the loop here, then n is prime
	return n
end

print(largest_prime_factor(target))
