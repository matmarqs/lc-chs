local display_table = require("utils").display_table

local words = {
	[1] = "one",
	[2] = "two",
	[3] = "three",
	[4] = "four",
	[5] = "five",
	[6] = "six",
	[7] = "seven",
	[8] = "eight",
	[9] = "nine",
	[10] = "ten",
	[11] = "eleven",
	[12] = "twelve",
	[13] = "thirteen",
	[14] = "fourteen",
	[15] = "fifteen",
	[16] = "sixteen",
	[17] = "seventeen",
	[18] = "eighteen",
	[19] = "nineteen",
	[20] = "twenty",
	[30] = "thirty",
	[40] = "forty",
	[50] = "fifty",
	[60] = "sixty",
	[70] = "seventy",
	[80] = "eighty",
	[90] = "ninety",
	[100] = "onehundred",
	[200] = "twohundred",
	[300] = "threehundred",
	[400] = "fourhundred",
	[500] = "fivehundred",
	[600] = "sixhundred",
	[700] = "sevenhundred",
	[800] = "eighthundred",
	[900] = "ninehundred",
	[1000] = "onethousand",
}

local function map_word(n)
	assert(1 <= n and n <= 1000, "We only mapped between 1 and 1000")

	-- manually mapped
	if words[n] ~= nil then
		return words[n]
	end

	-- not mapped less than 100
	if 21 <= n and n <= 99 then
		words[n] = words[math.floor(n / 10) * 10] .. words[n % 10]
		return words[n]
	end

	-- 100 <= n <= 999, not mapped yet
	words[n] = words[math.floor(n / 100) * 100] .. "and" .. words[n % 100]
	return words[n]
end

local sum = 0

for n = 1, 1000 do
	sum = sum + #map_word(n)
end

print(sum)

--display_table(words)
