-- what is the largest palindrome number made from the product of two 3-digit number
--
-- 100 * 100 = 10000, 5-digit
-- 999 * 999 = 998001, 6-digit
--
-- abcba = 10000a + 1000b + 100c + 10b + a = 10001a + 1010b + 100c
-- abccba = 100001a + 10010b + 1100c
-- 001100

local function generate_palindrome_numbers()
	local palindromes = {}
	for a = 1, 9 do
		for b = 0, 9 do
			for c = 0, 9 do
				palindromes[#palindromes + 1] = 10001 * a + 1010 * b + 100 * c
				palindromes[#palindromes + 1] = 100001 * a + 10010 * b + 1100 * c
			end
		end
	end
	return palindromes
end

local function is_product_of_two_3_digit(n)
	for x = 100, 999 do
		if n % x == 0 then
			local y = math.floor(n / x)
			if 100 <= y and y <= 999 then
				return true
			end
		end
	end
	return false
end

local palindromes = generate_palindrome_numbers()

local max = 0
for i = 1, #palindromes do
	local pal = palindromes[i]
	if is_product_of_two_3_digit(pal) then
		max = math.max(pal, max)
	end
end

print(max)
