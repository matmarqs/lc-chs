local dump_table = require("utils").dump_table

local function sum_digits(d1, d2)
	local dmin = (#d1 < #d2) and d1 or d2
	local dmax = (#d1 < #d2) and d2 or d1

	local d = {}
	local carry = 0

	for i = 1, #dmin do
		d[i] = (dmin[i] + dmax[i] + carry) % 10
		carry = math.floor((dmin[i] + dmax[i] + carry) / 10)
	end

	for i = #dmin + 1, #dmax do
		d[i] = (dmax[i] + carry) % 10
		carry = math.floor((dmax[i] + carry) / 10)
	end

	if carry > 0 then
		d[#d + 1] = carry
	end

	return d
end

local function multiply_by_digit(d0, m)
	local d = {}
	local carry = 0

	for i = 1, #d0 do
		d[i] = (m * d0[i] + carry) % 10
		carry = math.floor((m * d0[i] + carry) / 10)
	end

	if carry > 0 then
		d[#d + 1] = carry
	end

	return d
end

local function shift_digits(d0, s)
	local d = {}
	for i = 1, s do
		d[i] = 0
	end
	for i = 1, #d0 do
		d[i + s] = d0[i]
	end
	return d
end

local function convert_to_digits(n)
	local d = {}
	local i = 1
	while n > 0 do
		d[i] = n % 10
		i = i + 1
		n = math.floor(n / 10)
	end
	return d
end

local function trim_zeros(d0)
	for i = #d0, 1, -1 do
		if d0[i] == 0 then
			d0[i] = nil
		else
			return d0
		end
	end
	return { 0 }
end

local function multiply(d1, d2)
	local dmin = (#d1 < #d2) and d1 or d2
	local dmax = (#d1 < #d2) and d2 or d1

	local d = {}

	for i = 1, #dmin do
		d = sum_digits(d, shift_digits(multiply_by_digit(dmax, dmin[i]), i - 1))
	end

	return trim_zeros(d)
end

local function sum_of_the_digits(d)
	local sum = 0
	for i = 1, #d do
		sum = sum + d[i]
	end
	return sum
end

local d = { 1 }
for i = 2, 100 do
	d = multiply(d, convert_to_digits(i))
end

print(sum_of_the_digits(d))

--local function test_multiply()
--	dump_table(multiply({ 8, 7, 3 }, { 2, 1 }))
--	dump_table(multiply({ 8, 5, 7, 4 }, { 3, 0, 3, 9, 3 }))
--	dump_table(multiply({ 0, 1, 0, 1, 0 }, { 2, 5, 4, 0 }))
--end
--test_multiply()
--local function test_convert_to_digits()
--	dump_table(convert_to_digits(893))
--end
--test_convert_to_digits()
--local function test_shift_digits()
--	dump_table(shift_digits({ 4, 3, 2, 1 }, 2))
--end
--test_shift_digits()
--local function test_multiply_by_digit()
--	dump_table(multiply_by_digit({ 8, 8, 8, 8, 8 }, 9))
--	dump_table(multiply_by_digit({ 4, 3, 2, 1 }, 5))
--end
--test_multiply_by_digit()
--local function test_sum_digits()
--	dump_table(sum_digits({ 6, 5, 4 }, { 7, 8, 9 }))
--	dump_table(sum_digits({ 9, 0, 0, 9 }, { 8, 7 }))
--	dump_table(sum_digits({ 8, 7 }, { 9, 0, 0, 9 }))
--	dump_table(sum_digits({ 8, 8, 8, 8, 8 }, { 5, 3, 2, 1 }))
--end
--test_sum_digits()
