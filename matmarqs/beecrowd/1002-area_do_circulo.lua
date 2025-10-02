local function circle_area(x)
	return 3.14159 * x * x
end

local function round_4(x)
	return string.format("%.4f", x)
end

local n = io.read("*number")

print("A=" .. round_4(circle_area(n)))
