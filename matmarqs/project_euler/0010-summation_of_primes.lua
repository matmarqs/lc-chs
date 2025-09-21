local function is_prime(n)
	if n <= 1 then
		return false
	end
	local i = 2
	while i * i <= n do
		if n % i == 0 then
			return false
		end
		i = i + 1
	end
	return true
end

local function summation_of_primes_below(n)
	local sum = 0
	for i = 1, n - 1 do
		if is_prime(i) then
			sum = sum + i
		end
	end
	return sum
end

print(summation_of_primes_below(2000000))
