local function gcd(a, b)
	if b == 0 then
		return a
	end
	return gcd(b, a % b)
end

local function lcm(a, b)
	return math.floor(a / gcd(a, b)) * b
end

local mul = 1
for i = 1, 20 do
	mul = lcm(mul, i)
end

print(mul)
