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

local function get_lowest_prime_factor(n, start)
	n = (n >= 0) and n or -n -- assure positive integer
	assert(n >= 2, "n must satisfy n >= 2 to have a prime factor")

	start = (start and start >= 3) and start or 3 -- odd prime to start
	assert(start % 2 == 1, "start must be an odd candidate prime")

	-- take care of even numbers
	if n % 2 == 0 then
		return 2
	end

	-- only test odd primes
	local i = start
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
	local p = 2
	while n > 1 do
		p = get_lowest_prime_factor(n, p)
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

function M.sum_of_proper_divisors(n)
	local decomp = M.get_prime_decomposition(n)
	local prod = 1
	for p, e in pairs(decomp) do
		prod = prod * ((p ^ (e + 1) - 1) / (p - 1))
	end
	return prod - n
end

return M
