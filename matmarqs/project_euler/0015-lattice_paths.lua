-- the answer is 2n chooses n

local function chooses(n, k)
	local prod = 1
	for i = 1, k do
		prod = math.floor(prod * (n - i + 1) / i)
	end
	return prod
end

print(chooses(2 * 20, 20))
