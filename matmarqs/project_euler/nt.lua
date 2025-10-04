-- number theory module

local M = {}

function M.gcd(a, b)
	if b == 0 then
		return a
	end
	return M.gcd(b, a % b)
end

function M.lcm(a, b)
	return math.floor(a / M.gcd(a, b)) * b
end

local function get_lowest_prime_factor(n)
	assert(n >= 2, "must satisfy n >= 2 to have a prime factor")
	if n < 0 then -- assure positive integer
		n = -n
	end
	if n <= 1 then -- 0 or 1
		return n -- TODO: this is mathematically incorrect, maybe change?
	end
	if n <= 3 then -- 2 or 3
		return n
	end
	if n % 2 == 0 then -- even number
		return 2
	end

	-- only test odd primes
	local i = 3
	while i * i <= n do
		if n % i == 0 then
			return i
		end
		i = i + 2
	end
	-- if reached the end of the loop here, then n is prime
	return n
end

function M.get_prime_decomposition(n)
	assert(n >= 0, "n must be non-negative")
	local prime_count = {}
	while n > 1 do
		local p = get_lowest_prime_factor(n)
		prime_count[p] = (prime_count[p] or 0) + 1
		n = math.floor(n / p)
	end
	return prime_count
end

function M.is_prime(n)
	assert(n >= 0, "n must be non-negative")
	if n <= 1 then
		return false
	end
	return n == get_lowest_prime_factor(n)
end

function M.nth_prime(n)
	assert(n >= 1, "n must be a positive integer")
	if n == 1 then
		return 2
	end
	local count = 1
	local p = 3
	while true do
		if M.is_prime(p) then
			count = count + 1
			if count == n then
				return p
			end
		end
		p = p + 2
	end
end

function M.chooses(n, k)
	local prod = 1
	for i = 1, k do
		prod = math.floor(prod * (n - i + 1) / i)
	end
	return prod
end

return M
