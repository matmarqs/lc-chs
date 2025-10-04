local function get_lowest_prime_factor(n)
	local i = 2
	while i * i <= n do
		if n % i == 0 then
			return i
		end
		i = i + 1
	end
	-- if reached the end of the loop here, then n is prime
	return n
end

local function get_prime_decomposition(n)
	local prime_count = {}
	while n > 1 do
		local p = get_lowest_prime_factor(n)
		prime_count[p] = (prime_count[p] or 0) + 1
		n = math.floor(n / p)
	end
	return prime_count
end

local function number_of_divisors(prime_count)
	local num = 1
	for _, count in pairs(prime_count) do
		num = num * (count + 1)
	end
	return num
end

local function display_table(t)
	print("{")
	for key, val in pairs(t) do
		print(string.format("  %s: %s", key, val))
	end
	print("}")
end

local function triangle_number(n)
	return math.floor((n * (n + 1)) / 2)
end

for n = 1, 1000000 do
	local x = triangle_number(n)
	if number_of_divisors(get_prime_decomposition(x)) >= 500 then
		print(x)
		break
	end
end
