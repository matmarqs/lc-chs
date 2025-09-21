local function is_pythagorean_triple(a, b, c)
	if a < b and b < c and a ^ 2 + b ^ 2 == c ^ 2 then
		return true
	end
	return false
end

for a = 1, 998 do
	for b = 1, 998 do
		local c = 1000 - a - b
		if c > 0 and is_pythagorean_triple(a, b, c) then
			print(a * b * c)
		end
	end
end
