local function print_table(t)
	print("{")
	for i, n in pairs(t) do
		print(string.format("\t%d: %d", i, n))
	end
	print("}")
end

local function compute_new_digits(digits)
	local new_digits = {}
	local carry = 0
	for i = 1, #digits do
		local d = digits[i]
		local dd = (2 * d + carry) % 10
		carry = (2 * d + carry >= 10) and 1 or 0
		new_digits[i] = dd
	end
	if carry == 1 then
		new_digits[#digits + 1] = 1
	end
	return new_digits
end

local digits = { 1 }

for _ = 1, 1000 do
	digits = compute_new_digits(digits)
end

local sum = 0
for _, d in ipairs(digits) do
	sum = sum + d
end

print(sum)
