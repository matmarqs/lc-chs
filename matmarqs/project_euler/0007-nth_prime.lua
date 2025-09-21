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

local function nth_prime(n)
	local count = 0
	local i = 2
	while true do
		if is_prime(i) then
			count = count + 1
			if count == n then
				return i
			end
		end
		i = i + 1
	end
end

print(nth_prime(10001))
