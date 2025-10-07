local digits = require("digits")

local function length(t)
	local count = 0
	for _, _ in pairs(t) do
		count = count + 1
	end
	return count
end

local terms = {}

for a = 2, 100 do
	for b = 2, 100 do
		terms[digits.to_string(digits.power(digits.from_integer(a), b))] = true
	end
end

print(length(terms))
